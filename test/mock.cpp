#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string_view>

#include "lib/i_alert.h"
#include "lib/i_command.h"
#include "lib/result.h"
#include "lib/server.h"

/*
 * 題目：
 * 使用 `Mock` 產生假的 `ICommand` 與 `IAlert`，測試 `Server.monitor()` 與 `IAlert.sendAlert()` 的互動
 */

class MockCommand : public lib::ICommand {
public:
    MOCK_METHOD(lib::Result, execute, (), (override));
};

class MockAlert : public lib::IAlert {
public:
    MOCK_METHOD(void, sendAlert, (std::string_view), (override));
};

TEST(Mock, sendAlertToMockWhenDoorOpen)
{
    // Arrange: 建立 mock 物件
    auto mock_alert = std::make_unique<MockAlert>();
    MockAlert* alert_ptr = mock_alert.get();  // 保留指標以便設定期望

    auto mock_command = std::make_unique<MockCommand>();
    MockCommand* command_ptr = mock_command.get();

    lib::Server server{ std::move(mock_alert) };
    server.addCommand(std::move(mock_command));

    // 設定期望：command 回傳 Critical 狀態（門開啟）
    EXPECT_CALL(*command_ptr, execute())
        .WillOnce(::testing::Return(lib::Result{ lib::ResultEnum::kCritical, "Door is open" }));

    // 設定期望：alert 應該被呼叫並帶有 "Door is open" 訊息
    EXPECT_CALL(*alert_ptr, sendAlert("Door is open")).Times(1);

    // Act: 執行監控
    server.monitor();

    // Assert: 由 EXPECT_CALL 自動驗證
}

TEST(Mock, sendAlertToMockWhenDoorClosed)
{
    // Arrange: 建立 mock 物件
    auto mock_alert = std::make_unique<MockAlert>();
    MockAlert* alert_ptr = mock_alert.get();

    auto mock_command = std::make_unique<MockCommand>();
    MockCommand* command_ptr = mock_command.get();

    lib::Server server{ std::move(mock_alert) };
    server.addCommand(std::move(mock_command));

    // 設定期望：command 回傳 OK 狀態（門關閉）
    EXPECT_CALL(*command_ptr, execute()).WillOnce(::testing::Return(lib::Result{ lib::ResultEnum::kOK, "OK" }));

    // 設定期望：alert 不應該被呼叫
    EXPECT_CALL(*alert_ptr, sendAlert(::testing::_)).Times(0);

    // Act: 執行監控
    server.monitor();

    // Assert: 由 EXPECT_CALL 自動驗證
}
