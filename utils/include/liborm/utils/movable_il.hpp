#ifndef LIBORM_UTILS_MOVABLE_IL_HPP
#define LIBORM_UTILS_MOVABLE_IL_HPP

#include <vector>

/* Explanation: https://stackoverflow.com/questions/46737054/vectorunique-ptra-using-initialization-list */
template<class T>
struct movable_il {
    mutable T t;
    operator T() const&& { return std::move(t); }
    movable_il( T&& in ): t(std::move(in)) {}
    //movable_il( T& in ): t(std::move(in)) {}
};

template<class T, class A=std::allocator<T>>
std::vector<T,A> vector_from_il( std::initializer_list< movable_il<T> > il ) {
  std::vector<T,A> r( std::make_move_iterator(il.begin()), std::make_move_iterator(il.end()) );
  return r;
}

template<class VT>
struct fix_vt {
  using type=VT;
};
template<class VT>
using fix_vt_t = typename fix_vt<VT>::type;
template<class VT>
struct fix_vt<const VT>:fix_vt<VT>{};
template<class K, class V>
struct fix_vt<std::pair<K,V>>{
  using type=std::pair<
    typename std::remove_cv<K>::type,
    typename std::remove_cv<V>::type
  >;
};

template<class C, class T=fix_vt_t<typename C::value_type>>
C container_from_il( std::initializer_list< movable_il<T> > il ) {
  C r( std::make_move_iterator(il.begin()), std::make_move_iterator(il.end()) );
  return r;
}

#endif