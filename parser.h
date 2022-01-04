//
// Created by henri on 15/11/2020.
//

#ifndef AEDA_2MIEIC02_09_READING_CLUB_PARSER_H
#define AEDA_2MIEIC02_09_READING_CLUB_PARSER_H

#include <vector>
#include <string>
class Date;

void cleanInput();

int getNumber(int min, int max);

int getOption(std::vector<std::string> options);

std::string getLine();

Date getDate();

#endif //AEDA_2MIEIC02_09_READING_CLUB_PARSER_H
