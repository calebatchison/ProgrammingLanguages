// Caleb Atchison
// C++ Assignment 1

#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
using namespace std;

// Problem 1: Class student
class student {
    private:
        int admno;
        char sname[21]; // up to 20 characters + null terminator
        float eng, math, science;
        float total;
        // Private function to calculate total marks
        float ctotal() {
            return eng + math + science;
        }
    public:
        // Function to take input and calculate total
        void Takedata() {
            cout << "Enter Admission Number: ";
            cin >> admno;
            cout << "Enter Student Name: ";
            cin.ignore();
            cin.getline(sname, 21);
            cout << "Enter marks for English, Math, Science (separated by spaces): ";
            cin >> eng >> math >> science;
            total = ctotal();
        }
        // Function to display student data
        void Showdata() {
            cout << "\n--- Student Information ---\n";
            cout << "Admission Number: " << admno << endl;
            cout << "Name: " << sname << endl;
            cout << "Marks: English = " << eng 
                << ", Math = " << math 
                << ", Science = " << science << endl;
            cout << "Total Marks: " << total << endl;
        }
};

void runProblem1() {
    cout << "\n========== Running Problem 1 ==========\n";
    student s;
    s.Takedata();
    s.Showdata();
}

// Problem 2: Class batsman
class batsman {
    private:
        int bcode;
        char bname[21];
        int innings, notout, runs;
        float batavg;
        // Function to calculate batting average
        void calcavg() {
            if ((innings - notout) != 0)
                batavg = static_cast<float>(runs) / (innings - notout);
            else
                batavg = 0;
        }
    public:
        // Function to input batsman details and calculate average
        void readdata() {
            cout << "Enter Batsman Code: ";
            cin >> bcode;
            cout << "Enter Batsman Name: ";
            cin.ignore();
            cin.getline(bname, 21);
            cout << "Enter Innings, Not Out and Runs (separated by spaces): ";
            cin >> innings >> notout >> runs;
            calcavg();
        }
        // Function to display batsman details
        void displaydata() {
            cout << "\n--- Batsman Information ---\n";
            cout << "Batsman Code: " << bcode << endl;
            cout << "Name: " << bname << endl;
            cout << "Innings: " << innings << ", Not Out: " << notout << ", Runs: " << runs << endl;
            cout << "Batting Average: " << batavg << endl;
        }
};

void runProblem2() {
    cout << "\n========== Running Problem 2 ==========\n";
    batsman b;
    b.readdata();
    b.displaydata();
}

// Problem 3: Class TEST
class TEST {
    private:
        int TestCode;
        string Description;
        int NoCandidate;
        int CenterReqd;
        // Function to calculate number of centers required
        int CALCNTR() {
            return (NoCandidate / 100) + 1;
        }
    public:
        // Function to input test data and calculate centers required
        void SCHEDULE() {
            cout << "Enter Test Code: ";
            cin >> TestCode;
            cout << "Enter Description: ";
            cin.ignore();
            getline(cin, Description);
            cout << "Enter Number of Candidates: ";
            cin >> NoCandidate;
            CenterReqd = CALCNTR();
        }
        // Function to display test details
        void DISPTEST() {
            cout << "\n--- Test Information ---\n";
            cout << "Test Code: " << TestCode << endl;
            cout << "Description: " << Description << endl;
            cout << "Number of Candidates: " << NoCandidate << endl;
            cout << "Number of Centers Required: " << CenterReqd << endl;
        }
};

void runProblem3() {
    cout << "\n========== Running Problem 3 ==========\n";
    TEST t;
    t.SCHEDULE();
    t.DISPTEST();
}

// Problem 4: Flight Class
class Flight {
    private:
        int flightNumber;
        string Destination;
        float Distance;
        float Fuel;
        // Function to calculate fuel based on distance criteria
        void CALFUEL() {
            if (Distance <= 1000)
                Fuel = 500;
            else if (Distance <= 2000)
                Fuel = 1100;
            else
                Fuel = 2200;
        }
    public:
        // Function to input flight information and calculate fuel
        void FEEDINFO() {
            cout << "Enter Flight Number: ";
            cin >> flightNumber;
            cout << "Enter Destination: ";
            cin.ignore();
            getline(cin, Destination);
            cout << "Enter Distance: ";
            cin >> Distance;
            CALFUEL();
        }
        // Function to display flight details
        void SHOWINFO() {
            cout << "\n--- Flight Information ---\n";
            cout << "Flight Number: " << flightNumber << endl;
            cout << "Destination: " << Destination << endl;
            cout << "Distance: " << Distance << " km" << endl;
            cout << "Fuel Required: " << Fuel << " litres" << endl;
        }
};

