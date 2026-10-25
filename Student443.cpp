#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX = 100;   

class Person {
protected:
    int id;
    string name;
public:
    Person() : id(0), name("") {}
    Person(int i, string n) : id(i), name(n) {}

    int getId()  { return id; }
    string getName()  { return name; }
};


class Student : public Person {
    int present;   
    int total;     
public:
    Student() : Person(), present(0), total(0) {}
    Student(int i, string n) : Person(i, n), present(0), total(0) {}

    double percentage() const {
        if (total == 0) return 0;
        return (present * 100.0) / total;
    }

  
    Student& operator++() {
        present++;
        total++;
        return *this;
    }

  
    Student& operator--() {
        total++;
        return *this;
    }


    bool operator>(const Student& s) const {
        return percentage() > s.percentage();
    }

  
    bool operator==(const Student& s) const {
        return id == s.id;
    }


    friend ostream& operator<<(ostream& out, const Student& s) {
        out << left << setw(8) << s.id << setw(20) << s.name
            << setw(10) << s.present << setw(10) << s.total
            << fixed << setprecision(1) << s.percentage() << "%";
        return out;
    }

   
    friend istream& operator>>(istream& in, Student& s) {
        cout << "Enter Roll No : ";
        in >> s.id;
        cout << "Enter Name    : ";
        in.ignore();
        getline(in, s.name);
        return in;
    }
};

class Teacher : public Person {
    string subject;
public:
    Teacher(int i, string n, string sub) : Person(i, n), subject(sub) {}

    friend ostream& operator<<(ostream& out, const Teacher& t) {
        out << "Teacher: " << t.name << " (ID " << t.id << ") - Subject: " << t.subject;
        return out;
    }
};

void printHeader() {
    cout << left << setw(8) << "Roll" << setw(20) << "Name"
         << setw(10) << "Present" << setw(10) << "Total" << "Percent\n";
    cout << string(55, '-') << "\n";
}


int findStudent(Student list[], int count, int roll) {
    for (int i = 0; i < count; i++)
        if (list[i].getId() == roll) return i;
    return -1;
}

int main() {
    Student students[MAX]; 
    int count = 0;         

    Teacher teacher(101, "Prof. Mehta", "C++ Programming");
    cout << teacher << "\n";

    int choice;
    do {
        cout << "\n===== ATTENDANCE MENU =====\n"
             << "1. Add Student\n"
             << "2. Mark Attendance (all students)\n"
             << "3. Show All Students\n"
             << "4. Show Defaulters (below 75%)\n"
             << "5. Show Topper (best attendance)\n"
             << "0. Exit\n"
             << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            if (count == MAX) {
                cout << "Student limit reached!\n";
                continue;
            }
            Student s;
            cin >> s;                                        // operator >>
            if (findStudent(students, count, s.getId()) != -1)
                cout << "Roll number already exists!\n";
            else {
                students[count] = s;
                count++;
                cout << "Student added.\n";
            }
        }
        else if (choice == 2) {
            if (count == 0) { cout << "No students yet.\n"; continue; }
            for (int i = 0; i < count; i++) {
                char status;
                cout << students[i].getName() << " (P/A): ";
                cin >> status;
                if (status == 'P' || status == 'p') ++students[i];   
                else                                --students[i];   
            }
            cout << "Attendance recorded.\n";
        }
        else if (choice == 3) {
            if (count == 0) { cout << "No students yet.\n"; continue; }
            printHeader();
            for (int i = 0; i < count; i++)
                cout << students[i] << "\n";                
        }
        else if (choice == 4) {
            printHeader();
            bool found = false;
            for (int i = 0; i < count; i++)
                if (students[i].percentage() < 75) {
                    cout << students[i] << "\n";
                    found = true;
                }
            if (!found) cout << "No defaulters.\n";
        }
        else if (choice == 5) {
            if (count == 0) { cout << "No students yet.\n"; continue; }
            int top = 0;
            for (int i = 1; i < count; i++)
                if (students[i] > students[top])             
                    top = i;
            printHeader();
            cout << students[top] << "\n";
        }
    } while (choice != 0);

    cout << "Goodbye!\n";
    return 0;
}