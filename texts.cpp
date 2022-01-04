//
// Created by henri on 15/11/2020.
//

#include "texts.h"
#include <vector>
#include <string>

std::string LOAD_LIBRARY_DONT_LOAD = "Start a new library";
std::string LOAD_LIBRARY_DO_LOAD = "Load a library from memory";
std::vector<std::string> LOAD_LIBRARY = {LOAD_LIBRARY_DONT_LOAD, LOAD_LIBRARY_DO_LOAD};
std::string LOAD_LIBRARY_EXCEPTION = "Couldn't load library. Terminating";


std::string SAVE_LIBRARY_DONT_SAVE = "Exit without saving";
std::string SAVE_LIBRARY_DO_SAVE = "Save and exit";
std::vector<std::string> SAVE_LIBRARY = {SAVE_LIBRARY_DONT_SAVE, SAVE_LIBRARY_DO_SAVE};
std::string SAVE_LIBRARY_EXCEPTION = "Couldn't save library. Terminating without saving. There might be corrupted data";

std::string RUN_LIBRARY_SEE_PEOPLE = "Access people";
std::string RUN_LIBRARY_SEE_MEMBERS = "Access members";
std::string RUN_LIBRARY_SEE_NON_MEMBERS = "Access non members";
std::string RUN_LIBRARY_SEE_TITLES = "Access titles";
std::string RUN_LIBRARY_SEE_BOOKS = "Access books";
std::string RUN_LIBRARY_ADD_PERSON = "Add person";
std::string RUN_LIBRARY_ADD_TITLE = "Add title";
std::string RUN_LIBRARY_EXIT = "Exit";
std::vector<std::string> RUN_LIBRARY = {RUN_LIBRARY_SEE_PEOPLE, RUN_LIBRARY_SEE_MEMBERS, RUN_LIBRARY_SEE_NON_MEMBERS, RUN_LIBRARY_SEE_TITLES, RUN_LIBRARY_SEE_BOOKS,RUN_LIBRARY_ADD_PERSON, RUN_LIBRARY_ADD_TITLE, RUN_LIBRARY_EXIT};

std::string ACCESS_PEOPLE_EXIT = "Exit";
std::string ACCESS_PEOPLE_CHOOSE = "Choose a person";
std::vector<std::string> ACCESS_PEOPLE = {ACCESS_PEOPLE_EXIT, ACCESS_PEOPLE_CHOOSE};

std::string CHOOSE_PEOPLE_EXIT = "Exit";
std::string CHOOSE_PEOPLE_SELECT = "Select a person from a list";
std::string CHOOSE_PEOPLE_NAME = "Select a person by name";
std::vector<std::string> CHOOSE_PEOPLE = {CHOOSE_PEOPLE_EXIT, CHOOSE_PEOPLE_SELECT, CHOOSE_PEOPLE_NAME};
std::string CHOOSE_PERSON_INVALID = "Invalid person";
std::string CHOOSE_PERSON_COULDNT_FIND = "Couldn't find person";
std::string CHOOSE_PERSON_EMPTY_EXCEPTION = "List of people is empty";

std::string OPERATE_PERSON_EXIT = "Exit";
std::string OPERATE_PERSON_VIEW_PERSON = "View person";
std::string OPERATE_PERSON_EDIT_MEMBER = "Edit membership";
std::string OPERATE_PERSON_MAKE_REQUEST = "Make a request";
std::string OPERATE_PERSON_RETURN_BOOK = "Return book";
std::string OPERATE_PERSON_RENEW_BOOK = "Renew book";
std::string OPERATE_PERSON_CANCEL_REQUEST = "Cancel request";
std::string OPERATE_PERSON_LOST_BOOK = "Lost book";
std::string OPERATE_PERSON_ADD_BOOK = "Add book to owned books";
std::string OPERATE_PERSON_ADD_BALANCE = "Add balance";
std::string OPERATE_PERSON_REMOVE_PERSON = "Remove person";
std::string OPERATE_PERSON_REMOVE_BOOK = "Remove book";
std::vector<std::string> OPERATE_PERSON = {OPERATE_PERSON_EXIT, OPERATE_PERSON_VIEW_PERSON, OPERATE_PERSON_EDIT_MEMBER, OPERATE_PERSON_MAKE_REQUEST, OPERATE_PERSON_RETURN_BOOK, OPERATE_PERSON_RENEW_BOOK, OPERATE_PERSON_CANCEL_REQUEST, OPERATE_PERSON_LOST_BOOK, OPERATE_PERSON_ADD_BOOK, OPERATE_PERSON_ADD_BALANCE,
                                           OPERATE_PERSON_REMOVE_PERSON, OPERATE_PERSON_REMOVE_BOOK};

