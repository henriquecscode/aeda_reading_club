//
// Created by henri on 16/10/2020.
//

#ifndef AEDA_2MIEIC02_09_READING_CLUB_CRITIQUE_H
#define AEDA_2MIEIC02_09_READING_CLUB_CRITIQUE_H

#include "review.h" // Needed because Classification is enum type
#include <ostream>
#include <vector>
#include <map>

class Title;
class Review;

/*!
 * The standard number of decimal places to round the rating to
 */
extern unsigned int ROUNDING;
//https://stackoverflow.com/a/55238546

/*!
 * @brief Class to hold and process the Review s of a Title
 */
class Critique {
    /*!
     * @brief Title the critique refers to
     */
    Title *title;

    /*!
     * @brief Reviews that make this critique
     */
    std::vector<Review> reviews;

    /*!
     * @brief Rating of the title
     */
    float rating = 0;
public:

    /*!
     * @brief Critique destructor
     */
    ~Critique();

    Critique();

    /*!
     * @brief Constructs the critique for a Title
     * @param ti Title that the critique refers to
     */
    explicit Critique(Title *ti);


    /*!
     * @brief Sets the #title the critique refers to
     * @param ti Title of the Critique
     */
    void setTitle(Title *ti);

    /*!
     * @brief Adds a review to the #reviews
     * @param review Review to be added
     */
    void addReview(Review review);

    /*!
     * @brief Calculates the new #rating for this critique
     * @details Iterative mean calculation that calculates the #rating
     * @param classification The new Classification attributed
     */
    void calculateMeanRating(Classification classification); //Iterative mean calculation (ignore rouding errors)

    /*!
     * @brief Returns the rating (with a certain precision)
     * @param rounding The number of decimal places to round to. Default is ::ROUNDING
     * @return The #rating rounded to the pretended number of decimal places
     */
    float getRating(unsigned int rounding = ROUNDING) const;

    /*!
    * @brief Gets the review made by a person
    * @param p Person that made the review
    * @return The Review
     */
    Review& getReview(Person*p);

    /*!
     * @brief Updates the classification of the review
     * @details Needs to change the average rating
     * @param r The Review to edit
     * @param c The new Classification
     */
    void updateReview(Review &r, Classification c);

    /*!
     * @brief Updates the comment of the review
     * @param r The Review to edit
     * @param comment The new comment
     */
    void updateReview(Review &r, std::string comment);

    /*!
     * @brief Gets the reviews
     * @return Returns a vector with the #reviews
     */
    std::vector<Review> getReviews() const;

    /*!
     * @brief Gets the existing comments
     * @return Returns a vector with comments of the #reviews
     */
    std::vector<std::string> getComments() const;

    /*!
     * @brief Prints the reviews to a stream
     * @details Prints the classification and, if applicable, the comment of each review
     * @param ss The stream the reviews are printed to
     * @see Review::printRating(std::stringstream &ss) const;
     * @see Review::printComment(std::stringstream &ss) const;

     */
    void printReviews(std::stringstream &ss) const;

    /*!
     * @brief Prints the reviews to the console
     * @details prints the classification and, if applicable, the comment of each review
     * @see #printReviews(std::stringstream &ss) const;
     */
    void printReviews() const;


    /*!
     * @brief Prints the comments to a stream
     * @details Prints the comment of each review, if it has any
     * @param ss The stream the comments are printed to
     * @see printComment(std::stringstream &ss) const;
     */
    void printComments(std::stringstream &ss) const;

    /*!
     * @brief Prints the comments to the console
     * @details Prints the comment of each review, if it has any
     * @see #printComments(std::stringstream &ss) const;
     */
    void printComments() const;

    /*!
     * @brief Prints the #rating to a stream
     * @param ss The stream the #rating is printed to
     * @see ::ROUNDING
     */
    void printRating(std::stringstream &ss) const;

    /*!
     * @brief Prints the #rating to the console
     * @see #printRating(std::stringstream &ss) const
     */
    void printRating() const;

    /*!
     * @brief Prints the critique to a stream
     * @details Prints the #title being reviewed, all of the the #reviews and the #rating
     * @param ss The stream to print to
     * @see printReviews(std::stringstream &ss) const
     * @seeprintComments(std::stringstream &ss) const
     */
    void print(std::stringstream &ss) const;

    /*!
     * @brief Prints the critique to the console
     * @details Prints the #title being reviewed, all of the the #reviews and the #rating
     * @see #print(std::stringstream &ss) const
     */
    void print() const;

    friend std::ostream &operator<<(std::ostream &os, const Critique &critique);

    /*
    * Should save the number of reviews
    * Should save the reviews calling its save method
    */
    //std::ostream saveCritique() const;
    /*!
     *
     * @brief Saves the information of Critique
     * @details Saves the information of each review
     * @param ofs Stream to save the information to
     * @see Review::saveReview(std::ofstream &ofs) const;
     */
    void saveCritique(std::ofstream &ofs) const;

    /*!
     * @brief Loads a critique from memory
     * @details Assigns the critique to the Title t and uses the people_map to complete the information of each review
     * @param ifs Where the data is fetched from
     * @param t The Title of the critique
     * @param people_map Maps an id to a pointer to a Person. Used for loading the Review's
     * @return The Critique object
     * @see Review::loadReview
     */
    static Critique loadCritique(std::ifstream &ifs, Title *t, const std::map<unsigned int, Person *> &people_map);

};
/*!
 * @brief Tried to add a Review from a person that already made one
 * @see Critique::addReview
 */
class PersonAlreadyMadeReview{
    Person *person;
public:
    PersonAlreadyMadeReview(Person *p): person(p){};
};

/*!
 * @brief Tried to get a Review from a person that didn't make one
 * @see Critique::getReview
 */
class PersonDidntMakeReview{
    Person *person;
public:
    PersonDidntMakeReview(Person *p): person(p){};
};

#endif //AEDA_2MIEIC02_09_READING_CLUB_CRITIQUE_H
