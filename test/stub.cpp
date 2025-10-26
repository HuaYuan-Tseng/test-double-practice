#include <gtest/gtest.h>

#include <string>

#include "lib/door_command.h"
#include "lib/i_door.h"
#include "lib/result.h"

/*
 * 題目：
 * 使用 `Stub` 實作 `IDoor`，用以測試 `DoorCommand.execute()`
 */

class StubOpenDoor final : public lib::IDoor {
public:
    [[nodiscard]] std::string getStatus() const override { return "open"; }
};

class StubClosedDoor final : public lib::IDoor {
public:
    [[nodiscard]] std::string getStatus() const override { return "closed"; }
};

TEST(Stub, executeDoorCommandWhenDoorOpen)
{
    // write StubOpenDoor to pass this test case
    lib::DoorCommand door_cmd{ std::make_unique<StubOpenDoor>() };
    lib::Result result{ door_cmd.execute() };
    EXPECT_EQ(static_cast<int>(lib::ResultEnum::kCritical), result.status());
    EXPECT_TRUE(result.message().starts_with("Door is open"));
}

TEST(Stub, executeDoorCommandWhenDoorClosed)
{
    // write StubClosedDoor to pass this test case
    lib::DoorCommand door_cmd{ std::make_unique<StubClosedDoor>() };
    lib::Result result{ door_cmd.execute() };
    EXPECT_EQ(static_cast<int>(lib::ResultEnum::kOK), result.status());
    EXPECT_EQ("OK", result.message());
}
