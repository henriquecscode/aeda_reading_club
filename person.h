//
// Created by henri on 16/10/2020.
//

#ifndef AEDA_2MIEIC02_09_READING_CLUB_PERSON_H
#define AEDA_2MIEIC02_09_READING_CLUB_PERSON_H

#include "object.h"
#include <ostream>
#include <vector>
#include <map>

class Book;
class Request;
struct PersonData;
extern std::string NO_NAME;

/*!
 * @brief Person in the Library
 */
class Person: public Object {

    /*!
     * @brief Person object identifier
     */
    static unsigned int id;

    /*!
     * @brief The id of the Person
     */
    unsigned int person_id;

    /*!
     * @brief The name of the Person
     */
     std::string person_name = NO_NAME;

     /*!
      * @brief The balance of the Person
      */
     int balance;

    /*!
     * @brief If the Person is a member of the book club
     * @details Being a member comes with a few privileges<br>
     * true if is a member, false otherwise
     */
    bool is_member = false;

    /*!
     * @brief Book's owned by the person
     * @details Book's that the person owns. Might be being lent by the book club
     */
    std::vector<Book *> books;

    /*!
     * @brief Request of a Book by the person
     * @details Pointer to a Request if the request has been fulfilled, NULL pointer otherwise<br>NULL on construction, unless specified
     */
    Request *request;

    /*!
     * @brief Increases #id
     * @return New #id
     */
    static int increasePersonId() { return ++id; }

public:

    /*!
     * @brief Sets the #person_id
     * @param new_id Id to be set
     */
    static void setPersonId(unsigned int new_id) { id = new_id; }

    /*!
     * @brief Person destructor
     */
    ~Person();

    /*!
     * @brief Constructs a Person
     */
    Person();

    /*!
     * @brief Constructs a Person
     * @param name The #person_name
     */
    Person(std::string name);

    /*!
     * @brief Constructs a Person
     * @param name The #person_name
     * @param bal The #balance
     */
    Person(std::string name, int bal);

    /*!
     * @brief Constructs a Person
     * @param id The #person_id
     */
    Person(unsigned int id);

    /*!
     *
     * @brief Constructs a Person
     * @param name The #person_name
     * @param id The #person_id
     */
    Person(std::string name, unsigned int id);

    /*!
     * @brief Constructs a Person
     * @param name The #person_name
     * @param is_memb If #is_member
     */
    Person(std::string name, bool is_memb);

    /*!
     * @brief Constructs a Person
     * @param name The #person_name
     * @param bal The #balance
     * @param id The #person_id
     * @param is_memb If #is_member
     */
    Person(std::string name, int bal, unsigned int id, bool is_memb);

    /*!
     * @brief Gets the id of the person
     * @return The #person_id
     */
    unsigned int getId() const;

    /*!
     * @brief Gets the name of the person
     * @return The #person_name
     */
     std::string getName()const;

     /*!
      * @brief Gets the balance of the person
      * @return The #balance
      */
     int getBalance() const;

     /*!
      * @brief Sets the balance of the person
      * @param new_balance The new #balance of the Person
      */
     void setBalance(int new_balance);

     /*!
      * @brief Alters the balance of the person by a given amount
      * @param change The change to the #balance
      */
     void addBalance(int change);

    /*!
     * @brief The person becomes a member
     * @see #is_member
     */
    void turnMember();

    /*!
     * @brief If is a member
     * @return true if is a member, false otherwise
     */
    bool isMember() const;

    /*!
     * @brief Gets the owned books
     * @return Returns a vector with the #books
     */
    std::vector<Book*> getBooks() const;

    /*!
     * @brief Gets if the person has any book available in the library
     * @return True if has at least one book, false otherwise
     */
    bool hasBooksInLibrary() const;

    /*!
     * @brief If has a request
     * @return true if has a request, false otherwise
     */
    bool hasRequest() const;

    /*!
     * @brief Gets the request the person made
     * @details A pointer to a request if there is a request, NULL otherwise
     * @return The #request
     */
    Request * getRequest() const;

    /*!
     * @brief Removes the request
     */
    void removeRequest();

    /*!
     * @brief Gives the Person a #request
     * @details The request the person made has been fulfilled<br>The request can't be NULL
     * @param req The Request the Person issued
     */
    void fulfillRequest(Request *req); //Necessarily not NULL

