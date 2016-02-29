#ifndef NIH_SWAP_H_
#define NIH_SWAP_H_

// swap.h
//
// An efficient swap function and a type safe macro for calling it.
// GDB disassembly shows that the code inlines to simple register
// swaps as needed.
//
// Author(s):
// Antti Nilakari <antti.nilakari@gmail.com>

#include <stddef.h> // size_t
#include <string.h> // memcpy

// Expose the macro as a pseudo-function to doxygen
#ifdef DOXYGEN

// For documentation only
typedef void *T;

/// @short Swap two addressable objects. Implemented as a macro.
/// @param left object to swap
/// @param right object to swap
void swap(T left, T right);

#else

// Worker inline function.
// Inlines to register operations if optimization is enabled.
static inline
void swap(void *left, void *right,
          void *restrict left_temp, void *restrict right_temp,
          size_t size) {
    // Read - modify - write paradigm. No modifications here, though.
    memcpy(left_temp, left, size);
    memcpy(right_temp, right, size);
    memcpy(right, left_temp, size);
    memcpy(left, right_temp, size);
}

#endif


// Caller macro. The ternary expressions ensure that the types
// are cross-assignable, and sizeof in array initializers
// ensure that the parameter sizes are the same.
#define swap(LEFT, RIGHT) \
(swap)( \
    1 ? &(LEFT) : ((LEFT) = (RIGHT), NULL), \
    1 ? &(RIGHT) : ((RIGHT) = (LEFT), NULL), \
    (char[sizeof(LEFT)]) {[sizeof(LEFT) - sizeof(RIGHT)] = 0}, \
    (char[sizeof(RIGHT)]) {[sizeof(RIGHT) - sizeof(LEFT)] = 0}, \
    sizeof(LEFT))

#endif // NIH_SWAP_H_
