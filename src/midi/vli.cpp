#include "vli.h"
#include "read.h"

namespace io
{
	bool is_msb_set(uint8_t byte)
	{
		return (byte >> 7) == 1;
	}

	uint8_t unset_msb(uint8_t byte)
	{
		return byte & 0b0111'1111;
	}
	uint64_t accumulate(uint64_t acc, uint8_t b)
	{
		return (acc << 7) | unset_msb(b);

	}


}
uint64_t io::read_variable_length_integer(std::istream& in)
{
	uint8_t byte = read<uint8_t>(in);
	uint64_t acc = 0;

	while (is_msb_set(byte))
	{
		acc = accumulate(acc, byte);
		byte = read<uint8_t>(in);
	}
	acc = accumulate(acc, byte);
	return acc;
}