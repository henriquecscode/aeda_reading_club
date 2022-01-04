//
// Created by henri on 25/10/2020.
//

#include "title.h"
#include "person.h"
#include "book.h"
#include "review.h"
#include "request.h"
#include "critique.h"
#include "date.h"
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>

unsigned int LENDING_DURATION = 10;

unsigned int Title::id = 1;

Title::~Title() {
    delete &critique;
    for (auto r: all_requests) {
        delete r;
    }
}

Title::Title() : title_id(Title::id) { increaseTitleId(); }

Title::Title(unsigned int id) : title_id(id) { increaseTitleId(); }

Title::Title(std::string tit_name, std::string tit_type) : name(tit_name), type(tit_type), title_id(Title::id) { increaseTitleId(); }

Title::Title(std::string tit_name, std::string tit_type, unsigned int id) : name(tit_name), type(tit_type), title_id(id) { increaseTitleId(); }

unsigned int Title::getId() const {
    return title_id;
}

std::string Title::getName() const {
    return name;
}

std::string Title::getType() const {
    return type;
}

const Critique *Title::getCritique() const {
    return &critique;
}

Critique *Title::getCritique() {
    return &critique;
}

void Title::setCritique(Critique &crit) {
    critique = crit;
}

bool Title::existsCopies() {
    return books.size() > 1;
}

void Title::addReview(Review *review) {
    critique.addReview(*review);
}

Review &Title::getReview(Person *p) {
    try {
        return critique.getReview(p);
    }
    catch (PersonDidntMakeReview e) {
        throw e;
    }
}

std::vector<Book *> Title::getBooks() const {
    return books;
}

bool Title::existsBook(Book *book) {
    return find(books.begin(), books.end(), book) != books.end();
}

void Title::addBook(Book *book) {
    if (book->getTitle() != this) {
        throw BookDoesntBelongToTitle(book, this);
    }
    books.push_back(book);
}

void Title::removeBook(Book *book) {
    auto it = find(books.begin(), books.end(), book);
    if (it == books.end()) {
        throw TitleDoesntHaveBook(book);
    }

    for (auto it = fulfilled_requests.begin(); it != fulfilled_requests.end(); it++) {
        if ((*it)->hasBook() && (*it)->getBook() == book) {
            throw BookBeingLent(book);
        }
    }

    for (auto it = pending_requests.begin(); it != pending_requests.end(); it++) {
        if ((*it)->hasBook() && (*it)->getBook() == book) {
            //Shouldn't throw an exception since hasBook is evaluated first
            //There is a request to this book
            (*it)->getPerson()->removeRequest();
            it = pending_requests.erase(it);
        }
    }
    for (auto it = all_requests.begin(); it != all_requests.end(); it++) {

        if ((*it)->hasBook() && (*it)->getBook() == book) {
            //Shouldn't throw an exception since hasBook is evaluated first
            //There is a request to this book
            auto to_delete = *it;
            (*it)->getPerson()->removeRequest();
            it = all_requests.erase(it);
            delete to_delete; // This request has effectively stopped existing
        }
    }
    books.erase(it);
}

void Title::removeRequest(Person *person) {
    if (person->getRequest()->isFulfilled()) {
        throw PersonIsBorrowing();
    }
    auto it = pending_requests.begin();
    for (; it != pending_requests.end();) {
        if ((*it)->getPerson() == person) {
            it = pending_requests.erase(it);
            break;
        } else {
            it++;
        }
    }
    auto it2 = all_requests.begin();
    for (; it2 != all_requests.end();) {
        if ((*it2)->getPerson() == person) {
            it2 = all_requests.erase(it2);
            break;
        } else {
            it2++;
        }
    }
    auto it3 = fulfilled_requests.begin();
    for (; it3 != fulfilled_requests.end();) {
        if ((*it3)->getPerson() == person) {
            throw PersonIsBorrowing();
        } else {
            it3++;
        }
    }
    delete person->getRequest();
}

