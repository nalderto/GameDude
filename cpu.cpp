#include "cpu.hpp"

#define VRAM_SIZE 8192
#define WRAM_SIZE 8192
#define IO_REG_SIZE 0x7F
#define HRAM_SIZE 0x7F
#define CART_ROM_SIZE 16384

class CPU {
    unsigned char wram[WRAM_SIZE];
    unsigned char vram[VRAM_SIZE];
    unsigned char ioReg[IO_REG_SIZE];
    unsigned char hram[HRAM_SIZE];

    unsigned char interruptReg;

    unsigned char cartRom[CART_ROM_SIZE];

    // Register structure from CTurt
    // https://cturt.github.io/cinoop.html
    struct registers {
        struct {
            union {
                struct {
                    unsigned char f; // Flag Register
                    unsigned char a; // Accumulator
                };
                unsigned short af;
            };
        };

        struct {
            union {
                struct {
                    unsigned char c;
                    unsigned char b;
                };
                unsigned short bc;
            };
        };

        struct {
            union {
                struct {
                    unsigned char e;
                    unsigned char d;
                };
                unsigned short de;
            };
        };

        struct {
            union {
                struct {
                    unsigned char l;
                    unsigned char h;
                };
                unsigned short hl;
            };
        };

        unsigned short sp; // Stack Pointer
        unsigned short pc; // Program Counter
    };

    bool loadGame(std::string fileName) {
        FILE *fp;
        try {
            fp = fopen(fileName.c_str(), "rb");

            if (fp == NULL) {
                return false;
            }

            int i = 0;
            while (!feof(fp)) {
                fread(&cartRom[i], sizeof(unsigned char), 1, fp);
                i++;
            }
            return true;
        }
        catch (int e) {
            return false;
        }
    };

    void read(unsigned short address) {
        if (0x0000 <= address && address < 0x8000) {
            return cartRom[address];
        }
        else if (0x8000 <= address && address < 0xA000) {
            return vram[address - 0x8000];
        }
        else if (0xC000 <= address && address < 0xE000) {
            return wram[address - 0xC000];
        }
        else if (0xE000 <= address && address < 0xFE00) {
            return wram[address - 0xE000];
        }
        else if (0xFF80 <= address && address < 0xFFFF) {
            return hram[address - 0xFF80];
        }
        else if (address == 0xFFFF) {
            return 
        }

    }

    void write(unsigned short address, unsigned char value) {
        if (0x8000 <= address && address < 0xA000) {
            vram[address - 0x8000] = value;
        }
        else if (0xC000 <= address && address < 0xE000) {
            wram[address - 0xC000] = value;
        }
        else if (0xE000 <= address && address < 0xFE00) {
            wram[address - 0xE000] = value;
        }
    }
};
