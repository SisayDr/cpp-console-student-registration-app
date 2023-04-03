/*
___________________________________________________________________
	Title: Student Details Record Based on Doubly Linked List
	@date: June 30 2022
-------------------------------------------------------------------
	@name: Sisay Driba
-------------------------------------------------------------------
*/


#include <iostream>
#include <conio.h>
#include <string>
#include <iomanip>
#include "./menu.h"
using namespace std;

struct CS_Student{
    string name;
    int id;
    int age;
    float gpa;
    CS_Student *next;
    CS_Student *prev;
};

CS_Student *first_student = NULL;
CS_Student *current = NULL;
CS_Student *new_student = NULL;

int count_students = 0;
bool sorted = false;
int sorted_by;

void custom_insert();//automatic insert to save some time for testing sort and search operations

string toLower(string text){
    string lower = "";
    for(int i=0; i<text.length(); i++){
        lower += tolower(text[i]);
    }
    return lower;
}

bool sort_list_handler();
void displaystudents(){
    int number = 1;
    bool go_again = true;
    current = first_student;
    cout<<main_title;

    if(current == NULL){
        cout<<"    No students are added yet. ";
        return;
    }

    cout<<left<<"    "<<setw(3)<<"No."<<setw(7)<<" | ID No. "<<setw(23)<<" | Full Name "<<setw(5)<<" | Age"<<setw(5)<<" | GPA";
    while(current != NULL){
        cout<<"\n  -----------------------------------------------------\n";
        cout<<left<<"    "<<setw(3)<<number++<<" | "<<setw(7)<<current->id<<" | "<<setw(20)<<current->name<<" | "<<setw(3)<<current->age<<" | "<<setw(5)<<current->gpa;
        current = current->next;
    }
    go_again = sort_list_handler();
    if(go_again) displaystudents();
}

void insert_at_end(CS_Student* new_student){
    current = first_student;
    new_student->next = NULL;

    while(current->next != NULL)
        current = current->next;

    current->next = new_student;
    new_student->prev = current;
    count_students++;

    cout<<"  > "<<new_student->name<<" is inserted at the end of the list. ";
    getch();
}
void insert_at_begnning(CS_Student* new_student){
    new_student->prev = NULL;
    new_student->next = first_student;
    first_student->prev = new_student;

    first_student = new_student;

    count_students++;
    cout<<"  > "<<new_student->name<<" is now the first student in the list. ";
    getch();
}
void insert_at_middle(CS_Student* new_student, int mid_position){
/*                  Always expect for the worst case scenario!.
            one may choose middle but give 1 or end for mid position.
Since inserting at position 1 & at the end is possible, correct their mistake and direct them to the right functions*/
    if(mid_position == 1)
        insert_at_begnning(new_student);
    else if(mid_position == count_students+1)
        insert_at_end(new_student);
    else if(mid_position > count_students){
        cout<<"  > Position is out of range (1 - "<<count_students<<")";
        getch();
    }
    else{//if the user has chosen a correct middle position
        current = first_student;
        for(int i=1; i<mid_position; i++)
            current = current->next;

        current->prev->next = new_student;
        new_student->prev = current->prev;
        new_student->next = current;
        current->prev = new_student;
        count_students++;
        cout<<"  > "<<new_student->name<<" is inserted at the position "<<mid_position;
        getch();
    }
}

