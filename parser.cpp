//
// Created by henri on 15/11/2020.
//

#include "parser.h"
#include <iostream>
#include <ios>
#include <limits>
#include "date.h"

void cleanInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int getNumber(int min, int max) {
    int num;
    std::cin >> num;
    while (std::cin.fail() || num < min || num > max) {
        cleanInput();
        std::cin >> num;
    }
    std::cin.ignore(1);
    return num;
}

int getOption(std::vector<std::string> options) {
    for (int i = 0; i < options.size(); i++) {
        std::cout << i << ": " << options[i] << '\n';
    }
    return getNumber(0, options.size() - 1);
}

std::string getLine(){
    std::string line;
    //std::cin.ignore(1);
    getline(std::cin, line);
    return line;
}

Date getDate(){
    unsigned int year, month, day;
    std::cout << "Year:";
    year = getNumber(0, INT_MAX);
    std::cout << "Month:";
    month = getNumber(1, 12);
    std::cout << "Day:";
    day = getNumber(1, 31);
    try{
        Date d(year, month, day);
        return d;
    }
    catch(...){
        throw;
    }
}
