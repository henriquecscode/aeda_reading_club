//
// Created by henri on 16/10/2020.
//

#ifndef AEDA_2MIEIC02_09_READING_CLUB_LIBRARY_H
#define AEDA_2MIEIC02_09_READING_CLUB_LIBRARY_H

#include <vector>
#include <ostream>
#include <map>

class Person;

class Title;

class Book;

class Request;

class Date;

struct PersonData;
struct TitleData;
struct RequestData;

/*!
 * @brief Handling of the Person's, Title's and Book's of the book club
 */
class Library {

    /*!
     * @brief The Person's that are member of the club
     */
    std::vector<Person *> members;

    /*!
     * @brief The Person's that interacted with the club
     */
    std::vector<Person *> people;

    /*!
     * @brief The Title's present in the library
     */
    std::vector<Title *> titles;

    /*!
     * @brief The physical Book's present in the library
     */
    std::vector<Book *> books;

    /*!
     * @brief Amount to be paid by a non-member to issue a Request for a Book
     */
    unsigned int request_credit = 5;

public:

    ~Library();

    Library();

    /*!
     * @brief Gets the members of the library
     * @return The #members
     */
    std::vector<Person *> getMembers();

    /*!
     * @brief Gets the non members of the library
     * @return The non-members
     */
    std::vector<Person *> getNonMembers();

    /*!
     * @brief Gets the people in the library
     * @return The #people
     */
    std::vector<Person *> getPeople();

    /*!
     * @brief Creates a person and adds it to the library
     * @param name The Person::name
     * @return The Person created if successful, NULL otherwise
     */
    Person *addPerson(std::string name);

    /*!
     * @brief Removes a person from the library
     * @details Only deletes if there is no review made by the person
     * @param person The Person to be removed
     * @throw PersonHasBooksInLibrary
     * @throw PersonHasReviews
     */
    void removePerson(Person *person);

    /*!
     * @brief Gets the titles in the library
     * @return The #titles
     */
    std::vector<Title *> getTitles();

    /*!
     * @brief Adds a title to the library
     * @param title The title to be added
     * @return The Title created if successful, NULL otherwise
     */
    Title *addTitle(Title *title);

    /*!
     * @brief Creates a title and adds it to the library
     * @param name The Title::name
     * @param type The Title::type
     * @return The Title created if successful, NULL otherwise
     */
    Title *addTitle(std::string name, std::string type);

    /*!
     * @brief Removes a title from the library
     * @param title The Title to be removed
     * @throw TitleStillHasBooks
     * @throw BookHasTitle
     */
    void removeTitle(Title *title);

    /*!
     * @brief Gets the books in the library
     * @return The #books
     */
    std::vector<Book *> getBooks();


    /*!
     * @brief Makes a Book avaialble for the library
     * @param book The Book to be made available
     * @return True if was able to add book, false otherwise
     */
    bool addBook(Book *book);

    /*!
     * @brief Removes a Book from the library
     * @details Removes a book from the library, unless it is being requested
     * @param book The Book to be removed
     * @return True if was able to remove book from library, false otherwise]
     * @throw BookDoesNotExist
     */
    bool removeBook(Book *book);

    /*!
     * @brief A Person becomes a member by making some Book's availalable
     * @param person The Person that intends on becoming a member
     * @param books The Book's donated to be added to the library
     */
    void becomeMember(Person *person/*, std::vector<Book *> books*/);

    /*!
     * @brief Sees if a Person exists in a certain group of people
     * @param person The Person to check if exists
     * @param people The group of Person's
     * @return true if is in #people, false otherwise
     */
    bool personExists(Person *person, std::vector<Person *> people);

    /*!
     * @brief Sees if a Person exists in a certain group of people
     * @param person The name of the person to check if exists
     * @param people The group of Person's
     * @return true if is in #people, false otherwise
     */
    bool personExists(std::string name, std::vector<Person *> people);

    /*!
     * @brief If a certain Person exists and is a member of the club
     * @param person The Person to check if exists and is a member
     * @return true if is in #members, false otherwise
     */
    bool memberExists(Person *person);

    /*!
     * @brief If a certain Title is present in the library
     * @param title The Title to check if exists
     * @return true if is in #titles, false otherwise
     */
    bool titleExists(Title *title);

    /*!
     * @brief If a certain Book is present in the Library
     * @param title The name of the title to check for
     * @return true if is in #titles, false otherwise
     */
    bool titleExists(std::string title);

    /*!
     * @brief If a certain Book is present in the Library
     * @param book The Book to check if exists
     * @return true if is in #books, false otherwise
     */
    bool bookExists(Book *book);

