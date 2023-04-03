#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

char *main_title = "\n  -----------------------------------------------------"
                   "\n            CS Students Doubly Linked List"
                   "\n  -----------------------------------------------------\n";

char *main_menu =
                  "\n       1. View All Students "
                  "\n       2. Insert a New Student "
                  "\n       3. Delete a Student "
                  "\n       4. Search a Student "
                  "\n       5. Exit "
                  "\n\n  -----------------------------------------------------\n"
                  "\n  > ";


char *position_menu = "\n  ------------------------------"
                      "\n       Choose a Position "
                      "\n  ------------------------------"
                      "\n      1. End "
                      "\n      2. Middle"
                      "\n      3. Beginning "
                      "\n      4. Back To Main Menu "
                      "\n\n  ------------------------------\n"
                      "\n  > ";
int End = 1, Middle = 2, Beginning = 3;//Descriptive positional menu options code

char *search_menu =   "\n  --------------------------------------"
                      "\n      Choose an option to Search BY "
                      "\n  --------------------------------------"
                      "\n      1. ID "
                      "\n      2. Name "
                      "\n\n  --------------------------------------\n"
                      "\n  > ";

char *sort_menu =     "\n  --------------------------------------"
                      "\n      Choose an option to Sort BY "
                      "\n  --------------------------------------"
                      "\n      1. ID "
                      "\n      2. GPA "
                      "\n      3. Age "
                      "\n      4. Name "
                      "\n\n  --------------------------------------\n"
                      "\n  > ";

 char *exit_message = "\n\t  --------------------------------------"
                      "\n\t             Good Bye :) "
                      "\n\t  --------------------------------------\n";
#endif
