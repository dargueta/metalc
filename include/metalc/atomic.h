/**
 * Basic support for mutexes and other atomic operations.
 *
 * @file atomic.h
 */

#ifndef INCLUDE_METALC_ATOMIC_H_
#define INCLUDE_METALC_ATOMIC_H_

#include "metalc.h"
#include "stdint.h"

typedef uint32_t atomic_t;

typedef struct {
    union {
        uint8_t u8;
        uint16_t u16;
        uint32_t u32;
        uint64_t u64;
        void *pointer;
    } value;
    uint32_t status;
} atomic_object_t;


/**
 * Read the byte stored in the data area of the lock object.
 */
METALC_EXPORT_WITH_ATTR(nonnull) uint8_t atomic_load_8(const atomic_object_t *object);

/**
 * Read the 16-bit integer stored in the data area of the lock object.
 */
METALC_EXPORT_WITH_ATTR(nonnull) uint16_t atomic_load_16(const atomic_object_t *object);

/**
 * Read the 32-bit integer stored in the data area of the lock object.
 */
METALC_EXPORT_WITH_ATTR(nonnull) uint32_t atomic_load_32(const atomic_object_t *object);

/**
 * Read the 64-bit integer stored in the data area of the lock object.
 */
METALC_EXPORT_WITH_ATTR(nonnull) uint64_t atomic_load_64(const atomic_object_t *object);
METALC_EXPORT_WITH_ATTR(nonnull) void atomic_store_8(atomic_object_t *object, uint8_t value);
METALC_EXPORT_WITH_ATTR(nonnull) void atomic_store_16(atomic_object_t *object, uint16_t value);
METALC_EXPORT_WITH_ATTR(nonnull) void atomic_store_32(atomic_object_t *object, uint32_t value);
METALC_EXPORT_WITH_ATTR(nonnull) void atomic_store_64(atomic_object_t *object, uint64_t value);
METALC_EXPORT_WITH_ATTR(nonnull) uint8_t atomic_exchange_8(atomic_object_t *object, uint8_t value);
METALC_EXPORT_WITH_ATTR(nonnull) uint16_t atomic_exchange_16(atomic_object_t *object, uint16_t value);
METALC_EXPORT_WITH_ATTR(nonnull) uint32_t atomic_exchange_32(atomic_object_t *object, uint32_t value);
METALC_EXPORT_WITH_ATTR(nonnull) uint64_t atomic_exchange_64(atomic_object_t *object, uint64_t value);

#endif  /* INCLUDE_METALC_ATOMIC_H_ */
