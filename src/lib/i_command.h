#ifndef LIB_I_COMMAND_H_
#define LIB_I_COMMAND_H_

#include "lib/result.h"

namespace lib {

class ICommand {
public:
    virtual ~ICommand() = default;

    [[nodiscard]] virtual Result execute() = 0;
};

}  // namespace lib

#endif  // !LIB_I_COMMAND_H_
