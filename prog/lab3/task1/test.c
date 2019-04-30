#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/time.h>

#define MAX 2

size_t encode_varint(uint32_t value, uint8_t* buf);
uint32_t generate_number();
uint32_t decode_varint(const uint8_t** bufp);

int main()
{
    system("clear");
	srand(time(NULL));

	FILE* uncompressed_file;
	FILE* compressed_file;
	uncompressed_file = fopen("uncompressed.dat", "wb");
    if (uncompressed_file == NULL) {
        printf("Erorr opening file\n");
        return -1;
    }
	compressed_file = fopen("compressed.dat", "wb");
    if (compressed_file == NULL) {
        printf("Erorr opening file\n");
        return -1;
    }

    uint32_t numb = 5478;
    uint32_t numb_2 = 6540;

    fwrite(&numb, sizeof(uint32_t), 1, uncompressed_file);
    fwrite(&numb_2, sizeof(uint32_t), 1, uncompressed_file);

    uint8_t* buf = (uint8_t *)&numb;
    uint8_t* buf_2 = (uint8_t *)&numb_2;
    encode_varint(numb, buf);
    encode_varint(numb_2, buf_2);

    fwrite(buf, sizeof(uint8_t), 1, compressed_file);

    fwrite(buf_2, sizeof(uint8_t), 1, compressed_file);
    fwrite(buf_2 + 1, sizeof(uint8_t), 1, compressed_file);

    rewind(compressed_file);

    fread(buf, sizeof(uint8_t), 1, compressed_file);
    fread(buf + 1, sizeof(uint8_t), 1, compressed_file);
    fread(buf + 2, sizeof(uint8_t), 1, compressed_file);

    const uint8_t** bufp = (const uint8_t**)&buf;
    printf("%d\n", decode_varint(bufp));

	fclose(uncompressed_file);
	fclose(compressed_file);

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