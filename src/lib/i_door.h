#ifndef LIB_I_DOOR_H_
#define LIB_I_DOOR_H_

#include <string>

namespace lib {

class IDoor {
public:
    virtual ~IDoor() = default;

    [[nodiscard]] virtual std::string getStatus() const = 0;
};

}  // namespace lib

#endif  // !LIB_I_DOOR_H_
