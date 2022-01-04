

#include "book.h"
#include "title.h"
#include "person.h"
#include "request.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>

unsigned int Book::id = 1;

Book::~Book() {}

Book::Book() : request(NULL), book_id(Book::id) { increaseBookId(); }

Book::Book(unsigned int id) : book_id(id), request(NULL) { increaseBookId(); }

Book::Book(unsigned int id, unsigned int val) : book_id(id), value(val), request(NULL) { increaseBookId(); }

Book::Book(Title *tit, unsigned int val): title(tit), owner(NULL), request(NULL), value(val), book_id(Book::id) {increaseBookId();}

Book::Book(Title *tit, Person *own, unsigned int val) : title(tit), owner(own), request(NULL), value(val), book_id(Book::id) {
    increaseBookId();
    own->addBook(this);
}

Book::Book(Title *tit, unsigned int val, unsigned int id): title(tit), owner(NULL), request(NULL), value(val), book_id(id) {increaseBookId();}


Book::Book(Title *tit, Person *own, unsigned int val, unsigned int id) : title(tit), owner(own), request(NULL), value(val), book_id(id) {
    increaseBookId();
    own->addBook(this);
}

unsigned int Book::getId() const {
    return book_id;
}

bool Book::isInTheLibrary() const {
    std::vector<Book *> titles_books = getTitle()->getBooks();
    if (find(titles_books.begin(), titles_books.end(), this) != titles_books.end()){
        return true;
    }
    return false;
}

Person *Book::getOwner() const {
    return owner;
}

void Book::setOwner(Person *p) {
    owner = p;
}

Title *Book::getTitle() const{
    return title;
}

void Book::setTitle(Title *t) {
    title = t;
}

unsigned int Book::getValue() const {
    return value;
};

Request *Book::getRequest() const {
    return request;
}

bool Book::hasRequest() const {
    return request != NULL;
}

void Book::setRequest(Request *r) {
    request = r;
}

void Book::requestBook(Request *req) {
    request = req;
}

void Book::returnBook() {
    request = NULL;
}

bool Book::bookComparatorId(const Book *b1, const Book* b2){
    return b1->getId() < b2->getId();
}

bool Book::bookComparatorValue(const Book *b1, const Book* b2){
    return b1->getValue() < b2->getValue()
           ||  (b1->getValue() == b2->getValue() && Book::bookComparatorTitle(b1,b2));
}

bool Book::bookComparatorTitle(const Book *b1, const Book* b2){
    return b1->getTitle()->getName() < b2->getTitle()->getName()
    || (b1->getTitle()->getName() == b2->getTitle()->getName() && Book::bookComparatorId(b1,b2));
}

bool Book::bookComparatorOwner(const Book *b1, const Book* b2){
    return b1->getOwner()->getName() < b2->getOwner()->getName()
           ||(b1->getOwner()->getName() == b2->getOwner()->getName() && Book::bookComparatorTitle(b1,b2));
}

bool Book::bookIsInTheLibrary(const Book *b1, const Book *b2) {
    return b1->isInTheLibrary() && !b2->isInTheLibrary()
    || (b1->isInTheLibrary() == b2->isInTheLibrary() && Book::bookComparatorTitle(b1, b2));
}

void Book::printValue(std::stringstream &ss) const {
    ss << value << '\n';
}

void Book::printValue() const {
    std::stringstream ss;
    printValue(ss);
    std::cout << ss.str();
}

void Book::printObject(std::stringstream &ss) const {
    ss << "Title: " << title->getName() << '\n';
    ss << "Owner's name: " << owner->getName() <<'\n';

    if(!hasRequest()){
        ss << "This book is not being lent" << '\n';
    }
    else{
        ss << "This book is being lent by " << getRequest()->getPerson()->getName() << '\n';
    }
    ss << "Value: " << value << '\n';

    ss << "Id: " << book_id << '\n';
}

void Book::printObject() const {
    std::stringstream ss;
    printObject(ss);
    std::cout << ss.str();
}

void Book::print(std::stringstream &ss) const {
    ss << "Book" << '\n';
    ss << "Book id: " << book_id << '\n';
    ss << "Owner: Person in " << owner << '\n';
    ss << "Title: Title in " << title << '\n';
    if(isInTheLibrary()){
        ss << "Book is in the library\n";
    }
    if (hasRequest()) {
        ss << "Has a request: " << request << '\n';
    }
    ss << "Value: " << value << '\n';
}

void Book::print() const {
    std::stringstream ss;
    print(ss);
    std::cout << ss.str();
}

std::ostream &operator<<(std::ostream &os, const Book &book) {
    std::stringstream ss;
    book.print(ss);
    os << ss.str();
    return os;
}

void Book::saveBook(std::ofstream &ofs) const{
    ofs << getId() << ' ' << getValue() << ' ' << title->getId() << ' ' << owner->getId() << ' ';
    if(hasRequest()){
        ofs << request->getId() << '\n';
    }
    else{
        ofs << -1 << '\n';
    }
}

BookData Book::loadBook(std::istream &ifs) {
    unsigned int b_id, value, t_id, p_id;
    int r_id;

    ifs>> b_id >> value >> t_id >> p_id >> r_id;
    BookData b_data{b_id, value, t_id, p_id, r_id};
    return b_data;
}

void Book::initializeBook(const BookData &b_data, const std::map<unsigned int, Person *> &people_map, const std::map<unsigned int, Title *> &title_map, const std::map<unsigned int, Request *> &request_map) {
    Person *p = people_map.at(b_data.person_id);
    setOwner(p);

    Title *t = title_map.at(b_data.title_id);
    setTitle(t);

    Request *r = NULL;
    if(b_data.request_id != -1){
        r = request_map.at(b_data.request_id);
    }
    setRequest(r);
}