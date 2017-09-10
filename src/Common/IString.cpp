
#include <Common/IString.hpp>

std::ostream <<(std::ostream & os, const IString & str) {
    return os << str.ToString();
}

std::ostream <<(std::ostream & os, const IString && str) {
    return os << str;
}