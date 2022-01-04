//
// Created by henri on 25/10/2020.
//

#include "library.h"
#include "person.h"
#include "title.h"
#include "book.h"
#include "request.h"
#include <algorithm>
#include <map>
#include <fstream>
#include <iostream>

Library::~Library() {
    for (auto p: people) {
        delete p;
    }
    for (auto t: titles) {
        delete t;
    }
}

Library::Library() {}


std::vector<Person *> Library::getNonMembers() {
    std::vector<Person *> non_members;
    for (auto p: people) {
        if (!p->isMember()) {
            non_members.push_back(p);
        }
    }
    return non_members;
}

std::vector<Person *> Library::getMembers() {
    return members;
}

std::vector<Person *> Library::getPeople() {
    return people;
}

void Library::removePerson(Person *person) {
    for (auto it = books.begin(); it != books.end(); it++) {
        if ((*it)->getOwner() == person) {
            throw PersonHasBooksInLibrary();
        }
    }
    for (auto t: titles) {
        try {
            t->getReview(person);
            throw PersonHasReviews();
        }
        catch (PersonDidntMakeReview e) {
            //No problem
            //Should make a Critique::hasReview(Person *person)
        }
    }
    if (person->hasRequest()) {
        try {
            person->getRequest()->getTitle()->removeRequest(person);
            person->removeRequest();
        }
        catch (PersonIsBorrowing e) {
            // std::cout << "Caught exception. ";
            throw e;
        }
    }
    auto it = find(people.begin(), people.end(), person);
    people.erase(it);
    // There should be no way we are calling this function and the person was not in the library

    if (person->isMember()) {
        it = find(members.begin(), members.end(), person);
        members.erase(it);
    }
}

std::vector<Title *> Library::getTitles() {
    return titles;
}


void Library::removeTitle(Title *title) {
    if (title->getBooks().size() != 0) {
        throw TitleStillHasBooks();
    }

    for (auto p: people) {
        auto books = p->getBooks();
        for (auto b: books) {
            if (b->getTitle() == title) {
                throw BookHasTitle();
            }
        }
    }
    for (auto it = titles.begin(); it != titles.end(); it++) {
        if ((*it) == title) {
            titles.erase(it);
            return;
        }
    }
}

std::vector<Book *> Library::getBooks() {
    return books;
}

bool Library::addBook(Book *book) {
    if (!titleExists(book->getTitle())) {
        addTitle(book->getTitle());
    }
    books.push_back(book);
    book->getTitle()->addBook(book);
    return true;
}

bool Library::removeBook(Book *book) {
    if (!bookExists(book)) {
        throw BookDoesNotExist();
    }

    if (book->getTitle()->existsBook(book)) {
        try {
            book->getTitle()->removeBook(book);
        }
        catch (BookBeingLent e) {
            throw;
        }
    }

    /*
    try{
        auto requestsSize = book->getTitle()->getRequests().size();
        if(requestsSize != 0){
            throw BookStillBeingLent();
        }
    }
    catch(BookStillBeingLent e){
        std::cout << "Caught exception. ";
        throw e;
    }*/

    for (auto it = books.begin(); it != books.end(); it++) {
        if ((*it) == book) {
            books.erase(it);
            return true;
        }
    }
    return true; //Book was not in the book vector in the first place (Should be fine)
}

Person *Library::addPerson(std::string name) {
    if (personExists(name, people)) {
        return NULL;
    }
    Person *newPerson = new Person(name);
    people.push_back(newPerson);
    return newPerson;
}

Title *Library::addTitle(Title *title) {
    if (titleExists(title)) {
        return NULL;
    }
    titles.push_back(title);
    return title;
}

Title *Library::addTitle(std::string name, std::string type) {
    if (titleExists(name)) {
        return NULL;
    }
    Title *newTitle = new Title(name, type);
    titles.push_back(newTitle);
    return newTitle;
}

void Library::becomeMember(Person *person) {
    members.push_back(person);  //adds the person to the members vector
    person->turnMember();
}

bool Library::personExists(Person *person, std::vector<Person *> people) {
    for (auto toCompare : people) {  //iterates through member vector
        if (toCompare == person) {    //until it finds the person
            return true;
        }
    }
    return false;   //if the person is not found
}

