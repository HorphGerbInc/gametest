
#ifndef VERSION_HPP_
#define VERSION_HPP_

#include <cstdint>
#include <string>

namespace jerobins {
  namespace common {
    /*
    *  Software version object.
    */
    class Version : public ISerializable<Version> {
    private:
      Version();
      mutable std::string strRep = "";

    public:

      const uint16_t Major;
      const uint16_t Minor;
      const uint16_t Patch;

      /*
       * Creates a version object.
       */
      Version(uint16_t major, uint16_t minor, uint16_t patch);

      /*
       *  Returns a string representation of the version.
       */
      const std::string ToString() const;

      // ISerializable
      void Serialize(std::ostream & os) const;
      Version Deserialize(std::istream & is);
    };

    /* Stream handling */
    std::ostream &operator<<(std::ostream &strm, const Version &a);
  }
};
#endif