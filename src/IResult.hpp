#ifndef IRESULT_HPP
#define IRESULT_HPP

#include <memory>

namespace ssg {

class IResult {
public:

    IResult() = default;
    virtual ~IResult() = default;
    IResult(const IResult & res) = default;
    IResult(IResult && res) = default;
    void operator=(const IResult & res);
    void operator=(IResult && res);

    virtual void merge(std::unique_ptr<IResult> other);
};

}
#endif