#include <ssg/Executor.hpp>
#include <ssg/ITask.hpp>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <mutex>

using namespace ssg;

class TestResult {
  int32_t result;

public:
  TestResult(const int32_t r) : result(r){};
  int32_t getResult() const { return result; }
  void merge(TestResult &&other) { result += other.getResult(); }
};

class TestTask {
public:
  TestTask(const int32_t b, const int32_t t) : bottom(b), top(t) {
    if (top < bottom) {
      throw std::runtime_error("Incorrect input data");
    }
  }

  TestTask(TestTask && rtask) {
    bottom = std::move(rtask.bottom);
    top = std::move(rtask.top);
    counter = std::move(rtask.counter);
  }

  TestResult run() {
    std::cout << "starting task with params: " << bottom << " " << top << "\n";
    for (int i = bottom; i < top; ++i) {
      if (isPrime(i)) {
        std::lock_guard<std::mutex> lck(m);
        ++counter;
      }
    }
    return TestResult(counter);
  }

private:
  int32_t bottom;
  int32_t top;
  int32_t counter = 0;
  static std::mutex m;

  bool isPrime(const int32_t num) {
    for (int i = 2; i < num; ++i) {
      if (num % i == 0) {
        return false;
      }
    }
    return true;
  }
};

std::mutex TestTask::m = {};

int main() {
  std::cout << "Hello from test\n";
  int noThreads = 3;
  Executor<TestResult> executor(3, TestResult(0));

  std::vector<ITask<TestResult>> tasks;
  for(int i = 0; i < noThreads; ++i) {
    std::cout << "Creating task for i : " << i << "\n";
    tasks.push_back(TestTask(i * 10, (i+1) * 10));
  }
  executor.execute(std::move(tasks));
  std::cout << "Result: " << executor.getResult().getResult() << "\n";
}