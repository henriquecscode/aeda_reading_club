//
// Created by henri on 14/11/2020.
//

#ifndef AEDA_2MIEIC02_09_READING_CLUB_LIBRARY_APP_H
#define AEDA_2MIEIC02_09_READING_CLUB_LIBRARY_APP_H

#include "library.h"

class Object;
class Person;
class Title;
class Book;
class Review;

/*!
 * @brief A pointer to a comparison function between two Object objects
 */
typedef bool (*objectComparator)(const Object &t1, const Object &t2);
/*!
 * @brief A pointer to a comparison function between two Title objects
 */
typedef bool (*titleComparator)(const Title *t1, const Title *t2);

/*!
 * @brief A pointer to a comparison function between two Book objects
 */
typedef bool (*bookComparator)(const Book *t1, const Book *t2);

/*!
 * @brief A pointer to a comparison function between two Person objects
 */
typedef bool (*personComparator)(const Person *t1, const Person *t2);

/*!
 * @brief Interface for the user to interact with the library app
 */
class LibraryApp {

    /*!
     * @brief The library being used
     */
    Library library;

    /*!
     * @brief Loads a Library
     * @throw CantOpenFile
     * @throw ErrorClosingFile
     */
    void loadLibrary();

    /*!
     * @brief Performs the operations to the Library
     */
    void runLibrary();

    /*!
     * @brief Chooses a person to perform operations on
     * @param people The people to be chosen from
     */
    void accessPeople(std::vector<Person*> people);


    /*!
     * @brief Performs operations on a specific person
     * @param person The Person to operate on
     */
    void operatePerson(Person * person);

    /*!
     * @brief Allows to become a member and add books to the library
     * @param person The person being edited
     */
    void personEditMembership(Person *person);

    /*!
     * @brief The member adds one of their books
     * @param person The person adding a book
     * @return True if was able to add, false otherwise
     */
    bool personMembershipAddBook(Person *person);

    /*!
     * @brief A person issues a request
     * @param person The Person making the Request
     */
    void personMakeRequest(Person *person);

    /*!
     * @brief A person issues a request by title
     * @return The Title to request
     */
    Title * personMakeRequestTitle();

    /*!
     * @brief A person issues a request by book
     * @return The Book to request
     */
    Book * personMakeRequestBook();

    /*!
     * @brief A person returns a book
     * @param person The Person returning the Book
     */
    void personReturnBook(Person *person);

    /*!
     * @brief A person renews a book
     * @param person The person renewing the Book
     */
    void personRenewBook(Person *person);

    /*!
     * @brief A person cancels a request
     * @param p The person canceling the request
     */
    void personCancelRequest(Person * person);

    /*!
     * @brief After reading a book, for the first time or not, adds a review
     * @param p The Person that is making the review
     * @param t The Title that is being reviewed
     */
    void reviewTitle(Person *p, Title *t);

    /*!
     * @brief Adds a review to the title read
     * @param p The Person that is adding the review
     * @param t The Title that is being reviewed
     */
    void addReview(Person *p, Title *t);

    /*!
     * @brief Edits a review to the title read
     * @param p The Person that is adding the review
     * @param t The Title that is being reviewed
     */
    void editReview(Person *p, Title *t, Review &r);

    /*!
     * @brief A person reports a book as lost
     * @param person The Person losing a book
     */
    void personLostBook(Person *person);

    /*!
     * @brief A person adds a book to their owned books
     * @param person The person adding a book
     */
    void personAddBook(Person *person);

    /*!
     * @brief A person increases their balance in the library
     * @param person The Person to have its balance increased
     */
    void personAddBalance(Person *person);

    /*!
     * @brief A person is removed from the library
     * @param person The Person to be removed
     */
    void personRemovePerson(Person *person);

    /*!
     * @brief Removes a book from the person's owned books
     * @param person The Person whose book is going to be removed
     */
    void personRemoveBook(Person *person);

    /*!
     * @brief The user chooses a certain person
     * @param people The people to choose from
     * @return The Person chosen, NULL if invalid
     */
    Person *choosePerson(std::vector<Person *> people) ;
    /*!
     * @brief The user selects a certain person
     * @details Lists the people by a certain parameter in order to help the user choose
     * @param people The Person's to choose from
     * @return The Person chosen
     */
    Person *selectPerson(std::vector<Person *> people) const;