void Title::loseBook(Book *book) {
    auto it = find(books.begin(), books.end(), book);
    if (it == books.end()) {
        throw TitleDoesntHaveBook(book);
    }

    for (auto it = fulfilled_requests.begin(); it != fulfilled_requests.end(); it++) {
        if ((*it)->hasBook() && (*it)->getBook() == book) {
            //Shouldn't throw an exception since hasBook is evaluated first
            //There is a request to this book
            it = fulfilled_requests.erase(it);
            break; //There should be only a fulfilled request for the specific book
        }
    }

    for (auto it = pending_requests.begin(); it != pending_requests.end();) {
        if ((*it)->hasBook() && (*it)->getBook() == book) {
            //Shouldn't throw an exception since hasBook is evaluated first
            //There is a request to this book
            (*it)->getPerson()->removeRequest();
            it = pending_requests.erase(it);
        }
        else{
            it++;
        }
    }
    for (auto it = all_requests.begin(); it != all_requests.end();) {

        if ((*it)->hasBook() && (*it)->getBook() == book) {
            //Shouldn't throw an exception since hasBook is evaluated first
            //There is a request to this book
            auto to_delete = *it;
            (*it)->getPerson()->removeRequest();
            (*it)->getBook()->returnBook();
            it = all_requests.erase(it);
            delete to_delete; // This request has effectively stopped existing
        }
        else{
            it++;
        }
    }
    books.erase(it);

    if (books.size() == 0) {
        //We need to remove all of the requests
        //There can't be any fulfilled requests, there can just be pending ones to any title

        for (auto it = pending_requests.begin(); it != pending_requests.end();) {
            if ((*it)->hasBook()) {
                throw TitleRequestsError();
            }
            (*it)->getPerson()->removeRequest();
            it = pending_requests.erase(it);
        }
        if (fulfilled_requests.size() != 0) {
            throw TitleRequestsError();
        }
        for (auto it = all_requests.begin(); it != all_requests.end();) {
            delete *it;
            it = all_requests.erase(it);
        }
    }
}

std::vector<Request *> Title::getRequests() const {
    return all_requests;
}

bool Title::requestTitle(Person *person, Date date) {
    if (person->hasRequest()) {
        throw PersonAlreadyHasRequest();
    }
    if (person->getBalance() < 0) {
        throw PersonIsInDebt();
    }
    if (books.size() == 0) {
        throw TitleHasNoBooks();
    }
    auto to_request = findAvailableBook();
    if (to_request != NULL) {
        //Easy case, we can ask for a book right away
        Date expiration = date + LENDING_DURATION; //To be overloaded
        Request *req = new Request(person, this, to_request, date, expiration);
        to_request->requestBook(req);
        person->fulfillRequest(req);
        fulfilled_requests.push_back(req);
        all_requests.push_back(req);
        return true;
    }

    //Add to the pending_requests
    Request *req = new Request(person, this);
    person->fulfillRequest(req);
    pending_requests.push_back(req);
    all_requests.push_back(req);
    return false;

}

bool Title::requestTitle(Person *person, Book *book, Date date) {

    if (person->hasRequest()) {
        throw PersonAlreadyHasRequest();
    }
    if (person->getBalance() < 0) {
        throw PersonIsInDebt();
    }
    if (books.size() == 0) {
        throw TitleHasNoBooks();
    }

    auto to_request = findAvailableBook(book);
    if (to_request != NULL) {
        //Easy case, we can ask for a book right away
        Date expiration = date + LENDING_DURATION; //To be overloaded
        Request *req = new Request(person, this, to_request, date, expiration);
        to_request->requestBook(req);
        person->fulfillRequest(req);
        fulfilled_requests.push_back(req);
        all_requests.push_back(req);
        return true;
    }

    Request *req = new Request(person, this, book);
    person->fulfillRequest(req);
    pending_requests.push_back(req);
    all_requests.push_back(req);
    return false;

}

void Title::returnTitle(Request *req, Date d) {
    // Outside function should do the fine calculations
    // This only does the removing from the fulfilled and all_requests and giving lending other books
    if (!req->isFulfilled()) {
        throw RequestForTitleNotFulfilled(req);
    }

    auto it_all_request = find(all_requests.begin(), all_requests.end(), req);
    auto it_ful_request = find(fulfilled_requests.begin(), fulfilled_requests.end(), req);
    if (it_all_request == all_requests.end() || it_ful_request == fulfilled_requests.end()) {
        throw RequestWasNotStored();
    }

    all_requests.erase(it_all_request);
    fulfilled_requests.erase(it_ful_request);

    Request *to_fulfill = NULL;
    auto it = pending_requests.begin();
    auto request_it = it;
    for (; it != pending_requests.end(); it++) {
        auto r = *it;
        if (to_fulfill == NULL || *r < *to_fulfill) { //If r has priority over to_fulfill or to_fulfill has not been initialized yet
            if ((r->hasBook() && r->getBook() == req->getBook()) || !r->hasBook()) { // Any book or the book that has been returned
                to_fulfill = r;
                request_it = it;
            }
        }
        if (to_fulfill->isPriority()) {
            break;
        }
    }

    if (to_fulfill == NULL) {
        //There was no other request in pending_requests or there were only requests for books that weren't this one
        req->getPerson()->removeRequest();
        req->getBook()->returnBook();
        return;
    } else {
        req->getPerson()->removeRequest();
        //Don't remove the book, we will still access it
    }
    if (!to_fulfill->hasBook()) {
        to_fulfill->setBook(req->getBook());
    }
    Date expiration_date = d + LENDING_DURATION; //This should make a copy
    to_fulfill->fulfillRequest(d, expiration_date, to_fulfill->getBook());
    to_fulfill->getPerson()->fulfillRequest(req); //If the person has a pending request, the pointer will point to the now changed request
    to_fulfill->getBook()->requestBook(req);

    pending_requests.erase(request_it);
    fulfilled_requests.push_back(to_fulfill);

    delete req; // Memory clean

}