    /*!
     * @brief If a certain Book is present in the Library
     * @param ownerName The name of the owner of the book to check
     * @param title The name of the title of the book to check
     * @return true if is in #books, false otherwise
     */
    bool bookExists(std::string ownerName, std::string title);

    /*!
     * @brief A Person makes a Request for a certain Title on a given Date
     * @param person The Person making the Request
     * @param title The Title to be requested
     * @param date The Date of the Request
     * @return true if the request if fulfilled, false otherwise
     * @throw PersonInDebt
     * @throw PersonAlreadyHasRequest
     * @throw PersonIsInDebt
     * @throw TitleHasNoBooks
     */
    bool requestTitle(Person *person, Title *title, Date date);

    /*!
     * @brief A Person makes a Request for a specific Book on a given Date
     * @param person The Person making the Request
     * @param book The Book to be requested
     * @param date The Date of the Request
     * @return true if the request if fulfilled, false otherwise
     * @throw PersonIsInDebt
     * @throw PersonAlreadyHasRequest
     * @throw TitleHasNoBooks
     */
    bool requestBook(Person *person, Book *book, Date date);


    /*!
     * @brief A Person tries to renew the Request for a Book
     * @param person ThePerson making the renewal Request
     * @param book The Book that was requested and that is going to be renewed
     * @param date TheDate the Request is being renewed on
     * @return true if is able to renew, false otherwise
     * @throw RequestForTitleNotFulfilled
     * @throw RequestWasNotStored
     * @throw PersonAlreadyHasRequest
     * @throw PersonIsInDebt
     */
    bool renewBook(Person *person, Book *book, Date date);

    /*!
     * @brief A Person cancels a request if they had one
     * @param person The Person canceling the request
     * @throw PersonDoesntHaveRequest
     * @trow PersonIsBorrowing
     */
    void cancelRequest(Person *person);

    /*!
     * @brief A Person returns a Book they had borrowed
     * @param person Person returning the Book
     * @param book The Book to be returned
     * @param date The Date the returning is being made on
     * @throw RequestForTitleNotFulfilled
     * @throw RequestWasNotStored
     * @throw PersonAlreadyHasRequest
     * @throw PersonIsInDebt
     */
    void returnBook(Person *person, Book *book, Date date);

    /*!
     * @brief A Person returns the book they were borrowing as lost
     * @param person The Person who lost the Book
     * @param book The Book that was lost
     * @throw TitleDoesntHaveBook
     * @throw BookDoesNotExist
     * @throw PersonDoesntOwnBook
     * @throw BookBeingLent
     */
    void lostBook(Person *person, Book *book);

    /*!
     * @brief Gets the fine for a Book that was lost
     * @param book The Book that was lost
     * @return The amount to be payed for the book
     */
    unsigned int getLosingFine(Book *book) const;

    /*!
     * @brief Gets the fine part corresponding to the delay on the return of the Book
     * @param expected The expected Date the book was supposed to be returned on
     * @param delivered The effective day the book was returned on
     * @return The amount to add to the usual fine (which is just the book's value)
     */
    unsigned int getDelayFine(Date expected, Date delivered) const;

    /*!
     * @brief Calculates the fine for returning a Book late
     * @param person The Person to be fined
     * @param book The Book that was returned late
     * @param date The Date the book was finally returned on
     * @return The amount to be fined
     */
    unsigned int totalTardinessFine(Person *person, Book *book, Date date);

    /*!
     * @brief Fines the person for the amount specified
     * @param person to be fined
     * @param amount to fine the person for
     */
    void finePerson(Person *person, unsigned int amount);

    /*!
     * @brief Gets the book with a certain owner and title
     * @param name The name of the Person who owns the book
     * @param title The name of the Title of the Book
     * @return A vector with the book fitting those parameters
     * @throw BookDoesNotExist
     */
    std::vector<Book *> searchForBooks(std::string name, std::string title);

    /*!
     * @brief Gets the person with a certain name
     * @param name The name of the person
     * @param people The people among who to search
     * @return A pointer to the Person if found, NULL otherwise
     * @throw PersonDoesNotExist
     */
    Person *searchForPerson(std::string name, std::vector<Person *> people);

    /*!
     * @brief Gets the title with a certain name
     * @param name The name of the title
     * @return A pointer to the Title if found, NULL otherwise
     * @throw TitleDoesNotExist
     */
    Title *searchForTitle(std::string name);

    friend std::ostream &operator<<(std::ostream &os, const Library &library);

    /*
     * Should save the people, the books and the titles independently
     * Save each on their own file
     */
    /*!
     * @brief Saves the current data of the Library
     * @throw CantOpenFile
     * @throw ErrorClosingFile
     */
    void saveLibrary() const;