bool Library::personExists(std::string name, std::vector<Person *> people) {
    for (auto toCompare : people) {  //iterates through member vector
        if (toCompare->getName() == name) {    //until it finds the person
            return true;
        }
    }
    return false;   //if the person is not found
}

bool Library::memberExists(Person *person) {
    for (auto toCompare : members) {  //iterates through member vector
        if (toCompare == person) {    //until it finds the person
            return true;
        }
    }
    return false;   //if the person is not found
}

bool Library::titleExists(Title *title) {
    for (auto toCompare : titles) {  //iterates through title vector
        if (toCompare == title) {    //until it finds the title
            return true;
        }
    }
    return false;   //if the title is not found
}

bool Library::titleExists(std::string title) {
    for (auto toCompare : titles) {  //iterates through title vector
        if (toCompare->getName() == title) {    //until it finds the title
            return true;
        }
    }
    return false;   //if the title is not found
}

bool Library::bookExists(Book *book) {
    for (auto toCheck : books) {  //iterates through book vector
        if (toCheck == book) {    //until it finds the book
            return true;
        }
    }
    return false;   //if the book is not found
}

bool Library::bookExists(std::string ownerName, std::string title) {
    for (auto toCheck : books) {  //iterates through book vector
        if (toCheck->getTitle()->getName() == title &&
            toCheck->getOwner()->getName() == ownerName) {    //until it finds the book
            return true;
        }
    }
    return false;   //if the book is not found
}

bool Library::requestTitle(Person *person, Title *title, Date date) {
    bool fulfilled;
    //try {
    if (!(person->isMember())) {
        if (person->getBalance() >= request_credit) {
            person->payCredit(request_credit);
        } else {
            throw PersonIsInDebt();
        }

    }
    /*
    }

    catch (PersonIsInDebt e) {
        std::cout << "Caught exception. ";
        throw e;
    }*/

    try {
        fulfilled = title->requestTitle(person, date);   //requests the title
    }
    catch (...) {
        //std::cout << "Caught exception. ";
        throw;
    }
    return fulfilled;
}


bool Library::requestBook(Person *person, Book *book, Date date) {
    bool fulfilled;
    //try {
    if (!(person->isMember())) {
        if (person->getBalance() >= request_credit) {
            person->payCredit(request_credit);
        } else {
            throw PersonIsInDebt();
        }

    }/*
    }

    catch (PersonIsInDebt e) {
        std::cout << "Caught exception. ";
        throw e;
    }*/

    Title *bookTitle = book->getTitle();                        //gets the book's title

    try {
        fulfilled = bookTitle->requestTitle(person, book, date);
    }
    catch (...) {
        //std::cout << "Caught exception. ";
        throw;
    }

    return fulfilled;
}

bool Library::renewBook(Person *person, Book *book, Date date) {

    bool fulfilled;
    try {
        returnBook(person, book, date); //return the book
    }
    catch (...) {
        throw;
    }

    try {
        fulfilled = book->getTitle()->requestTitle(person, date); //request the book's title
    }
    catch (...) {
        std::cout << "Caught exception. ";
        throw;
    }

    return fulfilled;
}

void Library::cancelRequest(Person *person) {
    if (!person->hasRequest()) {
        throw PersonDoesntHaveRequest();
    }
    if (person->getRequest()->isFulfilled()) {
        throw PersonIsBorrowing();
    }
    person->getRequest()->getTitle()->removeRequest(person);
    person->addBalance(request_credit);

}

void Library::returnBook(Person *person, Book *book, Date date) {

    Date expectedDate = person->getRequest()->getExpirationDate();

    if (date - expectedDate > 0) {    //if the book was returned late
        unsigned int toFine = totalTardinessFine(person, book, date);
        finePerson(person, toFine);
    }

    try {
        book->getTitle()->returnTitle(book->getRequest(), date);
    }
    catch (...) {
        //std::cout << "Caught exception. ";
        throw;
    }


    //book->returnBook();
    //person->removeRequest();           //make the book request NULL
    //book->getTitle()->addBook(book);    //add the book to the title again
    //addBook(book);
}