Book *Title::findAvailableBook() {
    for (auto r: pending_requests) {
        if (!r->hasBook()) return NULL; // There is already a request for any title
    }

    for (auto b: books) {
        if (!b->hasRequest()) {
            return b; //If the book isn't being lent, then there must not be a pending request to the book
        }
    }
    return NULL;
}

Book *Title::findAvailableBook(Book *b) {
    if (b->hasRequest()) {
        return NULL;
    }
    return b; //If the book isn't being lent, then there must not be a pending request to the book
}

/*
Book *Title::findBestRequestableBook() {

    //trivial case
    Book *to_request = findAvailableBook();
    if (to_request != NULL) {
        return to_request;
    }

    std::map<Book *, unsigned int> number_request;;
    for (auto r: pending_requests) {
        if (r->hasBook()) {
            if (number_request.find(r->getBook()) != number_request.end()) {
                number_request[r->getBook()] += 1;
            } else {
                number_request[r->getBook()] = 1;
            }
        }
    }

    Book *min_book;
    unsigned int min_value = INT32_MAX;
    for (auto it = number_request.begin(); it != number_request.end(); it++) {
        if (it->second < min_value) {
            min_book = it->first;
            min_value = it->second;
        }
    }
    return min_book;


}

Book *Title::findBestRequestableBook(bool is_member) {
    if (!is_member) return findBestRequestableBook();


    //trivial case
    Book *to_request = findAvailableBook();
    if (to_request != NULL) {
        return to_request;
    }

    std::map<Book *, unsigned int> number_request;;
    for (auto r: pending_requests) {
        if (r->isPriority() && r->hasBook()) {
            if (number_request.find(r->getBook()) != number_request.end()) {
                number_request[r->getBook()] += 1;
            } else {
                number_request[r->getBook()] = 1;
            }
        }
    }

    Book *min_book;
    unsigned int min_value = INT32_MAX;
    for (auto it = number_request.begin(); it != number_request.end(); it++) {
        if (it->second < min_value) {
            min_book = it->first;
            min_value = it->second;
        }
    }
    return min_book;
}*/

unsigned int Title::PendingRequestsToBook(Book *b) {
    unsigned int count = 0;
    for (auto r: pending_requests) {
        if (r->hasBook() && r->getBook() == b) count++;
    }
    return count;
}

unsigned int Title::PendingPriorityRequestsToBook(Book *b) {
    unsigned int count = 0;
    for (auto r: pending_requests) {
        if (r->hasBook() && r->isPriority() && r->getBook() == b) count++;
    }
    return count;
}

bool Title::titleComparatorId(const Title *t1, const Title *t2) {
    return t1->getId() < t2->getId();
}

bool Title::titleComparatorName(const Title *t1, const Title *t2) {
    return t1->getName() < t2->getName();
    // || (t1->getName() == t2->getName() && t1<t2); //This shouldn't happen as two titles can't have the same name
    //Grant that when adding books to the library, there can't be two titles with the same name
}

bool Title::titleComparatorType(const Title *t1, const Title *t2) {
    return t1->getType() < t2->getType()
           || (t1->getType() == t2->getType() && Title::titleComparatorName(t1, t2));
}

bool Title::titleComparatorNumberBooks(const Title *t1, const Title *t2) {
    return t1->getBooks().size() < t2->getBooks().size()
           || (t1->getBooks().size() == t2->getBooks().size() && Title::titleComparatorName(t1, t2));
}

bool Title::titleComparatorRating(const Title *t1, const Title *t2) {
    return t1->getCritique()->getRating() > t2->getCritique()->getRating()
           || (t1->getCritique()->getRating() == t2->getCritique()->getRating() && Title::titleComparatorName(t1, t2));
}

bool Title::titleComparatorNumberReviews(const Title *t1, const Title *t2) {
    return t1->getCritique()->getReviews().size() < t2->getCritique()->getReviews().size()
           || (t1->getCritique()->getReviews().size() == t2->getCritique()->getReviews().size() && Title::titleComparatorName(t1, t2));
}

bool Title::titleComparatorNumberComments(const Title *t1, const Title *t2) {
    return t1->getCritique()->getComments().size() < t2->getCritique()->getComments().size()
           || (t1->getCritique()->getComments().size() == t2->getCritique()->getComments().size() && Title::titleComparatorName(t1, t2));
}