void delete_at_end(){
    current = first_student;

    while(current->next != NULL){
        new_student = current;//the new student at the last position
        current = current->next;
    }
    new_student->next = NULL;
    count_students--;
    system("cls");
    cout<<"\n  > "<<current->name<<" is removed from the end of list";
    displaystudents();
    delete(current);
    getch();

}
void delete_at_begnning(){
    current = first_student;
    new_student = current->next; //the new student at the beginning of the list
    new_student->prev = NULL;
    first_student = new_student;
    count_students--;

    system("cls");
    cout<<"\n  > "<<current->name<<" is removed from the beginning of the list";
    displaystudents();
    delete(current);
    getch();

}
void delete_at_middle(int mid_position){
    if(mid_position > count_students){
        cout<<"  > Position is out of range (1 - "<<count_students<<")";
        getch();
    }
    else if(mid_position == 1)
        delete_at_begnning();
    else if(mid_position == count_students)
        delete_at_end();
    else{//if mid position is actually at the middle
        current = first_student;
        for(int i=1; i<mid_position; i++)
            current = current->next;
        current->prev->next = current->next;
        current->next->prev = current->prev;

        system("cls");
        cout<<"\n  > "<<current->name<<" is removed from the position "<<mid_position;
        displaystudents();
        delete(current);
        getch();
    }



}

void search_by_id(int student_id){
    current = first_student;
    bool student_found = false;
    do{
        if(student_id == current->id){
            system("cls");
            cout<<main_title;
            cout<<left<<"     "<<setw(7)<<" | ID No. "<<setw(23)<<" | Full Name "<<setw(5)<<" | Age"<<setw(5)<<" | GPA";
            cout<<"\n    -----------------------------------------------\n";
            cout<<left<<"     "<<" | "<<setw(7)<<current->id<<" | "<<setw(20)<<current->name<<" | "<<setw(3)<<current->age<<" | "<<setw(5)<<current->gpa;
            cout<<"\n    -----------------------------------------------\n";
            cout<<"   </Enter any key to go back> ";
            return;
        }
        else
            current = current->next;
    }while(current != NULL);

    if(!student_found){
        cout<<"\n  -------------------------------------------------\n";
        cout<<"    Couldn't find a student by ID: "<<student_id;
        cout<<"\n  -------------------------------------------------\n";
        cout<<"   </Enter any key to go back> ";
    }

}
void search_by_name(string student_name){
    int len = student_name.length();
    current = first_student;
    bool student_found = false;

    system("cls");
    cout<<"\n\t Showing Results for "<<student_name;
    cout<<"\n    -----------------------------------------------\n";
    cout<<left<<"     "<<setw(7)<<" | ID No. "<<setw(23)<<" | Full Name "<<setw(5)<<" | Age"<<setw(5)<<" | GPA";

    student_name = toLower(student_name);//to avoid case sensitivity
    do{
        if(toLower(current->name).substr(0, len).compare(student_name) == 0){
            student_found = true;
            cout<<"\n    -----------------------------------------------\n";
            cout<<left<<"     "<<" | "<<setw(7)<<current->id<<" | "<<setw(20)<<current->name<<" | "<<setw(3)<<current->age<<" | "<<setw(5)<<current->gpa;
        }
        current = current->next;
    }while(current != NULL);

    if(!student_found){
        system("cls");
        cout<<"\n\n  -------------------------------------------------\n";
        cout<<"    Couldn't find a student by the Name "<<student_name;
    }
    cout<<"\n  -----------------------------------------------------\n";
    cout<<"   </Enter any key to go back> ";
}

