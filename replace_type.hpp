/*
 * replace_type.hpp
 *
 *  Created on: 8 Aug 2016
 *      Author: acolomitchi
 */

#ifndef REPLACE_TYPE_HPP_
#define REPLACE_TYPE_HPP_


#include <algorithm>
#include <type_traits>

/**
 *
 * Write a ternary metafunction replace_type<c,x,y> that takes an arbitrary compound type c as its first
 * parameter, and replaces all occurrences of a type x within c with y:
 * <pre>
 * typedef replace_type< void*, void, int >::type t1; // int*
 *
 * typedef replace_type<
 *    int const*[10]
 *  , int const
 *  , long
 * >::type t2; // long* [10]
 *
 * typedef replace_type<
 *    char& (*)(char&)
 *  , char&
 *  , long&
 * >::type t3; // long& (*)(long&)
 *
 * You can limit the function types you operate on to those
 * with fewer than two arguments.
 */

/** Regarding the last example (function) - challenge:
 *  no, you cannot limit the function types to those with
 *  with fewer than two arguments.
 */

// Since 2004, the day the book was published, the C++11
// was adopted. Whew, we can use variadic template arguments
// and aliasing.

#include "arg_pack_trn.hpp"

namespace com {
namespace caffeineowl {


template <typename ...> struct replace_type;

template <typename context, typename particle, typename subst>
struct replace_type<context, particle, subst> {
  // with no specialization, it will just return the substitute
  // The specializations are expected to act on qualified types,
  //   removing one qualifier (const, *, &, etc), recursively calling into
  //   replace_type, then adding the qualifier to the result
  template <typename C, typename P, typename S>
  struct repl_op {
    using type=S;
  };

  template <typename C, typename P, typename S>
  struct repl_op<const C, P, S> {
    using type=typename replace_type<C,P,S>::type const;
  };

  template <typename C, typename P, typename S>
  struct repl_op<volatile C, P, S> {
    using type=typename replace_type<C,P,S>::type volatile;
  };

  template <typename C, typename P, typename S>
  struct repl_op<C*, P, S> {
    using type=typename replace_type<C,P,S>::type *;
  };

  template <typename C, typename P, typename S>
  struct repl_op<C&, P, S> {
    using type=typename replace_type<C,P,S>::type &;
  };

  template <typename C, typename P, typename S>
  struct repl_op<C[], P, S> {
    using type=typename replace_type<C,P,S>::type [];
  };

  template <typename C, typename P, typename S, std::size_t N>
  struct repl_op<C[N], P, S> {
    using type=typename replace_type<C,P,S>::type [N];
  };

  // Function replace_type

  template <
    typename P, typename S,
    typename Ret, typename... Args
  >
  struct repl_op<Ret(Args...), P, S> {

    // sort of a "closure", binding the already known ret_t arg,
    // but letting exposed the args... pack
    template <typename... args>
    struct func_builder {
      using ret_t=typename replace_type<Ret, P, S>::type;
      using type=ret_t(args...);
    };

    // returns the replaced type for the head of the pack
    template <typename H, typename... T>
    struct transformer {
      using type=typename replace_type<H, P, S>::type;
    };

    // finally
    using type=typename arg_pack_trn<
      func_builder<>,
      transformer<Args...>
    >::type::type;
  };


  using type=typename std::conditional<
     std::is_same<context, particle>::value,
     subst,
     typename repl_op<context, particle,subst>::type // here's the recursion
   >::type;
};

/**
 * typedef replace_type< void*, void, int >::type t1; // int*
 */
static_assert(
  std::is_same<
    replace_type< void*, void, int >::type,
    int*
  >::value,
  "t1 failure"
);

/** typedef replace_type<
 *    int const*[10]
 *  , int const
 *  , long
 * >::type t2; // long* [10]
 */
static_assert(
  std::is_same<
    replace_type< int const*[10], int const, long >::type,
    long* [10]
  >::value,
  "t2 failure"
);

/** typedef replace_type<
 *    char& (*)(char&)
 *  , char&
 *  , long&
 * >::type t3; // long& (*)(long&)
 **/
static_assert(
  std::is_same<
    replace_type< char& (*)(char&), char&, long& >::type,
    long& (*)(long&)
  >::value,
  "t3 failure"
);


} // ns caffeineowl
} // ns com



#endif /* REPLACE_TYPE_HPP_ */
