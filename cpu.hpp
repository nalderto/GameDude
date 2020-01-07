#define VRAM_SIZE 8192
#define WRAM_SIZE 8192
#define IO_REG_SIZE 0x7F
#define HRAM_SIZE 0x7F
#define CRAM_SIZE 0x7F
#define CART_ROM_SIZE 16384

class CPU {



    unsigned char wram[WRAM_SIZE]; // Working RAM
    unsigned char vram[VRAM_SIZE]; // Video RAM
    unsigned char ioReg[IO_REG_SIZE]; // I/O Registers
    unsigned char hram[HRAM_SIZE]; // High RAM
    unsigned char cram[CRAM_SIZE]; // Optional Cartidge RAM

    unsigned char interruptReg; // Interrupt Enabled Register (0xFFFF)

    unsigned char cartRom[CART_ROM_SIZE]; // Game ROM

    unsigned char reg[8]; // B, C, D, E, H, L, F, A

    unsigned short sp; // Stack Pointer
    unsigned short pc; // Program Counter
}