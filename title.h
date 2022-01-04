//
// Created by henri on 16/10/2020.
//

#ifndef AEDA_2MIEIC02_09_READING_CLUB_TITLE_H
#define AEDA_2MIEIC02_09_READING_CLUB_TITLE_H

#include "object.h"
#include "critique.h"
#include "request.h"
#include <string>
#include <vector>
#include <queue>
#include <map>

extern unsigned int LENDING_DURATION;
//https://stackoverflow.com/a/55238546

class Book;

class Request;

class Person;

struct TitleData;

/*!
 * @brief Title in the Library
 */
class Title : public Object {
    /*!
     * @brief Title object identifier
     */
    static unsigned int id;

    /*!
     * @brief The id of the Title
     */
    unsigned int title_id;

    /*!
     * @brief The type of the title
     */
    std::string type;

    /*!
     * @brief The name of the title
     */
    std::string name;

    /*!
     * @brief The Book's that correspond to this title
     */
    std::vector<Book *> books;

    /*!
     * @brief Public opinion of this title
     */
    Critique critique;


    /*!
     * @brief Request's made to this title that haven't been fulfilled
     */
    std::vector<Request *> pending_requests;

    /*!
     * @brief Request's made to this title that have been fulfilled
     */
    std::vector<Request *> fulfilled_requests;

    /*!
     * @brief All the Request's to this title
     */
    std::vector<Request *> all_requests;

    /*!
     * @brief Increases #id
     * @return New #id
     */
    static int increaseTitleId() { return ++id; }

public:

    /*!
     * @brief Sets the #title_id
     * @param new_id Id to be set
     */
    static void setTitleId(unsigned int new_id) { id = new_id; }

    /*!
     * @brief Title destructor
     */
    ~Title();

    /*!
     * @brief Constructs a Title
     */
    Title();

    /*!
     * @brief Constructs a Title
     * @param id The #title_id
     */
    Title(unsigned int id);

    /*!
     * @brief Constructs a Title
     * @param tit_name The #name of the title
     * @param tit_type The #type of the title
     */
    Title(std::string tit_name, std::string tit_type);

    /*!
     * @brief Constructs a Title
     * @param tit_name The #name of the title
     * @param tit_type The #type of the title
     * @param id The #title_id
     */
    Title(std::string tit_name, std::string tit_type, unsigned int id);

    /*!
     * @brief Constructs a Title
     * @param tit_name The #name of the title
     * @param tit_type The #type of the title
     * @param crit The #critique of the title
     * @param id The #title_id
     */
    Title(std::string tit_name, std::string tit_type, Critique crit, unsigned int id);

    /*!
     * @brief Gets the id of the title
     * @return The #title_id
     */
    unsigned int getId() const;

    /*!
     * @brief Gets the name of the title
     * @return The #name
     */
    std::string getName() const;

    /*!
     * @brief Gets the type of the title
     * @return The #type
     */
    std::string getType() const;

    /*!
     * @brief Gets the critique of the title
     * @return The #critique
     */
    const Critique *getCritique() const;

    /*!
     * @brief Gets the critique of the title
     * @return the #critique
     */
    Critique *getCritique();

    /*!
     * @brief Sets the Critique
     * @param crit The Critique to be set
     */
    void setCritique(Critique &crit);

    /*!
     * @brief If the title has copies, i.e. multiple books
     * @return true if has more than one Book, false otherwise
     */
    bool existsCopies();

    /*!
     * @brief Adds a Review to the #critique
     * @param review Review to be added
     */
    void addReview(Review *review);

    /*!
     * @brief Gets the review made by a person
     * @param p Person that made the review
     * @return The Review
     */
    Review &getReview(Person *p);

    /*!
     * @brief Gets the books of the title
     * @return The #books
     */
    std::vector<Book *> getBooks() const;

    /*!
     * @brief If the title has a certain book
     * @param book The Book to check if is in the title's books
     * @return true if the book is in #books, false otherwise
     */
    bool existsBook(Book *book);

    /*!
     * @brief Adds a book to the title's #books
     * @param book Book to be added
     * @throw BookDoesntBelongToTile
     */
    void addBook(Book *book);

    /*!
     * @brief Removes a book from the title's #books
     * @param book Book to be removed
     * @throw TitleDoesntHaveBook
     * @throw BookBeingLent
     */
    void removeBook(Book *book);

    /*!
     * @brief Removes the requests from the person from the title
     * @details If the person has a fullfilled request, then we throw an exception
     * @param person The Person whose request we are removing
     */
    void removeRequest(Person *person);

    /*!
     * @brief Reports a book has being lost
     * @details Removes the book from #books, s#pending_requests, #fulfilled_requests and #all_requests
     * @param book Book that was lost
     * @throw TitleDoesntHaveBook
     */
    void loseBook(Book *book);

    /*!
     * @brief Gets the requests of the title
     * @return The #all_requests
     */
    std::vector<Request *> getRequests() const;

