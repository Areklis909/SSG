#ifndef JTHREAD_HPP
#define JTHREAD_HPP

#include "IThread.hpp"

namespace ssg {

class JThread : public IThread {

public:
  template <typename Action>
  JThread(Action a) : IThread(std::forward<Action>(a)){};
  virtual ~JThread() { t.join(); };
};

} // namespace ssg

#endif