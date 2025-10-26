#ifndef LIB_SERVER_H_
#define LIB_SERVER_H_

#include <vector>
#include <memory>
#include <utility>

#include "lib/i_alert.h"
#include "lib/i_command.h"

namespace lib {

class Server {
public:
    explicit Server(std::unique_ptr<IAlert>&& alert)
        : alert_{ std::move(alert) }
    {
    }

    void monitor();

private:
    std::vector<ICommand> commands_;
    std::unique_ptr<IAlert> alert_;
};

}  // namespace lib

#endif  // !LIB_SERVER_H_
