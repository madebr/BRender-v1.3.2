#ifndef COMPILER_H
#define COMPILER_H

#if defined(__GNUC__) || defined(__clang__)
#  define ALIGN(x) __attribute__ ((aligned(x)))
#elif defined(_MSC_VER)
#  define ALIGN(x) __declspec(align(x))
#elif defined(__WATCOMC__)
#  define ALIGN(x)
// Watcom uses "#pragma pack(push,N)" and "#pragma pack(pop)"
#else
#  error "Unknown compiler; can't define ALIGN"
#endif

#endif
