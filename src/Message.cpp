#include "Message.hpp"
#include <utility>

namespace ssg {

Message::Message(ID iden, std::any d)
    : id(iden), data(d) {}


ID Message::getId() const { return id; }

} // namespace ssg