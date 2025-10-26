#ifndef LIB_RESULT_H_
#define LIB_RESULT_H_

#include <cstdint>
#include <string>
#include <utility>

namespace lib {

enum class ResultEnum : int8_t {
    kOK = 1,
    kCritical
};

class Result {
public:
    Result()
        : status_{ ResultEnum::kOK }
        , message_{ "OK" }
    {
    }

    Result(ResultEnum status, std::string message)
        : status_{ status }
        , message_{ std::move(message) }
    {
    }

    [[nodiscard]] int status() const { return static_cast<int>(status_); }
    [[nodiscard]] std::string message() const { return message_; }

private:
    ResultEnum status_;
    std::string message_;
};

}  // namespace lib

#endif  // !LIB_RESULT_H_
