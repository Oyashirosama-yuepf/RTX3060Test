/*!
 * \brief Common macro
 * \author Yuchao Hu (huyuchao@holomatic.com)
 * \date 2018-08-16
 * \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * \attention Refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_MAP_COMMON_COMMON_MACRO_H_
#define HOLO_MAP_COMMON_COMMON_MACRO_H_

/// Indicates that the following function is deprecated.
#ifdef __clang__
#  if __has_extension(attribute_deprecated_with_message)
#    define HOLO_MAP_DEPRECATED(message)  __attribute__ ((deprecated(message)))
#  endif
#elif defined __GNUC__ // not clang (gcc comes later since clang emulates gcc)
#  if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5))
#    define HOLO_MAP_DEPRECATED(message)  __attribute__ ((deprecated(message)))
#  elif (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1))
#    define HOLO_MAP__DEPRECATED(message)  __attribute__((__deprecated__))
#  endif  // GNUC version
#elif defined _MSC_VER
#  if (_MSC_VER >= 1500) // MSVC 2008    
#    define HOLO_MAP_DEPRECATED(message) __declspec(deprecated(message))
#  endif // _MSC_VER >= 1500
#endif // __clang__ || __GNUC__ || _MSC_VER

#if !defined(HOLO_MAP_DEPRECATED)
#pragma message("WARNING: You need to implement DEPRECATED for this compiler")
#define HOLO_MAP_DEPRECATED(message)
#endif /* if !defined(HOLO_MAP_DEPRECATED) */

#endif  // HOLO_MAP_COMMON_COMMON_MACRO_H_
