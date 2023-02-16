//
// Created by zaned on 2/16/2023.
//

#ifndef BOOKSEARCHZANEREISBIG_AUTHSYSTEM_H
#define BOOKSEARCHZANEREISBIG_AUTHSYSTEM_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <tuple>

class AuthSystem {
    std::vector<std::tuple<std::string, std::string>> users;

public:
    explicit AuthSystem(std::vector<std::vector<std::string>> vector1) {
        for(auto &user : vector1){
            users.emplace_back(std::make_tuple(user[0], user[1]));
        }
    }

    bool login(const std::string &username, const std::string &password){
        for(auto &user : users){
            if(std::get<0>(user) == username && std::get<1>(user) == password){
                return true;
            }
        }
        return false;
    }


};









#endif //BOOKSEARCHZANEREISBIG_AUTHSYSTEM_H