std::string EDIT_MEMBER_EXIT = "Exit";
std::string EDIT_MEMBER_BECOME_MEMBER = "Become a member";
std::string EDIT_MEMBER_ADD_BOOK_TO_LIBRARY = "Lend book to library";
std::vector<std::string> EDIT_MEMBER = {EDIT_MEMBER_EXIT, EDIT_MEMBER_BECOME_MEMBER, EDIT_MEMBER_ADD_BOOK_TO_LIBRARY};
std::string EDIT_MEMBER_ALREADY_IS_MEMBER = "You are already a member";
std::string EDIT_MEMBER_BECOME_MEMBER_SUCCESS = "Success. Became a member";
std::string EDIT_MEMBER_BECOME_MEMBER_FAILURE = "Failure in becoming a member";
std::string EDIT_MEMBER_NO_BOOKS = "No books to select from";
std::string EDIT_MEMBER_ADD_BOOK_FROM_SELECTION = "Choose a book from the following";
std::string EDIT_MEMBER_ADD_BOOK_FROM_SELECTION_SUCCESS = "Success adding book";
std::string EDIT_MEMBER_ADD_BOOK_FROM_SELECTION_FAILURE = "Failure adding book";


std::string MAKE_REQUEST_EXIT = "Exit";
std::string MAKE_REQUEST_TITLE = "Request a title";
std::string MAKE_REQUEST_BOOK = "Request a book";
std::vector<std::string> MAKE_REQUEST = {MAKE_REQUEST_EXIT, MAKE_REQUEST_TITLE, MAKE_REQUEST_BOOK};
std::string MAKE_REQUEST_ALREADY_HAS_REQUEST = "Person is already borrowing a book. Please return it";
std::string MAKE_REQUEST_GET_DATE = "Insert today's date";
std::string MAKE_REQUEST_GET_DATE_ERROR = "Error getting date";
std::string MAKE_REQUEST_ERROR = "Error making request";
std::string MAKE_REQUEST_IN_DEBT = "Person is in debt. Please add money to your balance";
std::string MAKE_REQUEST_TITLE_HAS_NO_BOOKS = "Title is in the library but has no books assigned";
std::string MAKE_REQUEST_BY_BOOK_EXIT = "Exit";
std::string MAKE_REQUEST_BY_BOOK_TITLE = "Choose a book from a title";
std::string MAKE_REQUEST_BY_BOOK_BOOK = "Choose a book";
std::vector<std::string> MAKE_REQUEST_BY_BOOK = {MAKE_REQUEST_BY_BOOK_EXIT, MAKE_REQUEST_BY_BOOK_TITLE, MAKE_REQUEST_BY_BOOK_BOOK};
std::string MAKE_REQUEST_SUCCESS_FULFILLED = "Book successfully borrowed";
std::string MAKE_REQUEST_SUCCESS_NOT_FULFILLED = "Book was occupied. It will be borrowed once it's available";


std::string RETURN_BOOK_EXIT = "Exit";
std::string RETURN_BOOK_GET_DATE = "Insert today's date";
std::vector<std::string> RETURN_BOOK = {RETURN_BOOK_EXIT, RETURN_BOOK_GET_DATE};
std::string RETURN_BOOK_SUCCESS = "Success returning book";
std::string RETURN_BOOK_GET_DATE_ERROR = "Invalid date";
std::string RETURN_BOOK_NO_REQUEST = "You haven't made a request";
std::string RETURN_BOOK_NOT_FULFILLED = "You're not borrowing a book";
std::string RETURN_BOOK_REQUEST_NOT_STORED = "Error storing the request";

std::string RENEW_BOOK_EXIT = "Exit";
std::string RENEW_BOOK_GET_DATE = "Insert today's date";
std::vector<std::string> RENEW_BOOK = {RENEW_BOOK_EXIT, RENEW_BOOK_GET_DATE};
std::string RENEW_BOOK_SUCCESS = "Success renewing book";
std::string RENEW_BOOK_SUCCESS_MADE_REQUEST = "Returned book but couldn't renew it";
std::string RENEW_BOOK_PERSON_IN_DEBT = "Could not renew. Not sufficient balance";
std::string RENEW_BOOK_GET_DATE_ERROR = "Invalid date";
std::string RENEW_BOOK_NO_REQUEST = "You haven't made a request";
std::string RENEW_BOOK_NOT_FULFILLED = "You're not borrowing a book";