    /*!
     * @brief Chooses the parameter to list the people by
     * @return Returns a pointer to a comparator function between two Person objects
     */
    personComparator choosePeopleListingBy() const;

    /*!
     * @brief Lists the Persons' by a defined parameter
     * @param people Person's to be sorted and listed
     * @param comparator A pointer to a comparator function between two Person objects
     */
    void listPeopleBy(std::vector<Person *> &people, personComparator comparator) const;

    /*!
     * @brief Chooses a Title to perform operations on
     */
    void accessTitles();

    /*!
     * @brief Performs operations on a specific title
     * @param title Title to operate on
     */
    void operateTitle(Title * title);

    /*!
     * @brief The user removes a title from the library
     * @param title The Title to be removed
     */
    void titleRemoveTitle(Title *title);
    /*!
     * @brief The user chooses a certain title
     * @return The Title chosen, NULL if invalid
     */
    Title* chooseTitle();

    /*!
     * @brief The user selects a certain title
     * @details Lists the titles by a certain parameter in order to help the user choose
     * @param titles The Title's to choose from
     * @return The Title chosen
     */
    Title *selectTitle(std::vector<Title *> titles) const;

    /*!
     * @brief Chooses the parameter to list the titles by
     * @return Returns a pointer to a comparator function between two Title objects
     */
    titleComparator chooseTitleListingBy() const;

    /*!
     * @brief Lists the Title's by a defined parameter
     * @param titles Title's to be sorted and listed
     * @param comparator A pointer to a comparator function between two Title objects
     */
    void listTitlesBy(std::vector<Title *> &titles, titleComparator comparator) const;

    /*!
     * @brief Chooses a Book to perform operations on
     */
    void accessBooks();

    /*!
     * @brief Performs operations on a specific book
     * @param book The Book to operate on
     */
    void operateBook(Book *book);

    /*!
     * @brief The user chooses a certain book
     * @return The Book chosen, NULL if invalid
     */
     Book * chooseBook();
    /*!
     * @brief The user selects a certain book
     * @details Lists the books by a certain parameter in order to help the user choose
     * @param books The Book's to choose from
     * @return The Book chosen
     */
    Book * selectBook(std::vector<Book *> books) const;

    /*!
     * @brief Chooses the parameter to list the books by
     * @return Returns a pointer to a comparator function between two Book objects
     */
    bookComparator  chooseBookListingBy() const;

    /*!
     * @brief lists the Book's by a defined parameter
     * @param books Book's to be sorted and listed
     * @param comparator A pointer to a comparator function between two Book objects
     */
    void listBooksBy(std::vector<Book *> books, bookComparator comparator) const;

    /*!
     * @brief Lists any object by a already defined order
     */
     void printObjectsList(std::vector<Object *> &objects) const;

     /*!
      * @brief Adds a person to the library
      */
     void addPerson();

     /*!
      * @brief Adds a title to the Library
      * @details Calls addTitle(std::string name)
      * @see addTitle(std::string name);
      */
     Title * addTitle();

     /*!
      * @brief Adds a title to the Library when we already know the Title::name
      * @param name The Title::name
      */
     Title * addTitle(std::string name);

    /*!
     * @brief Saves the Library
     * @throw CantOpenFile
     * @throw ErrorClosingFile
     */
    void saveLibrary();

public:

    ~LibraryApp(){};
    /*!
     * @brief Starts the interface program
     */
    LibraryApp();

};

/*!
 * @brief Tries to select a Person when there is none to select from
 */
class SelectObjectFromEmpty{
public:
    SelectObjectFromEmpty(){};
};

/*!
 * @brief An operation that invalidates the state of the UI was made.
 * @details Upon removal of an object, the argument of the function that removal was made on is now un-existent or error-bound. Returns to an upper function where there's no longer reference by value
 */
class UIStateOutdated{
public:
    UIStateOutdated(){};
};

#endif //AEDA_2MIEIC02_09_READING_CLUB_LIBRARY_APP_H
