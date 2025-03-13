// Assignment 2
// Caleb Atchison

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <cstring>
#include <iomanip>
#include <algorithm>
using namespace std;

// Problem 1: Write numbers 1 to 100 to NOTES.TXT
void writeNumbersToFile() {
    ofstream ofs("NOTES.TXT");
    if (!ofs) {
        cout << "Error opening NOTES.TXT for writing.\n";
        return;
    }
    for (int i = 1; i <= 100; i++) {
        ofs << i << "\n";
    }
    ofs.close();
    cout << "Numbers 1 to 100 written to NOTES.TXT\n";
}

// Problem 2: Write a string to OUT.TXT
void writeStringToFile() {
    string text = "Time is a great teacher but unfortunately it kills all its pupils. Berlioz";
    ofstream ofs("OUT.TXT");
    if (!ofs) {
        cout << "Error opening OUT.TXT for writing.\n";
        return;
    }
    ofs << text;
    ofs.close();
    cout << "String written to OUT.TXT\n";
}

// Problem 3: Count alphabets in OUT.TXT
void countAlphabetsInOUT() {
    ifstream ifs("OUT.TXT");
    if (!ifs) {
        cout << "Error opening OUT.TXT for reading.\n";
        return;
    }
    int count = 0;
    char ch;
    while (ifs.get(ch)) {
        if (isalpha(ch))
            count++;
    }
    ifs.close();
    cout << "Number of alphabets in OUT.TXT: " << count << "\n";
}

// Problem 4: Count blanks (spaces) in OUT.TXT
void countBlanksInOUT() {
    ifstream ifs("OUT.TXT");
    if (!ifs) {
        cout << "Error opening OUT.TXT for reading.\n";
        return;
    }
    int count = 0;
    char ch;
    while (ifs.get(ch)) {
        if (ch == ' ')
            count++;
    }
    ifs.close();
    cout << "Number of blanks in OUT.TXT: " << count << "\n";
}

// Problem 5: Count words in OUT.TXT
void countWordsInOUT() {
    ifstream ifs("OUT.TXT");
    if (!ifs) {
        cout << "Error opening OUT.TXT for reading.\n";
        return;
    }
    int count = 0;
    string word;
    while (ifs >> word) {
        count++;
    }
    ifs.close();
    cout << "Number of words in OUT.TXT: " << count << "\n";
}

// Problem 6: Count independent occurrences of "the" in STORY.TXT
void countTheInSTORY() {
    ifstream ifs("STORY.TXT");
    if (!ifs) {
        cout << "Error opening STORY.TXT for reading.\n";
        return;
    }
    int count = 0;
    string word;
    while (ifs >> word) {
        // Remove punctuation and convert to lowercase.
        string temp;
        for (size_t i = 0; i < word.length(); ++i) {
            char c = word[i];
            if (isalpha(c))
                temp.push_back(tolower(c));
        }
        if (temp == "the")
            count++;
    }
    ifs.close();
    cout << "Count of word \"the\" in STORY.TXT: " << count << "\n";
}

// Problem 7: Count lines not starting with 'A' in STORY.TXT
void countLinesNotStartingWithA() {
    ifstream ifs("STORY.TXT");
    if (!ifs) {
        cout << "Error opening STORY.TXT for reading.\n";
        return;
    }
    int count = 0;
    string line;
    while (getline(ifs, line)) {
        if (!line.empty()) {
            char first = line[0];
            if (first != 'A' && first != 'a')
                count++;
        }
    }
    ifs.close();
    cout << "Number of lines not starting with 'A': " << count << "\n";
}

// Problem 8: copyupper() – Copy words from FIRST.TXT to SECOND.TXT in UPPERCASE
void copyupper() {
    ifstream ifs("FIRST.TXT");
    if (!ifs) {
        cout << "Error opening FIRST.TXT for reading.\n";
        return;
    }
    ofstream ofs("SECOND.TXT");
    if (!ofs) {
        cout << "Error opening SECOND.TXT for writing.\n";
        return;
    }
    string word;
    while (ifs >> word) {
        transform(word.begin(), word.end(), word.begin(), ::toupper);
        ofs << word << " ";
    }
    ifs.close();
    ofs.close();
    cout << "Copied words in uppercase from FIRST.TXT to SECOND.TXT.\n";
}

