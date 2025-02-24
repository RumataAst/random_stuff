#include <iostream>
#include <fstream>

int main(void) {
    std::ifstream   iFile;
    std::string     line = "";
    int             location = 0;
    int             start = 0;

    try {
        iFile.open("data.csv");
        if (!iFile.is_open()) {
            throw std::runtime_error("File could not be opened.");
        }
    }
    catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    std::cout << "starting to read from file\n";
    while (getline(iFile, line)) {
        if (line.empty()) {
            continue;
        }
        start = 0;
        location = line.find(',');
        while (location != std::string::npos) {
            std::cout << "Word : " << line.substr(start, location - start) << std::endl;
            start = location + 1;
            location = line.find(',', start);
        }
        std::cout << "Word : " << line.substr(start) << std::endl;

    }

    iFile.close();
    return 0;
}