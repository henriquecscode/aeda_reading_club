//
// Created by henri on 16/10/2020.
//

#ifndef AEDA_2MIEIC02_09_READING_CLUB_REVIEW_H
#define AEDA_2MIEIC02_09_READING_CLUB_REVIEW_H


#include <string>
#include <ostream>
#include <map>

class Person;

class Title;

class Title;

/*!
 * @brief Possible classifications of a Title
 */
enum Classification {
    one = 1,
    two = 2,
    three = 3,
    four = 4,
    five = 5
};

/*!
 * @brief Review of a Title by a Person
 */
class Review {
    /*!
     * @brief The Person reviewing
     */
    Person *reviewer;

    /*!
     * @brief The Title being reviewed
     */
    Title *title;

    /*!
     * @brief The Classification given to the Title
     */
    Classification classification;

    /*!
     * @brief The comment given to a title
     * @details Emtpy string if none given, a string otherwise
     */
    std::string comment = "";
public:

    /*!
     * @brief Review destructor
     */
    ~Review();

    /*!
     * @brief Creates a Review object
     */
    Review();

    /*!
     * @brief Creates a Review object
     * @details Creates a Review object from a Person, with a Title and with a certain Classification
     * @param rewer The Person reviewing
     * @param tit The Title being reviewed
     * @param classific The Classification attributed
     */
    Review(Person *rewer, Title *tit, Classification classific);


    /*!
     * @brief Creates a Review object
     * @details Creates a Review object from a Person, with a Title, with a certain Classification and comment
     * @param rewer The Person reviewing
     * @param tit The Title being reviewed
     * @param classific The Classification attributed
     * @param com The comment attributed
     */
    Review(Person *rewer, Title *tit, Classification classific, std::string com);

    /*
     * These shouldn't be able to be altered
    void setReviewer(Person *reviewer);
    void setTitle(Title *title);
     */
    /*!
     * @details Gets the #classification
     * @return The #classification
     */
    Classification getClassification() const;

    void setClassification(Classification c);

    Person *getPerson() const;

    std::string getComment() const;

    /*
     * Comment will terminate with line break
     */
    /*!
     * @brief Sets the #comment
     * @param com The comment to be set
     */
    void setComment(const std::string &com);

    /*!
     * @brief If the review has a #comment
     * @return true if it has a comment, false otherwise
     */
    bool hasComment() const;


    /*!
     * @brief Prints the #classificaiton to a stream
     * @param ss The stream the #classification is printed to
     */
    void printClassification(std::stringstream &ss) const;

    /*!
     * @brief Prints the #classification to the console
     * @see #printClassification(std::stringstream &ss) const
     */
    void printClassification() const;

    /*!
     * @brief Prints the #comment to a stream
     * @param ss The stream the #comment is printed to
     */
    void printComment(std::stringstream &ss) const;

    /*!
     * @brief Prints the #comment to the console
     * @see #printComment(std::stringstream &ss) const
     */
    void printComment() const;

    /*!
     * @brief Prints the Review to a stream
     * @details Prints the #reviewer, the #title, the #classification and the #comment, if applicable
     * @param ss The stream to print to
     */
    void print(std::stringstream &ss) const;

    /*!
     * @brief Prints the Review to a stream
     * @details Prints the #reviewer, the #title, the #classification and the #comment, if applicable
     * @see #print(std::stringstream &ss) const
     */
    void print() const;

    friend std::ostream &operator<<(std::ostream &os, const Review &review);

    /*!
     * @brief Saves the information of Review
     * @param ofs Stream to save the information to
     */
    void saveReview(std::ofstream &ofs) const;

    /*!
     * @brief Loads a critique from memory
     * @details Assignes the review to the Title t and uses the people_map to set the Person reviewing. Sets the #classification and the #comment
     * @param ifs Where the data is fetched from
     * @param t The Title of the review
     * @param people_map Maps an id to a pointer to a Person
     * @return The Review object
     */
    static Review loadReview(std::ifstream &ifs, Title *t, const std::map<unsigned int, Person *> &people_map);
};


#endif //AEDA_2MIEIC02_09_READING_CLUB_REVIEW_H