// Problem 9: vowelwords() – Copy words starting with a lowercase vowel from FIRST.TXT to SECOND.TXT
void vowelwords() {
    ifstream ifs("FIRST.TXT");
    if (!ifs) {
        cout << "Error opening FIRST.TXT for reading.\n";
        return;
    }
    ofstream ofs("SECOND.TXT");
    if (!ofs) {
        cout << "Error opening SECOND.TXT for writing.\n";
        return;
    }
    string word;
    while (ifs >> word) {
        char first = word[0];
        if (first == 'a' || first == 'e' || first == 'i' || first == 'o' || first == 'u')
            ofs << word << " ";
    }
    ifs.close();
    ofs.close();
    cout << "Copied words starting with a lowercase vowel from FIRST.TXT to SECOND.TXT.\n";
}

// Problem 10: EMPLOYEE – Write/Read binary file (Employee records)
class EMPLOYEE {
    int ENO;
    char ENAME[10];
public:
    void GETIT() {
        cout << "Enter Employee Number: ";
        cin >> ENO;
        cin.ignore();
        cout << "Enter Employee Name: ";
        cin.getline(ENAME, 10);
    }
    void SHOWIT() {
        cout << "Employee Number: " << ENO << "  Name: " << ENAME << "\n";
    }
};

void writeEmployees() {
    ofstream ofs("employee.dat", ios::binary);
    if (!ofs) {
        cout << "Error opening employee.dat for writing.\n";
        return;
    }
    int n;
    cout << "How many employees to write? ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        EMPLOYEE emp;
        cout << "\nEmployee " << (i + 1) << ":\n";
        emp.GETIT();
        ofs.write((char*)&emp, sizeof(emp));
    }
    ofs.close();
    cout << n << " employees written to employee.dat.\n";
}

void readEmployees() {
    ifstream ifs("employee.dat", ios::binary);
    if (!ifs) {
        cout << "Error opening employee.dat for reading.\n";
        return;
    }
    EMPLOYEE emp;
    cout << "\nEmployee Records:\n";
    while (ifs.read((char*)&emp, sizeof(emp))) {
        emp.SHOWIT();
    }
    ifs.close();
}

// Problem 12: Computer – Read records from SHIP.DAT and count them
class computer {
    char chiptype[10];
    int speed;
public:
    // For this task, we assume records are already written in SHIP.DAT.
    void showdetails() {
        cout << "Chip " << chiptype << " Speed = " << speed << "\n";
    }
};

void readComputersFromShip() {
    ifstream ifs("SHIP.DAT", ios::binary);
    if (!ifs) {
        cout << "Error opening SHIP.DAT for reading.\n";
        return;
    }
    computer comp;
    int count = 0;
    cout << "\nComputer Records from SHIP.DAT:\n";
    while (ifs.read((char*)&comp, sizeof(comp))) {
        comp.showdetails();
        count++;
    }
    ifs.close();
    cout << "Total records in SHIP.DAT: " << count << "\n";
}

// Problem 13: Student – Display records from STUDENT.DAT with Percentage > 75
class Student {
    char S_Admno[10];   // Admission number
    char S_Name[30];    // Name
    int Percentage;     // Marks Percentage
public:
    void EnterData() {
        cin.ignore();
        cout << "Enter Admission Number: ";
        cin.getline(S_Admno, 10);
        cout << "Enter Name: ";
        cin.getline(S_Name, 30);
        cout << "Enter Percentage: ";
        cin >> Percentage;
    }
    void DisplayData() {
        cout << setw(12) << S_Admno
             << setw(32) << S_Name
             << setw(3) << Percentage << "\n";
    }
    int ReturnPercentage() { return Percentage; }
};

void displayTopStudents() {
    ifstream ifs("STUDENT.DAT", ios::binary);
    if (!ifs) {
        cout << "Error opening STUDENT.DAT for reading.\n";
        return;
    }
    Student s;
    cout << "\nStudents with Percentage > 75:\n";
    while (ifs.read((char*)&s, sizeof(s))) {
        if (s.ReturnPercentage() > 75)
            s.DisplayData();
    }
    ifs.close();
}

// Problem 14: Count records in EMP.DAT using seekg() and tellg()
int countEmpRecords() {
    fstream file("EMP.DAT", ios::binary | ios::in);
    if (!file) {
        cout << "Error opening EMP.DAT for reading.\n";
        return 0;
    }
    file.seekg(0, ios::end);                 // Statement 1
    int bytes = file.tellg();                // Statement 2
    int count = bytes / sizeof(EMPLOYEE);
    file.close();
    return count;
}

// Problem 15: Append new STUD record to STUDENT.DAT
class STUD {
    int Rno;
    char Name[20];
public:
    void Enter() {
        cout << "Enter Roll Number: ";
        cin >> Rno;
        cin.ignore();
        cout << "Enter Name: ";
        cin.getline(Name, 20);
    }
    void Display() {
        cout << "Roll Number: " << Rno << "  Name: " << Name << "\n";
    }
};

