//
// Created by henri on 17/10/2020.
//

#ifndef AEDA_2MIEIC02_09_READING_CLUB_REQUEST_H
#define AEDA_2MIEIC02_09_READING_CLUB_REQUEST_H

#include <ostream>
#include <map>
#include "date.h"

class Person;
class Title;
class Book;
class Date;
struct RequestData;

/*!
 * @brief Saves a request to a Title
 */
class Request {
    /*!
     * @brief Request object identifier
     */
    static unsigned int id;

    /*!
     * @brief The id of the Request
     */
    unsigned int request_id;

    /*!
     * @brief If the request has been fulfilled
     * @details true if has been fuliffled, false otherwise
     */
    bool fulfilled = false;

    /*!
     * @brief If the request was issued by a member
     * @deatils true if #requesting_person was a member at the time of the request, false otherwise
     * @see Person#is_member
     */
    bool priority_member;

    /*!
     * @brief The Person requesting the Title
     */
    Person *requesting_person;

    /*!
     * @brief The Title being requested
     */
    Title *requested_title;

    /*!
     * @brief The Book begin requested
     * @details Pointer to a Book if there is a specified book, NULL pointer otherwise<br>NULL on construction, unless specified
     */
    Book *requested_book;

    /*!
     * @brief The Date the Book was lent
     */
    Date issued_date;

    /*!
     * @brief The expiration Date until when the book must be retrieved
     */
    Date expiration_date;

    /*!
     * @brief Increases #id
     * @return New #id
     */
    static unsigned int increaseRequestId() { return ++id; }

public:
    /*
    explicit Request(Date issued);
    Request(Date issued, unsigned int id);
    Request(Person *req_person, Title* req_title, Date issued);
    Request(Person *req_person, Title* req_title, Date issued, unsigned int id);
    Request(Person *req_person, Title* req_title, Book * req_book, Date issued);
    Request(Person *req_person, Title* req_title, Book * req_book, Date issued, unsigned int id);
    */

    /*!
     * @brief Sets the #request_id
     * @param new_id Id to be set
     */
    static void setRequestId(unsigned int new_id){id = new_id;}


    /*!
     * @brief Request destructor
     */
     ~Request();

    /*!
     * @brief Constructs a Request
     * @param id The #request_id
     * @param ful If is #fulfilled
     * @param priority If was issued by a #priority_member
     */
    Request(unsigned int id, bool ful, bool priority);
    /*!
     * @brief Constructs a Request
     * @param id The #request_id
     * @param ful If is #fulfilled
     * @param priority If was issued by a #priority_member
     * @param issued The #issued_date
     * @param expiration The #expiration_date
     */
    Request(unsigned int id, bool ful, bool priority, Date issued, Date expiration);

    /*!
     * @brief Constructs a Request
     * @param req_person The #requesting_person
     * @param req_title The #requested_title
     */
    Request(Person *req_person, Title *req_title);

    /*!
     * @brief Constructs a Request
     * @param req_person The #requesting_person
     * @param req_title The #requested_title
     * @param id The #request_id
     */
    Request(Person *req_person, Title *req_title, unsigned int id);

    /*!
     * @brief Constructs a Request
     * @param req_person The #requesting_person
     * @param req_title The #requested_title
     * @param req_book The #requested_book
     */
    Request(Person *req_person, Title *req_title, Book *req_book);

    /*!
     * @brief Constructs a Request
     * @param req_person The #requesting_person
     * @param req_title The #requested_title
     * @param req_book The #requested_book
     * @param id The #request_id
     */
    Request(Person *req_person, Title *req_title, Book *req_book, unsigned int id);

    /*!
     * @brief Constructs a Request
     * @param req_person The #requesting_person
     * @param req_title The #requested_title
     * @param issued The #issued_date
     * @param expiration The #expiration_date
     */
    Request(Person *req_person, Title *req_title, Date issued, Date expiration);

