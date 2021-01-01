#include "Executor.hpp"
#include <numeric>
#include <utility>

namespace ssg {

Executor::Executor(const int32_t numberOfThreads,
                     std::unique_ptr<IResult> res)
    : noThreads(numberOfThreads), availableWorkers(numberOfThreads),
      threadPool(numberOfThreads), result(std::move(res)) {
  std::iota(availableWorkers.begin(), availableWorkers.end(), threadStartIndex);
}

void Executor::update(std::shared_ptr<Message> m) {
  {
    std::lock_guard<std::mutex> lck(mtx);
    availableWorkers.push_front(m->getId());
  }
  result->merge(m->getData());
}

ID Executor::waitForWorker() {
  std::unique_lock<std::mutex> lck(mtx);
  while (availableWorkers.empty()) {
    cv.wait(lck);
  }
  const ID id = availableWorkers.front();
  availableWorkers.pop_front();
  return id;
}

void Executor::execute(std::vector<ITask> &&v) {
  while (v.empty() == false) {
    const ID id = waitForWorker();
    ITask copied(v.back());
    threadPool.at(id).reset(
        new DThread(id, [copied]() mutable { return copied.run(); }));
    v.pop_back();
  }
}

std::unique_ptr<IResult> Executor::getResult() { return std::move(result); }

} // namespace ssg