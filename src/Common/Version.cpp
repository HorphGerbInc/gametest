
#include <Common/Version.hpp>

namespace jerobins
{
namespace common
{
/*
         * Creates a version object.
         */
Version::Version(uint16_t major, uint16_t minor, uint16_t patch) : Major(major), Minor(minor), Patch(patch)
{
    /* Empty */
}

/*
*  Returns a string representation of the version.
*/
const std::string Version::ToString() const
{
    if (this->strRep == "")
    {
        this->strRep = std::to_string(this->Major) + "." + std::to_string(this->Minor) + "." + std::to_string(this->Patch);
    }
    return this->strRep;
}
}
};