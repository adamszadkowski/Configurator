#pragma once

#include <functional>
#include "Arduino.h"

namespace configurator {

class Configurator {
 public:
  virtual ~Configurator() {
  }

  virtual void set(const String& name, const String& value) = 0;
  virtual String get(const String& name) = 0;
  virtual void iterate(std::function<void(const String&, const String&)> callback) = 0;
  virtual void commit() = 0;
};

}  // namespace configurator
