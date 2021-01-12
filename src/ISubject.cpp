
#include "ISubject.hpp"
#include <algorithm>

namespace ssg {

ISubject::ISubject(const ID iden) : id(iden) {}

void ISubject::attach(IObserver *obs) { observers.push_back(obs); }

void ISubject::remove(IObserver *obs) {
  observers.erase(
      std::remove_if(observers.begin(), observers.end(),
                     [obs](IObserver *other) { return *obs == *other; }),
      observers.end());
}

void ISubject::notifyAll() {
  for (auto obs : observers) {
    obs->update(result);
  }
}

void ISubject::removeAll() {
  observers.clear();
}

} // namespace ssg