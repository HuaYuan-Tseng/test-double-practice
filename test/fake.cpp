#include <gtest/gtest.h>

#include <fstream>
#include <string>
#include <string_view>

#include "lib/door_command.h"
#include "lib/i_alert.h"
#include "lib/i_door.h"
#include "lib/server.h"

/*
 * 題目：
 * 使用 `Fake` 實作 `IAlert`，把訊息送到檔案中
 */

class StubOpenDoor final : public lib::IDoor {
public:
    [[nodiscard]] std::string getStatus() const override { return "open"; }
};

class StubClosedDoor final : public lib::IDoor {
public:
    [[nodiscard]] std::string getStatus() const override { return "closed"; }
};

class FakeAlert final : public lib::IAlert {
public:
    explicit FakeAlert(std::string file_path = "fake.txt")
        : file_path_{ std::move(file_path) }
    {
    }

    void sendAlert(std::string_view message) override
    {
        std::ofstream file(file_path_);
        file << message;
    }

    [[nodiscard]] std::string getFilePath() const { return file_path_; }

private:
    std::string file_path_;
};

TEST(Fake, sendAlertToFakeFileWhenDoorOpen)
{
    auto fake = std::make_unique<FakeAlert>("fake_door_open.txt");
    auto* fake_ptr = fake.get();
    lib::Server server{ std::move(fake) };
    server.addCommand(std::make_unique<lib::DoorCommand>(std::make_unique<StubOpenDoor>()));
    server.monitor();

    // assert that the fake_door_open.txt contains a message
    std::ifstream file(fake_ptr->getFilePath());
    std::string content;
    std::getline(file, content);
    EXPECT_EQ("Door is open", content);
}

TEST(Fake, sendAlertToFakeFileWhenDoorClosed)
{
    auto fake = std::make_unique<FakeAlert>("fake_door_closed.txt");
    auto* fake_ptr = fake.get();
    lib::Server server{ std::move(fake) };
    server.addCommand(std::make_unique<lib::DoorCommand>(std::make_unique<StubClosedDoor>()));
    server.monitor();

    // assert that the fake_door_closed.txt is empty
    std::ifstream file(fake_ptr->getFilePath());
    std::string content;
    std::getline(file, content);
    EXPECT_TRUE(content.empty());
}
