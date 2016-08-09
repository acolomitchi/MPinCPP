/*
 * arg_pack_trn.hpp
 *
 *  Created on: 7 Aug 2016
 *      Author: acolomitchi
 */


#ifndef ARG_PACK_TRN_HPP_
#define ARG_PACK_TRN_HPP_

#include <algorithm>
#include <type_traits>

namespace com {
namespace caffeineowl {

template <typename H, typename... T>
struct identity_trn {
  using type=H;
};



template <typename...> struct arg_pack_trn;

template <
  template <typename...> class dest,
  typename... destTypes,
  template <typename...> class xf,
  typename toAppend
>
struct arg_pack_trn<dest<destTypes...>, xf<toAppend>>
{
  // simply make a new dest type, appendig the transformed type
  // to the already existing arg pack
  using type=dest<destTypes...,typename xf<toAppend>::type>;
};

template <
  template <typename...> class dest,
  typename... destTypes,
  template <typename...> class xf,
  typename toAppendH, typename... toAppendT
>
struct arg_pack_trn<dest<destTypes...>, xf<toAppendH, toAppendT...>>
{
  using type=typename
    arg_pack_trn<
    // consume the first one by appending to the target types
      typename arg_pack_trn<dest<destTypes...>, xf<toAppendH>>::type,
      // and prepare the rest of them to be transformed
      // in the next recursion steps
      xf<toAppendT...>
    >::type
  ;
};


template <
  template <typename...> class dest,
  typename... destTypes,
  typename toAppendH, typename... toAppendT
>
struct arg_pack_trn<dest<destTypes...>, toAppendH, toAppendT...> {
  using type=typename
    arg_pack_trn<
      dest<destTypes...>,
      identity_trn<toAppendH,  toAppendT...>
    >::type
  ;
};

} // ns caffeineowl
} // ns com



#endif /* ARG_PACK_TRN_HPP_ */

