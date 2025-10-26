#ifndef LIB_I_ALERT_H_
#define LIB_I_ALERT_H_

#include <string_view>

namespace lib {

class IAlert {
public:
    virtual ~IAlert() = default;

    virtual void sendAlert(std::string_view message) = 0;
};

}  // namespace lib

#endif  // !LIB_I_ALERT_H_
