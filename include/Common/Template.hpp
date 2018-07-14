
#ifndef _TEMPLATE_HPP_
#define _TEMPLATE_HPP_

/**
 * @brief   Enable a constructor if B is strue.
 *
 * @tparam B    The test.
 */
template <bool B> using EnableIfB = typename std::enable_if<B, int>::type;

#endif