void Library::lostBook(Person *person, Book *book) {


    unsigned int bookValue = getLosingFine(book);
    Person *owner = book->getOwner();
    person->payPerson(owner, bookValue);
    unsigned int toFine = getLosingFine(book);
    finePerson(person, toFine);

    try {
        book->getTitle()->loseBook(book);
        person->removeRequest();
    }
    catch (TitleRequestsError e) {
        //std::cout << "DATA ERROR";
        throw;
    }
    catch (...) {
        //std::cout << "Caught exception. ";
        throw;
    }

    try {
        removeBook(book);
    }
    catch (...) {
        //std::cout << "Caught exception. ";
        throw;
    }

    try {
        owner->removeBook(book);
    }
    catch (...) {
        //std::cout << "Caught exception. ";
        throw;
    }

}

unsigned int Library::getLosingFine(Book *book) const {
    return book->getValue();
}

unsigned int Library::getDelayFine(Date expected, Date delivered) const {
    //it seems that the - operator in Date returns days, which I hope it does (looking at you, dom)
    int dayDifference = delivered - expected;
    return dayDifference * 5;
}

unsigned int Library::totalTardinessFine(Person *person, Book *book, Date date) {
    //FULL FINE = valor livro * 2 + 5 * day
    Date expectedDate = person->getRequest()->getExpirationDate();
    unsigned int delayFine = getDelayFine(expectedDate, date);
    return book->getValue() * 2 + delayFine;
}

void Library::finePerson(Person *person, unsigned int amount) {
    person->addBalance(-amount);
}

std::vector<Book *> Library::searchForBooks(std::string name, std::string title) {

    if (!bookExists(name, title)) {
        throw BookDoesNotExist();
    }

    std::vector<Book *> toReturn;

    for (auto book : books) {
        if (book->getTitle()->getName() == title && book->getOwner()->getName() == name) {
            toReturn.push_back(book);
        }
    }
    return toReturn;
}

Person *Library::searchForPerson(std::string name, std::vector<Person *> people) {
    if (!personExists(name, people)) {
        throw PersonDoesNotExist();
    }

    for (auto p : people) {
        if (p->getName() == name) {
            return p;
        }
    }
    return NULL;
}

Title *Library::searchForTitle(std::string name) {
    if (!titleExists(name)) {
        throw TitleDoesNotExist();
    }

    for (auto t : titles) {
        if (t->getName() == name) {
            return t;
        }
    }
    return NULL;
}

/*
std::ostream &operator<<(std::ostream &os, const Library &library) {
    //TODO but probably not needed
    return os;
    //return <#initializer#>;
}*/

void Library::saveLibrary() const {

    try {
        savePeople();
        saveTitles();
        saveBooks();
        saveRequests();
    }
    catch (CantOpenFile e) {
        throw e;
    }
    catch (ErrorClosingFile e) {
        throw e;
    }
}

void Library::savePeople() const {
    std::ofstream people_file;
    try {
        people_file.open("people.txt", std::ofstream::trunc);
    }
    catch (...) {
        throw CantOpenFile("people.txt");
    }
    people_file << people.size() << '\n';
    for (auto p: people) {
        p->savePerson(people_file);
    }
    try {
        people_file.close();
    }
    catch (...) {
        throw ErrorClosingFile("people.txt");
    }
}

void Library::saveTitles() const {
    std::ofstream title_file;
    try {
        title_file.open("titles.txt", std::ofstream::trunc);
    }
    catch (...) {
        throw CantOpenFile("titles.txt");
    }
    title_file << titles.size() << '\n';
    for (auto t: titles) {
        t->saveTitle(title_file);
    }
    try {
        title_file.close();
    }
    catch (...) {
        throw ErrorClosingFile("titles.txt");
    }
}

void Library::saveBooks() const {
    int no_books = 0;
    std::ofstream book_file;
    try {
        book_file.open("books.txt", std::ofstream::trunc);
    }
    catch (...) {
        throw CantOpenFile("books.txt");
    }

    for (auto p: people) {
        no_books += p->getBooks().size();
    }
    book_file << no_books << '\n';
    for (auto p: people) {
        std::vector<Book *> books = p->getBooks();
        for (auto b: books) {
            b->saveBook(book_file);
        }
    }

    try {
        book_file.close();
    }
    catch (...) {
        throw ErrorClosingFile("books.txt");
    }
}

