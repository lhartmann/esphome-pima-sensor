#include <stdint.h>
#include <iostream>

class PimaFrameDecoder {
    constexpr unsigned bufflen{128};
    uint8_t buffer[bufflen];
    uint8_t i, left;
    static constexpr uint8_t offset_length = 7;

    bool is_valid() {
        uint8_t payload = buffer[offset_length];
        if (payload > bufflen-10)
            return false;

        uint16_t acc = 0;
        uint16_t P = 0xA001;
        for (int i=2; i < payload+10-2; i++) {
            acc ^= (buffer[i] & 0xff);
            acc = (acc >> 1) ^ (acc & 1 ? P : 0);
            acc = (acc >> 1) ^ (acc & 1 ? P : 0);
            acc = (acc >> 1) ^ (acc & 1 ? P : 0);
            acc = (acc >> 1) ^ (acc & 1 ? P : 0);
            acc = (acc >> 1) ^ (acc & 1 ? P : 0);
            acc = (acc >> 1) ^ (acc & 1 ? P : 0);
            acc = (acc >> 1) ^ (acc & 1 ? P : 0);
            acc = (acc >> 1) ^ (acc & 1 ? P : 0);
        }

        uint16_t crc = 0x100 * buffer[payload+9] + buffer[payload+8];
        if (crc != acc) 
            std::cerr << "Bad CRC: Packed " << crc << ", calculated " << acc << ".\n";
        
        return crc == acc;
    }

    public:
    PimaFrameDecoder() {
        i = left = 0;
    }

    bool operator() (uint8_t ch) {
        if (i < bufflen)
            buffer[i++] = ch;

        if (left) {
            if (--left)
                return false;

            // Prepare for next
            i = 0;

            if (is_valid())
                return true;

            return false;
        }

        // Sync:
        if (i==2 && ch != 0x55) {
            i=1;
        }

        if (i==1 && ch != 0xAA) {
            i=0;
            return false; 
        }
        
        // Wait for packet length
        if (i <= offset_length)
            return false;
        
        // Got length
        left = ch + 2;

        return false;
    }

    // Queries
    uint64_t bcd(uint8_t offset, uint8_t len) const {
        const uint8_t *p = buffer + offset;
        uint64_t acc = 0;
        while (len--) {
            acc *= 100;

            acc += *p / 16 * 10;
            acc += *p++ & 15;
        }
        return acc;
    }

    // Emulate vector, string and array.
    const uint8_t *data() const {
        return buffer;
    }
    uint8_t operator[] (size_t i) const {
        return buffer[i];
    }
    size_t size() {
        return buffer[offset_length]+10;
    }

    // PIMA-specific
    uint64_t id() const {
        return bcd(2, 5);
    }
    uint8_t scope() const {
        return buffer[8];
    }
    uint8_t index() const {
        return buffer[9];
    }
    const uint8_t *payload() const {
        // Skipping scope and index
        return buffer+10;
    }
    size_t payload_size() const {
        return buffer[offset_length]-2;
    }
    uint64_t payload_bcd(size_t begin, size_t len) const {
        return bcd(10+begin, len);
    }
    uint64_t payload_bcd() const {
        return payload_bcd(0, payload_size());
    }
};
