#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include "DThread.hpp"
#include "JThread.hpp"
#include "IObserver.hpp"
#include "IResult.hpp"
#include "ITask.hpp"
#include "Message.hpp"
#include "TypeDefinition.hpp"
#include <condition_variable>
#include <list>
#include <mutex>
#include <vector>

namespace ssg {

template <typename ResultType> class Executor : public IObserver {

public:
  Executor(int32_t noThreads, ResultType && res);
  virtual ~Executor() = default;
  Executor(const Executor &lex) = delete;
  Executor(Executor &&rex) = delete;
  void operator=(const Executor &lex) = delete;
  void operator=(Executor &&rex) = delete;
  virtual void update(std::shared_ptr<Message> m) override;
  void execute(std::vector<ITask<ResultType>> &&v);
  ResultType & getResult();

protected:
  int32_t noThreads;
  std::list<uint32_t> availableWorkers;
  std::vector<std::unique_ptr<IThread>> threadPool;
  ResultType result;
  std::mutex mtx;
  std::condition_variable cv;

  ID waitForWorker();

private:
  const int threadStartIndex = 0;
};

} // namespace ssg

#include "ExecutorDef.hpp"

#endif