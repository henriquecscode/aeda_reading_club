//
// Created by henri on 14/11/2020.
//
#include "library.h"
#include "person.h"
#include "book.h"
#include "title.h"
#include "review.h"
#include "tests.h"
#include <iostream>

void test1(){
    Library library;
}

void test2() {
    Person *p = new Person();
    Person *p2 = new Person();
    Person *p3 = new Person();
    Person *p4 = new Person();
    Classification c1 = one;
    Classification c2 = five;
    Classification c3 = four;
    Classification c4 = three;
    Title t("Monty python", "fiction");
    Review r(p, &t, c1);
    Review r2(p2, &t, c2, "best book i've read");
    Review r3(p3, &t, c3);
    Review r4(p4, &t, c4);
    Review r2_2(p2, &t, c3);
    t.addReview(&r);
    t.addReview(&r2);
    t.addReview(&r3);
    t.addReview(&r4);

    try{
        t.addReview(&r2_2);
    }
    catch (PersonAlreadyMadeReview) {
        std::cout << "Caught exception";
    }
    t.printReviews();
    t.printComments();
    t.print();
}

void test3(){
    Person *p = new Person("Henry");
    Person *p2 = new Person("Dom");
    Person *p3 = new Person("Mario");
    Title t("Monty python", "fiction");
    Book *b = new Book(&t, p ,5);
    Book *b2 = new Book(&t, p2, 5);
    Book *b3 = new Book(&t, p3, 5);

    std::cout << "Title initially: \n";
    t.printBooks();

    t.addBook(b);
    t.addBook(b2);
    t.addBook(b3);

    std::cout << "Title finally:\n";
    t.printBooks();
    std::cout <<"Title print:\n";
    t.print();
}

void test4(){
    std::string comment;
    Person *p = new Person();
    Classification c1 = one;
    Title t("Monty python", "fiction");
    Review r(p, &t, c1);
    getline(std::cin ,comment);
    r.setComment(comment);
    t.addReview(&r);


    t.printReviews();
    t.printComments();
    t.print();
}

void test5(){
    Person *p = new Person("Henry");
    Title t("Monty python", "fiction");
    Title t2("Algorithsm and data structures", "progamming");
    Book *b = new Book(&t, p ,5);
    Book *b2 = new Book(&t, p, 10);
    Book *b3 = new Book(&t2, p, 20);
    Book *b4 = new Book(&t2, 30);

    p->print();

    std::cout << "Hello";
    p->addBook(b4);

    p->print();
}


void test6(){
    Person *p = new Person();
    Person *p2 = new Person();
    Title t("Monty python", "fiction");
    Book *b = new Book(&t, p, 5);
    t.addBook(b);
    t.requestTitle(p, Date());
    t.requestTitle(p2, Date());

    t.printRequests();
}

void test7(){
    Person *p = new Person();
    Person *p2 = new Person();
    Title t("Monty python", "fiction");
    Book *b = new Book(&t, p, 5);
    Book *b2 = new Book (&t, p, 100);
    t.addBook(b2);
    t.addBook(b);
    t.requestTitle(p, Date());
    t.printBooks();
    p->getRequest()->printRequest();
    t.requestTitle(p2,b2, Date());
    std::cout << "\nFirst requests\n";
    t.printRequests();
    t.returnTitle(p->getRequest(), Date());
    std::cout << "\nSecond requests\n";
    t.printRequests();
}

void test8(){
    Person *p = new Person("Henry", true);
    Person *p2 = new Person("Dom", false);
    Person *p3 = new Person("Mario", false);

    Title t("Monty python", "fiction");
    Book *b = new Book(&t, p, 5);
    t.addBook(b);
    t.requestTitle(p2, Date());
    t.requestTitle(p3, Date());
    t.requestTitle(p, Date());
    t.returnTitle(p2->getRequest(), Date());
    t.printRequests();

}

void test9(){
    Person *p = new Person("Henry", true);
    Person *p2 = new Person("Dom", false);
    Person *p3 = new Person("Mario", false);
    Person *p4 = new Person("Joao", false);

    Title t("Monty python", "fiction");
    Book *b = new Book(&t, p, 5);
    Book *b2 = new Book(&t, p2, 5);
    t.addBook(b);
    t.addBook(b2);
    t.requestTitle(p2, Date());
    t.requestTitle(p4, Date());
    t.requestTitle(p3, Date());
    t.requestTitle(p, b2,Date());
    t.returnTitle(p2->getRequest(), Date());
    std::cout << "First requests\n";
    t.printRequests();
    t.returnTitle(p4->getRequest(), Date());
    std::cout << "Second requests\n";
    t.printRequests();

}