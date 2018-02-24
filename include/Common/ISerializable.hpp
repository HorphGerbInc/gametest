
#ifndef _ISERIALIZABLE_HPP_
#define _ISERIALIZABLE_HPP_

#include <istream>
#include <ostream>

namespace jerobins {
  namespace common {

    /**
     * @brief The serialization format of the object.  This can either be in
     * Binary or Text format.
     *
     */
    enum SerializationFormat { Binary, Text };

    /**
     * @brief Provides methods to serialize and deserialize an object.
     *
     * @tparam T  The object type.
     */
    template <class T> class ISerializable {
    public:
      /**
       * @brief Checks to see if a serialization format is supported.
       *
       * @param format  The format to check.
       * @return true   We support this serialization format.
       * @return false  We don't support this serialization format.
       */

      virtual bool SupportsFormat(SerializationFormat format) const = 0;

      /**
       * @brief Serialized an object to the stream.
       *
       * @param os      The output stream.
       * @param format  How to serialize the output.
       */
      virtual void Serialize(std::ostream &os,
                             SerializationFormat format) const = 0;

      /**
       * @brief Deserialize an object from a stream.
       *
       * @param is      The input stream.
       * @param format  How the object was serialized.
       * @return T      The deserialized object.
       */
      static T Deserialize(std::istream &is, SerializationFormat format);
    };
  } // namespace common
} // namespace jerobins

#endif