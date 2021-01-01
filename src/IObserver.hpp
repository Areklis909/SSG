#ifndef IOBSERVER_HPP
#define IOBSERVER_HPP

#include <cstdint>
#include <memory>
#include "TypeDefinition.hpp"
#include "Message.hpp"

namespace ssg {

class IObserver {

public:
  static ID globalId;

  IObserver();
  virtual ~IObserver() = default;
  IObserver(const IObserver &lobs) = delete;
  IObserver(IObserver &&robs) = delete;
  void operator=(const IObserver &lobs) = delete;
  void operator=(IObserver &&robs) = delete;
  bool operator==(const IObserver &other);
  uint32_t getId() const { return id; };
  virtual void update(std::shared_ptr<Message> m) = 0;

protected:
  ID id;
};

} // namespace ssg

#endif