#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstdio> // Ajout de cette bibliothèque pour utiliser la fonction remove()

std::string toHex(unsigned char byte) {
    std::stringstream ss;
    ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    return ss.str();
}

std::string getFileHexDump(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return "";
    }

    std::ostringstream oss;

    unsigned char byte;
    while (file.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
        oss << toHex(byte);
    }

    return oss.str();
}

void removeFile(const std::string& filename) {
    std::remove(filename.c_str());
}

int main() {
    std::string filename = "exe.exe";
    std::string hexDump = getFileHexDump(filename);

    std::string outputFilename = "hex.txt";

    removeFile(outputFilename); // Supprime le fichier s'il existe déjà

    std::ofstream outputFile(outputFilename);
    if (outputFile) {
        outputFile << hexDump;
        outputFile.close();
        std::cout << "Hex dump saved to " << outputFilename << std::endl;
    }
    else {
        std::cerr << "Failed to create " << outputFilename << std::endl;
    }

    return 0;
}
