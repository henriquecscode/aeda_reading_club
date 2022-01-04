//
// Created by henri on 25/10/2020.
//

#include "review.h"
#include "title.h"
#include "person.h"
#include <string>
#include <fstream>
#include <ostream>
#include <sstream>
#include <iostream>

Review::~Review(){}

Review::Review(): reviewer(NULL), title(NULL) {}

Review::Review(Person *rewer, Title *tit, Classification classific) : reviewer(rewer), title(tit), classification(classific) {
    //Todo
    //Is classification safe or do I need to do checking
    //to be sure, do all the checking outside of review
}

Review::Review(Person *rewer, Title *tit, Classification classific, std::string com) : reviewer(rewer), title(tit), classification(classific), comment(com) {}


Classification Review::getClassification() const {
    return classification;
}

void Review::setClassification(Classification c) {
    classification = c;
}
Person * Review::getPerson() const {
    return reviewer;
}

std::string Review::getComment() const {
    return comment;
}
void Review::setComment(const std::string &com) {
    // Overrides previous comment
    comment = com;
}

bool Review::hasComment() const {
    return comment != "";
}


void Review::printClassification(std::stringstream &ss) const {
    ss << classification;
}

void Review::printClassification() const {
    std::stringstream ss;
    printClassification(ss);
    std::cout << ss.str();
}

void Review::printComment(std::stringstream &ss) const {
    ss << comment << '\n';
}

void Review::printComment() const {
    std::stringstream ss;
    printComment(ss);
    std::cout << ss.str();
}

void Review::print(std::stringstream &ss) const {
    ss << "Review" << '\n';
    ss << "Reviewer: " << reviewer << '\n';
    ss << "Title: " << title << '\n';
    printClassification(ss);
    if (comment != "") {
        printComment(ss);
    }
}

void Review::print() const {
    std::stringstream ss;
    print(ss);
    std::cout << ss.str();
}

std::ostream &operator<<(std::ostream &os, const Review &review) {
    std::stringstream ss;
    review.print(ss);
    os << ss.str();
    return os;
}

void Review::saveReview(std::ofstream &ofs) const {
    bool has_comment = comment != "";
    ofs << reviewer->getId() << ' ' << classification << ' ' << has_comment << '\n';
    if (has_comment) {
        ofs << comment << '\n';
    }
}

Review Review::loadReview(std::ifstream &ifs, Title *t, const std::map<unsigned int, Person *> &people_map) {
    unsigned int p_id, int_classification;
    bool has_comment;
    std::string comment;
    Classification classification;
    Review r;

    ifs >> p_id >> int_classification >> has_comment;
    Person *p = people_map.at(p_id);
    classification = static_cast<Classification>(int_classification); // Converts a value from 1 to 5 into a Classification


    r = Review(p, t, classification);
    ifs.ignore(1); // The new line character
    if (has_comment) {
        getline(ifs, comment);
        r.setComment(comment);
    }
    return r;
}