void sort_student_list(int sort_by){
    //Sort BY 1=ID, 2=GPA, 3=Age
    CS_Student *least_of_sorted = NULL;//the student with the smallest {Sort By} out of sorted ones

    while(first_student != least_of_sorted){
        new_student = first_student;//the new student with greater {Sort By} (the one to be compared)
        current = new_student->next;
        while(current != least_of_sorted){
            if((sort_by == 1 && (new_student->id > current->id)) ||
               (sort_by == 2 && (new_student->gpa > current->gpa)) ||
               (sort_by == 3 && (new_student->age > current->age)) ||
               (sort_by == 4 && (new_student->name.compare(current->name) > 0))
              ){
            //link the targets to their new neighbors
                new_student->next = current->next;
                current->prev = new_student->prev;
            //link the new neighbors with the targets
                if(new_student == first_student){//if it is the first student, No Next pointer to it
                    current->next->prev = new_student;
                    first_student = current;
                }
                else if(current->next == NULL)//if it is the last students, No previous pointer to it
                    new_student->prev->next = current;
                else{//if it is somewhere in between
                    new_student->prev->next = current;
                    current->next->prev = new_student;
                }
            //link the two targets together
                new_student->prev = current;
                current->next = new_student;
            }
            else{//If the order is correct, No Swap is needed, Simply update the student to be compared.
                new_student = current;
            }

            current = new_student->next;
        /*uncomment the lines below to see the sorting in action
            CS_Student *s = first_student;
            while(s != NULL){
                cout<<s->name<<" -> ";
                s = s->next;
            }
            cout<<endl;
            getch();*/
        }
        least_of_sorted = new_student;
        //cout<<endl;//uncomment this line too.
    }
    sorted = true;
    system("cls");
    switch(sort_by){
        case 1:
            cout<<"\n\t\t  [ Sorted By ID ASC]";
            break;
        case 2:
            cout<<"\n\t\t  [ Sorted By GPA ASC]";
            break;
        case 3:
            cout<<"\n\t\t  [ Sorted By Age ASC]";
            break;
        case 4:
            cout<<"\n\t\t  [ Sorted By Name ASC]";
            break;
    }
    sorted_by = sort_by;
    displaystudents();
}
void reverse_list(){//Bubble sort concept with out the comparing part
    CS_Student *last_of_reversed = NULL;//lastly reversed student in the list

    while(first_student != last_of_reversed){
        new_student = first_student;//the new student with greater {Sorted By}
        current = new_student->next;
        while(current != last_of_reversed ){
        //link the targets to their new neighbors
            new_student->next = current->next;
            current->prev = new_student->prev;
        //link the new neighbors with the targets
            if(new_student == first_student){//if it is the first student, No Next pointer to it
                current->next->prev = new_student;
                first_student = current;
            }
            else if(current->next == NULL)//if it is the last students, No previous pointer to it
                new_student->prev->next = current;
            else{//if it is somewhere in between
                new_student->prev->next = current;
                current->next->prev = new_student;
            }
        //link the two targets together
            new_student->prev = current;
            current->next = new_student;

            current = new_student->next;
        }
        last_of_reversed = new_student;
    }
}

