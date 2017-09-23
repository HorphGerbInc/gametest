
#ifdef _TEMPLATE_HPP_
#define _TEMPLATE_HPP_

template <bool B> using EnableIfB = typename std::enable_if<B, int>::type;

#endif