std::string RENEW_BOOK_REQUEST_NOT_STORED = "Error storing the request";

std::string ADD_REVIEW_PROMPT = "Do you wish to add a review?";
std::string ADD_REVIEW_EXIT = "Exit";
std::string ADD_REVIEW_ADD_REVIEW = "Add review";
std::vector<std::string> ADD_REVIEW = {ADD_REVIEW_EXIT, ADD_REVIEW_ADD_REVIEW};
std::string ADD_REVIEW_GET_RATING = "Input a rating from 1 to 5";
std::string ADD_REVIEW_GET_COMMENT_PROMPT = "Do you wish to leave a comment?";
std::string ADD_REVIEW_GET_COMMENT_EXIT = "Exit";
std::string ADD_REVIEW_GET_COMMENT_INPUT = "Yes, leave my comment";
std::vector<std::string> ADD_REVIEW_GET_COMMENT = {ADD_REVIEW_GET_COMMENT_EXIT, ADD_REVIEW_GET_COMMENT_INPUT};

std::string EDIT_REVIEW_PROMPT = "You already have a review for this title. Do you wish to change it?";
std::string EDIT_REVIEW_EXIT = "Exit";
std::string EDIT_REVIEW_EDIT_REVIEW = "Change the review";
std::vector<std::string> EDIT_REVIEW = {EDIT_REVIEW_EXIT, EDIT_REVIEW_EDIT_REVIEW};
std::string EDIT_REVIEW_PREVIOUS_RATING = "Your previous rating was: ";
std::string EDIT_REVIEW_GET_RATING_PROMPT = "Do you wish to change it?";
std::string EDIT_REVIEW_GET_RATING_EXIT = "No";
std::string EDIT_REVIEW_GET_RATING_CHANGE = "Yes";
std::vector<std::string> EDIT_REVIEW_GET_RATING = {EDIT_REVIEW_GET_RATING_EXIT, EDIT_REVIEW_GET_RATING_CHANGE};
std::string EDIT_REVIEW_PREVIOUS_COMMENT = "Your previous comment was: ";
std::string EDIT_REVIEW_GET_COMMENT_PROMT = "Do you wish to change it?";
std::string EDIT_REVIEW_GET_COMMENT_EXIT = "No";
std::string EDIT_REVIEW_GET_COMMENT_CHANGE = "Yes";
std::vector<std::string> EDIT_REVIEW_GET_COMMENT = {EDIT_REVIEW_GET_COMMENT_EXIT, EDIT_REVIEW_GET_COMMENT_CHANGE
};


std::string CANCEL_REQUEST_NO_REQUEST = "You haven't made any request";
std::string CANCEL_REQUEST_IS_BORROWING = "You're borrowing a book. Please return it";
std::string CANCEL_REQUEST_SUCCESS = "Success";

std::string LOST_BOOK_NO_BOOK = "You're not borrowing a book";
std::string LOST_BOOK_ERROR = "There was an error while processing. Undefined behavior expected";

std::string ADD_BOOK_PROMPT= "Do you wish to create a new book?";
std::string ADD_BOOK_EXIT= "Exit";
std::string ADD_BOOK_VALUE= "Choose a value for the new book";
std::vector<std::string> ADD_BOOK= {ADD_BOOK_EXIT, ADD_BOOK_VALUE};
std::string ADD_BOOK_GET_TITLE= "What is the title of the book?";
std::string ADD_BOOK_GET_TITLE_SUCCESS= "Successfully created book";
std::string ADD_BOOK_GET_TITLE_FAILURE= "Couldn't find specified title";
std::string ADD_BOOK_CREATE_TITLE_PROMPT= "Do you wish to create a new title?";
std::string ADD_BOOK_CREATE_TITLE_EXIT= "Exit";
std::string ADD_BOOK_CREATE_TITLE_CREATE_TITLE= "Create new title";
std::vector<std::string> ADD_BOOK_CREATE_TITLE= {ADD_BOOK_CREATE_TITLE_EXIT, ADD_BOOK_CREATE_TITLE_CREATE_TITLE};

