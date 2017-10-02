
#ifdef _TEMPLATE_HPP_
#define _TEMPLATE_HPP_

// Use template parameters to determine if a method exists
template <bool B> using EnableIfB = typename std::enable_if<B, int>::type;

#endif