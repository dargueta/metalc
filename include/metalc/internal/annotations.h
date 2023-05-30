#ifndef INCLUDE_METALC_INTERNAL_ANNOTATIONS_H_
#define INCLUDE_METALC_INTERNAL_ANNOTATIONS_H_

// C2x standard attributes
#ifdef __has_c_attribute
#    if __has_c_attribute(nodiscard)
#        define METALC_ATTR__NODISCARD [[nodiscard]]
#    endif

#    if __has_c_attribute(noreturn)
#        define METALC_ATTR__NORETURN [[noreturn]]
#    endif

#    if __has_c_attribute(reproducible)
#        define METALC_ATTR__REPRODUCIBLE [[reproducible]]
#    endif

#    if __has_c_attribute(fallthrough)
#        define METALC_ATTR__FALLTHROUGH_MARKER [[fallthrough]]
#    endif

#    if __has_c_attribute(deprecated)
#        define METALC_ATTR__DEPRECATED [[deprecated]]
#    endif
#endif // __has_c_attribute

// GCC and GCC-compatible compilers. It's unclear if Sun's compiler defines __GNUC__ so we
// explicitly check for that here.
#if defined(__GNUC__) || defined(__SUNPRO_C)
#    define GCC_ATTRIBUTE(...) __attribute__((__VA_ARGS__))
#else
#    define GCC_ATTRIBUTE(...)
#endif

// GCC and compatible compilers, except some versions of ICC that don't define this.
#if defined(__has_attribute)
#    if __has_attribute(visibility)
#        define METALC_ATTR__EXPORT GCC_ATTRIBUTE(visibility("default"))
#        define METALC_ATTR__NO_EXPORT GCC_ATTRIBUTE(visibility("hidden"))
#    endif

#    if !defined(METALC_ATTR__DEPRECATED) && __has_attribute(deprecated)
#        define METALC_ATTR__DEPRECATED GCC_ATTRIBUTE(deprecated)
#    endif

#    if !defined(METALC_ATTR__NODISCARD) && __has_attribute(nodiscard)
#        define METALC_ATTR__NODISCARD GCC_ATTRIBUTE(nodiscard)
#    endif

#    if !defined(METALC_ATTR__NORETURN) && __has_attribute(noreturn)
#        define METALC_ATTR__NORETURN GCC_ATTRIBUTE(noreturn)
#    endif

#    if !defined(METALC_ATTR__REPRODUCIBLE) && __has_attribute(pure)
#        define METALC_ATTR__REPRODUCIBLE GCC_ATTRIBUTE(pure)
#    endif

#    if !defined(METALC_ATTR__CONST_FUNC) && __has_attribute(const)
#        define METALC_ATTR__CONST_FUNC GCC_ATTRIBUTE(const)
#    endif

#    if !defined(METALC_ATTR__FALLTHROUGH_MARKER) && __has_attribute(fallthrough)
#        define METALC_ATTR__FALLTHROUGH_MARKER GCC_ATTRIBUTE(fallthrough)
#    endif

#    if __has_attribute(returns_nonnull)
#        define METALC_ATTR__RETURNS_NONNULL GCC_ATTRIBUTE(returns_nonnull)
#    endif

#    if __has_attribute(nonnull)
#        define METALC_ATTR__NONNULL GCC_ATTRIBUTE(nonnull)
#        define METALC_ATTR__NONNULL_ARGS(...) GCC_ATTRIBUTE(nonnull(__VA_ARGS__))
#    endif

#    if __has_attribute(malloc)
#        define METALC_ATTR__MALLOC(...) GCC_ATTRIBUTE(malloc, malloc(__VA_ARGS__))
#    endif

#    if __has_attribute(weak)
#        define METALC_ATTR__EXPORT_WEAK GCC_ATTRIBUTE(weak)
#    endif

#    if __has_attribute(fastcall)
#        define METALC_ATTR__FASTCALL GCC_ATTRIBUTE(fastcall)
#    endif
#endif

// Visual Studio
#ifdef _MSC_VER
#    define METALC_ATTR__EXPORT __dllspec(export)
#    define METALC_ATTR__FASTCALL __declspec(fastcall)

#    ifndef METALC_ATTR__DEPRECATED
#        define METALC_ATTR__DEPRECATED __dllspec(deprecated)
#    endif

#    ifndef METALC_ATTR__NORETURN
#        define METALC_ATTR__NORETURN __declspec(noreturn)
#    endif
#endif

// OpenWatcom
#ifdef __WATCOM__
#    define METALC_ATTR__EXPORT __declspec(dllexport)
#    define METALC_ATTR__FASTCALL __declspec(fastcall)

#    ifndef METALC_ATTR__NORETURN
#        define METALC_ATTR__NORETURN __declspec(noreturn)
#    endif
#endif

/* Fallbacks */

#ifndef METALC_ATTR__EXPORT
#    define METALC_ATTR__EXPORT
#endif

#ifndef METALC_ATTR__NO_EXPORT
#    define METALC_ATTR__NO_EXPORT
#endif

#ifndef METALC_ATTR__DEPRECATED
#    define METALC_ATTR__DEPRECATED
#endif

#ifndef METALC_ATTR__NODISCARD
#    define METALC_ATTR__NODISCARD
#endif

#ifndef METALC_ATTR__NORETURN
#    if __STDC_VERSION__ >= 201112L
#        define METALC_ATTR__NORETURN _Noreturn
#    else
#        define METALC_ATTR__NORETURN
#    endif
#endif

#ifndef METALC_ATTR__REPRODUCIBLE
#    define METALC_ATTR__REPRODUCIBLE
#endif

#ifndef METALC_ATTR__CONST_FUNC
#    define METALC_ATTR__CONST_FUNC
#endif

#ifndef METALC_ATTR__FALLTHROUGH_MARKER
#    define METALC_ATTR__FALLTHROUGH_MARKER
#endif

#ifndef METALC_ATTR__NONNULL
#    define METALC_ATTR__NONNULL
#endif

#ifndef METALC_ATTR__NONNULL_ARGS
#    define METALC_ATTR__NONNULL_ARGS(...)
#endif

#ifndef METALC_ATTR__RETURNS_NONNULL
#    define METALC_ATTR__RETURNS_NONNULL
#endif

#ifndef METALC_ATTR__MALLOC
#    define METALC_ATTR__MALLOC(...)
#endif

#ifndef METALC_ATTR__EXPORT_WEAK
#    define METALC_ATTR__EXPORT_WEAK
#endif

#ifndef METALC_ATTR__FASTCALL
#    define METALC_ATTR__FASTCALL
#endif

#if __STDC_HOSTED__
#    define METALC_ATTR__UNHOSTED_ONLY(x)
#else
#    define METALC_ATTR__UNHOSTED_ONLY(x) x
#endif


#endif /* INCLUDE_METALC_INTERNAL_ANNOTATIONS_H_ */
