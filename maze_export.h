
#ifndef MAZE_EXPORT_H
#define MAZE_EXPORT_H

#ifdef MAZE_STATIC_DEFINE
#  define MAZE_EXPORT
#  define MAZE_NO_EXPORT
#else
#  ifndef MAZE_EXPORT
#    ifdef maze_EXPORTS
        /* We are building this library */
#      define MAZE_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define MAZE_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef MAZE_NO_EXPORT
#    define MAZE_NO_EXPORT 
#  endif
#endif

#ifndef MAZE_DEPRECATED
#  define MAZE_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef MAZE_DEPRECATED_EXPORT
#  define MAZE_DEPRECATED_EXPORT MAZE_EXPORT MAZE_DEPRECATED
#endif

#ifndef MAZE_DEPRECATED_NO_EXPORT
#  define MAZE_DEPRECATED_NO_EXPORT MAZE_NO_EXPORT MAZE_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef MAZE_NO_DEPRECATED
#    define MAZE_NO_DEPRECATED
#  endif
#endif

#endif /* MAZE_EXPORT_H */
