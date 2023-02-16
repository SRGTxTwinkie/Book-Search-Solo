#include <iostream>
#include "References/CSVReader.h"
#include "References/AuthSystem.h"
#include "References/EasyInput.h"

int main() {
    CSVReader reader("../Data/login.csv", ",");
    AuthSystem authSystem(reader.getTokens());




    return 0;

}
