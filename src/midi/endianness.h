#ifndef EDIANNESS_H
#define EDIANNESS_H

#include <cstdint>
namespace io {
	void switch_endianness(uint16_t* n);
	void switch_endianness(uint32_t* n);
	void switch_endianness(uint64_t* n);
}

#endif // !EDIANNESS_H