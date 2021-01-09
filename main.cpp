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
void addNewStudent(string);
//void displayStudent();
//void removeStudent();
//void editStudent();
//void displayAll();

int main()
{
    
    string fileName;
    fileName = "students.txt";


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
                addNewStudent(fileName);
                break;
            case 50:
                //displayStudent();
                break;
            case 51:
                //removeStudent();
                break;
            case 52:
                //editStudent();
                break;
            case 53:
                //displayAll();
                break;
            case 54:
                break;
        }
    } while (choice != 54);

    // successful termination
    return 0;
}

void addNewStudent(string fileName)
{
    fstream dataFile (fileName, ios::out | ios::binary | ios::app);

    if (!dataFile)
    {
        cout << "Error opening file. Try again." << endl;
        exit(0);
    }

    student S;

    cout << "Enter student name: ";
    cin.getline(S.name, 51);

    while (strlen(S.name) < 1)
    {
        cout << "Name cannot be left blank!" << endl;
        cin.getline(S.name, 51);
    }

    cout << "Enter student ID: ";
    cin.getline(S.registration, 8);

    while (strlen(S.registration) < 1)
    {
        cout << "Student ID cannot be left blank!" << endl;
        cin.getline(S.registration, 8);
    }

    cout << "Enter student major: ";
    cin.getline(S.major, 51);

    while (strlen(S.major) < 1)
    {
        cout << "Major cannot be left blank!" << endl;
        cin.getline(S.major, 51);
    }

    cout << "Enter student street address: ";
    cin.getline(S.address1, 51);

    while (strlen(S.address1) < 1)
    {
        cout << "Street address cannot be left blank!" << endl;
        cin.getline(S.address1, 51);
    }

    cout << "Enter student city, state, and zipcode: ";
    cin.getline(S.address2, 51);

    while (strlen(S.address2) < 1)
    {
        cout << "City, state, and zipcode cannot be left blank!" << endl;
        cin.getline(S.address2, 51);
    }

    cout << "Enter student phone number in format (XXX)XXX-XXXX: ";
    cin.getline(S.phone, 14);

    /*
    while (strlen(S.phone) < 1)
    {
        cout << "Phone cannot be left blank!" << endl;
        cin.getline(S.phone, 14);
    }
    */

    cout << "Enter student GPA: ";
    cin >> S.gpa;
    
    while (S.gpa < 0)
    {
        cout << "GPA cannot be negative!" << endl;
        cin >> S.gpa;
    }

    cout << "Enter student DOB in format DD//MM/YYYY: ";
    cin.getline(S.dob, 11);

    /*
    while (strlen(S.name) < 1)
    {
        cout << "Name cannot be left blank!" << endl;
        cin.getline(S.name, 51);
    }
    */

    cout << "Now writing to file..." << endl;

    dataFile.write(reinterpret_cast<char *>(&S), sizeof(S));

    cout << "Successful!" << endl;

    dataFile.close();



}