void runProblem4() {
    cout << "\n========== Running Problem 4 ==========\n";
    Flight f;
    f.FEEDINFO();
    f.SHOWINFO();
}

// Problem 5: Class BOOK
class BOOK {
    private:
        int bookNo;
        char bookTitle[21];
        float price;
        // Function to calculate total cost for a given number of copies
        float TOTAL_COST(int copies) {
            return price * copies;
        }
    public:
        // Function to input book details
        void INPUT() {
            cout << "Enter Book Number: ";
            cin >> bookNo;
            cout << "Enter Book Title: ";
            cin.ignore();
            cin.getline(bookTitle, 21);
            cout << "Enter Price per Copy: ";
            cin >> price;
        }
        // Function to handle purchase and display total cost
        void PURCHASE() {
            int copies;
            cout << "Enter number of copies to purchase: ";
            cin >> copies;
            float totalCost = TOTAL_COST(copies);
            cout << "\nTotal Cost to be paid: " << totalCost << endl;
        }
};

void runProblem5() {
    cout << "\n========== Running Problem 5 ==========\n";
    BOOK b;
    b.INPUT();
    b.PURCHASE();
}

// Problem 6: Class REPORT
class REPORT {
    private:
        int adno;
        char name[21];
        float marks[5];
        float average;
        // Function to calculate average marks
        void GETAVG() {
            float sum = 0;
            for (int i = 0; i < 5; i++) {
                sum += marks[i];
            }
            average = sum / 5;
        }
    public:
        // Function to input report information and compute average
        void READINFO() {
            cout << "Enter Admission Number: ";
            cin >> adno;
            cout << "Enter Name: ";
            cin.ignore();
            cin.getline(name, 21);
            cout << "Enter marks for 5 subjects:" << endl;
            for (int i = 0; i < 5; i++) {
                cout << "Subject " << i + 1 << ": ";
                cin >> marks[i];
            }
            GETAVG();
        }
        // Function to display report details
        void DISPLAYINFO() {
            cout << "\n--- Report Information ---\n";
            cout << "Admission Number: " << adno << endl;
            cout << "Name: " << name << endl;
            cout << "Marks: ";
            for (int i = 0; i < 5; i++) {
                cout << marks[i] << " ";
            }
            cout << "\nAverage Marks: " << average << endl;
        }
};

void runProblem6() {
    cout << "\n========== Running Problem 6 ==========\n";
    REPORT r;
    r.READINFO();
    r.DISPLAYINFO();
}

// Problem 7: Class Rectangle
class Rectangle {
    private:
        float length, width;
    public:
        void setlength(float l) {
            length = l;
        }
        void setwidth(float w) {
            width = w;
        }
        float perimeter() {
            return 2 * (length + width);
        }
        float area() {
            return length * width;
        }
        void show() {
            cout << "Length: " << length << ", Width: " << width << endl;
        }
        // Returns 1 if areas are equal, 0 otherwise
        int sameArea(Rectangle r) {
            return (area() == r.area()) ? 1 : 0;
        }
};

void runProblem7() {
    cout << "\n========== Running Problem 7 ==========\n";
    Rectangle r1, r2;
    
    // First scenario
    r1.setlength(5);    r1.setwidth(2.5);
    r2.setlength(5);    r2.setwidth(18.9);
    
    cout << "\n--- First Scenario ---" << endl;
    cout << "Rectangle 1:" << endl;
    r1.show();
    cout << "Area: " << r1.area() << ", Perimeter: " << r1.perimeter() << endl;
    
    cout << "\nRectangle 2:" << endl;
    r2.show();
    cout << "Area: " << r2.area() << ", Perimeter: " << r2.perimeter() << endl;
    
    if(r1.sameArea(r2))
        cout << "\nBoth rectangles have the same area." << endl;
    else
        cout << "\nRectangles have different areas." << endl;
    
    // Second scenario: Update r1
    r1.setlength(15);    r1.setwidth(6.3);
    
    cout << "\n--- Second Scenario (After updating Rectangle 1) ---" << endl;
    cout << "Rectangle 1:" << endl;
    r1.show();
    cout << "Area: " << r1.area() << ", Perimeter: " << r1.perimeter() << endl;
    
    cout << "\nRectangle 2:" << endl;
    r2.show();
    cout << "Area: " << r2.area() << ", Perimeter: " << r2.perimeter() << endl;
    
    if(r1.sameArea(r2))
        cout << "\nBoth rectangles have the same area." << endl;
    else
        cout << "\nRectangles have different areas." << endl;
}

// Problem 8: Class complex
class complex {
    private:
        float real, imag;
    public:
        // Set real and imaginary parts
        void set(float r, float i) {
            real = r;
            imag = i;
        }
        // Display complex number in "a + bi" format
        void disp() {
            cout << real << " + " << imag << "i" << endl;
        }
        // Return the sum of two complex numbers
        complex sum(complex c) {
            complex temp;
            temp.real = real + c.real;
            temp.imag = imag + c.imag;
            return temp;
        }
};

