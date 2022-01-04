//
// Created by henri on 16/10/2020.
//

#ifndef AEDA_2MIEIC02_09_READING_CLUB_DATE_H
#define AEDA_2MIEIC02_09_READING_CLUB_DATE_H

#include <ostream>
#include <sstream>

const int monthDays[12] = {31, 28, 31, 30, 31, 30,
                           31, 31, 30, 31, 30, 31};


/*!
 * @brief Holds the date of the requests made in the library
 */
class Date {

    /*!
     * @brief The year of the Date
     */
    unsigned int year;

    /*!
     * @brief The month of the Date
     */
    unsigned int month;

    /*!
     * @brief The day of the Date
     */
    unsigned int day;

public:
    ~Date();

    Date();

    /*!
     * @brief Date copy constructor
     * @param d The Date to copy
     */
    Date(const Date &d);

    /*!
     * @brief
     * @param year
     * @param month
     * @param day
     */
    Date(unsigned int year, unsigned int month, unsigned int day);

    /*!
     * @brief Gets the year of the date
     * @return The #year
     */
    unsigned int getYear() const;

    /*!
     * @brief Sets the year of the date
     * @param y The #year
     */
    void setYear(unsigned int y);

    /*!
     * @brief Gets the month of the date
     * @return The #month
     */
    unsigned int getMonth() const;

    /*!
     * @brief Sets the month of the date
     * @param m The #month
     */
    void setMonth(unsigned int m);

    /*!
     * @brief Gets the day of the datee
     * @return The #day
     */
    unsigned int getDay() const;

    /*!
     * @brief Sets the day of the date
     * @param d The #day
     */
    void setDay(unsigned int d);

    /*!
     * @brief Counts the number of leap years until the current year
     * @return The number of leap years
     */
    int countLeapYears() const;

    Date &operator=(const Date &d1);

    bool operator<(const Date &d) const;

    bool operator==(const Date &d) const;

    /*!
     * @brief Gets the difference in days to another date
     * @param d The other date
     * @return The number of days
     */
    int operator-(const Date &d) const;

    /*!
     * @brief Gets the date after a certain number of days have passed
     * @param d Initial Dat
     * @param days The days to increment
     * @return The final Date
     */
    friend Date operator+(Date &d, int days); //https://www.codeproject.com/Questions/788061/Date-operation-using-operator-overloading

    /*!
     * @brief Prints the date to a stream
     * @param ss The stream to print to
     */
    void print(std::stringstream &ss) const;

    /*!
     * @brief Prints the date to the console
     */
    void print() const;

    friend std::ostream &operator<<(std::ostream &os, const Date &date);

    friend std::istream &operator>>(std::istream &is, Date &obj);

    /*!
     * @brief Saves the Date
     * @param ofs Stream to save the information to
     */
    void saveDate(std::ofstream &ofs) const;

};


#endif //AEDA_2MIEIC02_09_READING_CLUB_DATE_H