void appendSTUD() {
    ofstream ofs("STUDENT.DAT", ios::binary | ios::app);
    if (!ofs) {
        cout << "Error opening STUDENT.DAT for appending.\n";
        return;
    }
    STUD s;
    s.Enter();
    ofs.write((char*)&s, sizeof(s));
    ofs.close();
    cout << "Record appended to STUDENT.DAT.\n";
}

// Problem 16: Item – Search and Modify records in STOCK.DAT using seekp() and seekg()
class Item {
    int Ino;
    char ItemName[20];
public:
    // Function to search and display the content from a particular record number
    void Search(int RecNo) {
        fstream file("STOCK.DAT", ios::binary | ios::in);
        if (!file) {
            cout << "Error opening STOCK.DAT for reading.\n";
            return;
        }
        file.seekg((RecNo - 1) * sizeof(Item), ios::beg); // Statement 1
        file.read((char*)this, sizeof(Item));
        cout << "Record " << RecNo << " => " << Ino << " ==> " << ItemName << "\n";
        file.close();
    }
    // Function to modify the content of a particular record number
    void Modify(int RecNo) {
        fstream file("STOCK.DAT", ios::binary | ios::in | ios::out);
        if (!file) {
            cout << "Error opening STOCK.DAT for updating.\n";
            return;
        }
        cout << "Enter new Ino: ";
        cin >> Ino;
        cin.ignore();
        cout << "Enter new Item Name: ";
        cin.getline(ItemName, 20);
        file.seekp((RecNo - 1) * sizeof(Item), ios::beg); // Statement 2
        file.write((char*)this, sizeof(Item));
        file.close();
        cout << "Record modified in STOCK.DAT.\n";
    }
};

// Main driver: Menu to run individual problems
int main() {
    int choice;
    do {
        cout << "\n================== Menu ==================\n";
        cout << "1. Write numbers 1-100 to NOTES.TXT\n";
        cout << "2. Write string to OUT.TXT\n";
        cout << "3. Count alphabets in OUT.TXT\n";
        cout << "4. Count blanks in OUT.TXT\n";
        cout << "5. Count words in OUT.TXT\n";
        cout << "6. Count occurrences of \"the\" in STORY.TXT\n";
        cout << "7. Count lines not starting with 'A' in STORY.TXT\n";
        cout << "8. copyupper() – Copy words (uppercase) from FIRST.TXT to SECOND.TXT\n";
        cout << "9. vowelwords() – Copy words starting with a lowercase vowel from FIRST.TXT to SECOND.TXT\n";
        cout << "10. EMPLOYEE – Write/Read binary file (Employee records)\n";
        cout << "12. Computer – Read records from SHIP.DAT and count them\n";
        cout << "13. Display Students (Percentage > 75) from STUDENT.DAT\n";
        cout << "14. Count records in EMP.DAT using seekg()/tellg()\n";
        cout << "15. Append new STUD record to STUDENT.DAT\n";
        cout << "16. Item – Search/Modify record in STOCK.DAT\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "\n";
        switch (choice) {
            case 1: writeNumbersToFile(); break;
            case 2: writeStringToFile(); break;
            case 3: countAlphabetsInOUT(); break;
            case 4: countBlanksInOUT(); break;
            case 5: countWordsInOUT(); break;
            case 6: countTheInSTORY(); break;
            case 7: countLinesNotStartingWithA(); break;
            case 8: copyupper(); break;
            case 9: vowelwords(); break;
            case 10: {
                int subchoice;
                cout << "1. Write EMPLOYEE records\n2. Read EMPLOYEE records\nEnter choice: ";
                cin >> subchoice;
                if (subchoice == 1)
                    writeEmployees();
                else if (subchoice == 2)
                    readEmployees();
                else
                    cout << "Invalid subchoice.\n";
                break;
            }
            case 12: readComputersFromShip(); break;
            case 13: displayTopStudents(); break;
            case 14: {
                int cnt = countEmpRecords();
                cout << "Total records in EMP.DAT: " << cnt << "\n";
                break;
            }
            case 15: appendSTUD(); break;
            case 16: {
                Item it;
                int recno;
                cout << "Enter record number to search: ";
                cin >> recno;
                it.Search(recno);
                cout << "Enter record number to modify: ";
                cin >> recno;
                it.Modify(recno);
                break;
            }
            case 0: break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
    return 0;
}