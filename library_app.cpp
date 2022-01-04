//
// Created by henri on 14/11/2020.
//

#include "library_app.h"
#include "parser.h"
#include "texts.h"

#include "object.h"
#include "person.h"
#include "critique.h"
#include "title.h"
#include "book.h"
#include <algorithm>
#include <iostream>


LibraryApp::LibraryApp() {
    try {
        loadLibrary();
    }
    catch(...){
        return;
    }

    runLibrary();

    try{
        saveLibrary();
    }
    catch(...){
        return;
    }
}

void LibraryApp::loadLibrary() {
    int op = getOption(LOAD_LIBRARY);
    if (op == 1) {
        try {
            library.loadLibrary();
        }
        catch(...){
            std::cout << LOAD_LIBRARY_EXCEPTION << '\n';
            throw;
        }
    }
}

void LibraryApp::runLibrary() {
    int op;
    while (1) {
        op = getOption(RUN_LIBRARY);
        switch (op) {
            case 0:
                accessPeople(library.getPeople());
                break;
            case 1:
                accessPeople(library.getMembers());
                break;
            case 2:
                accessPeople(library.getNonMembers());
                break;
            case 3:
                accessTitles();
                break;
            case 4:
                accessBooks();
                break;
            case 5:
                addPerson();
                break;
            case 6:
                addTitle();
                break;
            case 7:
                return;

        }
    }
}

void LibraryApp::accessPeople(std::vector<Person *> people) {
    Person *p;
    int op;
    while (1) {
        op = getOption(ACCESS_PEOPLE);
        if (op == 0) {
            return;
        }
        //op == 1
        p = choosePerson(people);
        if (p == NULL) {
            continue;
        }
        try {
            operatePerson(p);
        }
        catch (UIStateOutdated e) {
            return;
        }
        //do what you can to a person
    }
}

void LibraryApp::operatePerson(Person *person) {
    int op;
    while (1) {
        op = getOption(OPERATE_PERSON);
        switch (op) {
            case 0:
                return;
            case 1:
                person->printObject();
                break;
            case 2:
                personEditMembership(person);
                break;
            case 3:
                personMakeRequest(person);
                break;
            case 4:
                personReturnBook(person);
                break;
            case 5:
                personRenewBook(person);
                break;
            case 6:
                personCancelRequest(person);
                break;
            case 7:
                personLostBook(person);
                break;
            case 8:
                personAddBook(person);
                break;
            case 9:
                personAddBalance(person);
                break;
            case 10:
                personRemovePerson(person);
                throw UIStateOutdated();
            case 11:
                personRemoveBook(person);
                break;
        }
    }
}

void LibraryApp::personEditMembership(Person *person) {
    int op;
    while (1) {
        op = getOption(EDIT_MEMBER);
        switch (op) {
            case 0:
                return;
            case 1:
                if (person->isMember()) {
                    std::cout << EDIT_MEMBER_ALREADY_IS_MEMBER << '\n';
                    break;
                }

                if (person->hasBooksInLibrary()) {
                    library.becomeMember(person);
                    std::cout << EDIT_MEMBER_BECOME_MEMBER_SUCCESS << '\n';
                    break;
                }

                if (personMembershipAddBook(person)) {
                    library.becomeMember(person);
                    std::cout << EDIT_MEMBER_BECOME_MEMBER_SUCCESS << '\n';
                } else {
                    std::cout << EDIT_MEMBER_BECOME_MEMBER_FAILURE << '\n';
                }
                break;

            case 2:
                if (personMembershipAddBook(person)) {
                    library.becomeMember(person);
                    std::cout << EDIT_MEMBER_ADD_BOOK_FROM_SELECTION_SUCCESS << '\n';
                } else {
                    std::cout << EDIT_MEMBER_ADD_BOOK_FROM_SELECTION_FAILURE << '\n';
                }
                break;
        }
    }
}

bool LibraryApp::personMembershipAddBook(Person *person) {
    if (person->getBooks().size() == 0) {
        std::cout << EDIT_MEMBER_NO_BOOKS << '\n';
        return false;
    }
    Book *b = NULL;
    std::cout << EDIT_MEMBER_ADD_BOOK_FROM_SELECTION << '\n';
    b = selectBook(person->getBooks());
    if (library.addBook(b)) {
        return true;
    };
    return false;

}

