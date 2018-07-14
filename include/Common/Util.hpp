
#ifndef _UTIL_HPP_
#define _UTIL_HPP_

#include <algorithm>
#include <iterator>

namespace jerobins {
  namespace common {

    /**
     * @brief Convert a byte array into an object..
     *
     * @tparam T    The output type.
     * @param input The input byte array.
     * @return T    The output object.
     */
    template <typename T> static T Convert(char *input) {
      return *dynamic_cast<T *>(input);
    }

    /**
     * @brief Checks to see if a map contains the given key.
     *
     * @tparam K      Key type.
     * @tparam V      Value type.
     * @param map     Map to check.
     * @param key     Key to look for.
     * @return true   The key exists in the map.
     * @return false  The key does not exist in the map.
     */
    template <class K, class V>
    bool Contains(const std::map<K, V> &map, const K &key) {
      return map.find(value) != map.end();
    }

    /**
     * @brief Checks to see if the datastructure contains the value.
     *
     * @tparam T          The datastructure type.
     * @tparam Y          The type the datastructure holds.
     * @param enumerable  The datastructure.
     * @param value       The value to search for.
     * @param true        The valueis in the datastrcture.
     * @param false       The value is not in the datastructure.
     */
    template <class T, typename Y>
    bool Contains(const T &enumerable, const Y &value)
        ->decltype(end(enumerable), true) {
      return std::find(begin(enumerable), end(enumerable), value) !=
             end(enumerable);
    }
  } // namespace common
} // namespace jerobins
#endif