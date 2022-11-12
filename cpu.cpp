#include "cpu.hpp"

void CPU::cycle() {
    uint8_t opcode = readMem(pc);

    switch (opcode) {

        // LD r1,r2
        case 0x40: case 0x41: case 0x42: case 0x43: case 0x44: case 0x45: case 0x47: // ld b,reg
        case 0x48: case 0x49: case 0x4a: case 0x4b: case 0x4c: case 0x4d: case 0x4f: // ld c,reg
        case 0x50: case 0x51: case 0x52: case 0x53: case 0x54: case 0x55: case 0x57: // ld d,reg
        case 0x58: case 0x59: case 0x5a: case 0x5b: case 0x5c: case 0x5d: case 0x5f: // ld e,reg
        case 0x60: case 0x61: case 0x62: case 0x63: case 0x64: case 0x65: case 0x67: // ld h,reg
        case 0x68: case 0x69: case 0x6a: case 0x6b: case 0x6c: case 0x6d: case 0x6f: // ld l,reg
        case 0x78: case 0x79: case 0x7a: case 0x7b: case 0x7c: case 0x7d: case 0x7f: // ld a,reg
        {
            reg[opcode >> 3 & 7] = reg[opcode & 7];
            break;
        }

        // LD nn,n
        case 0x06: case 0x0E: case 0x16: case 0x1E: case 0x26: case 0x2E:
        {
            pc++;
            uint8_t byte = readMem(pc);
            reg[opcode % 8] = byte;
            break;
        }

        // LD reg, reg
        case 0x7E: case 0x46: case 0x4E: case 0x56: case 0x5E: case 0x66: case 0x6E:
        {
            short hl = (reg[5] << 8) | reg[4];
            if (opcode == 0x7E) {
                reg[7] = hl;
            }
            else {
                reg[opcode - 0x46 % 8] = hl;
            }
            break;
        }

        // LD (HL), reg
        case 0x70: case 0x71: case 0x72: case 0x73: case 0x74: case 0x75: {
            reg[4] = reg[opcode - 0x70];
            reg[5] = 0;
            break;
        }
        
        // LD (HL),n
        case 0x36:
        {
            pc++;
            uint8_t byte = readMem(pc);
            reg[4] = byte;
            reg[5] = 0;
            break;
        }

        // LD A, (BC)
        case 0x0A: {
            reg[7] = reg[0];
            break;
        }

        // LD A, (DE)
        case 0x1A: {
            reg[7] = reg[2];
            break;
        }

        // LD A, (nn)
        case 0xFA: {
            pc++;
            uint8_t byte = readMem(pc);
            reg[7] = byte;
            break;
        }

        // LD A, #
        case 0x3E: {
            pc++;
            uint8_t byte = readMem(pc);
            pc++;
            reg[7] = byte;
            break;
        }

        // LD (BC),A
        case 0x02: {
            reg[0] = reg[7];
            reg[1] = 0;
            break;
        }

        // LD (DE),A
        case 0x12: {
            reg[2] = reg[7];
            reg[3] = 0;
            break;
        }

        // LD (BC),A
        case 0x77: {
            reg[4] = reg[7];
            reg[5] = 0;
            break;
        }

        // LD (nn),A
        case 0xEA: {
            reg[0] = reg[7];
            reg[1] = 0;
            break;
        }
    }
}


bool CPU::loadGame(std::string fileName) {
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
}

uint8_t CPU::readMem(uint16_t address) {
    if (0x0000 <= address && address < 0x8000) {
        return cartRom[address];
    } else if (0x8000 <= address && address < 0xA000) {
        return vram[address - 0x8000];
    } else if (0xC000 <= address && address < 0xE000) {
        return wram[address - 0xC000];
    } else if (0xE000 <= address && address < 0xFE00) {
        return wram[address - 0xE000];
    } else if (0xFEA0 <= address && address <= 0xFEFF) {
        return 0;
    } else if (0xFF80 <= address && address < 0xFFFF) {
        return hram[address - 0xFF80];
    } else if (address == 0xFFFF) {
        return interruptReg;
    } else {
        throw std::invalid_argument("Invalid read address");
    }
}

bool CPU::writeMem(uint16_t address, uint8_t value) {
    if (0x8000 <= address && address < 0xA000) {
        vram[address - 0x8000] = value;
    }
    else if (0xC000 <= address && address < 0xE000) {
        wram[address - 0xC000] = value;
    }
    else if (0xE000 <= address && address < 0xFE00) {
        wram[address - 0xE000] = value;
    }
    else {
        return false;
    }
    return true;
}
