//
// Created by henri on 15/11/2020.
//

#ifndef AEDA_2MIEIC02_09_READING_CLUB_TEXTS_H
#define AEDA_2MIEIC02_09_READING_CLUB_TEXTS_H

#include <vector>
#include <string>

extern std::string LOAD_LIBRARY_DONT_LOAD;
extern std::string LOAD_LIBRARY_DO_LOAD;
extern std::vector<std::string> LOAD_LIBRARY;
extern std::string LOAD_LIBRARY_EXCEPTION;

extern std::string SAVE_LIBRARY_DONT_SAVE;
extern std::string SAVE_LIBRARY_DO_SAVE;
extern std::vector<std::string> SAVE_LIBRARY;
extern std::string SAVE_LIBRARY_EXCEPTION;

extern std::string RUN_LIBRARY_SEE_PEOPLE;
extern std::string RUN_LIBRARY_SEE_MEMBERS;
extern std::string RUN_LIBRARY_SEE_NON_MEMBERS;
extern std::string RUN_LIBRARY_SEE_TITLES;
extern std::string RUN_LIBRARY_SEE_BOOKS;
extern std::string RUN_LIBRARY_ADD_PERSON;
extern std::string RUN_LIBRARY_ADD_TITLE;
extern std::string RUN_LIBRARY_EXIT;
extern std::vector<std::string> RUN_LIBRARY;

extern std::string ACCESS_PEOPLE_EXIT;
extern std::string ACCESS_PEOPLE_CHOOSE;
extern std::vector<std::string> ACCESS_PEOPLE;

extern std::string CHOOSE_PEOPLE_EXIT;
extern std::string CHOOSE_PEOPLE_SELECT;
extern std::string CHOOSE_PEOPLE_NAME;
extern std::vector<std::string> CHOOSE_PEOPLE;
extern std::string CHOOSE_PERSON_INVALID;
extern std::string CHOOSE_PERSON_COULDNT_FIND;
extern std::string CHOOSE_PERSON_EMPTY_EXCEPTION;

extern std::string OPERATE_PERSON_EXIT;
extern std::string OPERATE_PERSON_VIEW_PERSON;
extern std::string OPERATE_PERSON_EDIT_MEMBER;
extern std::string OPERATE_PERSON_MAKE_REQUEST;
extern std::string OPERATE_PERSON_RETURN_BOOK;
extern std::string OPERATE_PERSON_RENEW_BOOK;
extern std::string OPERATE_PERSON_CANCEL_REQUEST;
extern std::string OPERATE_PERSON_LOST_BOOK;
extern std::string OPERATE_PERSON_ADD_BOOK;
extern std::string OPERATE_PERSON_ADD_BALANCE;
extern std::string OPERATE_PERSON_REMOVE_PERSON;
extern std::string OPERATE_PERSON_REMOVE_BOOK;
extern std::vector<std::string> OPERATE_PERSON;


extern std::string EDIT_MEMBER_EXIT;
extern std::string EDIT_MEMBER_BECOME_MEMBER;
extern std::string EDIT_MEMBER_ADD_BOOK_TO_LIBRARY;
extern std::vector<std::string> EDIT_MEMBER;
extern std::string EDIT_MEMBER_ALREADY_IS_MEMBER;
extern std::string EDIT_MEMBER_BECOME_MEMBER_SUCCESS;
extern std::string EDIT_MEMBER_BECOME_MEMBER_FAILURE;
extern std::string EDIT_MEMBER_NO_BOOKS;
extern std::string EDIT_MEMBER_ADD_BOOK_FROM_SELECTION;
extern std::string EDIT_MEMBER_ADD_BOOK_FROM_SELECTION_SUCCESS;
extern std::string EDIT_MEMBER_ADD_BOOK_FROM_SELECTION_FAILURE;

extern std::string MAKE_REQUEST_EXIT;
extern std::string MAKE_REQUEST_TITLE;
extern std::string MAKE_REQUEST_BOOK;
extern std::vector<std::string> MAKE_REQUEST;
extern std::string MAKE_REQUEST_ALREADY_HAS_REQUEST;
extern std::string MAKE_REQUEST_GET_DATE;
extern std::string MAKE_REQUEST_GET_DATE_ERROR;
extern std::string MAKE_REQUEST_ERROR;
extern std::string MAKE_REQUEST_IN_DEBT;
extern std::string MAKE_REQUEST_TITLE_HAS_NO_BOOKS;
extern std::string MAKE_REQUEST_BY_BOOK_EXIT;
extern std::string MAKE_REQUEST_BY_BOOK_TITLE;
extern std::string MAKE_REQUEST_BY_BOOK_BOOK;
extern std::vector<std::string> MAKE_REQUEST_BY_BOOK;
extern std::string MAKE_REQUEST_SUCCESS_FULFILLED;
extern std::string MAKE_REQUEST_SUCCESS_NOT_FULFILLED;