void insert_handler(){
    int position, middle_position;
    new_student = new CS_Student();

    system("cls");
    cout<<"  ------------------------------";
    cout<<"\n     >>>>ADD NEW STUDENT<<<<";
    cout<<position_menu;
    cin>>position;
    if(position == Middle && first_student == NULL){//if no students are present & the user chose middle position
        cout<<"    There is no mid position. No students are added yet. ";
        getch();
        return;
    }
    else if(position > 4 || position < 1){
        cout<<"  Invalid Position!";
        return;
    }
    else if(position == 4)
        return;


    system("cls");
    cout<<main_title<<endl;
    cout<<"               >>>> ADD NEW STUDENT <<<<\n"<<endl;
    cout<<"   Enter ID: ";
    cin>>new_student->id;

    cout<<"   Enter Name: ";
    cin.ignore();
    getline(cin, new_student->name);

    cout<<"   Enter Age: ";
    cin>>new_student->age;

    cout<<"   Enter GPA: ";
    cin>>new_student->gpa;

    cout<<"\n  -----------------------------------------------------\n";
    new_student->next = NULL;
    new_student->prev = NULL;

/******* Common Insertions for all positions *******/
    current = first_student;
    if(current == NULL){
        first_student = new_student;
        count_students++;
        cout<<"  > "<<new_student->name<<" is the first student in the list. ";
        getch();
    }
/******* if the list has at least 1 student, insert at the desired position. *******/
    else if(position == End)
        insert_at_end(new_student);
    else if(position == Middle){
        cout<<"   Enter the Position No.: ";
        cin>>middle_position;
        insert_at_middle(new_student, middle_position);
    }
    else if(position == Beginning)
        insert_at_begnning(new_student);
}
void delete_handler(){
    int position, middle_position;
    system("cls");
    cout<<position_menu;
    cin>>position;
    if(position == 4)
        return;
    else if(position > 3 || position< 1)
        cout<<"    Invalid Position.";

/******* Common deletion for lists containing 1 or no students at all. *******/
    current = first_student;
    if(current == NULL){//If no Student is present in the list
        cout<<"    No students are added yet."<<endl;
        getch();
    }
    else if (current->next == NULL && position != Middle){//If only one Student is present
        first_student = NULL;
        count_students--;
        cout<<"\n    > "<<current->name<<", is removed from of the list\n\t( The list is now Empty. ) ";
        getch();
    }
/******* If more than 1 student is present in the list call the respective functions *******/
    else{
        if(position == End)
            delete_at_end();
        else if(position == Middle){
            cout<<"   Enter the Position No.: ";
            cin>>middle_position;
            delete_at_middle(middle_position);
        }
        else if(position == Beginning)
            delete_at_begnning();
    }

}
bool sort_list_handler(){
    int sort_by;
    char wanna_sort, wanna_desc;
    if(!sorted){
        cout<<"\n  -----------------------------------------------------\n";
        cout<<"    Sort (y, n): ";
        cin>>wanna_sort;
        if(tolower(wanna_sort) != 'y'){
            sorted = false;
            cout<<"   </Enter any key to go back> ";
            return false;
        }
        else{
            cout<<sort_menu;
            cin>>sort_by;
            if(sort_by >= 1 && sort_by<=4)
                sort_student_list(sort_by);
            else{
                sorted = false;
                cout<<"   </Enter any key to go back> ";
                return false;
            }
        }
    }
    else if(sorted){
        cout<<"\n  -----------------------------------------------------\n";
        cout<<"   Sort In DESC (y, n): ";
        cin>>wanna_desc;
        sorted = false;
        if(tolower(wanna_desc) == 'y'){
            reverse_list();
            system("cls");
            switch(sorted_by){
                case 1:
                    cout<<"\n\t\t  [ Sorted By ID DESC]";
                    break;
                case 2:
                    cout<<"\n\t\t  [ Sorted By GPA DESC]";
                    break;
                case 3:
                    cout<<"\n\t\t  [ Sorted By Age DESC]";
                    break;
                case 4:
                    cout<<"\n\t\t  [ Sorted By Name DESC]";
                    break;
            }
        }
        else{
            system("cls");
            cout<<endl;
            return false;
        }
    }

    return true;
}
void search_handler(){
    int search_by, student_id;
    bool student_found;
    string name;

    system("cls");
    current = first_student;
    if(current == NULL){//If no Student is present in the list
        cout<<main_title<<"    No students are added yet.";
        return;
    }
    cout<<search_menu;
    cin>>search_by;

    if(search_by == 1){
        cout<<"   Enter Student Id: ";
        cin>>student_id;
        search_by_id(student_id);
    }
    else if(search_by == 2){
        cout<<"   Enter Student Name: ";
        cin>>name;
        search_by_name(name);
    }
    else
        cout<<"  Invalid Choice!";

}


int main(){
    int main_menu_choice;
    start:
        system("cls");
        cout<<main_title<<main_menu;
        cin>>main_menu_choice;
        switch(main_menu_choice){
            case 1:
                system("cls");
                displaystudents();
                getch();
                goto start;
                break;
            case 2:
                insert_handler();
                goto start;
                break;
            case 3:
                delete_handler();
                goto start;
                break;
            case 4:
                search_handler();
                getch();
                goto start;
                break;
            case 5:
                system("cls");
                cout<<exit_message;
                exit(0);
            default:
                cout<<" Invalid Input! Enter any key to continue.";
                getch();
                goto start;

        }

    return 0;
}
