/* Only supporting GCC (Clang) and MSVC
 TODO: Add ARM support for Android */

#ifndef __MY__MACROS__
#define __MY__MACROS__

/* Retired from Hedley (https://t.ly/DpCm) and edited */

#define __VERSION_ENCODE__(MAJOR, MINOR, PATCH) (MAJOR * 1000000) + (MINOR * 1000) + PATCH

#if defined(__GNUC__) && defined(__GNUC_PATCHLEVEL__)
	#define __GNUC_VERSION__ __VERSION_ENCODE__(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
#elif defined(__GNUC__)
	#define __GNUC_VERSION__ __VERSION_ENCODE__(__GNUC__, __GNUC_MINOR__, 0)
#else
	#define __GNUC_VERSION__ 0
#endif

#ifdef __GNUC_VERSION__
	#define __GNUC_VERSION_CHECK__(MAJOR, MINOR, PATCH) (__GNUC_VERSION__ >= __VERSION_ENCODE__(MAJOR, MINOR, PATCH))
#else
	#define __GNUC_VERSION_CHECK__(MAJOR, MINOR, PATCH) (0)
#endif

#ifndef _MSC_VER
	#define __MSVC_VERSION_CHECK__(MAJOR, MINOR, PATCH) (0)
#elif _MSC_VER >= 1400
	#define __MSVC_VERSION_CHECK__(MAJOR, MINOR, PATCH) (_MSC_FULL_VER >= (MAJOR * 10000000) + (MINOR * 100000) + PATCH)
#elif _MSC_VER >= 1200
	#define __MSVC_VERSION_CHECK__(MAJOR, MINOR, PATCH) (_MSC_FULL_VER >= (MAJOR * 1000000) + (MINOR * 10000) + PATCH)
#else
	#define __MSVC_VERSION_CHECK__(MAJOR, MINOR, PATCH) (_MSC_VER >= (MAJOR * 100) + MINOR)
#endif

#ifdef __has_attribute
	#define __HAS_ATTRIBUTE__(X) __has_attribute(X)
#else
	#define __HAS_ATTRIBUTE__(X) (0)
#endif

#ifdef __has_builtin
	#define __HAS_BUILTIN__(X) __has_builtin(X)
#else
	#define __HAS_BUILTIN__(X) (0)
#endif

/* Utils */

// 32 & 64 Bits
#if defined(_WIN64) || defined(__x86_64__)
	#define __64_BITS__
#else
	#define __32_BITS__
#endif

// string_view
#if __cplusplus >= 201703L
	#include <string_view>
	#define string_view std::string_view
#else
	#define string_view std::string
#endif

/* Keywords */

// constorexpr & constexpr11
#if __cplusplus >= 201103L
	#define constorexpr constexpr
	#define constexpr11 constexpr
#else
	#define constorexpr const
	#define constexpr11
#endif

// constexpr14 (for functions)
#if __cplusplus >= 201402L
	#define constexpr14 constexpr
#else
	#define constexpr14
#endif

// LIKELY & UNLIKELY
#if __cplusplus >= 202002L
	#define __LIKELY__ [[likely]]
	#define __UNLIKELY__ [[unlikely]]
#else
	#define __LIKELY__
	#define __UNLIKELY__
#endif

// RESTRICT
#if __GNUC_VERSION_CHECK__(3, 1, 0)	|| \
	__MSVC_VERSION_CHECK__(14, 0, 0)	|| \
	defined(clang)
	#define __RESTRICT__ __restrict
#elif __STDC_VERSION__ >= 199901L
	#define __RESTRICT__ restrict
#else
	#define __RESTRICT__
#endif

/* Builtins */

// ATTRIBUTE
#ifdef _MSC_VER
	#define __ATTRIBUTE__(X) __declspec(X)
#elif __GCC__
	#define __ATTRIBUTE__(X) __attribute__((X))
#else
	#define __ATTRIBUTE__(X)
#endif

// PRAGMA
#if __STDC_VERSION__ >= 199901L		|| \
	__GNUC_VERSION_CHECK__(3, 0, 0)	|| \
	defined(__clang__)
	#define __PRAGMA__(X) _Pragma(#X)
#elif __MSVC_VERSION_CHECK__(15, 0, 0)
	#define __PRAGMA__(X) __pragma(X)
#else
	#define __PRAGMA__(X)
#endif

// ASSUME
#if __MSVC_VERSION_CHECK__(13, 10, 0)
	#define __ASSUME__(X) __assume(X)
#elif __HAS_BUILTIN__(__builtin_assume)
	#define __ASSUME__(X) __builtin_assume(X)
#endif

// UNREACHABLE
#if __HAS_BUILTIN__(__builtin_unreachable)	|| \
	__GNUC_VERSION_CHECK__(4, 5, 0)
	#define __UNREACHABLE__ __builtin_unreachable()
#elif defined(__ASSUME__)
	#define __UNREACHABLE__ __ASSUME__(0)
#endif

// EXPECT & UNEXPECT
#if __HAS_BUILTIN__(__builtin_expect)	|| \
	__GNUC_VERSION_CHECK__(3, 0, 0)
	#define __EXPECT__(X) __builtin_expect(!!(X), 1)
	#define __UNEXPECT__(X) __builtin_expect(!!(X), 0)
#elif defined(__ASSUME__)
	#define __UNREACHABLE__ __ASSUME__(0)
#endif

/* Attributes */

// HOT & COLD
#if (__HAS_ATTRIBUTE__(hot)		&& \
	__HAS_ATTRIBUTE__(cold))	|| \
	__GNUC_VERSION_CHECK__(4, 3, 0)
	#define __HOT__ __ATTRIBUTE__(hot)
	#define __COLD__ __ATTRIBUTE__(cold)
#else
	#define __HOT__
	#define __COLD__
#endif

// MALLOC
#if __HAS_ATTRIBUTE__(malloc)		|| \
	__GNUC_VERSION_CHECK__(3, 1, 0)
	#define __MALLOC__ __ATTRIBUTE__(__malloc__)
#elif __MSVC_VERSION_CHECK__(14, 0, 0)
	#define __MALLOC__ __ATTRIBUTE__(restrict)
#else
	#define __MALLOC__
#endif

// NO THROW
#if __HAS_ATTRIBUTE__(nothrow)		|| \
	__GNUC_VERSION_CHECK__(3, 3, 0)
	#define __NO_THROW__ __ATTRIBUTE__(__nothrow__)
#elif __MSVC_VERSION_CHECK__(13, 1, 0)
	#define __NO_THROW__ __ATTRIBUTE__(nothrow)
#else
	#define __NO_THROW__
#endif

// NO RETURN
#if __HAS_ATTRIBUTE__(noreturn)		|| \
	__GNUC_VERSION_CHECK__(3, 2, 0)
	#define __NO_RETURN__ __ATTRIBUTE__(__noreturn__)
#elif __MSVC_VERSION_CHECK__(13, 10, 0)
	#define __NO_RETURN__ __ATTRIBUTE__(noreturn)
#else
	#define __NO_RETURN__
#endif

// CONST
#if __HAS_ATTRIBUTE__(const)		|| \
	__GNUC_VERSION_CHECK__(2, 5, 0)
	#define __CONST__ __ATTRIBUTE__(__const__)
#else
	#define __CONST__
#endif

#endif
