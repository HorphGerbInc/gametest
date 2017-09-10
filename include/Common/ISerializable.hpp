
#ifndef _ISERIALIZABLE_HPP_
#define _ISERIALIZABLE_HPP_

#include <istream>
#include <ostream>

namespace jerobins {
  namespace common {

    enum SerializationFormat { Binary, Text };

    /*
    *   Provides methods to serialize and deserialize an object.
    */
    template <class T> class ISerializable {
    public:
      // Serialize an object to a stream.
      virtual void Serialize(std::ostream &os,
                             SerializationFormat format) const = 0;

      // Deserialize an object
      static T Deserialize(std::istream &is, SerializationFormat format);
    };
  }
}

#endif