    /*!
     * @brief A Person makes a Request for a Title
     * @details A Person issues a request<br>If there is any book available it will fulfill the request, otherwise the request will stay in queue
     * @param person The Person making the request
     * @param date The Date the request is being issued on
     * @return true if was able to fulfill the request, false otherwise
     * @throw PersonAlreadyHasRequest
     * @throw PersonIsInDebt
     * @throw TitleHasNoBooks
     */
    bool requestTitle(Person *person, Date date);

    /*!
     * @brief A Person makes a Request for a Book
     * @details A Person issues a request for a specific<br>If the book is available it will fulfill the request, otherwise the request will stay in queue
     * @param person A Person makes a request for a Book
     * @param book The Book to be requested
     * @param date The Date the request is being issued on
     * @return true if was able to fulfill the request, false otherwise
     */
    bool requestTitle(Person *person, Book *book, Date date);

    /*!
     * @brief A Person returns a book
     * @details The request holds the information about the book that is being returned
     * @param req The Request with the information
     * @param d The Date the book is being returned on
     * @throw RequestForTitleNotFulfilled
     * @throw RequestWasNotStored
     */
    void returnTitle(Request *req, Date d);

    /*!
     * @brief Gets a book immediately available for lending
     * @return A pointer to the Book to be lent if available, NULL pointer otherwise
     */
    Book *findAvailableBook();

    /*!
     * @brief Gets the specified book if it is immediately available for lending
     * @param b The Book to be lended
     * @return A pointer to be specified Book to be lent if available, NULL pointer otherwise
     */
    Book *findAvailableBook(Book *b); // Change to isBookAvailable(Book *b)?

    /*
    Book *findBestRequestableBook();

    Book *findBestRequestableBook(bool is_member);
    */

    /*!
     * @brief Gets the number of requests to a certain book
     * @param b The Book whose number of requests we count
     * @return The number of Request's for the book
     */
    unsigned int PendingRequestsToBook(Book *b);

    /*!
     * @brief Gets the number of requests from a member to a certain book
     * @param b The Book whose number of requests from members we count
     * @return The number of priority Request's for the book
     * @see Person::is_member
     */
    unsigned int PendingPriorityRequestsToBook(Book *b);


    static bool titleComparatorId(const Title *t1, const Title *t2);

    static bool titleComparatorName(const Title *t1, const Title *t2);

    static bool titleComparatorType(const Title *t1, const Title *t2);

    static bool titleComparatorNumberBooks(const Title *t1, const Title *t2);

    static bool titleComparatorRating(const Title *t1, const Title *t2);

    static bool titleComparatorNumberReviews(const Title *t1, const Title *t2);

    static bool titleComparatorNumberComments(const Title *t1, const Title *t2);

    /*!
     * @brief Prints the #books to a stream
     * @param ss The stream to print to
     * @see std::ostream &operator<<(std::ostream &os, const Book &book)
     */
    void printBooks(std::stringstream &ss) const;

    /*!
     * @brief Prints the #books to the console
     * @see printBooks(std::stringstream &ss) const
     */
    void printBooks() const;

    /*!
     * @brief Prints each Review to a stream
     * @details Prints the reviews of the #critique
     * @param ss The stream to print to
     * @see Critique::printReviews(std::stringstream &ss) const
     */
    void printReviews(std::stringstream &ss) const;

    /*!
     * @brief Prints each Review to the console
     * @details Prints the Review's of the #critique
     * @see printReviews(std::stringstream &ss) const
     */
    void printReviews() const;

    /*!
     * @brief Prints the comments of each Review to a stream
     * @details Prints the Review::comment from the #critique's Review's
     * @param ss The stream to print to
     * @see Critique::printComments(std::stringstream &ss) const;
     */
    void printComments(std::stringstream &ss) const;

    /*!
     * @brief Prints the comments of each Review to the console
     * @details Prints the Review::commment of the Review's of the #critique
     * @see Critique::printComments(std::stringstream &ss) const
     */
    void printComments() const;

    /*!
     * @brief Print the rating of the Title to a stream
     * @details Prints the Critique::rating of the #critique
     * @param ss The stream to print to
     * @see Critique::printRating(std::stringstream &ss) const
     */
    void printRating(std::stringstream &ss) const;

    /*!
     * @brief Print the rating of the Title to the console
     * @details Prints the Critique::rating of the #critique
     * @see printRating(std::stringstream &ss) const;
     */
    void printRating() const;


    /*!
     * @brief Prints #all_requests to a stream
     * @param ss The stream to print to
     * @see std::ostream &operator<<(std::ostream &os, const Request &request)
     */
    void printRequests(std::stringstream &ss) const;

    /*!
     * @brief Prints #all_requests to the console
     * @see printRequests(std::stringstream &ss) const
     */
    void printRequests() const;

    /*!
     * @brief Prints the Title in a friendly way to a stream
     * @param ss The stream to print to
     */
    void printObject(std::stringstream &ss) const;

    /*!
     * @brief Prints the Title in a friendly wya to the console
     */
    void printObject() const;

