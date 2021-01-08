#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

struct student
{
    char name[51];
    // registration number A123456
    char registration[8];
    // degree major
    char major[51];
    // street address
    char address1[51];
    // city, state, and zipcode
    char address2[51];
    // phone number format like (888)888-8888
    char phone[14];
    // gpa like 4.0
    double gpa;
    // dob format like DD/MM/YYYY
    char dob[11];
};

// function prototypes
void addNewStudent();
void displayStudent();
void removeStudent();
void editStudent();
void displayAll();

int main()
{
    // variable to store user's menu choice
    char choice;

    // display the menu until user quits
    do {
        // display menu
        cout << "1. Add New Student" << endl;
        cout << "2. Display a Students" << endl;
        cout << "3. Remove Student" << endl;
        cout << "4. Edit Student" << endl;
        cout << "5. Display All Students" << endl;
        cout << "6. Quit" << endl;
        cout << "Enter a choice: ";
        
        cin >> choice;

        // using ASCII values because choice is a char
        // check for valid choice
        while (choice < 49 || choice > 54)
        {
            cout << "Please enter a valid choice between 1 and 6!" << endl;
            cin >> choice;
        }

        cin.ignore();

        // switch-case to execute proper menu choice
        switch (choice) {
            case 49:
                addNewStudent();
                break;
            case 50:
                displayStudent();
                break;
            case 51:
                removeStudent();
                break;
            case 52:
                editStudent();
                break;
            case 53:
                displayAll();
                break;
            case 54:
                break;
        }
    } while (choice != 54);

    // successful termination
    return 0;
}