std::string PERSON_ADD_BALANCE_EXIT = "Exit";
std::string PERSON_ADD_BALANCE_ADD = "Add balance";
std::vector<std::string> PERSON_ADD_BALANCE = {PERSON_ADD_BALANCE_EXIT, PERSON_ADD_BALANCE_ADD};


std::string REMOVE_PERSON_STILL_HAS_BOOKS = "Can't remove person. Still has books. Please removed them first";
std::string REMOVE_PERSON_STILL_HAS_REQUEST = "Can't remove person. Still has a book. Please return it first";
std::string REMOVE_PERSON_HAS_REVIEWS = "Won't be able to remove. Person has made a review";
std::string REMOVE_PERSON_SUCCESS = "Successfully removed a person";


std::string REMOVE_BOOK_EXIT = "Exit";
std::string REMOVE_BOOK_CHOOSE_BOOK = "Remove a book from the person";
std::vector<std::string> REMOVE_BOOK = {REMOVE_BOOK_EXIT, REMOVE_BOOK_CHOOSE_BOOK};
std::string REMOVE_BOOK_NO_BOOKS = "Person doesn't have any book";
std::string REMOVE_BOOK_REMOVED_FROM_LIBRARY = "Removed book from library";
std::string REMOVE_BOOK_SUCCESS = "Success removing the book";
std::string REMOVE_BOOK_FAILURE = "Couldn't remove the book from the library";

std::string LIST_PEOPLE_PRESENT = "List people by:";
std::string LIST_PEOPLE_NAME = "Name";
std::string LIST_PEOPLE_MEMBER = "Members and non members";
std::string LIST_PEOPLE_BALANCE = "Balance";
std::string LIST_PEOPLE_NUMBER_BOOKS = "Number of books owned";
std::string LIST_PEOPLE_ID = "Id";
std::vector<std::string> LIST_PEOPLE = {LIST_PEOPLE_NAME, LIST_PEOPLE_MEMBER, LIST_PEOPLE_BALANCE, LIST_PEOPLE_NUMBER_BOOKS, LIST_PEOPLE_ID};

std::string ACCESS_TITLE_EXIT = "Exit";
std::string ACCESS_TITLE_CHOOSE = "Choose a title";
std::vector<std::string> ACCESS_TITLE = {ACCESS_TITLE_EXIT, ACCESS_TITLE_CHOOSE};

std::string CHOOSE_TITLE_EXIT = "Exit";
std::string CHOOSE_TITLE_SELECT = "Select a title from a list";
std::string CHOOSE_TITLE_NAME = "Select a title by name";
std::vector<std::string> CHOOSE_TITLE = {CHOOSE_TITLE_EXIT, CHOOSE_TITLE_SELECT, CHOOSE_TITLE_NAME};
std::string CHOOSE_TITLE_INVALID = "Invalid title";
std::string CHOOSE_TITLE_EMPTY_EXCEPTION = "List of titles is empty";

std::string OPERATE_TITLE_EXIT = "Exit";
std::string OPERATE_TITLE_VIEW_TITLE = "View title";
std::string OPERATE_TITLE_VIEW_RATING = "View rating";
std::string OPERATE_TITLE_VIEW_REVIEWS = "View reviews";
std::string OPERATE_TITLE_VIEW_COMMENTS = "View comments";
std::string OPERATE_TITLE_VIEW_BOOKS = "View books";
std::string OPERATE_TITLE_VIEW_REQUESTS = "View requests";
std::string OPERATE_TITLE_REMOVE_TITLE = "Remove title from library";
std::vector<std::string> OPERATE_TITLE = {OPERATE_TITLE_EXIT, OPERATE_TITLE_VIEW_TITLE, OPERATE_TITLE_VIEW_RATING, OPERATE_TITLE_VIEW_REVIEWS, OPERATE_TITLE_VIEW_COMMENTS, OPERATE_TITLE_VIEW_BOOKS, OPERATE_TITLE_VIEW_REQUESTS, OPERATE_TITLE_REMOVE_TITLE};

std::string REMOVE_TITLE_SUCCESS = "Success removing title";
std::string REMOVE_TITLE_FAILURE = "Failure removing title";

