#include "lib/door_command.h"

namespace lib {

Result DoorCommand::execute()
{
    if (door_->getStatus() == "open")
    {
        return { ResultEnum::kCritical, "Door is open" };
    }
    return { ResultEnum::kOK, "OK" };
}

};  // namespace lib
