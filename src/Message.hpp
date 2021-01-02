#ifndef MESSAGE_HPP
#define MESSAGE_HPP

// #include "IResult.hpp"
#include <any>
#include <cstdint>
#include "TypeDefinition.hpp"

namespace ssg {

class Message {
protected:
  ID id;
  std::any data;

public:
  Message(const ID iden, std::any d);
  virtual ~Message() = default;

  ID getId() const;

  template<typename R>
  R getData() {
    return std::any_cast<R>(data);
  }
};

} // namespace ssg

#endif