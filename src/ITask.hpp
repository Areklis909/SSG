#ifndef ITASK_HPP
#define ITASK_HPP

#include <memory>
#include <utility>
#include <any>
#include "IResult.hpp"

namespace ssg {

class ITask {
public:
  class TaskConcept {
  public:
    virtual std::unique_ptr<IResult> run() = 0;
    virtual ~TaskConcept() = default;
  };

  template <typename T> class TaskModel : public TaskConcept {
    T object;

  public:
    TaskModel(T &&t) : object(std::forward<T>(t)){};
    virtual ~TaskModel() = default;
    virtual std::unique_ptr<IResult> run() override { return object.run(); }
  };

  template <typename U>
  ITask(U u) : conc(new TaskModel<U>(std::forward<U>(u))) {}

  ITask(const ITask &other) { conc = other.conc; }

  ITask(ITask &&other) {
    conc = std::move(other.conc);
    other.conc = nullptr;
  }

  std::unique_ptr<IResult> run() {
      return conc->run();
  }

private:
  std::shared_ptr<TaskConcept> conc;
};

} // namespace ssg

#endif