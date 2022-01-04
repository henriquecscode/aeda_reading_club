//
// Created by henri on 25/10/2020.
//

#include "request.h"
#include "person.h"
#include "title.h"
#include "book.h"
#include "date.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>

unsigned int Request::id = 1;

/*
Request::Request(Date issued) : priority_member(false), issued_date(issued) {}

Request::Request(Date issued, unsigned int id) : priority_member(false), request_id(id), issued_date(issued) {}

Request::Request(Person *req_person, Title *req_title, Date issued) : priority_member(
        req_person->isMember()), requesting_person(req_person),
                                                                      requested_title(req_title), requested_book(NULL),
                                                                      issued_date(issued) {}

Request::Request(Person *req_person, Title *req_title, Date issued, unsigned int id) : priority_member(
        req_person->isMember()),
                                                                                       requesting_person(req_person),
                                                                                       requested_title(req_title),
                                                                                       requested_book(NULL),
                                                                                       issued_date(issued),
                                                                                       request_id(id) {}


Request::Request(Person *req_person, Title *req_title, Book *req_book, Date issued) : priority_member(
        req_person->isMember()), requesting_person(req_person),
                                                                                      requested_title(req_title),
                                                                                      requested_book(req_book),
                                                                                      issued_date(issued) {}

Request::Request(Person *req_person, Title *req_title, Book *req_book, Date issued, unsigned int id)
        : priority_member(req_person->isMember()), requesting_person(req_person),
          requested_title(req_title), requested_book(req_book), issued_date(issued), request_id(id) {}
*/

Request::~Request() {
    //TODO do I need to delete the dates?
    //delete &issued_date;
    //delete &expiration_date;
}

Request::Request(unsigned int id, bool ful, bool priority) : request_id(id), fulfilled(ful), priority_member(priority) { increaseRequestId(); }

Request::Request(unsigned int id, bool ful, bool priority, Date issued, Date expiration) : request_id(id), fulfilled(ful), priority_member(priority), issued_date(issued), expiration_date(expiration) { increaseRequestId(); }


Request::Request(Person *req_person, Title *req_title) : priority_member(req_person->isMember()),
                                                         requesting_person(req_person),
                                                         requested_title(req_title),
                                                         requested_book(NULL),
                                                         request_id(Request::id) { increaseRequestId(); }

Request::Request(Person *req_person, Title *req_title, unsigned int id) : priority_member(req_person->isMember()),
                                                                          requesting_person(req_person),
                                                                          requested_title(req_title),
                                                                          requested_book(NULL),
                                                                          request_id(id) { increaseRequestId(); }


Request::Request(Person *req_person, Title *req_title, Book *req_book) : priority_member(req_person->isMember()), requesting_person(req_person),
                                                                         requested_title(req_title),
                                                                         requested_book(req_book),
                                                                         request_id(Request::id) { increaseRequestId(); }

Request::Request(Person *req_person, Title *req_title, Book *req_book, unsigned int id) : priority_member(req_person->isMember()),
                                                                                          requesting_person(req_person),
                                                                                          requested_title(req_title),
                                                                                          requested_book(req_book),
                                                                                          request_id(id) { increaseRequestId(); }

Request::Request(Person *req_person, Title *req_title, Date issued, Date expiration) : priority_member(req_person->isMember()),
                                                                                       requesting_person(req_person),
                                                                                       requested_title(req_title),
                                                                                       requested_book(NULL),
                                                                                       issued_date(issued),
                                                                                       expiration_date(expiration),
                                                                                       fulfilled(true),
                                                                                       request_id(Request::id) { increaseRequestId(); }

Request::Request(Person *req_person, Title *req_title, Date issued, Date expiration, unsigned int id) : priority_member(req_person->isMember()),
                                                                                                        requesting_person(req_person),
                                                                                                        requested_title(req_title),
                                                                                                        requested_book(NULL),
                                                                                                        issued_date(issued),
                                                                                                        expiration_date(expiration),
                                                                                                        fulfilled(true),
                                                                                                        request_id(id) { increaseRequestId(); }


Request::Request(Person *req_person, Title *req_title, Book *req_book, Date issued, Date expiration) : priority_member(req_person->isMember()), requesting_person(req_person),
                                                                                                       requested_title(req_title),
                                                                                                       requested_book(req_book),
                                                                                                       issued_date(issued),
                                                                                                       expiration_date(expiration),
                                                                                                       fulfilled(true),
                                                                                                       request_id(Request::id) { increaseRequestId(); }

Request::Request(Person *req_person, Title *req_title, Book *req_book, Date issued, Date expiration, unsigned int id) : priority_member(req_person->isMember()),
                                                                                                                        requesting_person(req_person),
                                                                                                                        requested_title(req_title),
                                                                                                                        requested_book(req_book),
                                                                                                                        issued_date(issued),
                                                                                                                        expiration_date(expiration),
                                                                                                                        fulfilled(true),
                                                                                                                        request_id(id) { increaseRequestId(); }


