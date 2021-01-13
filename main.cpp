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
    char studentID[51];
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
void removeStudent(string);
void editStudent(string);
void displayAll(string);
void displayRecord(student);
bool validatePhone(char []);
bool validateDOB(char []);
void Delete(char []);


int main()
{
    string fileName = "students.txt";

    // variable to store user's menu choice
    char choice;

    // display the menu until user quits
    do {
        // display menu
        cout << "1. Add New Student\n";
        cout << "2. Display a Student\n";
        cout << "3. Remove Student\n";
        cout << "4. Edit Student\n";
        cout << "5. Display All Students\n";
        cout << "6. Quit\n";
        cout << "Enter a choice: ";
        
        cin >> choice;

        // using ASCII values because choice is a char
        while (choice < 49 || choice > 54)
        {
            cout << "Please enter a valid choice between 1 and 6!\n";
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
                removeStudent(fileName);
                break;
            case 52:
                editStudent(fileName);
                break;
            case 53:
                displayAll(fileName);
                break;
            case 54:
                break;
        }
    } while (choice != 54);

    // termination
    return 0;
}

void addNewStudent(string fileName)
{
    fstream dataFile(fileName, ios::out | ios::binary | ios::app);

    // check that file opened correctly, terminate if not
    if(!dataFile){
        cout << "ERROR opening file. Please try again!\n";
        exit(0);
    }

    // declare new struct for reading data
    student Student;

    // read data into Student

    cout << "\nEnter Student name:\n";
    cin.getline(Student.name, 51);
    // validate input for empty strings
    while(strlen(Student.name) < 1){
        cout << "Name cannot be left blank!\n";
        cin.getline(Student.name, 51);
    }

    cout << "Enter Student ID number:\n";
    cin.getline(Student.studentID, 51);
    // validate input for empty strings
    while(strlen(Student.studentID) < 1){
        cout << "Student ID cannot be left blank!\n";
        cin.getline(Student.studentID, 51);
    }

    cout << "Enter Student major:\n";
    cin.getline(Student.major, 51);
    // validate input for empty strings
    while(strlen(Student.major) < 1){
        cout << "Student major cannot be left blank!\n";
        cin.getline(Student.major, 51);
    }

    cout << "Enter Student street address:\n";
    cin.getline(Student.address1, 51);
    // validate input for empty strings
    while(strlen(Student.address1) < 1){
        cout << "Street address cannot be left blank!\n";
        cin.getline(Student.address1, 51);
    }

    cout << "Enter Student city, state and ZIP:\n";
    cin.getline(Student.address2, 51);
    // validate input for empty strings
    while(strlen(Student.address2) < 1){
        cout << "City, state and ZIP cannot be left blank!\n";
        cin.getline(Student.address2, 51);
    }

    cout << "Enter Student phone number in format (XXX)XXX-XXXX:\n";
    cin.getline(Student.phone, 14);
    // validate phone number input
    while(!validatePhone(Student.phone)){
        cout << "Please enter a valid phone number!\n";
        cin.getline(Student.phone, 14);
    }

    cin.clear();
    cin.ignore(5, '\n');

    cout << "Enter Student student gpa:\n";
    cin >> Student.gpa;
    // validate gpa input
    while(Student.gpa < 0){
        cout << "Negative values are not accepted!\n";
        cin >> Student.gpa;
    }

    cin.ignore();

    cout << "Enter the date of the last payment in format DD/MM/YYYY:\n";
    cin.getline(Student.dob, 11);
    // validate date input
    while(!validateDOB(Student.dob)){
        cout << "Please enter a valid date!\n";
        cin.getline(Student.dob, 11);
    }

    cin.clear();
    cin.ignore(5, '\n');

    cout << "\nNow writing to file...\n";
    // write into the file
    dataFile.write(reinterpret_cast<char *>(&Student), sizeof(Student));
    cout << "Done writing!\n";

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

void removeStudent(string fileName)
{
    fstream dataFile (fileName, ios::in | ios::out | ios::binary);

    if (!dataFile)
    {
        cout << "Error opening file. Please try again!\n";
        exit(0);
    }

    student temp;

    char searchName[51];

    cout << "\nEnter the name of the student to delete\n";
    cin.getline(searchName, 51);

    // move read to beginning of file
    dataFile.seekg(0L, ios::beg);

    // read first record
    dataFile.read(reinterpret_cast<char *>(&temp), sizeof(temp));

    // continue reading until found or eof
    while (!dataFile.eof())
    {
        if (strcmp(temp.name, searchName) == 0)
        {
            cout << "\nRecord found!\n";
            displayRecord(temp);
            cout << "\nNow removing...\n";
            Delete(temp.name);
            Delete(temp.studentID);
            Delete(temp.major);
            Delete(temp.address1);
            Delete(temp.address2);
            Delete(temp.phone);
            temp.gpa = 0.0;
            Delete(temp.dob);

            dataFile.seekp(-(sizeof(temp)), ios::cur);

            dataFile.write(reinterpret_cast<char *>(&temp), sizeof(temp));

            cout << "\nStudent removed!\n";

            dataFile.close();

            return;
        }
        else
        {
            dataFile.read(reinterpret_cast<char *>(&temp), sizeof(temp));                      
        }
        
    }

    if (dataFile.eof())
    {
        cout << "\nAll entries searched!\n";
        cout << "There is no match for " << searchName << "!\n";
    }

    dataFile.close();
}

void editStudent(string fileName)
{
    fstream dataFile (fileName, ios::in | ios::out | ios::binary);

    if (!dataFile)
    {
        cout << "Error opening file. Please try again!\n";
        exit(0);
    }

    student temp;

    char searchName[51];

    cout << "\nEnter the name of the student to delete\n";
    cin.getline(searchName, 51);

    // move read to beginning of file
    dataFile.seekg(0L, ios::beg);

    // read first record
    dataFile.read(reinterpret_cast<char *>(&temp), sizeof(temp));

    // continue reading until found or eof
    while (!dataFile.eof())
    {
        if (strcmp(temp.name, searchName) == 0)
        {
            cout << "\nRecord Found!\n";
            displayRecord(temp);
            cout << "Please enter updated values!\n";

            cout << "Enter Student name:\n";
            cin.getline(temp.name, 51);
            // validate input for empty strings
            while(strlen(temp.name) < 1){
                cout << "Name cannot be left blank!\n";
                cin.getline(temp.name, 51);
            }

            cout << "Enter Student ID number:\n";
            cin.getline(temp.studentID, 51);
            // validate input for empty strings
            while(strlen(temp.studentID) < 1){
                cout << "Student ID cannot be left blank!\n";
                cin.getline(temp.studentID, 51);
            }

            cout << "Enter Student major:\n";
            cin.getline(temp.major, 51);
            // validate input for empty strings
            while(strlen(temp.major) < 1){
                cout << "Student major cannot be left blank!\n";
                cin.getline(temp.major, 51);
            }

            cout << "Enter Student street address:\n";
            cin.getline(temp.address1, 51);
            // validate input for empty strings
            while(strlen(temp.address1) < 1){
                cout << "Street address cannot be left blank!\n";
                cin.getline(temp.address1, 51);
            }

            cout << "Enter Student city, state and ZIP:\n";
            cin.getline(temp.address2, 51);
            // validate input for empty strings
            while(strlen(temp.address2) < 1){
                cout << "City, state and ZIP cannot be left blank!\n";
                cin.getline(temp.address2, 51);
            }

            cout << "Enter Student phone number in format (XXX)XXX-XXXX:\n";
            cin.getline(temp.phone, 14);
            // validate phone number input
            while(!validatePhone(temp.phone)){
                cout << "Please enter a valid phone number!\n";
                cin.getline(temp.phone, 14);
            }

            cin.clear();
            cin.ignore(5, '\n');

            cout << "Enter Student gpa:\n";
            cin >> temp.gpa;
            // validate gpa input
            while(temp.gpa < 0){
                cout << "Negative values are not accepted!\n";
                cin >> temp.gpa;
            }
       
            cin.ignore();

            cout << "Enter the date of the last payment in format DD/MM/YYYY:\n";
            cin.getline(temp.dob, 11);
            // validate date input
            while(!validateDOB(temp.dob)){
                cout << "Please enter a valid date!\n";
                cin.getline(temp.dob, 11);
            }

            cin.clear();
            cin.ignore(5, '\n');

            dataFile.seekp(-(sizeof(temp)), ios::cur);

            dataFile.write(reinterpret_cast<char * >(&temp), sizeof(temp));

            cout << "Record changed!\n";
            dataFile.close();
            return;
        }
        else
        {
            dataFile.read(reinterpret_cast<char *>(&temp), sizeof(temp));                      
        }
        
    }

    if (dataFile.eof())
    {
        cout << "\nAll entries searched!\n";
        cout << "There is no match for " << searchName << "!\n";
    }

    dataFile.close();
}

void displayAll(string fileName)
{
    fstream dataFile (fileName, ios::in | ios::out | ios::binary);

    if (!dataFile)
    {
        cout << "Error opening file. Please try again!\n";
        exit(0);
    }

    student temp;

    // move read to beginning of file
    dataFile.seekg(0L, ios::beg);

    // read first record
    dataFile.read(reinterpret_cast<char *>(&temp), sizeof(temp));

    // continue reading until found or eof
    while (!dataFile.eof())
    {
        displayRecord(temp);
        dataFile.read(reinterpret_cast<char *>(&temp), sizeof(temp));
    }
}


bool validateDOB(char dob[11]){
    //  check separators
    if(dob[2] != '/' || dob[5] != '/')
        return false;

    //  check length
    if(strlen(dob) != 10)
        return false;

    // convert the char array to numbers accessing relevant indexes
    int day = (dob[0]-'0')*10 + (dob[1]-'0');
    int month = (dob[3]-'0')*10 + (dob[4]-'0');
    int year = (dob[6]-'0')*1000 + (dob[7]-'0')*100
                + (dob[8]-'0')*10 + (dob[9]-'0');

    // validate for day, month then year
    if(day < 1 || day > 31)
        return false;
    else if(month < 1 || month > 12)
        return false;
    else if(year < 1900 || year > 2020)
        return false;

    return true;
}

bool validatePhone(char phone[]){
    // check length
    if(strlen(phone) != 13)
        return false;

    // check format
    else if(phone[0] != '(' || phone[4] != ')' || phone[8] != '-')
        return false;

    // validate for any char that is not digit
    for(int counter = 0; counter < 13; counter++){
        // disregard the separators
        if(counter == 0 || counter == 4 || counter == 8)
            continue;
        else{
            // check if it's not a digit
            if(!isdigit(phone[counter]))
                return false;
        }
    }
    
    return true;
}

void displayRecord(student Student){
    // display each field along with the information
    cout << "\nStudent Name: ";
    cout << Student.name << endl;
    cout << "Student ID Number: ";
    cout << Student.studentID << endl;
    cout << "Student major: ";
    cout << Student.major << endl;
    cout << "Student street address: ";
    cout << Student.address1 << endl;
    cout << "Student city, state and ZIP: ";
    cout << Student.address2 << endl;
    cout << "Student phone number: ";
    cout << Student.phone << endl;
    cout << "Student GPA: ";
    cout << Student.gpa << endl;
    cout << "Student birth date: ";
    cout << Student.dob << endl;
}

void Delete(char arr[])
{
    strcpy(arr, "DELETED");
}