void Library::saveRequests() const {
    std::ofstream requests_file;
    try {
        requests_file.open("requests.txt", std::ofstream::trunc);
    }
    catch (...) {
        throw CantOpenFile("requests.txt");
    }
    int no_requests = 0;
    for (auto t:titles) {
        no_requests += t->getRequests().size();
    }
    requests_file << no_requests << '\n';
    for (auto t: titles) {
        for (auto r: t->getRequests()) {
            r->saveRequest(requests_file);
        }
    }

    try {
        requests_file.close();
    }
    catch (...) {
        throw ErrorClosingFile("requests.txt");
    }
}

void Library::loadLibrary() {
    std::map<unsigned int, Person *> people_map;
    std::map<unsigned int, Title *> title_map;
    std::map<unsigned int, Book *> book_map;
    std::map<unsigned int, Request *> request_map;

    try {
        auto people_data = createPeople(people_map);
        auto titles_data = createTitles(title_map, people_map);
        auto requests_data = createRequests(request_map);
        initializeBooks(book_map, title_map, people_map,
                        request_map); //Don't need createBooks since this already does that (Has all of the maps necessaries already)
        initializePeople(people_map, book_map, request_map, people_data);
        initializeTitles(title_map, book_map, request_map, titles_data);
        initializeRequests(request_map, people_map, title_map, book_map, requests_data);
        updateIds(request_map, people_map, title_map, book_map);
    }
    catch (CantOpenFile e) {
        throw e;
    }
    catch (ErrorClosingFile e) {
        throw e;
    }
}

std::map<unsigned int, PersonData> Library::createPeople(std::map<unsigned int, Person *> &people_map) {
    int no_people;
    std::map<unsigned int, PersonData> people_data;
    std::ifstream people_file;
    try {
        people_file.open("people.txt");
    }
    catch (...) {
        throw CantOpenFile("people.txt");
    }
    if (!people_file.is_open()) {
        throw CantOpenFile("people.txt");
    }
    people_file >> no_people;
    for (int i = 0; i < no_people; i++) { // Might need to use a different condition
        PersonData p_data = Person::loadPerson(people_file);
        Person *p = new Person(p_data.name, p_data.balance, p_data.id, p_data.is_member);
        people_data[p_data.id] = p_data;
        people_map[p_data.id] = p;
        people.push_back(p);
        if (p->isMember()) {
            members.push_back(p);
        }
    }

    try {
        people_file.close();
    }
    catch (...) {
        throw ErrorClosingFile("people.txt");
    }
    return people_data;
}


std::map<unsigned int, TitleData>
Library::createTitles(std::map<unsigned int, Title *> &title_map, std::map<unsigned int, Person *> &people_map) {
    int no_titles;
    std::map<unsigned int, TitleData> titles_data;
    std::ifstream title_file;
    try {
        title_file.open("titles.txt");
    }
    catch (...) {
        throw CantOpenFile("titles.txt");
    }
    if (!title_file.is_open()) {
        throw CantOpenFile("titles.txt");
    }
    title_file >> no_titles;
    for (int i = 0; i < no_titles; i++) {
        TitleData t_data = Title::loadTitle(title_file, people_map);
        title_map[t_data.id] = t_data.title; //The loadTitle should already create a pointer, store it, and return it in the data
        titles_data[t_data.id] = t_data;
        titles.push_back(t_data.title);
    }

    try {
        title_file.close();
    }
    catch (...) {
        throw ErrorClosingFile("titles.txt");
    }
    return titles_data;
}

std::map<unsigned int, RequestData> Library::createRequests(std::map<unsigned int, Request *> &request_map) {
    int no_requests;
    std::map<unsigned int, RequestData> requests_data;
    std::ifstream request_file;
    try {
        request_file.open("requests.txt");
    }
    catch (...) {
        throw CantOpenFile("requests.txt");
    }
    if (!request_file.is_open()) {
        throw CantOpenFile("requests.txt");
    }
    request_file >> no_requests;
    for (int i = 0; i < no_requests; i++) {
        RequestData r_data = Request::loadRequest(request_file);
        Request *r = NULL;
        if (r_data.fulfilled) {
            r = new Request(r_data.id, r_data.fulfilled, r_data.priority_member, r_data.issued, r_data.expiration);
        } else {
            r = new Request(r_data.id, r_data.fulfilled, r_data.priority_member);
        }
        request_map[r_data.id] = r; //The loadTitle should already create a pointer, store it, and return it in the data
        requests_data[r_data.id] = r_data;
    }

    try {
        request_file.close();
    }
    catch (...) {
        throw ErrorClosingFile("requests.txt");
    }
    return requests_data;
}