void runProblem8() {
    cout << "\n========== Running Problem 8 ==========\n";
    complex c1, c2, c3;
    float r, i;
    
    cout << "Enter real and imaginary parts for first complex number: ";
    cin >> r >> i;
    c1.set(r, i);
    
    cout << "Enter real and imaginary parts for second complex number: ";
    cin >> r >> i;
    c2.set(r, i);
    
    c3 = c1.sum(c2);
    
    cout << "\nFirst complex number: ";
    c1.disp();
    cout << "Second complex number: ";
    c2.disp();
    cout << "Sum: ";
    c3.disp();
}

// Problem 9: Class Distance
class Distance {
    private:
        int feet;
        float inches;
    public:
        void set(int f, float in) {
            feet = f;
            inches = in;
        }
        void disp() {
            cout << feet << " feet " << inches << " inches" << endl;
        }
        // Adds two distances and adjusts inches to feet if needed
        Distance add(Distance d) {
            Distance temp;
            temp.feet = feet + d.feet;
            temp.inches = inches + d.inches;
            if (temp.inches >= 12) {
                temp.feet += static_cast<int>(temp.inches / 12);
                temp.inches = fmod(temp.inches, 12);
            }
            return temp;
        }
};

void runProblem9() {
    cout << "\n========== Running Problem 9 ==========\n";
    Distance d1, d2, d3;
    int f;
    float in;
    
    cout << "Enter feet and inches for first distance: ";
    cin >> f >> in;
    d1.set(f, in);
    
    cout << "Enter feet and inches for second distance: ";
    cin >> f >> in;
    d2.set(f, in);
    
    d3 = d1.add(d2);
    
    cout << "\nDistance 1: ";
    d1.disp();
    cout << "Distance 2: ";
    d2.disp();
    cout << "Sum of distances: ";
    d3.disp();
}

// Problem 10: Class time
class timeClass {  // renamed to avoid conflict with std::time
    private:
        int hours, minutes;
    public:
        // Set time and adjust minutes if needed
        void settime(int h, int m) {
            hours = h;
            minutes = m;
            if (minutes >= 60) {
                hours += minutes / 60;
                minutes = minutes % 60;
            }
        }
        // Display time in hours and minutes
        void showtime() {
            cout << hours << " hours " << minutes << " minutes" << endl;
        }
        // Sum two time objects and adjust minutes if needed
        timeClass sum(timeClass t) {
            timeClass temp;
            temp.hours = hours + t.hours;
            temp.minutes = minutes + t.minutes;
            if (temp.minutes >= 60) {
                temp.hours += temp.minutes / 60;
                temp.minutes = temp.minutes % 60;
            }
            return temp;
        }
};

void runProblem10() {
    cout << "\n========== Running Problem 10 ==========\n";
    timeClass t1, t2, t3;
    int h, m;
    
    cout << "Enter hours and minutes for first time: ";
    cin >> h >> m;
    t1.settime(h, m);
    
    cout << "Enter hours and minutes for second time: ";
    cin >> h >> m;
    t2.settime(h, m);
    
    t3 = t1.sum(t2);
    
    cout << "\nFirst time: ";
    t1.showtime();
    cout << "Second time: ";
    t2.showtime();
    cout << "Sum of times: ";
    t3.showtime();
}

// Main Function with a Menu to Run Each Problem
int main() {
    int choice;
    do {
        cout << "\n===========================================" << endl;
        cout << "Select a problem to run:" << endl;
        cout << "1. Problem 1: Student" << endl;
        cout << "2. Problem 2: Batsman" << endl;
        cout << "3. Problem 3: TEST" << endl;
        cout << "4. Problem 4: Flight" << endl;
        cout << "5. Problem 5: BOOK" << endl;
        cout << "6. Problem 6: REPORT" << endl;
        cout << "7. Problem 7: Rectangle" << endl;
        cout << "8. Problem 8: Complex Numbers" << endl;
        cout << "9. Problem 9: Distance" << endl;
        cout << "10. Problem 10: Time" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1: runProblem1(); break;
            case 2: runProblem2(); break;
            case 3: runProblem3(); break;
            case 4: runProblem4(); break;
            case 5: runProblem5(); break;
            case 6: runProblem6(); break;
            case 7: runProblem7(); break;
            case 8: runProblem8(); break;
            case 9: runProblem9(); break;
            case 10: runProblem10(); break;
            case 0: cout << "Exiting program." << endl; break;
            default: cout << "Invalid choice. Please try again." << endl;
        }
    } while(choice != 0);
    
    return 0;
}