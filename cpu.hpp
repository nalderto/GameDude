#include <stdint.h>
#include <string>
#include <stdexcept>

#define VRAM_SIZE 8192
#define WRAM_SIZE 8192
#define IO_REG_SIZE 0x7F
#define HRAM_SIZE 0x7F
#define CRAM_SIZE 0x7F
#define CART_ROM_SIZE 16384

class CPU {
    uint8_t wram[WRAM_SIZE]; // Working RAM
    uint8_t vram[VRAM_SIZE]; // Video RAM
    uint8_t ioReg[IO_REG_SIZE]; // I/O Registers
    uint8_t hram[HRAM_SIZE]; // High RAM
    uint8_t cram[CRAM_SIZE]; // Optional Cartidge RAM

    uint8_t interruptReg; // Interrupt Enabled Register (0xFFFF)

    uint8_t cartRom[CART_ROM_SIZE]; // Game ROM

    uint8_t reg[8]; // B, C, D, E, H, L, F, A

    uint16_t sp; // Stack Pointer
    uint16_t pc; // Program Counter


    // Functions
    void cycle();
    bool loadGame(std::string fileName);
    uint8_t readMem(uint16_t address);
    bool writeMem(uint16_t address, uint8_t value);
};