#ifndef BOOST_SERIALIZATION_BASE_OBJECT_HPP
#define BOOST_SERIALIZATION_BASE_OBJECT_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// base_object.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// if no archive headers have been included this is a no op
// this is to permit BOOST_EXPORT etc to be included in a 
// file declaration header

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_const.hpp>

#include <boost/static_assert.hpp>
#include <boost/serialization/type_info_implementation.hpp>
#include <boost/serialization/force_include.hpp>
#include <boost/serialization/void_cast_fwd.hpp>

namespace boost {
namespace serialization {

namespace detail
{
// only register void casts if the types are polymorphic
  template<class Base, class Derived>
  struct base_register
  {
      static void const* execute(mpl::false_) { return 0; }

      static void const* execute(mpl::true_)
      {
          return &void_cast_register((Derived const*)0, (Base const*)0);
      }
            
      static void const* invoke()
      {
          typedef mpl::bool_<
              type_info_implementation<Base>::type::is_polymorphic::value
          > is_polymorphic;
          
          return execute(is_polymorphic());
      }
  };

  // get the base type for a given derived type
  // preserving the const-ness
  template<class B, class D>
  struct base_cast
  {
      typedef BOOST_DEDUCED_TYPENAME
      mpl::if_<
          is_const<D>,
          const B,
          B
      >::type type;
      BOOST_STATIC_ASSERT(is_const<type>::value == is_const<D>::value);
  };
} // namespace detail

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x560))
template<class Base, class Derived>
const Base & 
base_object(const Derived & d)
{
    BOOST_STATIC_ASSERT(! is_pointer<Derived>::value);
    detail::base_register<Base, Derived>::invoke();
    return static_cast<const Base &>(d);
}
#else
template<class Base, class Derived>
BOOST_DEDUCED_TYPENAME detail::base_cast<Base, Derived>::type & 
base_object(Derived &d)
{
    BOOST_STATIC_ASSERT(( is_base_and_derived<Base,Derived>::value));
    BOOST_STATIC_ASSERT(! is_pointer<Derived>::value);
    typedef BOOST_DEDUCED_TYPENAME detail::base_cast<Base, Derived>::type type;
    detail::base_register<type, Derived>::invoke();
    return static_cast<type &>(d);
}
#endif

} // namespace serialization
} // namespace boost

#endif // BOOST_SERIALIZATION_BASE_OBJECT_HPP