void Library::initializeBooks(std::map<unsigned int, Book *> &book_map, std::map<unsigned int, Title *> &title_map,
                              const std::map<unsigned int, Person *> &people_map,
                              const std::map<unsigned int, Request *> &request_map) {
    int no_books;
    std::ifstream book_file;
    try {
        book_file.open("books.txt");
    }
    catch (...) {
        throw CantOpenFile("books.txt");
    }
    if (!book_file.is_open()) {
        throw CantOpenFile("books.txt");
    }
    book_file >> no_books;
    for (int i = 0; i < no_books; i++) {
        BookData b_data = Book::loadBook(book_file);
        Book *b = new Book(b_data.id, b_data.value);
        book_map[b->getId()] = b;
        b->initializeBook(b_data, people_map, title_map, request_map);
    }

    try {
        book_file.close();
    }
    catch (...) {
        throw ErrorClosingFile("books.txt");
    }

}

void Library::initializePeople(const std::map<unsigned int, Person *> &people_map,
                               const std::map<unsigned int, Book *> &book_map,
                               std::map<unsigned int, Request *> &request_map,
                               const std::map<unsigned int, PersonData> &people_data) {
    for (auto k: people_map) {
        PersonData p_data = people_data.at(k.first);
        k.second->initializePerson(p_data, book_map, request_map);
    }
}


void Library::initializeRequests(const std::map<unsigned int, Request *> &request_map,
                                 const std::map<unsigned int, Person *> &people_map,
                                 const std::map<unsigned int, Title *> &title_map,
                                 const std::map<unsigned int, Book *> &book_map,
                                 const std::map<unsigned int, RequestData> &requests_data) {
    for (auto k: request_map) {
        RequestData r_data = requests_data.at(k.first);
        k.second->initializeRequest(r_data, people_map, title_map, book_map);
    }
}

void Library::initializeTitles(const std::map<unsigned int, Title *> &title_map,
                               const std::map<unsigned int, Book *> &book_map,
                               const std::map<unsigned int, Request *> &request_map,
                               const std::map<unsigned int, TitleData> &title_data) {
    for (auto k: title_map) {
        TitleData t_data = title_data.at(k.first);
        k.second->initializeTitle(t_data, book_map, request_map);
        for (auto b: k.second->getBooks()) {
            books.push_back(b);
        }
    }

}

void Library::updateIds(const std::map<unsigned int, Request *> &request_map,
                        const std::map<unsigned int, Person *> &people_map,
                        const std::map<unsigned int, Title *> &title_map,
                        const std::map<unsigned int, Book *> &book_map) {
    unsigned int max_people_id = 0, max_title_id = 0, max_book_id = 0, max_request_id = 0;

    for (auto k: request_map) {
        unsigned int r_id = k.second->getId();
        if (r_id > max_request_id) {
            max_request_id = r_id;
        }
    }

    for (auto k: title_map) {
        unsigned int t_id = k.second->getId();
        if (t_id > max_title_id) {
            max_title_id = t_id;
        }
    }

    for (auto k: book_map) {
        unsigned int b_id = k.second->getId();
        if (b_id > max_book_id) {
            max_book_id = b_id;
        }
    }

    for (auto k: people_map) {
        unsigned int p_id = k.second->getId();
        if (p_id > max_people_id) {
            max_people_id = p_id;
        }
    }

    // TODO
    // ++<variable> alters the value before calling the function right?
    max_request_id++;
    max_title_id++;
    max_book_id++;
    max_people_id++;
    Request::setRequestId(max_request_id);
    Title::setTitleId(max_title_id);
    Book::setBookId(max_book_id);
    Person::setPersonId(max_people_id);
}
