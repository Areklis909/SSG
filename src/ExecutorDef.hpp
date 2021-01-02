#include <cstdint>
#include <memory>
#include <numeric>
#include <utility>

namespace ssg {

template <typename ResultType>
Executor<ResultType>::Executor(int32_t numberOfThreads, ResultType &&emptyRes)
    : noThreads(numberOfThreads), availableWorkers(numberOfThreads),
      threadPool(numberOfThreads), result(std::forward<ResultType>(emptyRes)) {
  std::iota(availableWorkers.begin(), availableWorkers.end(), threadStartIndex);
}

template <typename ResultType>
void Executor<ResultType>::update(std::shared_ptr<Message> m) {
  {
    std::lock_guard<std::mutex> lck(mtx);
    availableWorkers.push_front(m->getId());
  }
  cv.notify_all();
  result.merge(m->getData<ResultType>());
}

template <typename ResultType> ID Executor<ResultType>::waitForWorker() {
  std::unique_lock<std::mutex> lck(mtx);
  while (availableWorkers.empty()) {
    cv.wait(lck);
  }
  const ID id = availableWorkers.front();
  availableWorkers.pop_front();
  return id;
}

template <typename ResultType>
void Executor<ResultType>::execute(std::vector<ITask<ResultType>> &&v) {
  while (v.empty() == false) {
    const ID id = waitForWorker();
    ITask<ResultType> copied(v.back());
    std::unique_ptr<DThread> t =
        std::make_unique<DThread>(id, [copied]() mutable {
          return copied.run();
        });
    t->attach(this);
    threadPool.at(id) = std::move(t);
    v.pop_back();
  }

  std::unique_lock<std::mutex> lck(mtx);
  while(availableWorkers.size() != noThreads) {
    cv.wait(lck);
  }
}

template <typename ResultType> ResultType &Executor<ResultType>::getResult() {
  return result;
}

} // namespace ssg