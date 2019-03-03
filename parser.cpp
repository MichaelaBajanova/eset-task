//
// Created by Michaela Bajanová on 25/02/2019.
//

#include "parser.h"

std::string& Parser::cutChildFiles(std::string& filePath) {
    size_t i = 0;
    while (filePath[i] != ' ') {
        ++i;
    }
    filePath = filePath.substr(0, i);
    return filePath;
}

std::set<std::string>& Parser::getPackers(const std::string& filePath, std::set<std::string>& packers) {
    size_t i = 0;
    size_t end = 0;
    std::string string;
    bool isFile;
    unsigned count = 0;
    while ((i = filePath.find("»", end)) != std::string::npos) {
        ++count;
        if ((end = filePath.find("»", i + 1)) == std::string::npos) {
            end = filePath.length() - 1;
            string = filePath.substr(i + 3);
        } else {
            string = filePath.substr(i + 3, end - (i + 3) - 1);
        }
        isFile = (string.find('.') != std::string::npos && string.find(' ') == std::string::npos) || count % 2 == 0;
        if (!isFile) {
            packers.insert(string);
        }
    }
    return packers;
}

void Parser::printFile(const std::string& filePath) const {
    std::cout << "===== " << countFiles << " =====\n";
    std::cout << "FILE: " << filePath << "\n";
}

void Parser::printArchive() const {
    std::cout << "ARCHIVE: ";
    if (isCurrentFileArchive) {
        std::cout << "yes\n";
        std::cout << "PACKERS: \n";
        for (const std::string& packer : packers) {
            std::cout << "   - " << packer << "\n";
        }
    } else {
        std::cout << "no\n";
    }
}

void Parser::printInfected() const {
    std::cout << "INFECTED: ";
    if (infiltrations.size() != 0) {
        std::cout << "yes\n";
        std::cout << "INFILTRATIONS: \n";
        for (const std::string& infiltration : infiltrations) {
            std::cout << "   - " << infiltration << "\n";
        }
    } else {
        std::cout << "no\n";
    }
}

void Parser::parseAndPrint(const std::string& line) {
    size_t endOfSubstring = line.find("\"", FILE_PATH_START); // finds where value of name ends
    std::string filePath = line.substr(FILE_PATH_START, endOfSubstring - FILE_PATH_START);

    if (filePath.find("»") != std::string::npos) {
        isCurrentFileArchive = true;
        getPackers(filePath, packers);
        filePath = cutChildFiles(filePath);
    }

    size_t threatPos = line.find("threat=\"") + 8; // 8 is the length of "threat=\"" string
    endOfSubstring = line.find("\"", threatPos); // finds where value of threat ends
    std::string threat = line.substr(threatPos, endOfSubstring - threatPos);
    if (threat != "is OK" && threat != "multiple threats" && threat != "" && filePath == prevFile) {
        infiltrations.insert(threat);
    }

    if (filePath != prevFile) {
        if (prevFile != "") {
            printArchive();
            printInfected();
            std::cout << "\n";
        }

        ++countFiles;
        printFile(filePath);

        prevFile = filePath;
        isCurrentFileArchive = false;
        infiltrations.clear();
        packers.clear();
    }
}