    /*!
     * @brief Prints the Title to a stream
     * @details Prints the #title_id, the #title, the #type, the #books, the #critique and the #all_requests
     * @param ss The stream to print to
     * @see printComments(std::stringstream &ss) const
     * @see printRequests(std::stringstream &ss) const
     */
    void print(std::stringstream &ss) const;

    /*!
     * @brief Prints the Title to the console
     * @details Prints the #title_id, the #title, the #type, the #books, the #critique and the #all_requests
     * @see print(std::stringstream &ss) const
     */
    void print() const;

    friend std::ostream &operator<<(std::ostream &os, const Title &title);

    /*
     * Should save the id of the title
     * Go through the books and get their id
     * Should pass to the os the number of books and the ids of the books
     *
     * Go through the requests and get their id
     * Should pass to the os the number of requests and the ids of the requests
     *
     * Should save the critique by calling the saveCritique
     */
    //std::ostream saveTitle() const;

    /*!
     * @brief Saves the information of the Title
     * @param ofs Stream to save the information to
     */
    void saveTitle(std::ofstream &ofs) const;

    /*!
     * @brief Loads the TitleData from memory
     * @details Loads the TitleData so we can later initialize the title
     * @param ifs Where the data is fetched from
     * @param people_map Maps each id to a pointer to a Person. Used for loading the critique's Review's
     * @return The TitleData
     * @see Review::loadReview
     */
    static TitleData loadTitle(std::ifstream &ifs, const std::map<unsigned int, Person *> &people_map);

    /*!
     * @brief Initializes the Title from the TitleData and the maps
     * @details Uses the ids in the TitleData and the maps to initialize the title
     * @param t_data The TitleData
     * @param book_map Maps each id to a pointer to a Book
     * @param request_map Mas each id to a pointer to a Request
     */
    void initializeTitle(const TitleData &t_data, const std::map<unsigned int, Book *> book_map, const std::map<unsigned int, Request *> &request_map);
};

/*!
 * @brief Holds the temporary uninitialized data of a Title
 */
struct TitleData {
    /*!
     * @brief The id of the Title
     * @see Title::title_id
     */
    unsigned int id;

    /*!
     * @brief The pointer to the Title
     */
    Title *title;

    /*!
     * @brief Id's of the title's books
     * @see Title::books
     */
    std::vector<unsigned int> books_id;

    /*!
     * @brief If's of the title's requests
     * @see Title::all_requests
     */
    std::vector<unsigned int> requests_id;
};

/*!
 * @brief Tried to add a Book that doesn't belong to the Title it's being added to
 * @see Title::addBook
 */
class BookDoesntBelongToTitle {
    const Book *book;
    const Title *title;
public:
    BookDoesntBelongToTitle(const Book *b, const Title *t) : book(b), title(t) {}
};

/*!
 * @brief Tried to remove a Book from a Title that didn't have the book
 * @see Title::removeBook
 */
class TitleDoesntHaveBook {
    const Book *book;
public:
    explicit TitleDoesntHaveBook(const Book *b) : book(b) {}
};

/*!
 * @brief Tries to make a Request when the Person already has one fulfilled
 * @see Title::requestTitle(Person *person, Date date)
 * @see Title::requestTitle(Person *person, Book *book, Date date)
 */
class PersonAlreadyHasRequest {
public:
    PersonAlreadyHasRequest() {};
};

/*!
 * @brief Tries to request a Title when the Person is in debt
 * @see Title::requestTitle(Person *person, Date date)
 * @see Title::requestTitle(Person *person, Book *book, Date date)
 */
class PersonIsInDebt {
public:
    PersonIsInDebt() {};
};

/*!
 * @brief Tries to remove the requests from a Person but they are borrowing a book
 * @see Title::removeRequest
 * @see Library::cancelRequest
 */
class PersonIsBorrowing {
public:
    PersonIsBorrowing() {};
};

/*!
 * @brief Tried to remove a Book that was being lent
 * @see Title::removeBook
 */
class BookBeingLent {
    const Book *book;
public:
    explicit BookBeingLent(const Book *b) : book(b) {}
};

/*!
 * @brief Tried to return a Book that wasn't being lent
 * @see Title::returnTitle
 */
class RequestForTitleNotFulfilled {
    Request *request;
public:
    RequestForTitleNotFulfilled(Request *req) : request(req) {};
};

/*!
 * @brief Tried to return a Book that there is no record of being lent
 * @see Title::returnTitle
 */
class RequestWasNotStored {
public:
    RequestWasNotStored() {};
};

/*!
 * @brief Tries to request a title that has no books
 * @see Title::requestTitle(Person *person, Date date)
 * @see Title::requestTitle(Person *person, Book *book, Date date)
 */
class TitleHasNoBooks {
public:
    TitleHasNoBooks() {};
};

/*!
 * @brief There is an inconsistency with the state of the title
 * @see Title::loseBook
 */
class TitleRequestsError{
    public:
    TitleRequestsError(){};
};

#endif //AEDA_2MIEIC02_09_READING_CLUB_TITLE_H
