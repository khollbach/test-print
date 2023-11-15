#include <stdint.h>
#include <assert.h>

typedef uint8_t u8;
typedef int8_t i8;
typedef uint16_t u16;
typedef int16_t i16;

char _read_val; // needed so the compiler doesn't optimize away the read
#define ADDR(a) ((char*)a)
#define READ(a) (_read_val = *ADDR(a))
#define WRITE(a, x) (*ADDR(a) = x)

void test_print();
void print(u8 x, u8 y, u8 c);
u8 ascii_to_2e(u8 c);
u16 coord_to_addr(u8 x, u8 y);

int main() {
    test_print();
    while (1) {}
    return 0;
}

void test_print() {
    u8 x, y, c = 0;
    for (y = 0; y < 24; y++) {
        for (x = 0; x < 40; x++) {
            print(x, y, c);
            if (c == 0xff) {
                c = 0;
            } else {
                c += 1;
            }
        }
    }
}

void print(u8 x, u8 y, u8 c) {
    WRITE(coord_to_addr(x, y), ascii_to_2e(c));
}

u8 ascii_to_2e(u8 c) {
    if (c < 0x20) {
        return 0xff;
    } else if (c >= 0x80) {
        return 0xff;
    } else {
        return c | 0x80;
    }
}

u16 coord_to_addr(u8 x, u8 y) {
    u8 group;
    u16 base, offset;
    assert(x < 40);
    assert(y < 24);

    group = y / 8;
    switch (group) {
    case 0:
        base = 0x400;
        break;
    case 1:
        base = 0x428;
        break;
    case 2:
        base = 0x450;
        break;
    }

    offset = y % 8 * 0x80;

    return base + offset + x;
}
