#ifndef ENDIAN_COMPAT_H
#define ENDIAN_COMPAT_H

// Detect platform endianness for Windows (and fallback for others)

#if defined(_WIN32) || defined(_WIN64)

// Windows is usually little endian
#define __LITTLE_ENDIAN 1234
#define __BIG_ENDIAN    4321
#define __BYTE_ORDER    __LITTLE_ENDIAN

#elif defined(__APPLE__)
// macOS and iOS
#include <machine/endian.h>
#define __BYTE_ORDER _BYTE_ORDER

#elif defined(__linux__)
// Linux systems
#include <endian.h>

#else
// Fallback - assume little endian
#define __LITTLE_ENDIAN 1234
#define __BIG_ENDIAN    4321
#define __BYTE_ORDER    __LITTLE_ENDIAN

#endif

// Define macros similar to <endian.h>

#if __BYTE_ORDER == __LITTLE_ENDIAN
  #define IS_LITTLE_ENDIAN 1
  #define IS_BIG_ENDIAN    0
#elif __BYTE_ORDER == __BIG_ENDIAN
  #define IS_LITTLE_ENDIAN 0
  #define IS_BIG_ENDIAN    1
#else
  #define IS_LITTLE_ENDIAN 0
  #define IS_BIG_ENDIAN    0
#endif

// Common functions/macros to convert endianness

#include <stdint.h>

static inline uint16_t htobe16(uint16_t x) {
#if IS_LITTLE_ENDIAN
    return (x >> 8) | (x << 8);
#else
    return x;
#endif
}

static inline uint16_t be16toh(uint16_t x) {
#if IS_LITTLE_ENDIAN
    return (x >> 8) | (x << 8);
#else
    return x;
#endif
}

static inline uint32_t htobe32(uint32_t x) {
#if IS_LITTLE_ENDIAN
    return ((x >> 24) & 0xff) | 
           ((x >> 8) & 0xff00) | 
           ((x << 8) & 0xff0000) | 
           ((x << 24) & 0xff000000);
#else
    return x;
#endif
}

static inline uint32_t be32toh(uint32_t x) {
#if IS_LITTLE_ENDIAN
    return ((x >> 24) & 0xff) | 
           ((x >> 8) & 0xff00) | 
           ((x << 8) & 0xff0000) | 
           ((x << 24) & 0xff000000);
#else
    return x;
#endif
}

static inline uint64_t htobe64(uint64_t x) {
#if IS_LITTLE_ENDIAN
    return ((x >> 56) & 0x00000000000000FFULL) |
           ((x >> 40) & 0x000000000000FF00ULL) |
           ((x >> 24) & 0x0000000000FF0000ULL) |
           ((x >> 8)  & 0x00000000FF000000ULL) |
           ((x << 8)  & 0x000000FF00000000ULL) |
           ((x << 24) & 0x0000FF0000000000ULL) |
           ((x << 40) & 0x00FF000000000000ULL) |
           ((x << 56) & 0xFF00000000000000ULL);
#else
    return x;
#endif
}

static inline uint64_t be64toh(uint64_t x) {
#if IS_LITTLE_ENDIAN
    return ((x >> 56) & 0x00000000000000FFULL) |
           ((x >> 40) & 0x000000000000FF00ULL) |
           ((x >> 24) & 0x0000000000FF0000ULL) |
           ((x >> 8)  & 0x00000000FF000000ULL) |
           ((x << 8)  & 0x000000FF00000000ULL) |
           ((x << 24) & 0x0000FF0000000000ULL) |
           ((x << 40) & 0x00FF000000000000ULL) |
           ((x << 56) & 0xFF00000000000000ULL);
#else
    return x;
#endif
}

#endif // ENDIAN_COMPAT_H
