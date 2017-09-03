
#ifndef _STRINGUTIL_HPP_
#define _STRINGUTIL_HPP_

#include <vector>
#include <string>
#include <sstream>

namespace jerobins {
	namespace common {
		static std::vector<std::string> Split(std::string str, std::string delims) {
			std::vector<std::string> result;
			std::stringstream ss;
			for each (char c in str)
			{
				if (delims.find(c) != delims.npos) {
					std::string candidate = ss.str();
					if (candidate.length() != 0) {
						result.push_back(candidate);
					}
					ss.clear();
				}
				else {
					ss << c;
				}
			}
			return result;
		}
	}
}

#endif