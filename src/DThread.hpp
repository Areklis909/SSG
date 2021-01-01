#ifndef DTHREAD_HPP
#define DTHREAD_HPP

#include "IThread.hpp"
#include "TypeDefinition.hpp"
#include <utility>

namespace ssg {

class DThread : public IThread {

public:
  template <typename Action>
  DThread(const ID id, Action a) : IThread(id, std::forward<Action>(a)) {
    t.detach();
  }
  virtual ~DThread() = default;
};

} // namespace ssg

#endif