void LibraryApp::personMakeRequest(Person *person) {
    int op;
    Date d;
    bool fulfilled;
    if (person->hasRequest()) {
        std::cout << MAKE_REQUEST_ALREADY_HAS_REQUEST << '\n';
        return;
    }
    while (1) {
        Title *t = NULL;
        Book *b = NULL;
        op = getOption(MAKE_REQUEST);
        switch (op) {
            case 0:
                return;
            case 1:
                t = personMakeRequestTitle();
                break;
            case 2:
                b = personMakeRequestBook();
                break;
        }
        if (b == NULL && t == NULL) {
            std::cout << MAKE_REQUEST_ERROR << '\n';
            continue;
        }
        std::cout << MAKE_REQUEST_GET_DATE << '\n';
        try {
            d = getDate();
        }
        catch (...) {
            std::cout << MAKE_REQUEST_GET_DATE_ERROR << '\n';
            continue;
        }
        try {
            if (t != NULL) {
                fulfilled = library.requestTitle(person, t, d);
            } else if (b != NULL) {
                fulfilled = library.requestBook(person, b, d);
            }
        }
        catch (PersonIsInDebt e) {
            std::cout << MAKE_REQUEST_IN_DEBT << '\n';
            return;
        }
        catch (TitleHasNoBooks e) {
            std::cout << MAKE_REQUEST_TITLE_HAS_NO_BOOKS << '\n';
            return;
        }
        if (fulfilled) {
            std::cout << MAKE_REQUEST_SUCCESS_FULFILLED << '\n';
        } else {
            std::cout << MAKE_REQUEST_SUCCESS_NOT_FULFILLED << '\n';
        }
        return;
    }
}

Title *LibraryApp::personMakeRequestTitle() {
    return chooseTitle();
}

Book *LibraryApp::personMakeRequestBook() {
    int op = getOption(MAKE_REQUEST_BY_BOOK);
    if (op == 0) {
        return NULL;
    }
    if (op == 1) {
        Title *t = chooseTitle();
        if (t == NULL) {
            return NULL;
        }
        return selectBook(t->getBooks());
    }
    if (op == 2) {
        return chooseBook();
    }
    return NULL;
}

void LibraryApp::personReturnBook(Person *person) {
    int op;
    Date d;
    if (!person->hasRequest()) {
        std::cout << RETURN_BOOK_NO_REQUEST << '\n';
        return;
    }
    if (!person->getRequest()->isFulfilled()) {
        std::cout << RETURN_BOOK_NOT_FULFILLED << '\n';
        return;
    }
    while (1) {
        op = getOption(RETURN_BOOK);
        if (op == 0) {
            return;
        }
        try {
            d = getDate();
        }
        catch (...) {
            std::cout << RETURN_BOOK_GET_DATE_ERROR << '\n';
            continue;
        }

        Book *b = person->getRequest()->getBook();
        try {
            library.returnBook(person, b, d);
        }
        catch (RequestForTitleNotFulfilled e) {
            std::cout << RETURN_BOOK_NO_REQUEST << '\n';
            return;

        }
        catch (RequestWasNotStored e) {
            std::cout << RETURN_BOOK_REQUEST_NOT_STORED << '\n';
            return;
        }
        std::cout << RETURN_BOOK_SUCCESS << '\n';
        reviewTitle(person, b->getTitle());
        return;
    }
}

void LibraryApp::personRenewBook(Person *person) {
    int op;
    Date d;
    bool renewed;
    if (!person->hasRequest()) {
        std::cout << RENEW_BOOK_NO_REQUEST << '\n';
        return;
    }
    if (!person->getRequest()->isFulfilled()) {
        std::cout << RENEW_BOOK_NOT_FULFILLED << '\n';
        return;
    }
    while (1) {
        op = getOption(RETURN_BOOK);
        if (op == 0) {
            return;
        }
        try {
            d = getDate();
        }
        catch (...) {
            std::cout << RENEW_BOOK_GET_DATE_ERROR << '\n';
            continue;
        }

        Book *b = person->getRequest()->getBook();
        try {
            renewed = library.renewBook(person, b, d);
        }
        catch (RequestForTitleNotFulfilled e) {
            std::cout << RENEW_BOOK_NO_REQUEST << '\n';
            return;

        }
        catch (RequestWasNotStored e) {
            std::cout << RENEW_BOOK_REQUEST_NOT_STORED << '\n';
            return;
        }
        catch (PersonIsInDebt e) {
            std::cout << RENEW_BOOK_PERSON_IN_DEBT << '\n';
        }
        if (renewed) {
            std::cout << RENEW_BOOK_SUCCESS << '\n';
        } else {
            std::cout << RENEW_BOOK_SUCCESS_MADE_REQUEST << '\n';
        }
        reviewTitle(person, b->getTitle());
        return;

    }
}

