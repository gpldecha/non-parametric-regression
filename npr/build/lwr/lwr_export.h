
#ifndef LWR_EXPORT_H
#define LWR_EXPORT_H

#ifdef LWR_STATIC_DEFINE
#  define LWR_EXPORT
#  define LWR_NO_EXPORT
#else
#  ifndef LWR_EXPORT
#    ifdef lwr_EXPORTS
        /* We are building this library */
#      define LWR_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define LWR_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef LWR_NO_EXPORT
#    define LWR_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef LWR_DEPRECATED
#  define LWR_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef LWR_DEPRECATED_EXPORT
#  define LWR_DEPRECATED_EXPORT LWR_EXPORT LWR_DEPRECATED
#endif

#ifndef LWR_DEPRECATED_NO_EXPORT
#  define LWR_DEPRECATED_NO_EXPORT LWR_NO_EXPORT LWR_DEPRECATED
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define LWR_NO_DEPRECATED
#endif

#endif
