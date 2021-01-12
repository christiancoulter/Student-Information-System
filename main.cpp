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
void displayStudent(string);
//void removeStudent();
//void editStudent();
//void displayAll();
void displayRecord(student);
bool validatePhone(char []);
bool validateDOB(char []);


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
                displayStudent(fileName);
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

    
    while (!validatePhone(S.phone))
    {
        cout << "Enter a valid phone number!" << endl;
        cin.getline(S.phone, 14);
    }
    
   cin.clear();
   cin.ignore(5, '\n');

    cout << "Enter student GPA: ";
    cin >> S.gpa;
    
    while (S.gpa < 0)
    {
        cout << "GPA cannot be negative!" << endl;
        cin >> S.gpa;
    }
    cin.ignore();

    cout << "Enter student DOB in format DD//MM/YYYY: ";
    cin.getline(S.dob, 11);

    
    while (!validateDOB(S.dob))
    {
        cout << "Enter a valid date of birth!" << endl;
        cin.getline(S.dob, 51);
    }
    
    cin.clear();
    cin.ignore(5, '\n');

    cout << "Now writing to file..." << endl;

    dataFile.write(reinterpret_cast<char *>(&S), sizeof(S));

    cout << "Successful!" << endl;

    dataFile.close();
}

void displayStudent(string fileName)
{
    fstream dataFile(fileName, ios::in | ios::binary);

    if (!dataFile)
    {
        cout << "Error opening file. Try again." << endl;
        exit(0);
    }

    // temporary struct to store data
    student temp;

    // array to store student's name to search
    char searchName[51];

    // prompt user to enter name to be searched
    cout << "Enter name of student to search: " << endl;
    cin.getline(searchName, 51);

    // move read position to beginning of the file
    dataFile.seekg(0L, ios::beg);

    // read first record
    dataFile.read(reinterpret_cast<char *>(&temp), sizeof(temp));

    while (!dataFile.eof())
    {
        if (strcmp(temp.name, searchName) == 0)
        {
            cout << "Record found! " << endl;
            // display record
            displayRecord(temp);
            dataFile.close();
            return;
        }
        else
        {
            dataFile.read(reinterpret_cast <char *>(&temp), sizeof(temp));
        }
    }
    // display error if no record found
    if (dataFile.eof())
    {
        cout << "No record found for " << searchName << "!" << endl;
    }

    // close file
    dataFile.close();
}


bool validateDOB(char date[11]){
    //check separators
    if(date[2] != '/' || date[5] != '/')
        return false;

    //check for length
    if(strlen(date) != 10)
        return false;

    //convert the char array to numbers accessing relevant indexes
    int day = (date[0]-'0')*10 + (date[1]-'0');
    int month = (date[3]-'0')*10 + (date[4]-'0');
    int year = (date[6]-'0')*1000 + (date[7]-'0')*100
                + (date[8]-'0')*10 + (date[9]-'0');

    //validate for day, month then year
    if(day < 1 || day > 31)
        return false;
    else if(month < 1 || month > 12)
        return false;

    return true;
}


//function for phone number validation
bool validatePhone(char phone[]){
    //check for length
    if(strlen(phone) != 13)
        return false;

    //format is (XXX)XXX-XXXX
    //check for separators
    else if(phone[0] != '(' || phone[4] != ')' || phone[8] != '-')
        return false;

    //validate for any char that is not digit
    for(int counter = 0; counter < 13; counter++){
        //disregard the separators located at
        //indexes 0, 4 and 8
        if(counter == 0 || counter == 4 || counter == 8)
            continue;
        else{
            //check if it's not a digit
            if(!isdigit(phone[counter]))
                return false;
        }
    }
    
    //otherwise, if all above have failed
    //means that date is input ok, return true
    return true;
}

void displayRecord(student S){
    //display each field along with the information
    cout << "\nStudent Name: ";
    cout << S.name << endl;
    cout << "Student Registration Number: ";
    cout << S.registration << endl;
    cout << "Student major: ";
    cout << S.major << endl;
    cout << "Student street address: ";
    cout << S.address1 << endl;
    cout << "Student city, state and ZIP: ";
    cout << S.address2 << endl;
    cout << "Student phone number: ";
    cout << S.phone << endl;
    cout << "Customer balance: ";
    cout << S.gpa << endl;
    cout << "Student birth date: ";
    cout << S.dob << endl;
}