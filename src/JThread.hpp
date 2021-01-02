#ifndef JTHREAD_HPP
#define JTHREAD_HPP

#include "IThread.hpp"
#include "TypeDefinition.hpp"

namespace ssg {

class JThread : public IThread {

public:
  template <typename Action>
  JThread(const ID id, Action && a) : IThread(id, std::forward<Action>(a)){};
  virtual ~JThread() { t.join(); };
};

} // namespace ssg

#endif