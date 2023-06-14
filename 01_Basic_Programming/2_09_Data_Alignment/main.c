#include <stdio.h>
#include <stdint.h>

struct STRUCT_t
{
    uint64_t b;
    uint16_t a;
    uint8_t c;
} __attribute__((packed));

int main()
{
    printf("%ld", sizeof(struct STRUCT_t));
}


