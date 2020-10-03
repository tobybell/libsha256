# libsha256

A minimal library for computing SHA 256 digests.

I created this library because I wanted to have a SHA 256 implementation I
could tinker with and integrate easily into other tools for distributed
computing.

The implementation in this library is based on the SHA 256 implementation from
[Git](https://git-scm.com).

You're welcome to use it if you like.

## Usage

This library has two main usage modes---one-shot and incremental.

#### 1. One-shot hashing

In one-shot usage, you can compute the digest for a buffer of data you already
have in its entirety. In this case, declare a `sha256_digest` object to store
the digest and call `sha256`. For example:

```c
// Get your data (from somewhere...)
size_t len = ...;
void *data = ...;

// Hash it and use the digest.
sha256_digest d;
sha256(&d, data, len);
do_shit_with(&d);
```

#### 2. Incremental hashing

In incremental usage, you can compute the digest progressively over incoming
ranges of data. In this case, declare a `sha256_ctx` context object first, and
use the `sha256_init`, `sha256_update`, and `sha256_final` functions on it to
process data. For example:

```c
// Create a context.
sha256_ctx c;
sha256_init(&c);

// Process data segments.
sha256_update(&c, "Hello", 5);
sha256_update(&c, ", ", 2);
sha256_update(&c, "world!", 6);

// Extract and use the digest.
sha256_digest d;
sha256_final(&d, &c);
do_shit_with(&d);
```

## Installation

You're on your own here. I built this project usng `clang` and `make`, so if
you have those installed, it-will-probably-just-work. Shouldn't be too hard to
be build it yourself using other tools, though.

## License

This software is provided under the [MIT License](LICENSE). Go wild.
