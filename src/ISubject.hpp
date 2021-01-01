#ifndef ISUBJECT_HPP
#define ISUBJECT_HPP

#include "IObserver.hpp"
#include "TypeDefinition.hpp"
#include "Message.hpp"
#include <vector>
#include <memory>

namespace ssg {

class ISubject {

protected:
  ID id;
  std::vector<IObserver *> observers;
  std::shared_ptr<Message> result;
public:
  ISubject(const ID iden);
  virtual ~ISubject() = default;
  ISubject(const ISubject &lsub) = delete;
  ISubject(ISubject &&rsub) = delete;
  void operator=(const ISubject &lsub) = delete;
  void operator=(ISubject &&rsub) = delete;

  void attach(IObserver *obs);
  void remove(IObserver *obs);
  void notifyAll() const;
};

} // namespace ssg

#endif