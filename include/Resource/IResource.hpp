
#ifndef _IRESOURCE_HPP_
#define _IRESOURCE_HPP_

#include <string>

#include <Common/IString.hpp>

namespace jerobins {
  namespace resource {
    template <class T> class IResource : public jerobins::common::IString {
    public:
      static T Load(std::string filename);
    };
  }
}

#endif