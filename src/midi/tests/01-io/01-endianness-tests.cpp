#ifdef TEST_BUILD
#define CATCH_CONFIG_PREFIX_ALL

#include "Catch.h"
#include <endianness.h>


namespace
{
    void test_switch_endianness_16bit(uint16_t x, uint16_t expected)
    {
        io::switch_endianness(&x);

        CATCH_CHECK(x == expected);
    }

    void test_switch_endianness_32bit(uint32_t x, uint32_t expected)
    {
        io::switch_endianness(&x);

        CATCH_CHECK(x == expected);
    }

    void test_switch_endianness_64bit(uint64_t x, uint64_t expected)
    {
        io::switch_endianness(&x);

        CATCH_CHECK(x == expected);
    }
}


#define TEST_ENDIANNESS_16(given, expected)   CATCH_TEST_CASE("Switching endianness of " #given " should yield " #expected) { test_switch_endianness_16bit(given, expected); }
#define TEST_ENDIANNESS_32(given, expected)   CATCH_TEST_CASE("Switching endianness of " #given "u should yield " #expected "u") { test_switch_endianness_32bit(given ## u, expected ## u); }
#define TEST_ENDIANNESS_64(given, expected)   CATCH_TEST_CASE("Switching endianness of " #given "ul should yield " #expected "ul") { test_switch_endianness_64bit(given ## ul, expected ## ul); }

TEST_ENDIANNESS_16(0x0000, 0x0000)
TEST_ENDIANNESS_16(0x0001, 0x0100)
TEST_ENDIANNESS_16(0x0100, 0x0001)
TEST_ENDIANNESS_16(0x1000, 0x0010)
TEST_ENDIANNESS_16(0x0054, 0x5400)
TEST_ENDIANNESS_16(0x1234, 0x3412)

TEST_ENDIANNESS_32(0x00000000, 0x00000000)
TEST_ENDIANNESS_32(0x00000001, 0x01000000)
TEST_ENDIANNESS_32(0x00000010, 0x10000000)
TEST_ENDIANNESS_32(0x00000100, 0x00010000)
TEST_ENDIANNESS_32(0x00001000, 0x00100000)
TEST_ENDIANNESS_32(0x00010000, 0x00000100)
TEST_ENDIANNESS_32(0x00100000, 0x00001000)
TEST_ENDIANNESS_32(0x01000000, 0x00000001)
TEST_ENDIANNESS_32(0x10000000, 0x00000010)
TEST_ENDIANNESS_32(0xAABBCCDD, 0xDDCCBBAA)
TEST_ENDIANNESS_32(0x12345678, 0x78563412)

TEST_ENDIANNESS_64(0x00000000, 0x00000000)
TEST_ENDIANNESS_64(0x00000001, 0x0100000000000000)
TEST_ENDIANNESS_64(0x00000010, 0x1000000000000000)
TEST_ENDIANNESS_64(0x00000100, 0x0001000000000000)
TEST_ENDIANNESS_64(0x00001000, 0x0010000000000000)
TEST_ENDIANNESS_64(0x00010000, 0x0000010000000000)
TEST_ENDIANNESS_64(0x00100000, 0x0000100000000000)
TEST_ENDIANNESS_64(0x01000000, 0x0000000100000000)
TEST_ENDIANNESS_64(0x10000000, 0x0000001000000000)
TEST_ENDIANNESS_64(0xAABBCCDD, 0xDDCCBBAA00000000)
TEST_ENDIANNESS_64(0x12345678, 0x7856341200000000)
TEST_ENDIANNESS_64(0x1234567812345678, 0x7856341278563412)
TEST_ENDIANNESS_64(0x1122334455667788, 0x8877665544332211)

#endif
