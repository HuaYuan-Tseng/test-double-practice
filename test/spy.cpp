#include <gtest/gtest.h>

#include <memory>
#include <print>
#include <string>
#include <string_view>

#include "lib/door_command.h"
#include "lib/i_alert.h"
#include "lib/i_door.h"
#include "lib/server.h"

/*
 * 題目：
 * 使用 `Spy` 實作 `IAlert`，測試 `Server.monitor()` 會呼叫 `IAlert.sendAlert()`
 */

class StubDoor final : public lib::IDoor {
public:
    [[nodiscard]] std::string getStatus() const override { return "open"; }
};

class SpyAlert final : public lib::IAlert {
public:
    void sendAlert(std::string_view message) override
    {
        std::println("{}", message);
        was_alerted_ = true;
    }

    [[nodiscard]] bool wasAlerted() const { return was_alerted_; }

private:
    bool was_alerted_{ false };
};

TEST(Spy, monitorSendAlert)
{
    auto spy = std::make_unique<SpyAlert>();
    auto* spy_ptr = spy.get();
    lib::Server server{ std::move(spy) };
    server.addCommand(std::make_unique<lib::DoorCommand>(std::make_unique<StubDoor>()));
    server.monitor();
    EXPECT_TRUE(spy_ptr->wasAlerted());
}