    /*!
     * @brief Constructs a Request
     * @param req_person The #requesting_person
     * @param req_title The #requested_title
     * @param issued The #issued_date
     * @param expiration The #expiration_date
     * @param id The #request_id
     */
    Request(Person *req_person, Title *req_title, Date issued, Date expiration, unsigned int id);

    /*!
     * @brief Constructs a Request
     * @param req_person The #requesting_person
     * @param req_title The #requested_title
     * @param req_book The #requested_book
     * @param issued The #issued_date
     * @param expiration The #expiration_date
     */
    Request(Person *req_person, Title *req_title, Book *req_book, Date issued, Date expiration);

    /*!
     * @brief Constructs a Request
     * @param req_person The #requesting_person
     * @param req_title The #requested_title
     * @param req_book The #requested_book
     * @param issued The #issued_date
     * @param expiration The #expiration_date
     * @param id The #request_id
     */
    Request(Person *req_person, Title *req_title, Book *req_book, Date issued, Date expiration, unsigned int id);

    /*!
     * @brief Gets the id of the request
     * @return The #request_id
     */
    unsigned int getId() const;

    /*!
     * @brief Gets the person requesting
     * @return The #requesting_person
     */
    Person *getPerson() const;

    /*!
     * @brief Sets the #requesting_person
     * @param p The Person that is requesting
     */
    void setPerson(Person *p);

    /*!
     * @brief Gets the title being requested
     * @return The #requested_title
     */
    Title *getTitle() const;

    /*!
     * @brief Sets the #requested_title
     * @param t The Title to be requested
     */
    void setTitle(Title *t);

    /*!
     * @brief If the request has a specified book
     * @return True if has a book, false otherwise
     */
    bool hasBook() const;

    /*!
     * @brief Gets the book being requested
     * @return The #requested_book
     * @throw RequestDoesntHaveBook
     */
    Book *getBook() const;

    /*!
     * @brief Sets the #requested_book
     * @param b The Book to be requested
     */
    void setBook(Book *b);

    /*!
     * @brief Gets the date the book was lent on
     * @return The #issued_date
     * @throw RequestNotFulfilled
     */
    Date getIssuedDate();

    /*!
     * @brief Gets the date until when the book must be returned
     * @return The #expiration_date
     * @throw RequestNotFulfilled
     */
    Date getExpirationDate();

    /*!
     * @brief Sets the #issued_date and the #request_date
     * @param issued The Date the book was lent on
     * @param expiration The date until when the book must be returned
     */
    void setRequestDate(Date issued, Date expiration);

    /*!
     * @brief Fulfills the request
     * @param issued The #issued_date the book is being lent on
     * @param expiration The #expiration_date until when the book is to be returned
     * @param b The Book being lent
     * @throw RequestAlreadyFulfilled
     */
    void fulfillRequest(Date issued, Date expiration, Book *b);

    /*!
     * @brief If the request has been fulfilled
     * @return true if is #fulfilled, false otherwise
     */
    bool isFulfilled() const;

    /*!
     * @brief If the #requesting_person was a member when they did the request
     * @return true if was a member, false otherwise
     * @see #priority_member
     */
    bool isPriority() const;

    /*!
     * @brief If a request has priority over the other
     * @param rq1 First Request
     * @param rq2 Second Request
     * @return true if first is a member and the other is not, false otherwise
     */
    friend bool operator<(const Request &rq1, const Request &rq2);

    /*!
     * @brief Prints the  Request in a friendly way
     * @param ss The stream to print to
     */
    void printRequest(std::stringstream &ss) const;

    /*!
     * @brief Prints the  Request in a friendly way
     */
    void printRequest() const;

    /*!
     * @brief Prints the Request to a stream
     * @details Prints the #request_id, #requested_title, #requesting_person, #requested_book, #fulfilled, #issued_date, #expiration_date
     * @param ss The stream to print to
     */
    void print(std::stringstream &ss) const;

    /*!
     * @brief Prints the Request to the console
     * @details Prints the #request_id, #requested_title, #requesting_person, #requested_book, #fulfilled, #issued_date, #expiration_date
     * @see print(std::stringstream &ss) const
     */
    void print() const;

