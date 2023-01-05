#ifdef __POWERPC__
# ifndef _BIG_ENDIAN_
#  define _BIG_ENDIAN_
# endif
# undef _LITTLE_ENDIAN_
# ifdef __ppc64__
#  define __WORDSIZE 64
# else
#  define __WORDSIZE 32
# endif
# ifdef __APPLE__
#  define _MAC_OSX_
# endif
#else
# ifndef _LITTLE_ENDIAN_
#  define _LITTLE_ENDIAN_
# endif
# undef _BIG_ENDIAN_
# ifndef _WIN32
#  ifdef __APPLE__
#   define _MAC_OSX_
#  else
#   define _X86_LINUX_
#  endif
#  define __WORDSIZE 64
# endif
#endif