void LibraryApp::reviewTitle(Person *p, Title *t) {
    try {
        Review &r = t->getReview(p);
        editReview(p, t, r);
    }
    catch (PersonDidntMakeReview e) {
        addReview(p, t);
    }

}

void LibraryApp::addReview(Person *p, Title *t) {
    int op;
    int rating;
    std::string comment;
    std::cout << ADD_REVIEW_PROMPT << '\n';
    op = getOption(ADD_REVIEW);
    if (op == 0) {
        return;
    }
    std::cout << ADD_REVIEW_GET_RATING << '\n';
    rating = getNumber(1, 5);
    std::cout << ADD_REVIEW_GET_COMMENT_PROMPT << '\n';
    op = getOption(ADD_REVIEW_GET_COMMENT);
    if (op == 0) {
        comment = "";
    } else {
        comment = getLine();
    }
    if (comment == "") {
        t->addReview(new Review(p, t, (Classification) rating));
    } else {
        t->addReview(new Review(p, t, (Classification) rating, comment));
    }
}

void LibraryApp::editReview(Person *p, Title *t, Review &r) {
    int op;
    std::string comment;
    int rating;
    std::cout << EDIT_REVIEW_PROMPT << '\n';
    op = getOption(EDIT_REVIEW);
    if (op == 0) {
        return;
    }
    std::cout << EDIT_REVIEW_PREVIOUS_RATING << r.getClassification() << '\n';
    std::cout << EDIT_REVIEW_GET_RATING_PROMPT << '\n';
    op = getOption(EDIT_REVIEW_GET_RATING);
    if (op == 1) {
        rating = getNumber(1, 5);
        t->getCritique()->updateReview(r, static_cast<Classification>(rating));
    }
    std::cout << EDIT_REVIEW_PREVIOUS_COMMENT << r.getComment() << '\n';
    std::cout << EDIT_REVIEW_GET_COMMENT_PROMT << '\n';
    op = getOption(EDIT_REVIEW_GET_COMMENT);
    if (op == 1) {
        comment = getLine();
        if (comment != "") {
            t->getCritique()->updateReview(r, comment);
        }
    }
}

void LibraryApp::personCancelRequest(Person *person) {
    try{
        library.cancelRequest(person);
    }
    catch(PersonDoesntHaveRequest e){
        std::cout << CANCEL_REQUEST_NO_REQUEST << '\n';
        return;
    }
    catch(PersonIsBorrowing e){
        std::cout << CANCEL_REQUEST_IS_BORROWING << '\n';
        return;
    }
    std::cout << CANCEL_REQUEST_SUCCESS << '\n';
    return;
}


void LibraryApp::personLostBook(Person *person) {
    if (!person->hasRequest() || !person->getRequest()->isFulfilled()) {
        std::cout << LOST_BOOK_NO_BOOK << '\n';
        return;
    }
    try {
        library.lostBook(person, person->getRequest()->getBook());
    }
    catch (...) {
        std::cout << LOST_BOOK_ERROR << '\n';
    }
}

void LibraryApp::personAddBalance(Person *person) {
    int op;
    int bal;
    while (1) {
        op = getOption(PERSON_ADD_BALANCE);
        if (op == 0) {
            return;
        }
        bal = getNumber(0, INT_MAX);
        person->addBalance(bal);
    }
}

void LibraryApp::personAddBook(Person *person) {
    int op;
    int value;
    Title *t;
    std::cout << ADD_BOOK_PROMPT << '\n';
    while (1) {
        op = getOption(ADD_BOOK);
        if (op == 0) {
            return;
        }
        value = getNumber(1, INT_MAX);
        std::cout << ADD_BOOK_GET_TITLE << '\n';
        t = chooseTitle();
        if (t == NULL) {
            std::cout << ADD_BOOK_GET_TITLE_FAILURE << '\n';
            std::cout << ADD_BOOK_CREATE_TITLE_PROMPT << '\n';
            op = getOption(ADD_BOOK_CREATE_TITLE);
            if (op == 0) {
                continue;
            }
            t = addTitle();
        } else {
            std::cout << ADD_BOOK_GET_TITLE_SUCCESS << '\n';
            //Create the book
        }
        new Book(t, person, value); //Constructor with person already adds to the person's books
    }

}

