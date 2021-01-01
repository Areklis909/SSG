#include <IExecutor.hpp>
#include <memory>
#include <stdexcept>

using namespace ssg;

class TestResult : public IResult {};

class TestTask {
public:
  TestTask(const int32_t b, const int32_t t) : bottom(b), top(t) {
    if(top < bottom) {
      throw std::runtime_error("Incorrect input data");
    }
  }

  std::unique_ptr<IResult> run() {
    for (int i = bottom; i < top; ++i) {
      if (isPrime(i)) {
        ++counter;
      }
    }
  }

private:
  int32_t bottom;
  int32_t top;
  int32_t counter;

  bool isPrime(const int32_t num) {
    for (int i = 2; i < num; ++i) {
      if (num % i == 0) {
        return false;
      }
    }
    return true;
  }
};

int main() {}