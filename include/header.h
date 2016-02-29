#ifndef NIH_HEADER_H_
#define NIH_HEADER_H_

// Bit/struct packing and unpacking macros
//
// Helper macros to facilitate packing and unpacking
// data structures and to handle byte order swapping
//
// Author(s):
// Antti Nilakari <antti.nilakari@iki.fi>

#include <inttypes.h>


static inline
void header_pack_u8(void *buffer, uint8_t data) {
	uint8_t *b = buffer;
	b[0] = data;
}

static inline
void header_pack_u16(void *buffer, uint16_t data) {
	uint8_t *b = buffer;
	header_pack_u8(b, (data >> 8) & 0xFF);
	header_pack_u8(b + 1, data & 0xFF);
}

static inline
void header_pack_u16le(void *buffer, uint16_t data) {
	uint8_t *b = buffer;
	header_pack_u8(b, data & 0xFF);
	header_pack_u8(b + 1, (data >> 8) & 0xFF);
}

static inline
void header_pack_u32(void *buffer, uint32_t data) {
	uint8_t *b = buffer;
	header_pack_u16(b, (data >> 16) & 0xFFFF);
	header_pack_u16(b + 2, data & 0xFFFF);
}

static inline
void header_pack_u32le(void *buffer, uint32_t data) {
	uint8_t *b = buffer;
	header_pack_u16le(b, data & 0xFFFF);
	header_pack_u16le(b + 2, (data >> 16) & 0xFFFF);
}

static inline
void header_pack_u64(void *buffer, uint64_t data) {
	uint8_t *b = buffer;
	header_pack_u32(b, (data >> 32) & 0xFFFFFFFF);
	header_pack_u32(b + 4, data & 0xFFFFFFFF);
}

static inline
void header_pack_u64le(void *buffer, uint64_t data) {
	uint8_t *b = buffer;
	header_pack_u32le(b, data & 0xFFFFFFFF);
	header_pack_u32le(b + 4, (data >> 32) & 0xFFFFFFFF);
}


static inline
uint8_t header_unpack_u8(void *buffer) {
	uint8_t *b = buffer;
	return b[0];
}

static inline
uint16_t header_unpack_u16(void *buffer) {
	uint8_t *b = buffer;
	uint16_t value = header_unpack_u8(b);
	value <<= 8;
	value |= header_unpack_u8(b + 1);
	return value;
}

static inline
uint16_t header_unpack_u16le(void *buffer) {
	uint8_t *b = buffer;
	uint16_t value_left = header_unpack_u8(b);
	uint16_t value_right = header_unpack_u8(b + 1);
	value_left |= value_right << 8;
	return value_left;
}

static inline
uint32_t header_unpack_u32(void *buffer) {
	uint8_t *b = buffer;
	uint32_t value = header_unpack_u16(b);
	value <<= 16;
	value |= header_unpack_u16(b + 2);
	return value;
}

static inline
uint32_t header_unpack_u32le(void *buffer) {
	uint8_t *b = buffer;
	uint32_t value_left = header_unpack_u16le(b);
	uint32_t value_right = header_unpack_u16le(b + 2);
	value_left |= value_right << 16;
	return value_left;
}

static inline
uint64_t header_unpack_u64(void *buffer) {
	uint8_t *b = buffer;
	uint64_t value = header_unpack_u32(b);
	value <<= 32;
	value |= header_unpack_u32(b + 4);
	return value;
}

static inline
uint64_t header_unpack_u64le(void *buffer) {
	uint8_t *b = buffer;
	uint64_t value_left = header_unpack_u32le(b);
	uint64_t value_right = header_unpack_u32le(b + 4);
	value_left |= value_right << 32;
	return value_left;
}

#endif // NIH_HEADER_H_