unsigned int Request::getId() const {
    return request_id;
}

Person *Request::getPerson() const {
    return requesting_person;
}

void Request::setPerson(Person *p) {
    requesting_person = p;
}

Title *Request::getTitle() const {
    return requested_title;
}

void Request::setTitle(Title *t) {
    requested_title = t;
}

bool Request::hasBook() const {
    return requested_book != NULL;
}

Book *Request::getBook() const {
    if (!hasBook()) {
        throw RequestDoesntHaveBook();
    }
    return requested_book;
}

void Request::setBook(Book *b) {
    requested_book = b;
}

Date Request::getIssuedDate() {
    if (!fulfilled) {
        throw RequestNotFulfilled();
    }
    return issued_date;
}

Date Request::getExpirationDate() {
    if (!fulfilled) {
        throw RequestNotFulfilled();
    }
    return expiration_date;
}

void Request::setRequestDate(Date issued, Date expiration) {
    issued_date = issued;
    expiration_date = expiration;
}

void Request::fulfillRequest(Date issued, Date expiration, Book *b) {
    if (fulfilled) {
        throw RequestAlreadyFulfilled();
    }
    /*
    if (d < issued_date || d == issued_date) {
        throw InvalidExpirationDate(expiration_date, d);
    }*/
    fulfilled = true;
    requested_book = b;
    issued_date = issued;
    expiration_date = expiration_date;
}

bool Request::isFulfilled() const {
    return fulfilled;
}

bool Request::isPriority() const {
    return priority_member;
}

bool operator<(const Request &rq1, const Request &rq2) {
    if (rq1.getPerson()->isMember() && !rq2.getPerson()->isMember()) {
        //A person only has priority if they are a member and the other isn't
        return true;
    }
    return false;

}

void Request::printRequest(std::stringstream &ss) const {
    ss << '\n';
    ss << "Request id: " << request_id << '\n';
    ss << "Requested title: " << requested_title->getName() << '\n';
    ss << "Requesting person: " << requesting_person->getName() << '\n';
    if (hasBook()) {
        ss << "Requested book belongs to: " << requested_book->getOwner()->getName() << '\n';
    }

    if (isFulfilled()) {
        ss << "The request has been fulfilled\n";
        ss << "Issued date: " << issued_date << '\n';
        ss << "Expiration date: " << expiration_date << '\n';
    } else {
        ss << "The request is still pending\n";
    }

}

void Request::printRequest() const {
    std::stringstream ss;
    printRequest(ss);
    std::cout << ss.str();
}

void Request::print(std::stringstream &ss) const {
    ss << "Request" << '\n';
    ss << "Request id: " << request_id << '\n';
    ss << "Requested title: " << requested_title << '\n';
    ss << "Requesting person: " << requesting_person << '\n';
    if (hasBook()) {
        ss << "Requested book: " << requested_book << '\n';
    }
    ss << "Request is fulfilled: " << fulfilled;
    if (isFulfilled()) {
        ss << "Issued date: " << issued_date << '\n';
        ss << "Expiration date: " << expiration_date << '\n';
    }
}

void Request::print() const {
    std::stringstream ss;
    print(ss);
    std::cout << ss.str();
}

std::ostream &operator<<(std::ostream &os, const Request &request) {
    std::stringstream ss;
    request.print(ss);
    os << ss.str();
    return os;
}

void Request::saveRequest(std::ofstream &ofs) const {
    ofs << getId() << ' ' << isFulfilled() << ' ' << isPriority() << ' ' << getPerson()->getId() << ' ' << getTitle()->getId() << ' ';
    if (hasBook()) {
        ofs << getBook()->getId() << ' ';
    } else {
        ofs << -1 << ' ';
    }
    issued_date.saveDate(ofs);
    ofs << ' ';
    expiration_date.saveDate(ofs);
    ofs << '\n';
}

RequestData Request::loadRequest(std::ifstream &ifs) {
    unsigned int r_id, p_id, t_id;
    int b_id;
    bool fulfilled, priority;
    Date issued, expiration;

    ifs >> r_id >> fulfilled >> priority >> p_id >> t_id >> b_id >> issued >> expiration;
    RequestData r_data{r_id, fulfilled, priority, p_id, t_id, b_id, issued, expiration};
    return r_data;
}

void Request::initializeRequest(const RequestData &r_data, const std::map<unsigned int, Person *> &people_map, const std::map<unsigned int, Title *> &title_map, const std::map<unsigned int, Book *> &book_map) {
    Person *p = people_map.at(r_data.person_id);
    setPerson(p);

    Title *t = title_map.at(r_data.title_id);
    setTitle(t);

    Book *b = NULL;
    if (r_data.book_id != -1) {
        b = book_map.at(r_data.book_id);
    }
    setBook(b);
}
