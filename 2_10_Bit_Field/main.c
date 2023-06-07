#include <stdio.h>
#include <stdint.h>

struct STRUCT_t
{
    uint16_t a : 10;
    uint32_t b : 32;
    uint32_t c : 22;
} __attribute__((packed));

int main()
{
    printf("%ld", sizeof(struct STRUCT_t));
}


