#include "configurator/ConfiguratorBuilder.h"

#include "configurator/web/WebServer.h"

namespace configurator {

ConfiguratorBuilder& ConfiguratorBuilder::withExecutor(Executor& executor) {
  ConfiguratorBuilder::executor = &executor;
  return *this;
}

ConfiguratorBuilder& ConfiguratorBuilder::withConfigurator(Configurator& configurator) {
  ConfiguratorBuilder::configurator = &configurator;
  return *this;
}

void ConfiguratorBuilder::start() {
  executor->executeInCycle(*new configurator::web::WebServer(*configurator));
}

}  // namespace configurator
