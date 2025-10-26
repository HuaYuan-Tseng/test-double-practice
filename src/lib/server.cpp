#include "lib/server.h"

#include <algorithm>
#include <memory>
#include <utility>

#include "lib/result.h"

namespace lib {

void Server::monitor()
{
    std::ranges::for_each(commands_,
                          [this](const std::unique_ptr<ICommand>& command)
                          {
                              Result res = command->execute();
                              if (res.status() != static_cast<int>(ResultEnum::kOK))
                              {
                                  alert_->sendAlert(res.message());
                              }
                          });
}

void Server::addCommand(std::unique_ptr<ICommand>&& command)
{
    commands_.emplace_back(std::move(command));
}

}  // namespace lib