    friend std::ostream &operator<<(std::ostream &os, const Request &request);

    /*
     * Should save the id of the request
     * Should save the ids of the other pointer variables
     * Save the date as a char* or the info itself (which ever is easier to create the same date later)
     * Should save the book_id as -1 if doesn't have a book
     */
    //std::ostream saveRequest() const;

    /*!
     * @brief Saves the information of Request
     * @param ofs Stream to save the information to
     */
    void saveRequest(std::ofstream &ofs) const;

    /*!
     * @brief Loads the RequestData from memory
     * @details Loads the RequestData so we can later initialize the request
     * @param ifs Where the data is fetched from
     * @return The RequestData
     */
    static RequestData loadRequest(std::ifstream &ifs);

    /*!
     * @brief Initializes the Request from the RequestData and the maps
     * @details Uses the ids in the RequestDate and the maps to initialize the request
     * @param r_data The RequestData
     * @param people_map Maps each id to a pointer to a Person
     * @param title_map Maps an id to a pointer to a Title
     * @param book_map Maps an id to a pointer to a Book
     */
    void initializeRequest(const RequestData &r_data, const std::map<unsigned int, Person *> &people_map, const std::map<unsigned int, Title *> &title_map, const std::map<unsigned int, Book *> &book_map);

};
/*!
 * @brief Holds the temporary uninitialized data of a Request
 */
struct RequestData {
    //Since Date is present, this struct is a non-aggregate
    /*
    RequestData(unsigned int _id, bool _fulfilled, bool _priority, unsigned int p_id, unsigned int t_id, unsigned int b_id, Date _issued, Date _expiration):
    id(_id), fulfilled(_fulfilled), priority_member(_priority), person_id(p_id), title_id(t_id), book_id(b_id), issued(_issued), expiration(_expiration){};
     */
    //RequestData(const RequestData &r_data){};
    /*!
     * @brief The id of the Request
     * @see Request::request_id
     */
    unsigned int id;

    /*!
     * @brief If request is fulfilled
     * @see Request:fulfilled
     */
    bool fulfilled;

    /*!
     * @brief If person requesting is a member
     * @see Request::priority_member
     */
    bool priority_member;

    /*!
     * @brief The id of the Person
     * @see Request::requesting_person
     */
    unsigned int person_id;

    /*!
     * @brief The id of the Title
     * @see Request::requested_title
     */
    unsigned int title_id;

    /*!
     * @brief The if of the Book
     * @details Non-negative if has a book, -1 otherwise
     * @see Request::requested_book
     */
    int book_id; // Should be -1 if doesn't have a book

    /*!
     * @brief Issued date
     * @see Request::issued_date
     */
    Date issued;

    /*!
     * @brief Expiration date
     * @see Request::expiration_date
     */
    Date expiration;
};

/*
class RequestComparator {
public:
    bool operator()(Request *a, Request *b) {
        return *a < *b;
    }
};*/

/*!
 * @brief Tried to get a Book from a Request, when there wasn't any
 * @see Reuquest::requested_book
 * @see Request::getBook
 */
class RequestDoesntHaveBook {
public:
    RequestDoesntHaveBook() = default;
};

/*!
 * @brief Tried to get the issued or expiration Date of a Request when there wasn't any
 * @see Request::issued_date
 * @see Request::expiration_date
 * @see Request::getIssuedDate
 * @see Request::getExpirationDate
 */
class RequestNotFulfilled {
public:
    RequestNotFulfilled() = default;
};

/*!
 * @brief Tries to fulfill a Request when it was already fulfilled
 * @see Request::fulfilled
 * @see Request::fulfillRequest
 */
class RequestAlreadyFulfilled {
public:
    RequestAlreadyFulfilled(){};
};
/*
class InvalidExpirationDate{
    Date issued_date, expiration_date;
public:
    InvalidExpirationDate(Date issued, Date expiration): issued_date(issued), expiration_date(expiration){};
};*/
#endif //AEDA_2MIEIC02_09_READING_CLUB_REQUEST_H
