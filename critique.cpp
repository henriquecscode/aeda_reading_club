//
// Created by henri on 25/10/2020.
//

#include "critique.h"
#include "title.h"
#include "review.h"
#include <fstream>
#include <ostream>
#include <sstream>
#include <iostream>
#include <math.h>

unsigned int ROUNDING = 1;

Critique::~Critique() {}

Critique::Critique() {}

Critique::Critique(Title *ti) :title(ti){}

void Critique::setTitle(Title *ti) {
    title = ti;
}

void Critique::addReview(Review review) {
    for(auto r: reviews){
        if (r.getPerson() == review.getPerson()){
            throw PersonAlreadyMadeReview(review.getPerson());
        }
    }
    reviews.push_back(review);
    calculateMeanRating(review.getClassification());
}

void Critique::calculateMeanRating(Classification classification) {
    rating = (rating * (reviews.size()-1) + classification) / reviews.size();
}

float Critique::getRating(unsigned int rounding) const {
    return (int) (rating * pow(10, rounding)) / pow(10,rounding);
}

void Critique::updateReview(Review &r, Classification c) {
    rating = (rating * reviews.size() - r.getClassification() + c) / reviews.size();
    r.setClassification(c);
}

void Critique::updateReview(Review &r, std::string comment) {
    r.setComment(comment);
}

Review & Critique::getReview(Person *p) {
    for (auto &r: reviews) {
        if (r.getPerson() == p) {
            return r;
        }
    }
    throw PersonDidntMakeReview(p);
}

std::vector<Review> Critique::getReviews() const {
    return reviews;
}

std::vector<std::string> Critique::getComments() const {
    std::vector<std::string> comments;
    for(auto &r: reviews){
        if(r.hasComment()){
            comments.push_back(r.getComment());
        }
    }
    return comments;
}

void Critique::printReviews(std::stringstream &ss) const {
    for(auto r: reviews){
        r.printClassification(ss);
        if(r.hasComment()){
            ss << ": ";
            r.printComment(ss);
        }
        else{
            ss << '\n';
        }
    }
}

void Critique::printReviews() const {
    std::stringstream ss;
    printReviews(ss);
    std::cout << ss.str();
}

void Critique::printComments(std::stringstream &ss) const {
    for(auto r: reviews){
        r.printComment(ss);
    }
}

void Critique::printComments() const {
    std::stringstream ss;
    printComments(ss);
    std::cout << ss.str();
}

void Critique::printRating(std::stringstream &ss) const {
    ss << getRating(ROUNDING) << '\n';
}

void Critique::printRating() const {
    std::stringstream ss;
    printRating(ss);
    std::cout << ss.str();
}

void Critique::print(std::stringstream &ss) const {
    ss << "Title's critique:\n";
    printReviews(ss);
    ss << "Rating: ";
    printRating(ss);
}

void Critique::print() const {
    std::stringstream ss;
    print(ss);
    std::cout << ss.str();
}

std::ostream &operator << (std::ostream &os, const Critique &critique){
    std::stringstream ss;
    critique.print(ss);
    os << ss.str();
    return os;
}

void Critique::saveCritique(std::ofstream &ofs) const {
    ofs << reviews.size() << '\n';
    for(auto r: reviews){
        r.saveReview(ofs);
    }
}

Critique Critique::loadCritique(std::ifstream &ifs, Title *t , const std::map<unsigned int, Person*> &people_map) {
    // float rating; //Shouldn't need to save since it's calculated when adding the reviews
    unsigned int reviews_no;
    std::vector<Review> c_reviews;
    ifs >> reviews_no;
    c_reviews.resize(reviews_no);
    Critique critique(t);
    for(int i =0; i < reviews_no; i++){
        Review r = Review::loadReview(ifs, t, people_map);
        critique.addReview(r);
    }
    return critique;
}