    /*!
     * @brief Saves the current data of the Person's
     */
    void savePeople() const;

    /*!
     * @brief Saves the current data of the Title's
     */
    void saveTitles() const;

    /*!
     * @brief Saves the current data of the Book's
     */
    void saveBooks() const;

    /*!
     * @brief Saves the current data of the Request's
     */
    void saveRequests() const;


    /*
     *ATTENTION
     * Since some objects might be deleted, the ids we get from creating the objects without initializing might be different (not reach a high enough number) from the stored ones
     * This problem might be fixed by being able to set the id and by being able to set the static variable to the biggest of id's found
     */
    /*
     * Should first create all of the books, title and persons, storing the ids of the pointers that are not yet initialized
     * Create a std::map<unsigned int, Object*>
     * Initialize all the pointers
     */
    /*!
     * @brief Loads the Library from memory
     * @details Creates all the Person, Title, Book, Request objects and attributes them the respective pointers
     * @throw CantOpenFile
     * @throw ErrorClosingFile
     */
    void loadLibrary();

    /*!
     * @brief Creates all of the Person objects
     * @param people_map Maps each id to a pointer to a Person. It will later be used to initialize the other objects
     * @return A map with the PersonData of each Person
     * @see createTitles
     * @see initializeBooks
     * @see initializePeople
     * @see initializeRequests
     */
    std::map<unsigned int, PersonData> createPeople(std::map<unsigned int, Person *> &people_map);/*
 *
 *
     * The titles have all the requests there are which it should also create
     * It should also create the reviews with the pointers initialized
     */
    /*!
     * @brief Creates all of the Title objects and the respective Critique and Review's
     * @param title_map Maps each id to a pointer to a Title. It will later be used to initialize the other objects
     * @param people_map Maps each id to a pointer to a Person. Used for loading the title's Review's
     * @return A map with the TitleData of each Title
     * @see Review::loadReview
     * @see initializeBooks
     * @see initializePeople
     * @see initializeRequests
     * @see initializeTitles
     * @throw CantOpenFile
     */
    std::map<unsigned int, TitleData> createTitles(std::map<unsigned int, Title *> &title_map, std::map<unsigned int, Person *> &people_map);

    /*
     * Should already initialize the pointers to the requests after calling the createRequests
     *
     * */
    /*!
     * @brief Creates all of the Request objects
     * @param request_map Maps each id to a pointer to a Request. It will later be used to initialize the other objects
     * @return A map with the RequestData of each Title
     * @see initializeBooks
     * @see initializePeople
     * @see initializeRequests
     * @see initializeTitles
     */
    std::map<unsigned int, RequestData> createRequests(std::map<unsigned int, Request *> &request_map);

    /*
     * If I get the people map I can create the reviews already with the right pointers, since each review will be about the Title object we have already created
     */
    //void createReviews(const std::map<unsigned int, Person*> &people_map, Title* title, std::ifstream &title_file);

    /*!
     * @brief Creates and initializes each Book with the Title, Person and Request pointers
     * @param book_map Maps each id to a Book. It will later be used to initialize the other objects
     * @param title_map Maps each id to a pointer to a Title
     * @param person_map Maps each id to a pointer to a Person
     * @param request_map Maps each id to a pointer to a Request
     */
    void initializeBooks(std::map<unsigned int, Book *> &book_map, std::map<unsigned int, Title *> &title_map, const std::map<unsigned int, Person *> &person_map, const std::map<unsigned int, Request *> &request_map);

    /*!
     * @brief Initializes each Person with the Book and Request pointers
     * @param people_map Map with the ids and pointers of the Person objects to be initialized
     * @param book_map Maps each id to a pointer to a Book
     * @param request_map Maps each id to a pointer to a Request
     * @param people_data Holds the ids of the Person's, Book's and Request's pointers to initialize
     * TODO remove the people_map as it doesn't seem necessary since people_data contains all of the id's already
     */
    void initializePeople(const std::map<unsigned int, Person *> &people_map, const std::map<unsigned int, Book *> &book_map, std::map<unsigned int, Request *> &request_map, const std::map<unsigned int, PersonData> &people_data);

    /*!
     * @brief Initializes each Request with the Person, Title and Book pointers
     * @param request_map Map with the ids and pointers of the Request objects to be initialized
     * @param people_map Maps each id to a pointer to a Person
     * @param title_map Maps each id to a pointer to a Title
     * @param book_map Maps each id to a pointer to a Book
     * @param requests_data Holds the ids of the Person's, Title's and Book's pointers to initialize
     * TODO remove the request_map as it doesn't seem necessary since requests_data contains all of the id's already
     */
    void initializeRequests(const std::map<unsigned int, Request *> &request_map, const std::map<unsigned int, Person *> &people_map, const std::map<unsigned int, Title *> &title_map, const std::map<unsigned int, Book *> &book_map, const std::map<unsigned int, RequestData> &requests_data);

