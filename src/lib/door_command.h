#ifndef LIB_DOOR_COMMAND_H_
#define LIB_DOOR_COMMAND_H_

#include <memory>
#include <utility>

#include "lib/i_command.h"
#include "lib/i_door.h"
#include "lib/result.h"

namespace lib {

class DoorCommand final : public ICommand {
public:
    explicit DoorCommand(std::unique_ptr<IDoor>&& door)
        : door_{ std::move(door) }
    {
    }

    [[nodiscard]] Result execute() override;

private:
    std::unique_ptr<IDoor> door_;
};

}  // namespace lib

#endif  // !LIB_DOOR_COMMAND_H_
