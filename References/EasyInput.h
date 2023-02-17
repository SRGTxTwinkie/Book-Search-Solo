//
// Created by zaned on 2/16/2023.
//

#ifndef BOOKSEARCHZANEREISBIG_EASYINPUT_H
#define BOOKSEARCHZANEREISBIG_EASYINPUT_H

#include <iostream>
#include <string>
#include <utility>
#include <limits>

void eCin(std::string &input){
    std::cin >> input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void eCin(int &input){
    std::cin >> input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void eCin(std::string &input, const std::string &prompt){
    std::cout << prompt;
    std::cin >> input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void eCin(int &input, const std::string &prompt){
    std::cout << prompt;
    std::cin >> input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


class Menu
{


public:
    explicit Menu(std::string title)
    {
        this->title = std::move(title);
    }

    void addOption(std::string name, int returnValue)
    {
        options.emplace_back(std::tuple<std::string, int>(name, returnValue));
    }

    void display()
    {
        std::cout << title << std::endl;
        for (int i = 0; i < options.size(); i++)
        {
            std::cout << i + 1
                      << ": "
                      << std::get<0>(options[i])
                      << std::endl;
        }
    }

    void getChoice(int &choice)
    {
        std::cout << "Enter your choice: ";
        eCin(choice);

        if (choice < 1 || choice > options.size())
        {
            std::cout << "Invalid choice.";
        }
        else
        {
            choice = std::get<1>(options[choice - 1]);
        }
    }

    void getChoice(int &choice, std::string &prompt)
    {
        system("cls");
        std::cout << prompt;
        eCin(choice);

        if (choice < 1 || choice > options.size())
        {
            std::cout << "Invalid choice.";
        }
        else
        {
            choice = std::get<1>(options[choice - 1]);
        }
    }

private:
    std::vector<std::tuple<std::string, int>> options;
    std::string title;
};


#endif //BOOKSEARCHZANEREISBIG_EASYINPUT_H