extern std::string RETURN_BOOK_EXIT;
extern std::string RETURN_BOOK_GET_DATE;
extern std::vector<std::string> RETURN_BOOK;
extern std::string RETURN_BOOK_SUCCESS;
extern std::string RETURN_BOOK_GET_DATE_ERROR;
extern std::string RETURN_BOOK_NO_REQUEST;
extern std::string RETURN_BOOK_NOT_FULFILLED;
extern std::string RETURN_BOOK_REQUEST_NOT_STORED;

extern std::string RENEW_BOOK_EXIT;
extern std::string RENEW_BOOK_GET_DATE;
extern std::vector<std::string> RENEW_BOOK;
extern std::string RENEW_BOOK_SUCCESS;
extern std::string RENEW_BOOK_SUCCESS_MADE_REQUEST;
extern std::string RENEW_BOOK_PERSON_IN_DEBT;
extern std::string RENEW_BOOK_GET_DATE_ERROR;
extern std::string RENEW_BOOK_NO_REQUEST;
extern std::string RENEW_BOOK_NOT_FULFILLED;
extern std::string RENEW_BOOK_REQUEST_NOT_STORED;

extern std::string ADD_REVIEW_PROMPT;
extern std::string ADD_REVIEW_EXIT;
extern std::string ADD_REVIEW_ADD_REVIEW;
extern std::vector<std::string> ADD_REVIEW;
extern std::string ADD_REVIEW_GET_RATING;
extern std::string ADD_REVIEW_GET_COMMENT_PROMPT;
extern std::string ADD_REVIEW_GET_COMMENT_EXIT;
extern std::string ADD_REVIEW_GET_COMMENT_INPUT;
extern std::vector<std::string> ADD_REVIEW_GET_COMMENT;

extern std::string EDIT_REVIEW_PROMPT;
extern std::string EDIT_REVIEW_EXIT;
extern std::string EDIT_REVIEW_EDIT_REVIEW;
extern std::vector<std::string> EDIT_REVIEW;
extern std::string EDIT_REVIEW_PREVIOUS_RATING;
extern std::string EDIT_REVIEW_GET_RATING_PROMPT;
extern std::string EDIT_REVIEW_GET_RATING_EXIT;
extern std::string EDIT_REVIEW_GET_RATING_CHANGE;
extern std::vector<std::string> EDIT_REVIEW_GET_RATING;
extern std::string EDIT_REVIEW_PREVIOUS_COMMENT;
extern std::string EDIT_REVIEW_GET_COMMENT_PROMT;
extern std::string EDIT_REVIEW_GET_COMMENT_EXIT;
extern std::string EDIT_REVIEW_GET_COMMENT_CHANGE;
extern std::vector<std::string> EDIT_REVIEW_GET_COMMENT;

extern std::string CANCEL_REQUEST_NO_REQUEST;
extern std::string CANCEL_REQUEST_IS_BORROWING;
extern std::string CANCEL_REQUEST_SUCCESS;

extern std::string LOST_BOOK_NO_BOOK;
extern std::string LOST_BOOK_ERROR;

extern std::string ADD_BOOK_PROMPT;
extern std::string ADD_BOOK_EXIT;
extern std::string ADD_BOOK_VALUE;
extern std::vector<std::string> ADD_BOOK;
extern std::string ADD_BOOK_GET_TITLE;
extern std::string ADD_BOOK_GET_TITLE_SUCCESS;
extern std::string ADD_BOOK_GET_TITLE_FAILURE;
extern std::string ADD_BOOK_CREATE_TITLE_PROMPT;
extern std::string ADD_BOOK_CREATE_TITLE_EXIT;
extern std::string ADD_BOOK_CREATE_TITLE_CREATE_TITLE;
extern std::vector<std::string> ADD_BOOK_CREATE_TITLE;

extern std::string PERSON_ADD_BALANCE_EXIT;
extern std::string PERSON_ADD_BALANCE_ADD;
extern std::vector<std::string> PERSON_ADD_BALANCE;

extern std::string REMOVE_PERSON_STILL_HAS_BOOKS;
extern std::string REMOVE_PERSON_STILL_HAS_REQUEST;
extern std::string REMOVE_PERSON_HAS_REVIEWS;
extern std::string REMOVE_PERSON_SUCCESS;

extern std::string REMOVE_BOOK_EXIT;
extern std::string REMOVE_BOOK_CHOOSE_BOOK;
extern std::vector<std::string> REMOVE_BOOK;
extern std::string REMOVE_BOOK_NO_BOOKS;
extern std::string REMOVE_BOOK_REMOVED_FROM_LIBRARY;
extern std::string REMOVE_BOOK_SUCCESS;
extern std::string REMOVE_BOOK_FAILURE;

