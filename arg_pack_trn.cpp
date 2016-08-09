/*
 * arg_pack_trn.cpp
 *
 *  Created on: 7 Aug 2016
 *      Author: acolomitchi
 */

#include "typeout.hpp"
#include "arg_pack_trn.hpp"


template <typename... A> struct dummy {

};

template <typename...> struct always_int;
//template <typename H>
//struct always_int<H> {
//  using type=int;
//};
template <typename H, typename... T>
struct always_int<H, T...> {
  using type=int;
};

//
//int main() {
//  typedef arg_pack_trn<
//    dummy<>, always_int<long, void>
//  >::type a;
//  outname<a>("a");
//}



