#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <cstdint>
#include "TypeDefinition.hpp"
#include "IResult.hpp"

namespace ssg {

class Message {
protected:
  ID id;
  std::unique_ptr<IResult> data;

public:
  Message(const ID iden,std::unique_ptr<IResult> d);
  virtual ~Message() = default;

  ID getId() const;

  std::unique_ptr<IResult> getData();

};

} // namespace ssg

#endif