extern std::string LIST_PEOPLE_PRESENT;
extern std::string LIST_PEOPLE_NAME;
extern std::string LIST_PEOPLE_MEMBER;
extern std::string LIST_PEOPLE_BALANCE;
extern std::string LIST_PEOPLE_NUMBER_BOOKS;
extern std::string LIST_PEOPLE_ID;
extern std::vector<std::string> LIST_PEOPLE;

extern std::string ACCESS_TITLE_EXIT;
extern std::string ACCESS_TITLE_CHOOSE;
extern std::vector<std::string> ACCESS_TITLE;

extern std::string CHOOSE_TITLE_EXIT;
extern std::string CHOOSE_TITLE_SELECT;
extern std::string CHOOSE_TITLE_NAME;
extern std::vector<std::string> CHOOSE_TITLE;
extern std::string CHOOSE_TITLE_INVALID;
extern std::string CHOOSE_TITLE_EMPTY_EXCEPTION;

extern std::string OPERATE_TITLE_EXIT;
extern std::string OPERATE_TITLE_VIEW_TITLE;
extern std::string OPERATE_TITLE_VIEW_RATING;
extern std::string OPERATE_TITLE_VIEW_REVIEWS;
extern std::string OPERATE_TITLE_VIEW_COMMENTS;
extern std::string OPERATE_TITLE_VIEW_BOOKS;
extern std::string OPERATE_TITLE_VIEW_REQUESTS;
extern std::string OPERATE_TITLE_REMOVE_TITLE;
extern std::vector<std::string> OPERATE_TITLE;

extern std::string REMOVE_TITLE_SUCCESS;
extern std::string REMOVE_TITLE_FAILURE;

extern std::string LIST_TITLE_PRESENT;
extern std::string LIST_TITLE_NAME;
extern std::string LIST_TITLE_TYPE;
extern std::string LIST_TITLE_NUMBER_BOOKS;
extern std::string LIST_TITLE_RATING;
extern std::string LIST_TITLE_NUMBER_REVIEWS;
extern std::string LIST_TITLE_NUMBER_COMMENTS;
extern std::string LIST_TITLE_ID;
extern std::vector<std::string> LIST_TITLE;

extern std::string ACCESS_BOOK_EXIT;
extern std::string ACCESS_BOOK_CHOOSE;
extern std::vector<std::string> ACCESS_BOOK;

extern std::string CHOOSE_BOOK_EXIT;
extern std::string CHOOSE_BOOK_SELECT;
extern std::string CHOOSE_BOOK_NAME;
extern std::vector<std::string> CHOOSE_BOOK;
extern std::string CHOOSE_BOOK_INVALID;
extern std::string CHOOSE_BOOK_EMPTY_EXCEPTION;
extern std::string CHOOSE_BOOK_COULDNT_FIND;

extern std::string OPERATE_BOOK_EXIT;
extern std::string OPERATE_BOOK_VIEW_BOOK;
extern std::string OPERATE_BOOK_VIEW_TITLE;
extern std::string OPERATE_BOOK_VIEW_OWNER;
extern std::string OPERATE_BOOK_VIEW_VALUE;
extern std::string OPERATE_BOOK_VIEW_REQUEST;
extern std::string OPERATE_BOOK_REMOVE_BOOK;
extern std::vector<std::string> OPERATE_BOOK;
extern std::string OPERATE_BOOK_NO_REQUEST;
extern std::string OPERATE_BOOK_REMOVE_BOOK_BEING_LENT_EXCEPTION;
extern std::string OPERATE_BOOK_REMOVE_BOOK_OTHER_EXCEPTION;
extern std::string OPERATE_BOOK_REMOVE_BOOK_SUCCESS;

extern std::string LIST_BOOK_PRESENT;
extern std::string LIST_BOOK_TITLE_NAME;
extern std::string LIST_BOOK_OWNER_NAME;
extern std::string LIST_BOOK_VALUE;
extern std::string LIST_BOOK_IS_IN_LIBRARY;
extern std::string LIST_BOOK_ID;
extern std::vector<std::string> LIST_BOOK;


extern std::string LISTING_PARTIAL_ALL;
extern std::string LISTING_PARTIAL_INPUT;
extern std::vector<std::string> LISTING_PARTIAL;

extern std::string ADD_PERSON_GET_NAME;
extern std::string ADD_PERSON_GET_BALANCE;
extern std::string ADD_PERSON_SUCCESS;
extern std::string ADD_PERSON_NAME_ALREADY_EXISTS;

extern std::string ADD_TITLE_GET_NAME;
extern std::string ADD_TITLE_GET_TYPE;
extern std::string ADD_TITLE_SUCCESS;
extern std::string ADD_TITLE_NAME_ALREADY_EXISTS;



#endif //AEDA_2MIEIC02_09_READING_CLUB_TEXTS_H
