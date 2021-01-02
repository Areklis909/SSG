#ifndef ITASK_HPP
#define ITASK_HPP

#include <any>
#include <memory>
#include <utility>
// #include <iostream>

namespace ssg {

template <typename ResultType> class ITask {
public:
  class TaskConcept {
  public:
    virtual ResultType run() = 0;
    virtual ~TaskConcept() = default;
  };

  template <typename T> class TaskModel : public TaskConcept {
    T object;

  public:
    TaskModel(T &&t) : object(std::forward<T>(t)) {};
    virtual ~TaskModel() = default;
    virtual ResultType run() override { return object.run(); }
  };

  template <typename U>
  ITask(U u) : conc(new TaskModel<U>(std::forward<U>(u))) {}

  // ITask(const ITask &other) {
  //   std::cout << "const ITask & \n";
  //   conc = other.conc;
  // }

  // ITask(ITask &&other) {
  //   std::cout << "ITask && \n";
  //   conc = std::move(other.conc);
  //   other.conc = nullptr;
  // }

  ResultType run() {
    return conc->run();
  }

private:
  std::shared_ptr<TaskConcept> conc;
};

} // namespace ssg

#endif