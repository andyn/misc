#ifndef NIH_BIT_H_
#define NIH_BIT_H_

// bit.h
//
// Bit twiddling hacks. Many ideas lifted from the internets
// and compiled into one (hopefully) coherent library
//
// Sources:
// https://graphics.stanford.edu/~seander/bithacks.html 
//
// Compiled into single file by:
// Antti Nilakari <antti.nilakari@gmail.com>

// Return 1 for positive and zero values, -1 for negative ones
#define BIT_SIGN(x) (+1 | ((x) >> (sizeof(x) * CHAR_BIT - 1)))

// Return 1 for positive values, 0 for zero, -1 for negative ones
#define BIT_SIGN_OR_ZERO(x) (((x) > 0) - ((x) < 0))

// Return nonzero if signs are opposite, zero otherwise
#define BIT_SIGN_IS_OPPOSITE(x, y) (((x) ^ (y)) < 0)

// Return the absolute value of an integer
#define BIT_ABS(x) (((x) ^ ((x) >> sizeof(x) * CHAR_BIT - 1)) - (x >> sizeof(x) * CHAR_BIT - 1));

// Return the minimum of two integers
#define BIT_MIN(x, y) ((y) ^ (((x) ^ (y)) & -((x) < (y))))

// Return the maximum of two integers
#define BIT_MAX(x, y) ((x) ^ (((x) ^ (y)) & -((x) < (y))))

// Return nonzero, if an unsigned integer is a power of two, zero otherwise
#define BIT_IS_POW2(x) ((x) && !((x) & ((x) - 1)))

// Return nonzero, if an unsigned integer is a power of two, zero otherwise
#define BIT_IS_POW2(x) ((x) && !((x) & ((x) - 1)))




#endif // NIH_BIT_H_
