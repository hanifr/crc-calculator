#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>

// Calculate Modbus CRC-16
uint16_t calculateCRC(const std::vector<uint8_t>& data) {
    uint16_t crc = 0xFFFF;
    
    for (uint8_t byte : data) {
        crc ^= byte;
        
        for (int i = 0; i < 8; i++) {
            if (crc & 0x0001) {
                crc = (crc >> 1) ^ 0xA001;
            } else {
                crc >>= 1;
            }
        }
    }
    
    return crc;
}

// Convert hex string to bytes
std::vector<uint8_t> hexStringToBytes(const std::string& hex) {
    std::vector<uint8_t> bytes;
    std::string cleanHex = hex;
    
    // Remove spaces
    cleanHex.erase(remove(cleanHex.begin(), cleanHex.end(), ' '), cleanHex.end());
    
    for (size_t i = 0; i < cleanHex.length(); i += 2) {
        std::string byteString = cleanHex.substr(i, 2);
        uint8_t byte = static_cast<uint8_t>(strtol(byteString.c_str(), nullptr, 16));
        bytes.push_back(byte);
    }
    
    return bytes;
}

// Print bytes as hex
void printHex(const std::vector<uint8_t>& data, uint16_t crc) {
    for (uint8_t byte : data) {
        std::cout << std::hex << std::uppercase << std::setfill('0') 
                  << std::setw(2) << static_cast<int>(byte) << " ";
    }
    
    // Print CRC (Low byte first, then High byte)
    std::cout << std::setw(2) << static_cast<int>(crc & 0xFF) << " "
              << std::setw(2) << static_cast<int>((crc >> 8) & 0xFF);
    std::cout << std::dec << std::endl;
}

int main() {
    std::cout << "=======================================" << std::endl;
    std::cout << "     Modbus RTU CRC Calculator" << std::endl;
    std::cout << "=======================================" << std::endl;
    
    while (true) {
        std::cout << "\nEnter hex bytes (space separated, e.g., 37 03 00 00 00 0A)" << std::endl;
        std::cout << "Or type 'exit' to quit" << std::endl;
        std::cout << "> ";
        
        std::string input;
        std::getline(std::cin, input);
        
        if (input == "exit" || input == "quit") {
            break;
        }
        
        if (input.empty()) {
            continue;
        }
        
        try {
            // Convert input to bytes
            std::vector<uint8_t> data = hexStringToBytes(input);
            
            if (data.empty()) {
                std::cout << "ERROR: Invalid input" << std::endl;
                continue;
            }
            
            // Calculate CRC
            uint16_t crc = calculateCRC(data);
            
            // Display results
            std::cout << "\nInput:          ";
            for (uint8_t byte : data) {
                std::cout << std::hex << std::uppercase << std::setfill('0') 
                          << std::setw(2) << static_cast<int>(byte) << " ";
            }
            std::cout << std::dec << std::endl;
            
            std::cout << "CRC (hex):      " << std::hex << std::uppercase 
                      << std::setfill('0') << std::setw(4) << crc << std::dec << std::endl;
            std::cout << "CRC Low Byte:   " << std::hex << std::uppercase 
                      << std::setfill('0') << std::setw(2) << (crc & 0xFF) << std::dec << std::endl;
            std::cout << "CRC High Byte:  " << std::hex << std::uppercase 
                      << std::setfill('0') << std::setw(2) << ((crc >> 8) & 0xFF) << std::dec << std::endl;
            
            std::cout << "\nComplete Command: ";
            printHex(data, crc);
            
        } catch (...) {
            std::cout << "ERROR: Failed to parse input" << std::endl;
        }
    }
    
    std::cout << "\nGoodbye!" << std::endl;
    return 0;
}
