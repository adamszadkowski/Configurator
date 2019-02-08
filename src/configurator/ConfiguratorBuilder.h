#pragma once

#include <Executor.h>
#include "configurator/Configurator.h"

namespace configurator {

class ConfiguratorBuilder {
 public:
  ConfiguratorBuilder& withExecutor(Executor& executor);
  ConfiguratorBuilder& withConfigurator(Configurator& configurator);
  void start();

 private:
  Executor* executor;
  Configurator* configurator;
};

}  // namespace configurator
