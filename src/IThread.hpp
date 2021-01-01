#ifndef ITHREAD_HPP
#define ITHREAD_HPP

#include "ISubject.hpp"
#include <memory>
#include <thread>

namespace ssg {

class IThread : public ISubject {
public:
  template <typename Action>
  IThread(const ID id, Action action)
      : ISubject(id), t([this, &action, id] {
          result = std::make_shared<Message>(id, action());
          notifyAll();
        }) {}
  virtual ~IThread() = default;

protected:
  std::thread t;
};

} // namespace ssg

#endif