//
// Created by henri on 17/11/2020.
//

#ifndef AEDA_2MIEIC02_09_READING_CLUB_OBJECT_H
#define AEDA_2MIEIC02_09_READING_CLUB_OBJECT_H

#include <sstream>

/*!
 * @brief General class for function polymorphism
 */
class Object {
public:
    virtual void printObject(std::stringstream &ss) const = 0;
    virtual void printObject() const = 0;
};


#endif //AEDA_2MIEIC02_09_READING_CLUB_OBJECT_H
