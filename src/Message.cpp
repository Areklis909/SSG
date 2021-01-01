#include "Message.hpp"
#include <utility>

namespace ssg {

Message::Message(ID iden, std::unique_ptr<IResult> d)
    : id(iden), data(std::move(d)) {}


ID Message::getId() const { return id; }

std::unique_ptr<IResult> Message::getData() { return std::move(data); }

} // namespace ssg