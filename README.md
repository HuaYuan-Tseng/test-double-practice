# Test Double 練習專案

本專案主要用於練習和學習 Test Double 概念，參考資料來源：[Teddy 的測試替身文章系列](https://teddy-chen-tw.blogspot.com/search?q=test+double)

- 練習使用不同的 Test Double 替代真實相依物件
- 練習 Google Test 的 `gMock` 基本使用方法
- 順便看了一下 [Google Test](https://github.com/google/googletest) 的一些 Samples，學習一些 C++ 撰寫測試的小技巧（應該算吧？ 🤣）

## 先決條件

- C++ 的編譯器（如 Clang, GCC, MSVC）
- [CMake](https://cmake.org/download/)（版本 3.19 或更新）

## 開始使用

### 配置與建置

本專案使用 [HuaYuan-Tseng/cpp-template](https://github.com/HuaYuan-Tseng/cpp-template) 簡化建置流程。

1. **列出可用的預設配置：**

    ```bash
    cmake --list-presets
    ```

2. **配置專案：**

    ```bash
    cmake --preset <preset name>
    ```

3. **建置專案：**

    ```bash
    cmake --build --preset <preset name>
    ```

    執行檔將會產生在 `bin/<preset name>/` 目錄下。

### 執行應用程式

```bash
./bin/<preset name>/cpp-template-app
```

## 執行測試

使用 CTest 執行測試：

```bash
ctest --preset <preset name>
```

或直接執行測試執行檔：

```bash
./bin/<preset name>/cpp-template-test
```

## 目錄結構

```text
.
├── CMakeLists.txt          # 主要 CMake 建置腳本
├── CMakePresets.json       # CMake 預設配置
├── README.md               # 本說明檔
├── bin/                    # 執行檔輸出目錄
├── build/                  # 建置中間檔案目錄
├── cmake/                  # CMake 輔助腳本
├── src/                    # 原始碼
│   ├── app/
│   │   └── main.cpp        # 主程式入口
│   └── lib/                # 函式庫實作
│       ├── i_command.h     # Command 介面
│       ├── door_command.h/cpp  # Door 命令實作
│       ├── i_door.h        # Door 介面
│       ├── i_alert.h       # Alert 介面
│       ├── result.h        # 結果定義
│       └── server.h/cpp    # Server 實作
├── test/                   # 測試原始碼
│   └── hello_test.cxx      # 範例測試
└── thirdparty/             # 第三方函式庫
```

## 授權條款

本專案採用 MIT License 授權。