void LibraryApp::personRemovePerson(Person *person) {
    if (person->getBooks().size() != 0) {
        std::cout << REMOVE_PERSON_STILL_HAS_BOOKS << '\n';
    }
    if (person->hasRequest() && person->getRequest()->isFulfilled()) {
        std::cout << REMOVE_PERSON_STILL_HAS_REQUEST << '\n';
    }

    try {
        library.removePerson(person);
    }
    catch (PersonIsBorrowing e) {
        //Redundancy
        std::cout << REMOVE_PERSON_STILL_HAS_REQUEST << '\n';

    }
    catch (PersonHasReviews e) {
        std::cout << REMOVE_PERSON_HAS_REVIEWS << '\n';

    }
    delete person;
    std::cout << REMOVE_PERSON_SUCCESS << '\n';

}

void LibraryApp::personRemoveBook(Person *person) {
    int op;
    bool success;
    Book *b;
    while (1) {
        if (person->getBooks().size() == 0) {
            std::cout << REMOVE_BOOK_NO_BOOKS << '\n';
            return;
        }
        op = getOption(REMOVE_BOOK);
        if (op == 0) {
            return;
        }
        try {
            b = selectBook(person->getBooks());
        }
        catch (SelectObjectFromEmpty) {
            std::cout << REMOVE_BOOK_NO_BOOKS << '\n';
        }
        try {
            success = library.removeBook(b);
            std::cout << REMOVE_BOOK_REMOVED_FROM_LIBRARY << '\n';
        }
        catch (BookDoesNotExist) {
            success = true;
        }
        person->removeBook(b);
        if (success) {
            std::cout << REMOVE_BOOK_SUCCESS << '\n';
            delete b;
        } else {
            std::cout << REMOVE_BOOK_FAILURE << '\n';
        }
    }
}

Person *LibraryApp::choosePerson(std::vector<Person *> people) {
    Person *p;
    std::string name;
    int op;
    while (1) {
        op = getOption(CHOOSE_PEOPLE);
        if (op == 0) {
            return NULL;
        } else if (op == 1) {
            try {
                p = selectPerson(people);
            }
            catch (SelectObjectFromEmpty e) {
                std::cout << CHOOSE_PERSON_EMPTY_EXCEPTION << '\n';
                continue;
            }
            //TODO can choose a member or a non-member even if selected access non-member or members resp.
        } else if (op == 2) {
            name = getLine();
            try {
                p = library.searchForPerson(name, people); //TODO search person static that takes people as an argument
            }
            catch (PersonDoesNotExist e) {
                std::cout << CHOOSE_PERSON_COULDNT_FIND << '\n';
                continue;
            }

        }
        if (p == NULL) {
            std::cout << CHOOSE_PERSON_INVALID << '\n';
            continue;
        }
        return p;
    }
}

Person *LibraryApp::selectPerson(std::vector<Person *> people) const {
    if (people.size() == 0) {
        throw SelectObjectFromEmpty();
    }
    int num;
    personComparator comparator = choosePeopleListingBy();
    listPeopleBy(people, comparator);
    num = getNumber(0, people.size() - 1);
    return people[num];
}

personComparator LibraryApp::choosePeopleListingBy() const {
    std::cout << LIST_PEOPLE_PRESENT << '\n';
    personComparator comparator = NULL;
    int op = getOption(LIST_PEOPLE);
    switch (op) {
        case 0:
            comparator = &Person::personComparatorName;
            break;
        case 1:
            comparator = &Person::personComparatorIsMember;
            break;
        case 2:
            comparator = &Person::personComparatorBalance;
            break;
        case 3:
            comparator = &Person::personComparatorNumberBooks;
            break;
        case 4:
            comparator = &Person::personComparatorId;
            break;
    }
    return comparator;
}

void LibraryApp::listPeopleBy(std::vector<Person *> &people, personComparator comparator) const {
    std::sort(people.begin(), people.end(), comparator);
    printObjectsList(reinterpret_cast<std::vector<Object *> &>(people));
}

void LibraryApp::accessTitles() {
    Title *t;
    int op;
    while (1) {
        op = getOption(ACCESS_TITLE);
        if (op == 0) {
            return;
        }
        t = chooseTitle();
        if (t == NULL) {
            continue;
        }
        try {
            operateTitle(t);
        }
        catch (UIStateOutdated e) {
            return;
        }
    }
}

