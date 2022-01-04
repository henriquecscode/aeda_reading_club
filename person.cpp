//
// Created by henri on 25/10/2020.
//
#include "person.h"
#include "title.h"
#include "book.h"
#include "date.h"
#include "request.h"
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iostream>

std::string NO_NAME = "NO_NAME";
unsigned int Person::id = 1;

Person::~Person() {
    for(auto b: books){
        delete b;
    }
}

Person::Person(): balance(0), request(NULL), person_id(Person::id){increasePersonId();}

Person::Person(std::string name): person_name(name), balance(0), request(NULL), person_id(Person::id){increasePersonId();}

Person::Person(std::string name, int bal): person_name(name), balance(bal), request(NULL), person_id(Person::id){increasePersonId();}

Person::Person(unsigned int id): balance(0), person_id(id), request(NULL){ increasePersonId();}

Person::Person(std::string name, unsigned int id): person_name(name), balance(0), person_id(id), request(NULL){ increasePersonId();}

Person::Person(std::string name, bool is_memb) : person_name(name), balance(0), request(NULL), person_id(Person::id), is_member(is_memb){increasePersonId();}

Person::Person(std::string name, int bal, unsigned int id, bool is_memb): person_name(name), balance(bal), request(NULL), person_id(id), is_member(is_memb) {increasePersonId();}


unsigned int Person::getId() const {
    return person_id;
}

void Person::turnMember() {
    is_member = true;
}

std::string Person::getName() const {
    return person_name;
}

int Person::getBalance() const {
    return balance;
}

void Person::setBalance(int new_balance) {
    balance = new_balance;
}

void Person::addBalance(int change) {
    balance += change;
}

bool Person::isMember() const{
    return is_member;
}

std::vector<Book *> Person::getBooks() const {
    return books;
}

bool Person::hasBooksInLibrary() const {
    std::vector<Book *> titles_books;
    for(auto b: books){
        if(b->isInTheLibrary()){
            return true;
        }
    }
    return false;
}


bool Person::hasRequest() const {
    return request != NULL;
}

Request * Person::getRequest() const {
    return request;
}

void Person::removeRequest() {
    request = NULL;
}

void Person::fulfillRequest(Request *req) {
    request = req;
}

void Person::setRequest(Request *req) {
    request = req;
}

void Person::addBook(Book * book){
    books.push_back(book);
    if(book->getOwner() == NULL){
        book->setOwner(this);
    }
}

void Person::removeBook(Book * book) {
    auto it = find(books.begin(), books.end(), book);
    if (it == books.end()){
        throw PersonDoesntOwnBook(book);
    }
    books.erase(it);
    delete book;
}

bool Person::payPerson(Person *person, unsigned int amount) {
    addBalance(-amount);
    person->addBalance(amount);
    if(balance >0){
        return true;
    }
    return false;
}

bool Person::payCredit(unsigned int value) {
    addBalance(-value);
    if(balance > 0){
        return true;
    }
    return false;
}


bool Person::personComparatorId(const Person *p1, const Person *p2){
    return p1->getId() < p2->getId();
}
bool Person::personComparatorName(const Person *p1, const Person *p2){
    return p1->getName() < p2->getName();
    //There are no two equal names
}

bool Person::personComparatorBalance(const Person *p1, const Person *p2) {
    return p1->getBalance() < p2->getBalance();
}

bool Person::personComparatorIsMember(const Person *p1, const Person *p2){
    return p1->isMember() && !p2->isMember()
    || (p1->isMember() == !p1->isMember() && Person::personComparatorName(p1,p2));
}

bool Person::personComparatorNumberBooks(const Person *p1, const Person *p2){
    return p1->getBooks().size() < p2->getBooks().size()
    || (p1->getBooks().size() ==  p1->getBooks().size() && Person::personComparatorName(p1,p2));
}

void Person::printBooks(std::stringstream &ss) const{
    for(auto b: books){
        b->printObject(ss);
    }
}

void Person::printBooks() const {
    std::stringstream ss;
    printBooks(ss);
    std::cout << ss.str();
}

void Person::printObject(std::stringstream &ss) const {
    ss << getName() << '\n';
    ss << "Balance: " << getBalance() << '\n';
    if(isMember()){
        ss <<"Is a member\n";
    }
    else{
        ss << "Not a member\n";
    }
    if(hasRequest() && getRequest()->isFulfilled()){
        ss << "Is reading " << request->getTitle()->getName() << '\n';
    }
    else if (hasRequest()){
        ss << "Has a pending request for: " << request->getTitle()->getName() << '\n';
    }
    ss << "Owns " << getBooks().size() << " books\n";
    ss << "Id: " << person_id << '\n';
}

void Person::printObject() const {
    std::stringstream ss;
    printObject(ss);
    std::cout << ss.str();
}

void Person::print(std::stringstream &ss) const {
    ss << '\n';
    ss << "Person:" << '\n';
    ss << "Person id: " << person_id << '\n';
    ss << "Person name: " << person_name << '\n';
    printBooks(ss);
    if(is_member){
        ss << "Is a member of the book club" << '\n';
    }
    if(request != NULL){
        ss << "Has a request: " << request << '\n';
    }
}

void Person::print() const{
    std::stringstream ss;
    print(ss);
    std::cout << ss.str();
}

std::ostream &operator<<(std::ostream &os, const Person &person){
    std::stringstream ss;
    person.print(ss);
    os << ss.str();
    return os;
}

void Person::savePerson(std::ofstream &ofs) const {
    ofs << getId() << '\n' << getName() << '\n' << getBalance() << ' ' << isMember() << ' ' << books.size() << '\n';
    for(auto b: books){
        ofs << b->getId() << ' ';
    }
    if(hasRequest()){
        ofs << getRequest()->getId();
    }
    else{
        ofs << -1;
    }
    ofs << '\n';
}

PersonData Person::loadPerson(std::ifstream &ifs) {

    unsigned int p_id, books_no;
    std::vector<int> p_books_id;
    std::string p_name;
    int p_balance, r_id;
    bool p_is_member;

    ifs >> p_id;
    ifs.ignore(1);
    std::getline(ifs, p_name);
    ifs >> p_balance >> p_is_member >> books_no;
    p_books_id.resize(books_no);
    for(int i = 0; i < books_no; i++){
        ifs >> p_books_id[i];
    }
    ifs >> r_id;

    PersonData p_data{p_id, p_name, p_balance, p_is_member, p_books_id, r_id};
    return p_data;

}

void Person::initializePerson(const PersonData &p_data, const std::map<unsigned int, Book *> &book_map, const std::map<unsigned int, Request *> &request_map) {
    std::vector<int> b_ids = p_data.books_ids;
    for(auto b_id: b_ids){
        Book * b = book_map.at(b_id);
        addBook(b);
    }

    Request *r = NULL;
    if(p_data.request_id != -1){
         r = request_map.at(p_data.request_id);
    }
    setRequest(r);
}