std::string LIST_TITLE_PRESENT = "List titles by:";
std::string LIST_TITLE_NAME = "Name";
std::string LIST_TITLE_TYPE = "Type";
std::string LIST_TITLE_NUMBER_BOOKS = "Number of books";
std::string LIST_TITLE_RATING = "Rating";
std::string LIST_TITLE_NUMBER_REVIEWS = "Number of reviews";
std::string LIST_TITLE_NUMBER_COMMENTS = "Number of comments";
std::string LIST_TITLE_ID = "Id";
std::vector<std::string> LIST_TITLE = {LIST_TITLE_NAME, LIST_TITLE_TYPE, LIST_TITLE_NUMBER_BOOKS, LIST_TITLE_RATING, LIST_TITLE_NUMBER_REVIEWS, LIST_TITLE_NUMBER_COMMENTS, LIST_TITLE_ID};

std::string ACCESS_BOOK_EXIT = "Exit";
std::string ACCESS_BOOK_CHOOSE = "Choose a book";
std::vector<std::string> ACCESS_BOOK = {ACCESS_BOOK_EXIT, ACCESS_BOOK_CHOOSE};

std::string CHOOSE_BOOK_EXIT = "Exit";
std::string CHOOSE_BOOK_SELECT = "Select a book from a list";
std::string CHOOSE_BOOK_NAME = "Select a book by name and title";
std::vector<std::string> CHOOSE_BOOK = {CHOOSE_BOOK_EXIT, CHOOSE_BOOK_SELECT, CHOOSE_BOOK_NAME};
std::string CHOOSE_BOOK_INVALID = "Invalid book";
std::string CHOOSE_BOOK_EMPTY_EXCEPTION = "List of books is empty";
std::string CHOOSE_BOOK_COULDNT_FIND = "Couldn't find that book";

std::string OPERATE_BOOK_EXIT = "Exit";
std::string OPERATE_BOOK_VIEW_BOOK = "View book";
std::string OPERATE_BOOK_VIEW_TITLE = "View title";
std::string OPERATE_BOOK_VIEW_OWNER = "View owner";
std::string OPERATE_BOOK_VIEW_VALUE = "View value";
std::string OPERATE_BOOK_VIEW_REQUEST = "View request";
std::string OPERATE_BOOK_REMOVE_BOOK = "Remove book";
std::vector<std::string> OPERATE_BOOK = {OPERATE_BOOK_EXIT, OPERATE_BOOK_VIEW_BOOK, OPERATE_BOOK_VIEW_TITLE, OPERATE_BOOK_VIEW_OWNER, OPERATE_BOOK_VIEW_VALUE, OPERATE_BOOK_VIEW_REQUEST, OPERATE_BOOK_REMOVE_BOOK};
std::string OPERATE_BOOK_NO_REQUEST = "Book is not being lent";
std::string OPERATE_BOOK_REMOVE_BOOK_BEING_LENT_EXCEPTION = "Can't remove book. Book is being lent";
std::string OPERATE_BOOK_REMOVE_BOOK_OTHER_EXCEPTION = "Can't remove book";
std::string OPERATE_BOOK_REMOVE_BOOK_SUCCESS = "Successfully removed book";

std::string LIST_BOOK_PRESENT = "List books by";
std::string LIST_BOOK_TITLE_NAME = "Title's name";
std::string LIST_BOOK_OWNER_NAME = "Owner's name";
std::string LIST_BOOK_VALUE = "Value";
std::string LIST_BOOK_IS_IN_LIBRARY ="Is in the library";
std::string LIST_BOOK_ID = "Id";
std::vector<std::string> LIST_BOOK = {LIST_BOOK_TITLE_NAME, LIST_BOOK_OWNER_NAME, LIST_BOOK_VALUE, LIST_BOOK_IS_IN_LIBRARY,LIST_BOOK_ID};

std::string LISTING_PARTIAL_ALL = "List all";
std::string LISTING_PARTIAL_INPUT = "Choose a number of results to list";
std::vector<std::string> LISTING_PARTIAL = {LISTING_PARTIAL_ALL, LISTING_PARTIAL_INPUT};


std::string ADD_PERSON_GET_NAME = "What the is the name of the person";
std::string ADD_PERSON_GET_BALANCE = "What is the initial balance of the person";
std::string ADD_PERSON_SUCCESS = "Person successfully added";
std::string ADD_PERSON_NAME_ALREADY_EXISTS = "Person with that name already exists";


std::string ADD_TITLE_GET_NAME = "What is the name of the title?";
std::string ADD_TITLE_GET_TYPE = "What is the type of the title?";
std::string ADD_TITLE_SUCCESS = "Title successfully added";
std::string ADD_TITLE_NAME_ALREADY_EXISTS = "Title with that name already exists";
