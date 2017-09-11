
#include <vector>

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

    Version::Version(const Version &&other)
        : Major(other.Major), Minor(other.Minor), Patch(other.Patch) {}

    Version::Version(const Version &other)
        : Major(other.Major), Minor(other.Minor), Patch(other.Patch) {}

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

      std::vector<std::uint8_t> bytes;

      switch (format) {
      case SerializationFormat::Binary:
        bytes = nlohmann::json::to_cbor(j);
        os.write((char *)&bytes[0], bytes.size());
        break;
      case SerializationFormat::Text:
        os << j;
        break;
      default:
        throw std::runtime_error("Unknown SerializationFormat");
        break;
      };
    }

    Version Version::Deserialize(std::istream &is, SerializationFormat format) {
      nlohmann::json j;
      uint16_t major;
      uint16_t minor;
      uint16_t patch;

      uint8_t buffer[512] = {0};
      std::vector<std::uint8_t> bytes;
      std::streamsize bytesRead = 0;

      switch (format) {
      case SerializationFormat::Binary:
        while (is.read((char *)buffer, 512)) {
          bytesRead = is.gcount();
        }
        bytes.insert(bytes.end(), buffer, buffer + bytesRead);
        j = nlohmann::json::from_cbor(bytes);
        break;
      case SerializationFormat::Text:
        is >> j;
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