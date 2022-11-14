#include <string>
#include <map>
#include <stdint.h>

class Cartridge {
    private:
        char title[15];
        char manufacturer[4];

        std::string publisher;
        std::string mapper;

        uint8_t cgbFlag;
        uint8_t sgbFlag;
        uint8_t type;
        uint8_t romCode;
        uint8_t ramCode;
        uint8_t destinationCode;
        uint8_t oldLicenseeCode;
        std::string newLicenseeCode;

        static std::map<uint8_t, std::string> cartridgeTypeMap;
        static std::map<uint8_t, std::string> oldLicenseeMap;
        static std::map<std::string, std::string> newLicenseeMap;

        int romBanks;
        bool ram;
        bool battery;
        bool timer;
        bool rumble;
        bool sensor;
        bool camera;
        bool infrared;
        bool buzzer;

        const uint8_t logo[48] = {0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D,
                                  0x00, 0x0B, 0x03, 0x73, 0x00, 0x83,
                                  0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08,
                                  0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E,
                                  0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD,
                                  0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63,
                                  0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC,
                                  0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E};

        void getPublisher(uint8_t oldLicenseeCode, std::string newLicenseeCode);
};