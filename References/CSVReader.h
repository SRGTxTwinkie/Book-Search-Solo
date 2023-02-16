//
// Created by zaned on 2/16/2023.
//
#ifndef BOOKSEARCHZANEREISBIG_CSVREADE_H
#define BOOKSEARCHZANEREISBIG_CSVREADE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

class FileNotFound : public std::exception {
    [[nodiscard]] const char *what() const noexcept override {
        return "File not found";
    }
};


class CSVReader {
    std::fstream file;
    std::vector<std::string> lines;
    std::vector<std::vector<std::string>> tokens;
    std::vector<std::string> headers;

    std::string storedDelimiter;

public:

        std::vector<std::string> getLines(){
            return lines;
        }

        std::vector<std::vector<std::string>> getTokens(){
            return tokens;
        }

        std::vector<std::string> getHeaders(){
            return headers;
        }

    explicit CSVReader(const std::string &fileNameWPath, const std::string &delimiter = ","){
        file.open(fileNameWPath);

        if(!file.is_open()){
            std::cout << "File not found" << std::endl;
            throw FileNotFound();
        }

        while(!file.eof()){
            std::string line;
            std::getline(file, line);
            lines.push_back(line);
        }

        file.close();
        finalInit(delimiter);
    }

    explicit CSVReader(const std::vector<std::string> &lines, const std::string &delimiter = ","){

        this->lines = lines;
        finalInit(delimiter);
    }

private:

    void finalInit(const std::string& delimiter){

        for(auto &line : lines){
            tokens.push_back(split(line, delimiter));
        }

        headers = tokens[0];
    }

    static std::vector<std::string> split(const std::string &line, const std::string &delimiter){
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(line);
        while (std::getline(tokenStream, token, delimiter[0])) {
            tokens.push_back(token);
        }
        return tokens;
    }

};


#endif //BOOKSEARCHZANEREISBIG_CSVREADE_H
