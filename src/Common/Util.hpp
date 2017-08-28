
#ifndef _UTIL_HPP_
#define _UTIL_HPP_

#include <algorithm>
#include <iterator>

namespace jerobins
{
namespace common
{

// Convert from one data-type to another
template <typename T>
static T Convert(char *input)
{
    return *dynamic_cast<T *>(input);
}

template <class T, typename Y>
auto Contains(const T &enumerable, const Y &value) -> decltype(end(enumerable), true)
{
    return std::find(begin(enumerable), end(enumerable), value) != end(enumerable);
}
}
}
#endif