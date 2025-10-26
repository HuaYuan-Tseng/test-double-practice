#include "lib/server.h"

#include <algorithm>

#include "lib/result.h"

namespace lib {

void Server::monitor()
{
    std::ranges::for_each(commands_,
                          [this](ICommand& command)
                          {
                              Result res = command.execute();
                              if (res.status() == static_cast<int>(ResultEnum::kOK))
                              {
                                  alert_->sendAlert(res.message());
                              }
                          });
}

}  // namespace lib
