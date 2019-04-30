#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <time.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 

#define MAX 10
#define LEN_STR 12

uint32_t generate_number();
uint32_t decode_varint(const uint8_t** bufp);
size_t encode_varint(uint32_t value, uint8_t* buf);

int main()
{
	srand(time(NULL));

	FILE* uncompressed_file;
	FILE* compressed_file;
	uncompressed_file = fopen("uncompressed.dat", "wr");
	compressed_file = fopen("bin_compressed.dat", "wr");

	uint8_t* buf = (uint8_t *)malloc(sizeof(int));

	uint32_t rand_numb;
	for (int i = 0; i < MAX; i++) {
		rand_numb = generate_number();
		fprintf(uncompressed_file, "%d ", rand_numb);
		size_t count = encode_varint(rand_numb, buf);
		for (int i = 0; i < count; i++) {
			fprintf(compressed_file, BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(*(buf + i)));
		}
		fprintf(compressed_file, " ");
	}

	fclose(compressed_file);
	fclose(uncompressed_file);

    return 0;	
}              


size_t encode_varint(uint32_t value, uint8_t* buf)
{
    assert(buf != NULL);
    uint8_t* cur = buf;
    while (value >= 0x80) {
        const uint8_t byte = (value & 0x7f) | 0x80;
        *cur = byte;
        value >>= 7;
        ++cur;
    }
    *cur = value;
    ++cur;
    return cur - buf;
}

uint32_t decode_varint(const uint8_t** bufp)
{
    const uint8_t* cur = *bufp;
    uint8_t byte = *cur++;
    uint32_t value = byte & 0x7f;
    size_t shift = 7;
    while (byte >= 0x80) {
        byte = *cur++;
        value += (byte & 0x7f) << shift;
        shift += 7;
    }
    *bufp = cur;
    return value;
}

/*
 * Диапазон             Вероятность
 * -------------------- -----------
 * [0; 128)             90%
 * [128; 16384)         5%
 * [16384; 2097152)     4%
 * [2097152; 268435455) 1%
 */
uint32_t generate_number()
{
    const int r = rand();
    const int p = r % 100;
    if (p < 90) {
        return r % 128;
    }
    if (p < 95) {
        return r % 16384;
    }
    if (p < 99) {
        return r % 2097152;
    }
    return r % 268435455;
}