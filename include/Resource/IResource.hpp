
#ifndef _IRESOURCE_HPP_
#define _IRESOURCE_HPP_

#include <string>

#include <Common/IString.hpp>

namespace jerobins {
  namespace resource {

    /**
     * @brief Base class for all resources.
     * 
     * @tparam T  The type resource. 
     */
    template <class T> class IResource : public jerobins::common::IString {
    public:
    /**
     * @brief Load the resource from a file.
     * 
     * @param filename  File to load the resource from.
     * @return T        Loaded resource.
     */
      static T Load(std::string filename);

      /**
       * @brief Save the resource to a file.
       * 
       * @param filename File to save the resource too.
       */
      virtual void Save(std:string filename) const = 0;
    };
  }
}

#endif