void LibraryApp::operateTitle(Title *title) {
    int op;
    while (1) {
        op = getOption(OPERATE_TITLE);
        switch (op) {
            case 0:
                return;
            case 1:
                title->printObject();
            case 2:
                title->printRating();
                break;
            case 3:
                title->printReviews();
                break;
            case 4:
                title->printComments();
                break;
            case 5:
                title->printBooks();
                break;
            case 6:
                title->printRequests();
                break;
            case 7:
                //TODO catch the exceptions
                titleRemoveTitle(title);
                throw UIStateOutdated();
        }
    }
}

void LibraryApp::titleRemoveTitle(Title *title) {
    try {
        library.removeTitle(title);
    }
    catch (TitleStillHasBooks e) {
        std::cout << REMOVE_TITLE_FAILURE << '\n';
    }
    catch (BookHasTitle e) {
        std::cout << REMOVE_TITLE_FAILURE << '\n';
    }
    std::cout << REMOVE_TITLE_SUCCESS << '\n';
}

Title *LibraryApp::chooseTitle() {

    Title *t;
    std::string name;
    int op;
    while (1) {
        op = getOption(CHOOSE_TITLE);
        if (op == 0) {
            return NULL;
        }
        if (op == 1) {
            try {
                t = selectTitle(library.getTitles());
            }
            catch (SelectObjectFromEmpty e) {
                std::cout << CHOOSE_TITLE_EMPTY_EXCEPTION << '\n';
                continue;
            }
        }
        if (op == 2) {
            name = getLine();
            t = library.searchForTitle(name);
        }
        if (t == NULL) {
            std::cout << CHOOSE_TITLE_INVALID << '\n';
            continue;
        }
        return t;
    }
}

Title *LibraryApp::selectTitle(std::vector<Title *> titles) const {
    if (titles.size() == 0) {
        throw SelectObjectFromEmpty();
    }
    int num;
    titleComparator comparator = chooseTitleListingBy();
    listTitlesBy(titles, comparator);
    num = getNumber(0, titles.size() - 1);
    return titles[num];
}

titleComparator LibraryApp::chooseTitleListingBy() const {

    std::cout << LIST_TITLE_PRESENT << '\n';
    titleComparator comparator = NULL;
    int op = getOption(LIST_TITLE);
    switch (op) {
        case 0:
            comparator = &Title::titleComparatorName;
            break;
        case 1:
            comparator = &Title::titleComparatorType;
            break;
        case 2:
            comparator = &Title::titleComparatorNumberBooks;
            break;
        case 3:
            comparator = &Title::titleComparatorRating;
            break;
        case 4:
            comparator = &Title::titleComparatorNumberReviews;
            break;
        case 5:
            comparator = &Title::titleComparatorNumberComments;
            break;
        case 6:
            comparator = &Title::titleComparatorId;
    }
    return comparator;
}

void LibraryApp::listTitlesBy(std::vector<Title *> &titles, titleComparator comparator) const {
    std::sort(titles.begin(), titles.end(), comparator);
    printObjectsList(reinterpret_cast<std::vector<Object *> &>(titles));
}

void LibraryApp::accessBooks() {
    Book *b;
    int op;
    while (1) {
        op = getOption(ACCESS_BOOK);
        if (op == 0) {
            return;
        }
        b = chooseBook();
        if (b == NULL) {
            continue;
        }
        try {
            operateBook(b);
        }
        catch (UIStateOutdated()) {
            return;
        }
        //do what you can to a book
    }
}

void LibraryApp::operateBook(Book *book) {
    int op;
    while (1) {
        op = getOption(OPERATE_BOOK);
        switch (op) {
            case 0:
                return;
            case 1:
                book->printObject();
                break;
            case 2:
                book->getTitle()->printObject();
                break;
            case 3:
                book->getOwner()->printObject();
                break;
            case 4:
                book->printValue();
                break;
            case 5:
                if (book->hasRequest()) {
                    book->getRequest()->printRequest();
                } else {
                    std::cout << OPERATE_BOOK_NO_REQUEST << '\n';
                }
                break;
            case 6:
                try {
                    library.removeBook(book);
                }
                catch (BookBeingLent e) {
                    std::cout << OPERATE_BOOK_REMOVE_BOOK_BEING_LENT_EXCEPTION << '\n';
                    continue;
                }
                catch (...) {
                    std::cout << OPERATE_BOOK_REMOVE_BOOK_OTHER_EXCEPTION << '\n';
                    continue;
                }
                std::cout << OPERATE_BOOK_REMOVE_BOOK_SUCCESS << '\n';
                throw UIStateOutdated();
        }
    }

}

