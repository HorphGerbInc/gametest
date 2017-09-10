
// LIB
#include <json.hpp>

// Mine
#include <Common/Version.hpp>

namespace jerobins {
  namespace common {
    /*
     * Creates a version object.
     */
    Version::Version(uint16_t major, uint16_t minor, uint16_t patch)
        : Major(major), Minor(minor), Patch(patch) {
      /* Empty */
    }

    /*
     *  Returns a string representation of the version.
     */
    const std::string Version::ToString() const {
      if (this->strRep == "") {
        this->strRep = std::to_string(this->Major) + "." +
                       std::to_string(this->Minor) + "." +
                       std::to_string(this->Patch);
      }
      return this->strRep;
    }

    void Version::Serialize(std::ostream &os,
                            SerializationFormat format) const {
      nlohmann::json j;
      j["major"] = this->Major;
      j["minor"] = this->Minor;
      j["patch"] = this->Patch;
      switch (format) {
      case SerializationFormat.Binary:
        std::vector<std::uint8_t> bytes =
            json::to_cbor(j) os.write((char *)&bytes[0], bytes.size());
        break;
      case SerializationFormat.Text:
        os << j;
        break;
      default:
        throw std::runtime_error("Unknown SerializationFormat");
      }
    }

    static Vesion Version::Deserialize(std::istream &is,
                                       SerializationFormat format) {
      nlohmann::json j;
      uint16_t major;
      uint16_t minor;
      uint16_t patch;
      switch (format) {
      case SerializationFormat.Binary:
        std::vector<std::uint8_t> bytes;
        char bytes[512];
        int bytesRead = 0;
        while(is.read(bytes, 512)) {
            bytesRead = is.gcount();            
        }
        bytes.insert(bytes, bytes + bytesRead);
        j <<  json::from_cbor(bytes);
        break;
      case SerializationFormat.Text:
        j << is;
        break;
      default:
        throw std::runtime_error("Unknown SerializationFormat");
      }

      // Create object
      major = j["major"];
      minor = j["minor"];
      patch = j["patch"];
      return Version(major, minor, patch);
    }

    std::ostream &operator<<(std::ostream &strm, const Version &a) {
      return strm << a.ToString();
    }
  }
};