void Title::printBooks(std::stringstream &ss) const {
    ss << books.size() << " books:\n";
    for (auto b: books) {
        b->printObject(ss);
    }
}

void Title::printBooks() const {
    std::stringstream ss;
    printBooks(ss);
    std::cout << ss.str();
}

void Title::printReviews(std::stringstream &ss) const {
    ss << "Title's reviews:\n";
    critique.printReviews(ss);
}

void Title::printReviews() const {
    std::stringstream ss;
    printReviews(ss);
    std::cout << ss.str();
}

void Title::printComments(std::stringstream &ss) const {
    ss << "Title's comments:\n";
    critique.printComments(ss);
}

void Title::printComments() const {
    std::stringstream ss;
    printComments(ss);
    std::cout << ss.str();
}

void Title::printRating(std::stringstream &ss) const {
    critique.printRating(ss);
}

void Title::printRating() const {
    std::stringstream ss;
    printRating(ss);
    std::cout << ss.str();
}

void Title::printRequests(std::stringstream &ss) const {
    std::cout << "Title Requests:\n";
    for (auto r: all_requests) {
        r->printRequest(ss);
    }
}

void Title::printRequests() const {
    std::stringstream ss;
    printRequests(ss);
    std::cout << ss.str();
}

void Title::printObject(std::stringstream &ss) const {
    ss << "Title: " << name << '\n';
    ss << "Type: " << type << '\n';
    ss << "Rating: ";
    printRating(ss);
    ss << "Has " << getBooks().size() << " books\n";
    ss << "Has " << critique.getReviews().size() << " reviews\n";
    ss << "Has " << critique.getComments().size() << " comments\n";
    ss << "Id: " << title_id << '\n';
}

void Title::printObject() const {
    std::stringstream ss;
    printObject(ss);
    std::cout << ss.str();
}

void Title::print(std::stringstream &ss) const {
    ss << '\n';
    ss << "Title:" << '\n';
    ss << "Title id: " << title_id << '\n';
    ss << "Title name: " << name << '\n';
    ss << "Title type: " << type << '\n';
    printBooks(ss);
    critique.print(ss);
    printRequests(ss);
    ss << '\n';
}

void Title::print() const {
    std::stringstream ss;
    print(ss);
    std::cout << ss.str();
}

std::ostream &operator<<(std::ostream &os, const Title &title) {
    std::stringstream ss;
    title.print(ss);
    os << ss.str();
    return os;
}

void Title::saveTitle(std::ofstream &ofs) const {
    ofs << getId() << ' ' << getName() << '\n' << getType() << '\n' << books.size() << ' ' << all_requests.size() << '\n';
    for (auto b: books) {
        ofs << b->getId() << ' ';
    }

    for (auto r: all_requests) {
        ofs << r->getId() << ' ';
    }
    critique.saveCritique(ofs);
}

TitleData Title::loadTitle(std::ifstream &ifs, const std::map<unsigned int, Person *> &people_map) {
    unsigned int t_id, books_no, request_no;
    std::string t_type, t_name;
    std::vector<unsigned int> t_books_id;
    std::vector<unsigned int> t_requests_id;

    ifs >> t_id;
    ifs.ignore(1);
    std::getline(ifs, t_name);
    std::getline(ifs, t_type);
    ifs >> books_no;
    t_books_id.resize(books_no);
    ifs >> request_no;
    t_requests_id.resize(request_no);
    for (int i = 0; i < books_no; i++) {
        ifs >> t_books_id[i];
    }

    for (int i = 0; i < request_no; i++) {
        ifs >> t_requests_id[i];
    }

    unsigned int t_book_id;
    Title *t = new Title(t_name, t_type, t_id);
    Critique critique = Critique::loadCritique(ifs, t, people_map);
    t->setCritique(critique);
    TitleData t_data{t_id, t, t_books_id, t_requests_id};
    return t_data;

}

void Title::initializeTitle(const TitleData &t_data, const std::map<unsigned int, Book *> book_map, const std::map<unsigned int, Request *> &request_map) {

    //Create the books array
    for (auto b_id: t_data.books_id) {
        Book *b = book_map.at(b_id);
        addBook(b);
    }

    for (auto r_id: t_data.requests_id) { // Keeps the order of the requests since requests_id is in the same order as in the save and as in the load


        Request *r = request_map.at(r_id);

        //TODO
        //Put this in a function addRequest(Request * r)?
        all_requests.push_back(r);
        if (r->isFulfilled()) {
            fulfilled_requests.push_back(r);
        } else {
            pending_requests.push_back(r);
        }
    }
}