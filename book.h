//
// Created by henri on 16/10/2020.
//

#ifndef AEDA_2MIEIC02_09_READING_CLUB_BOOK_H
#define AEDA_2MIEIC02_09_READING_CLUB_BOOK_H

#include "object.h"
#include <ostream>
#include <map>

class Person;

class Title;

class Request;

class BookData;

/*!
 * @brief Book in the Library or owned by a Person
 */
class Book: public Object {
    /*!
     * @brief Book object identifier
     */
    static unsigned int id;

    /*!
     * @brief The id of the Book
     */
    unsigned int book_id;

    /*!
     * @brief The monetary value of the book
     */
    unsigned int value;

    /*!
     * @brief The Title of the book
     */
    Title *title;

    /*!
     * @brief The Person who owns the book
     */
    Person *owner;

    /*!
     * @brief The Request for the book
     * @details Pointer to a Request if the request has been fulfilled, NULL pointer otherwise<br>NULL on construction unless specified
     */
    Request *request;

    /*!
     * @brief Increases #id
     * @return New #id
     */
    static int increaseBookId() { return ++id; }

public:

    /*!
     * @brief Sets the #book_id
     * @param new_id Id to be set
     */
    static void setBookId(unsigned int new_id) { id = new_id; }

    /*!
     * @brief Book destructor
     */
     ~Book();

    /*!
     * @brief Constructs a Book
     */
    Book();

    /*!
     * @brief Constructs a Book
     * @param id The #book_id
     */
    Book(unsigned int id);

    /*!
     * @brief Constructs a Book
     * @param id The #book_id
     * @param val The #value
     */
    Book(unsigned int id, unsigned int val);

    /*!
     * @brief Constructs a Book
     * @param tit The #title
     * @param val The #value
     */
    Book(Title *tit, unsigned int val);

    /*!
     * @brief Constructs a Book
     * @details Adds the book to the #owner's Person::books
     * @param tit The #title
     * @param own The #owner
     * @param val The #value
     */
    Book(Title *tit, Person *own, unsigned int val);

    /*!
     * @brief Constructs a Book
     * @param tit The #title
     * @param val The #value
     * @param id The #book_id
     */
    Book(Title *tit, unsigned int val, unsigned int id);
    /*!
     * @brief Constructs a Book
     * @details Adds the book to the #owner's Person::books
     * @param tit The #title
     * @param own The #owner
     * @param val The #value
     * @param id The #book_id
     */
    Book(Title *tit, Person *own, unsigned int val, unsigned int id);

    /*!
     * @brief Gets the id of the book
     * @return The #book_id
     */
    unsigned int getId() const;

    /*!
     * @brief Gets if the book is in the library
     * @return True if it is, false otherwise
     */
    bool isInTheLibrary() const;

    /*!
     * @brief Gets the Person who owns the book
     * @return The #owner
     */
    Person *getOwner() const;

    /*!
     * @brief Sets the #owner
     * @param p The Person to be the ownner
     */
    void setOwner(Person *p);

    /*!
     * @brief Gets the title of the book
     * @return The #title
     */
    Title *getTitle() const;

    /*!
     * @brief Sets the #title of the book
     * @param t The Title the book represents
     */
    void setTitle(Title *t);

    /*!
     * @brief Gets the monetary value of the book
     * @return The #value
     */
    unsigned int getValue() const;

    /*!
     * @brief Gets the Request of the book
     * @details A pointer to a request if there is a request, NULL otherwise
     * @return The #request
     */
    Request *getRequest() const;

    /*!
     * @brief If the book has a Request
     * @return true if has a request, false otherwise
     */
    bool hasRequest() const;

    /*!
     * @brief Sets the #request of the book
     * @details Sets the Requests, which can be NULL
     * @param r The Request to be set
     */
    void setRequest(Request *r);

    /*!
     * @brief Requests the Book from the Library
     * @details A request to this book has been fulfilled<br>Request can't be NULL
     * @param req
     */
    void requestBook(Request *req);

    /*!
     * @brief Returs the book to the library
     */
    void returnBook();

    static bool bookComparatorId(const Book *b1, const Book* b2);
    static bool bookComparatorValue(const Book *b1, const Book* b2);
    static bool bookComparatorTitle(const Book *b1, const Book* b2);
    static bool bookComparatorOwner(const Book *b1, const Book* b2);
    static bool bookIsInTheLibrary(const Book *b1, const Book*b2);

    /*!
     * @brief Prints the value to a stream
     * @param ss The stream to print to
     */
    void printValue(std::stringstream &ss) const;

    /*!
     * @brief Prints the value to the console
     */
    void printValue() const;
    /*!
     * @brief Prints the Book in a friendly way to a stream
     * @param ss The stream to print to
     */
    void printObject(std::stringstream &ss) const;

    /*!
     * @brief Prints the Book in a friendly way to the console
     */
    void printObject() const;

    /*!
     * @brief Prints the Book to a stream
     * @details Prints the #book_id, the #owner, the #title, the #request, if applicable, and the #value
     * @param ss The stream to print to
     */
    void print(std::stringstream &ss) const;

    /*!
     * @brief Prints the Book to the console
     * @details Prints the #book_id, the #owner, the #title, the #request, if applicable, and the #value
     * @see print(std::stringstream &ss) const
     */
    void print() const;

    friend std::ostream &operator<<(std::ostream &os, const Book &book);


    /*
     * Should save the id of the book
     * Save the id's of the owner, title and request
     */
    //std::ostream saveBook() const;
    /*!
     * @brief Saves the information of the Book
     * @param ofs Stream to save the information to
     */
    void saveBook(std::ofstream &ofs) const;

    /*!
     * @brief Loads the BookData from memory
     * @details Loads the BookData so we can later initialize the book
     * @param ifs where the data is fetched from
     * @return The BookData
     */
    static BookData loadBook(std::istream &ifs);

    /*!
     * @brief Initalizes the Book from the BookData and the maps
     * @details Uses the ids in the BookData and the maps to initialize the book
     * @param b_data The BookData
     * @param people_map Maps each id to a pointer to a Person
     * @param title_map Maps each id to a pointer to a Title
     * @param request_map Maps each id to a  pointer to a Request
     */
    void initializeBook(const BookData &b_data, const std::map<unsigned int, Person *> &people_map, const std::map<unsigned int, Title *> &title_map, const std::map<unsigned int, Request *> &request_map);
};

/*!
 * @brief Holds the temporary uninitialized data of a Book
 */
struct BookData {
    /*!
     * @brief The id of the Book
     * @see Book::book_id
     */
    unsigned int id;

    /*!
     * @brief The monetary value
     * @see Book::value
     */
    unsigned int value;

    /*!
     * @brief The id of the book's Title
     * @see Book::title
     */
    unsigned int title_id;

    /*!
     * @brief The id of the Person who owns the book
     * @see Book::owner
     */
    unsigned int person_id;


    /*!
     * @brief The id of the book's Request
     * @see Book::request
     */
    int request_id; // -1 if doesn't exist

};

#endif //AEDA_2MIEIC02_09_READING_CLUB_BOOK_H
