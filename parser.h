//
// Created by Michaela Bajanová on 25/02/2019.
//

#ifndef ESET_TASK_PARSER_H
#define ESET_TASK_PARSER_H

#include <iostream>
#include <string>
#include <set>

class Parser {
private:
    const int FILE_PATH_START = 6;
    size_t countFiles = 0;
    bool isCurrentFileArchive = false;
    std::string prevFile = "";
    std::set<std::string> infiltrations;
    std::set<std::string> packers;

public:
    /**
     * Crops out all child files, so only parent file remains.
     * @param filePath - path to file followed by packers and child files
     * @return - cropped filePath containing only parent file
     */
    std::string& cutChildFiles(std::string& filePath);

    /**
     * Parses filePath, sorts out which of the following names is a packer and inserts it into set
     * @param filePath - path to file followed by packers and child files
     * @param packers - set for inserting packers
     * @return - set containing string with packer names
     */
    std::set<std::string>& getPackers(const std::string& filePath, std::set<std::string>& packers);

    void printFile(const std::string& filePath) const;
    void printArchive() const;
    void printInfected() const;
    void parseAndPrint(const std::string& line);
};


#endif //ESET_TASK_PARSER_H