    /*!
     * @brief Initializes each Title with the Book and Request pointers
     * @details Initializes the Title::books and the Title::all_requests, as well as fitting each request in either Title::fulfilled_requests or Title::pending_requests
     * @param title_map Map with the ids and pointers of the Title objects to be initialized
     * @param book_map Maps each id to a pointer to Book
     * @param request_map Maps each id to a pointer to a Request
     * @param title_data Holds the ids of the Book's and Request's pointers to initialize
     * TODO remove the title_map as it doesn't seem necessary since titles_data contains all of the id's already
     */
    void initializeTitles(const std::map<unsigned int, Title *> &title_map, const std::map<unsigned int, Book *> &book_map, const std::map<unsigned int, Request *> &request_map, const std::map<unsigned int, TitleData> &title_data);

    /*!
     * @brief Updates the ids of each class so new objects of those classes will have a different identifier
     * @param request_map Ids of the Request objects
     * @param people_map Ids of the Person objects
     * @param title_map Ids of the Title objects
     * @param book_map Ids of the Book objects
     * @see Request::id
     * @see Person::id
     * @see Title::id
     * @see Book::id
     */
    void updateIds(const std::map<unsigned int, Request *> &request_map, const std::map<unsigned int, Person *> &people_map, const std::map<unsigned int, Title *> &title_map, const std::map<unsigned int, Book *> &book_map);


};

/*!
 * @brief Is not able to open the given file
 * @see Library::createPeople
 * @see Library::createTitles
 * @see Library::createRequests
 * @see Library::initializeBooks
 * @see Library::savePeople
 * @see Library::saveTitles
 * @see Library::saveBooks
 * @see library::saveRequests
 */
class CantOpenFile {
    std::string file_name;
public:
    CantOpenFile(std::string name) : file_name(name) {};
};

/*!
 * @brief Error while closing the given file
 * @see Library::createPeople
 * @see Library::createTitles
 * @see Library::createRequests
 * @see Library::initializeBooks
 * @see Library::savePeople
 * @see Library::saveTitles
 * @see Library::saveBooks
 * @see library::saveRequests
 * */
class ErrorClosingFile{
    std::string file_name;
public:
    ErrorClosingFile(std::string name): file_name(name){};
};

/*!
 * @brief The person we're trying to create already exists
 */
class PersonAlreadyExists {
public:
    PersonAlreadyExists() {};
};

/*!
 * @brief The title we're trying to create already exists
 * @see Library::addTitle
 */
class TitleAlreadyExists {
public:
    TitleAlreadyExists() {};
};

/*!
 * @brief Tried to access a book that doesn't exist
 * @see Library::removeBook, Library::searchForBooks
 */
class BookDoesNotExist {
public:
    BookDoesNotExist() {}
};

/*!
 * @brief The person we're trying to access doesn't exist
 * @see Library::searchForPerson
 */
class PersonDoesNotExist {
public:
    PersonDoesNotExist() {}
};

/*!
 * @brief The title we're trying to access doesn't exist
 * @see Library::searchForTitle
 */
class TitleDoesNotExist {
public:
    TitleDoesNotExist() {}
};

/*!
 * @brief Tried to remove a book that is still being lent
 * @see Library::removeBook
 */
class BookStillBeingLent {
public:
    BookStillBeingLent() {}
};

/*!
 * @brief Tries to remove a person that has reviews associated with it
 * @see Library::removePerson
 */
class PersonHasReviews {
public:
    PersonHasReviews() {};
};

/*!
 * @brief Tries to remove a person that still has book in the library
 * @see Library::removePerson
 */
class PersonHasBooksInLibrary {
public:
    PersonHasBooksInLibrary() {};
};

/*!
 * @brief Tries to remove a title that still has books
 * @see Library::removeTitle
 *
 */
class TitleStillHasBooks {
public:
    TitleStillHasBooks() {};
};

/*!
 * @brief Tries to remove a title but there is still a book that references to this title
 * @see Library::removeTitle
 */
class BookHasTitle {
public:
    BookHasTitle() {};
};

/*!
 * @brief Tries to cancel a request when the person doesn't have one
 * @see Library::cancelRequest
 */
class PersonDoesntHaveRequest{
public:
    PersonDoesntHaveRequest(){};
};

#endif //AEDA_2MIEIC02_09_READING_CLUB_LIBRARY_H
