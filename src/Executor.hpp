#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include "IObserver.hpp"
#include "ITask.hpp"
#include "Message.hpp"
#include "DThread.hpp"
#include "TypeDefinition.hpp"
#include "IResult.hpp"
#include <list>
#include <vector>
#include <mutex>
#include <condition_variable>

namespace ssg {

class Executor : public IObserver {

public:
  Executor(const int32_t noThreads, std::unique_ptr<IResult> res);
  virtual ~Executor() = default;
  Executor(const Executor &lex) = delete;
  Executor(Executor &&rex) = delete;
  void operator=(const Executor &lex) = delete;
  void operator=(Executor &&rex) = delete;
  virtual void update(std::shared_ptr<Message> m) override;
  virtual void execute(std::vector<ITask> && v);
  std::unique_ptr<IResult> getResult();

protected:
  int32_t noThreads;
  std::list<uint32_t> availableWorkers;
  std::vector<std::unique_ptr<DThread>> threadPool;
  std::unique_ptr<IResult> result;
  std::mutex mtx;
  std::condition_variable cv;

  ID waitForWorker();
private:
  const int threadStartIndex = 0;
};

} // namespace ssg

#endif