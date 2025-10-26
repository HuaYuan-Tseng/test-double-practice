#include <gtest/gtest.h>

#include "lib/i_command.h"
#include "lib/result.h"
#include "lib/server.h"

/*
 * 題目：
 * 使用 `Dummy` 實作 `ICommand`，測試 `Server.getCommandSize` 函式
 */

class DummyCommand final : public lib::ICommand {
public:
    lib::Result execute() override { return { lib::ResultEnum::kOK, "Dummy" }; }
};

TEST(Dummy, testCommandSize)
{
    lib::Server server(nullptr);
    EXPECT_EQ(0, server.getCommandsSize());

    // write your test code here
    // use Dummy object to test server.getCommandSize()
    server.addCommand(std::make_unique<DummyCommand>());
    server.addCommand(std::make_unique<DummyCommand>());

    EXPECT_EQ(2, server.getCommandsSize());
}
