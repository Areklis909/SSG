#include "IObserver.hpp"

namespace ssg {

ID IObserver::globalId = 0;

IObserver::IObserver() { id = globalId++; }

bool IObserver::operator==(const IObserver &other) {
  return getId() == other.getId();
}

} // namespace ssg