Book *LibraryApp::chooseBook() {
    Book *b;
    std::vector<Book *> books;
    int op;
    std::string name, title;

    while (1) {
        op = getOption(CHOOSE_BOOK);
        if (op == 0) {
            return NULL;
        } else if (op == 1) {
            try {
                b = selectBook(library.getBooks());
            }
            catch (SelectObjectFromEmpty e) {
                std::cout << CHOOSE_BOOK_EMPTY_EXCEPTION << '\n';
                continue;
            }
        } else if (op == 2) {
            name = getLine();
            title = getLine();
            try {
                books = library.searchForBooks(name, title);
            }
            catch (BookDoesNotExist e) {
                std::cout << CHOOSE_BOOK_COULDNT_FIND << '\n';
                continue;
            }
            if (books.size() > 1) {
                b = selectBook(books);
            } else if (books.size() == 0) {
                std::cout << CHOOSE_BOOK_INVALID << '\n';
                continue;
            }
        }
        if (b == NULL) {
            std::cout << CHOOSE_BOOK_INVALID << '\n';
            continue;
        }
        return b;
    }
}

Book *LibraryApp::selectBook(std::vector<Book *> books) const {
    if (books.size() == 0) {
        throw SelectObjectFromEmpty();
    }
    int num;
    bookComparator comparator = chooseBookListingBy();
    listBooksBy(books, comparator);
    num = getNumber(0, books.size() - 1);
    return books[num];

}

bookComparator LibraryApp::chooseBookListingBy() const {

    std::cout << LIST_BOOK_PRESENT << '\n';
    bookComparator comparator = NULL;
    int op = getOption(LIST_BOOK);
    switch (op) {
        case 0:
            comparator = &Book::bookComparatorTitle;
            break;
        case 1:
            comparator = &Book::bookComparatorOwner;
            break;
        case 2:
            comparator = &Book::bookComparatorValue;
            break;
        case 3:
            comparator = &Book::bookIsInTheLibrary;
            break;
        case 4:
            comparator = &Book::bookComparatorId;
    }
    return comparator;
}

void LibraryApp::listBooksBy(std::vector<Book *> books, bookComparator comparator) const {
    std::sort(books.begin(), books.end(), comparator);
    printObjectsList(reinterpret_cast<std::vector<Object *> &>(books));
}

void LibraryApp::printObjectsList(std::vector<Object *> &objects) const {
    int op = getOption(LISTING_PARTIAL);
    unsigned int size;
    if (op == 0) {
        size = objects.size();
    } else {
        size = getNumber(1, INT_MAX);
    }
    size = std::min(size, (unsigned int) objects.size());
    for (int i = 0; i < size; i++) {
        std::cout << i << ":\n";
        objects[i]->printObject();
    }
}

void LibraryApp::addPerson() {
    std::string name;
    int balance;
    bool success;
    std::cout << ADD_PERSON_GET_NAME << '\n';
    name = getLine();

    Person *p = library.addPerson(name);
    if (p == NULL) {
        //Name already existed
        std::cout << ADD_PERSON_NAME_ALREADY_EXISTS << '\n';
        return;
    }
    // Could add the person
    std::cout << ADD_PERSON_GET_BALANCE << '\n';
    balance = getNumber(INT_MIN, INT_MAX);
    p->setBalance(balance);
    std::cout << ADD_PERSON_SUCCESS << '\n';

}

Title *LibraryApp::addTitle() {
    std::string name;
    std::cout << ADD_TITLE_GET_NAME << '\n';
    name = getLine();
    return addTitle(name);
}

Title *LibraryApp::addTitle(std::string name) {
    bool success;
    std::string type;
    std::cout << ADD_TITLE_GET_TYPE << '\n';
    type = getLine();

    Title *t = library.addTitle(name, type);

    if (t != NULL) {
        std::cout << ADD_TITLE_SUCCESS << '\n';
    } else {
        std::cout << ADD_TITLE_NAME_ALREADY_EXISTS << '\n';
    }
    return t;

}

void LibraryApp::saveLibrary() {
    int op = getOption(SAVE_LIBRARY);
    if (op == 1) {
        try {
            library.saveLibrary();
        }
        catch(...){
            std::cout << SAVE_LIBRARY_EXCEPTION << '\n';
            throw;
        }
    }
}