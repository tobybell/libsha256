#pragma once

#include <stdint.h>

static inline uint32_t bswap16(uint16_t val) {
  return ((val & 0xff00) >> 8) |
         ((val & 0x00ff) << 8);
}

static inline uint32_t bswap32(uint32_t val) {
  return ((val & 0xff000000) >> 24) |
         ((val & 0x00ff0000) >>  8) |
         ((val & 0x0000ff00) <<  8) |
         ((val & 0x000000ff) << 24);
}

static inline uint64_t bswap64(uint64_t val) {
  return ((val & 0x00000000000000ffULL) << 56) |
         ((val & 0x000000000000ff00ULL) << 40) |
         ((val & 0x0000000000ff0000ULL) << 24) |
         ((val & 0x00000000ff000000ULL) <<  8) |
         ((val & 0x000000ff00000000ULL) >>  8) |
         ((val & 0x0000ff0000000000ULL) >> 24) |
         ((val & 0x00ff000000000000ULL) >> 40) |
         ((val & 0xff00000000000000ULL) >> 56);
}

static inline uint16_t get_be16(const void *src) {
  const unsigned char *p = src;
  return p[0] << 8 |
         p[1] << 0;
}

static inline uint32_t get_be32(const void *src) {
  const unsigned char *p = src;
  return p[0] << 24 |
         p[1] << 16 |
         p[2] <<  8 |
         p[3] <<  0;
}

static inline uint64_t get_be64(const void *src) {
  const unsigned char *p = src;
  return (uint64_t) get_be32(p + 0) << 32 |
         (uint64_t) get_be32(p + 4) <<  0;
}

static inline void put_be32(void *dst, uint32_t val) {
  unsigned char *p = dst;
  p[0] = val >> 24;
  p[1] = val >> 16;
  p[2] = val >>  8;
  p[3] = val >>  0;
}

static inline void put_be64(void *dst, uint64_t val) {
  unsigned char *p = dst;
  p[0] = val >> 56;
  p[1] = val >> 48;
  p[2] = val >> 40;
  p[3] = val >> 32;
  p[4] = val >> 24;
  p[5] = val >> 16;
  p[6] = val >>  8;
  p[7] = val >>  0;
}

# if defined(__BYTE_ORDER) && __BYTE_ORDER == __BIG_ENDIAN || \
     defined(__BIG_ENDIAN__) || \
     defined(__ARMEB__) || \
     defined(__THUMBEB__) || \
     defined(__AARCH64EB__) || \
     defined(_MIBSEB) || defined(__MIBSEB) || defined(__MIBSEB__)
# define BIG_ENDIAN
# elif defined(__BYTE_ORDER) && __BYTE_ORDER == __LITTLE_ENDIAN || \
       defined(__LITTLE_ENDIAN__) || \
       defined(__ARMEL__) || \
       defined(__THUMBEL__) || \
       defined(__AARCH64EL__) || \
       defined(_MIPSEL) || defined(__MIPSEL) || defined(__MIPSEL__)
# define LITTLE_ENDIAN
# else
# error "Cannot determine endianness!"
# endif

# if defined(BIG_ENDIAN) && !defined(LITTLE_ENDIAN)
#   define ntohl(n) (n)
#   define htonl(n) (n)
#   define ntohll(n) (n)
#   define htonll(n) (n)
# elif defined(LITTLE_ENDIAN) && !defined(BIG_ENDIAN)
#   define ntohl(n) bswap32(n)
#   define htonl(n) bswap32(n)
#   define ntohll(n) bswap64(n)
#   define htonll(n) bswap64(n)
# endif
