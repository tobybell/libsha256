#pragma once

#include <stddef.h>
#include <stdint.h>

#define SHA256_BLKSIZE 64
#define SHA256_DIGESTSIZE 32

struct sha256_ctx {
	uint32_t state[8];
	uint64_t size;
	uint32_t offset;
	uint8_t buf[SHA256_BLKSIZE];
};

struct sha256_digest {
  uint8_t buf[SHA256_DIGESTSIZE];
};

typedef struct sha256_ctx sha256_ctx;
typedef struct sha256_digest sha256_digest;

/** Hash some data, all at once. */
void sha256(sha256_digest *out, void* data, size_t len);

/** Initialize a new SHA 256 context for incremental hashing. */
void sha256_init(sha256_ctx *ctx);

/** Update a SHA 256 context with new data. */
void sha256_update(sha256_ctx *ctx, const void *data, size_t len);

/** Extract the final digest from a context. */
void sha256_final(sha256_digest* out, sha256_ctx *ctx);