    /*!
     * @brief Sets the #request
     * @details Sets the request, which can be NULL
     * @param req The Request to be set
     */
    void setRequest(Request *req); // Can be NULL

    /*!
     * @brief Adds a Book to the #books owned
     * @param book Book to be added
     */
    void addBook(Book *book);

    /*!
     * @brief Removes a Book from the #books owned
     * @param book Book to be removed
     */
    void removeBook(Book * book);

    /*!
     * @brief Pays a Person of the Library
     * @param person The Person to be payed
     * @param amount Amount to be payer
     * @return true if payment is successful, false otherwise
     */
    bool payPerson(Person *person, unsigned int amount);

    /*!
     * @brief Payment of a non-member to request a Book
     * @param value Amount to be payed
     * @return true if payment is successful, false otherwise
     */
    bool payCredit(unsigned int value);

    static bool personComparatorId(const Person *p1, const Person *p2);
    static bool personComparatorName(const Person *p1, const Person *p2);
    static bool personComparatorBalance(const Person *p1, const Person*p2);
    static bool personComparatorIsMember(const Person *p1, const Person *p2);
    static bool personComparatorNumberBooks(const Person *p1, const Person *p2);
    /*!
     * @brief Prints each Book to a stream
     * @param ss The stream the #books are printed to
     * @see std::ostream &operator<<(std::ostream &os, const Book &book)
     */
    void printBooks(std::stringstream &ss) const;

    /*!
     * @brief Prints each Book to the console
     * @see printBooks(std::stringstream &ss) const
     */
    void printBooks() const;

    /*!
     * @brief Prints the Person in a friendly way to a stream
     * @param ss The stream to print to
     */
    void printObject(std::stringstream &ss) const;

    /*!
     * @brief Prints the Person in a friendly way to the console
     */
    void printObject() const;

    /*!
     * @brief Prints the Person to a stream
     * @details Prints the #person_id, the #books, if #is_member and the request, if applicable
     * @param ss The stream to print to
     */
    void print(std::stringstream &ss) const;

    /*!
     * @brief Prints the Person to the console
     * @details Prints the #person_d, the #books, if #is_member and the request, if applicable
     * @see print(std::stringstream &ss) const
     */
    void print() const;

    friend std::ostream &operator<<(std::ostream &os, const Person &person);

    /*
     * Should save the id
     * Should save the number of books and their ids
     * Should save the id of the request, -1 if doesn't exist
     */
    //std::ostream savePerson() const;
    /*!
     * @brief Saves the information of the Person
     * @param ofs Stream to save the information to
     */
    void savePerson(std::ofstream &ofs) const;

    /*!
     * @brief Loads the PersonData from memory
     * @details Loads the PersonData so we can later initialize the person
     * @param ifs Where the data is fetched from
     * @return The PersonData
     */
    static PersonData loadPerson(std::ifstream &ifs);

    /*!
     * @brief Initializes the Person from the RequestData and the maps
     * @details Uses the ids in the PersonData and the maps to initialize the person
     * @param p_data The PersonData
     * @param book_map Maps each id to a pointer to a Book
     * @param request_map Maps each id to a pointer to a Request
     */
    void initializePerson(const PersonData &p_data, const std::map<unsigned int, Book *> &book_map, const std::map<unsigned int, Request *> &request_map);
};

/*!
 * @brief Holds the temporary uninitialized data of a Person
 */
struct PersonData {

    /*!
     * @brief The id of the Person
     * @see Person::person_id
     */
    unsigned int id;

    /*!
     * @brief The name of the Person
     * @see Person::person_name
     */
    std::string name;

    /*!
     * @brief The balance of the Person
     * @see Person::balance
     */
     int balance;

    /*!
     * @brief If person is a member
     * @see Person::is_member
     */
    bool is_member = false;

    /*!
     * @brief Ids of the person's books
     * @see Person::books
     */
    std::vector<int> books_ids;

    /*!
     * @brief The id of the person's Request
     * @details Non-negative if has a request, -1 otherwise
     * @see Person::request
     */
    int request_id; // Should be -1 if doesn't exist
};

/*!
 * @brief Tries to remove a Book the Person doesn't own
 * @see Person::books
 * @see Person::removeBook
 */
class PersonDoesntOwnBook {
    const Book *book;
public:
    PersonDoesntOwnBook(const Book *b) : book(b) {}
};
#endif //AEDA_2MIEIC02_09_READING_CLUB_PERSON_H
