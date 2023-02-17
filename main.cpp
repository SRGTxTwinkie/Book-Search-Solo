#include <iostream>
#include "References/CSVReader.h"
#include "References/AuthSystem.h"
#include "References/EasyInput.h"

struct Book {
    std::string isbn;
    std::string title;
    std::string author;
    std::string year;
    std::string publisher;
};

void displayAsPages(std::vector<Book>& books)
{
    // The number of books displayed on each page.
    int PAGESIZE = 1;
    // The current page number.
    int page = 0;

    // A string to store the user's input.
    std::string menuInput;

    // An infinite loop that continues until the user inputs "exit".
    while (true)
    {
        // Clears the console screen.
        system("cls");

        // Loops through the books on the current page.
        for (int i = page * PAGESIZE; i < (page + 1) * PAGESIZE; i++)
        {
            // Breaks out of the loop if the end of the books vector has been reached.
            if (i >= books.size())
            {
                break;
            }
            // Prints the ISBN, title, and author of each book on the current page.
            std::cout << "ISBN: " << books[i].isbn << std::endl;
            std::cout << "Title: " << books[i].title << std::endl;
            std::cout << "Author: " << books[i].author << std::endl;
            std::cout << std::endl
                      << std::endl;
        }

        // Calculates the total number of pages based on the number of books and the PAGESIZE.
        double pages = books.size() / PAGESIZE;
        pages = pages == 0 ? 1 : pages;

        // Prints the current page number and the total number of pages.
        std::cout << "Page ["
             << page + 1
             << "] of ["
             << pages
             << "]"
             << std::endl;

        // Prompts the user to press enter to go to the next page or type "exit" to exit.
        std::cout << "Press enter to go to the next page" << std::endl;
        std::cout << "Type 'exit' to exit" << std::endl;

        // Gets the user's input.
        eCin(menuInput);

        // Exits the loop if the user inputs "exit".
        if (menuInput == "exit")
        {
            // Clears the console screen.
            system("cls");
            break;
        }

        // Increments the page number.
        page++;
        // Resets the page number to 0 if the end of the books vector has been reached.
        if (page * PAGESIZE >= books.size())
        {
            page = 0;
        }
    }
}
bool login(AuthSystem *auth) {
    std::string username;
    std::string password;
    bool isLogged = false;

    eCin(username, "Username: ");
    eCin(password, "Password: ");

    while (!isLogged) {
        system("cls");

        if (auth->login(username, password)) {
            std::cout << "Logged in" << std::endl;
            isLogged = true;
        } else {
            std::cout << "Type \"exit\" to exit" << std::endl;
            std::cout << "Invalid username or password" << std::endl;

            eCin(username, "Username: ");

            if(username == "exit"){
                return false;
            }

            eCin(password, "Password: ");
        }
    }

    return true;
}

std::vector<Book> search(std::vector<Book> &books, int searchValue){
    std::vector<Book> returnBooks;
    searchValue = searchValue - 1;

    for(auto &book : books){
        if(searchValue == 0){
            std::string isbn;
            eCin(isbn, "ISBN: ");
            if(book.isbn == isbn){
                returnBooks.emplace_back(book);
            }
        } else if(searchValue == 1){
            std::string title;
            eCin(title, "Title: ");
            if(book.title == title){
                returnBooks.emplace_back(book);
            }
        } else if(searchValue == 2){
            std::string author;
            eCin(author, "Author: ");
            if(book.author == author){
                returnBooks.emplace_back(book);
            }
        } else if(searchValue == 3){
            std::string year;
            eCin(year, "Year: ");
            if(book.year == year){
                returnBooks.emplace_back(book);
            }
        } else if(searchValue == 4){
            std::string publisher;
            eCin(publisher, "Publisher: ");
            if(book.publisher == publisher){
                returnBooks.emplace_back(book);
            }
        }
    }

    return returnBooks;
}

void searchHandler(std::vector<Book> &books){
    std::vector<Book> searchResults;
    Menu menu("Search Menu");
    menu.addOption("Search by ISBN", 1);
    menu.addOption("Search by Title", 2);
    menu.addOption("Search by Author", 3);
    menu.addOption("Search by Year", 4);
    menu.addOption("Search by Publisher", 5);
    menu.addOption("Exit", 6);

    int choice;
    while (true) {
        system("cls");

        menu.display();
        menu.getChoice(choice);

        switch (choice) {
            case 1:
                std::cout << "Search by ISBN" << std::endl;
                searchResults = search(books, 1);
                break;
            case 2:
                std::cout << "Search by Title" << std::endl;
                searchResults = search(books, 2);
                break;
            case 3:
                std::cout << "Search by Author" << std::endl;
                searchResults = search(books, 3);
                break;
            case 4:
                std::cout << "Search by Year" << std::endl;
                searchResults = search(books, 4);
                break;
            case 5:
                std::cout << "Search by Publisher" << std::endl;
                searchResults = search(books, 5);
                break;
            case 6:
                std::cout << "Exited" << std::endl;
                return;
            default:
                std::cout << "Invalid choice" << std::endl;
                break;
        }

        if(!searchResults.empty()){
            displayAsPages(searchResults);
        } else {
            std::cout << "No results found" << std::endl;
        }
    }
}

void mainLoop() {
    std::cout << "Loading Data, Please wait..." << std::endl;
    CSVReader booksReader("../Data/books.csv", ",");
    std::vector<Book> books;
    for (auto &book : booksReader.getTokens()) {
        books.emplace_back(Book{
                book[0],
                book[1],
                book[2],
                book[3],
                book[4]
        });
    }

    Menu menu("Main Menu");
    menu.addOption("Search", 1);
    menu.addOption("Exit", 2);

    int choice;
    while (true) {
        system("cls");

        menu.display();
        menu.getChoice(choice);

        switch (choice) {
            case 1:
                std::cout << "Search" << std::endl;
                searchHandler(books);
                break;
            case 2:
                std::cout << "Exited" << std::endl;
                return;
            default:
                std::cout << "Invalid choice" << std::endl;
                break;
        }
    }

}

int main() {
    auto *reader = new CSVReader("../Data/login.csv", ",");

    AuthSystem authSystem(reader->getTokens());

    if(login(&authSystem)){
        std::cout << "Logged in" << std::endl;
    } else{
        std::cout << "Exited" << std::endl;
        return 1;
    }
    delete reader;

    mainLoop();
    return 0;

}
