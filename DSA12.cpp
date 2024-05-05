/*Company maintains employee information as employee ID, name, designation and salary. 
Allow user to add, delete information of employee. Display information of particular employee. 
If employee does not exist an appropriate message is displayed.
 If it is, then the system displays the employee details. Use index sequential file to maintain the data.*/
#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

class Employee {
    struct emp {
        int emp_id;
        char name[30];
        char department[20];
        char address[50];
    } rec;

public:
    void create();
    void display();
    int search();
    void Delete();
};

void Employee::create() {
    char ans;
    ofstream fout;
    fout.open("emp.dat", ios::out | ios::app | ios::binary); // Open file in append mode
    do {
        cout << "\n\tEnter Employee ID: ";
        cin >> rec.emp_id;
        cout << "\n\tEnter Employee Name: ";
        cin.ignore(); // Ignore newline character in buffer
        cin.getline(rec.name, 30);
        cout << "\n\tEnter Department: ";
        cin.getline(rec.department, 20);
        cout << "\n\tEnter Address: ";
        cin.getline(rec.address, 50);
        fout.write((char *)&rec, sizeof(emp)) << flush;
        cout << "\n\tDo You Want to Add More Employees (y/n)?: ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');
    fout.close();
}

void Employee::display() {
    ifstream fin;
    fin.open("emp.dat", ios::in | ios::binary);
    cout << "\n\tEmployee Records:\n";
    cout << "\n\tID\tName\t\t\tDepartment\tAddress";
    while (fin.read((char *)&rec, sizeof(emp))) {
        cout << "\n\t" << rec.emp_id << "\t" << rec.name << "\t\t" << rec.department << "\t\t" << rec.address;
    }
    fin.close();
}

int Employee::search() {
    int id;
    ifstream fin;
    fin.open("emp.dat", ios::in | ios::binary);
    cout << "\n\tEnter Employee ID to search: ";
    cin >> id;
    while (fin.read((char *)&rec, sizeof(emp))) {
        if (rec.emp_id == id) {
            cout << "\n\tRecord Found...\n";
            cout << "\n\tID\tName\t\t\tDepartment\tAddress";
            cout << "\n\t" << rec.emp_id << "\t" << rec.name << "\t\t" << rec.department << "\t\t" << rec.address;
            fin.close();
            return 1;
        }
    }
    cout << "\n\tRecord not Found...\n";
    fin.close();
    return 0;
}

void Employee::Delete() {
    int id;
    cout << "\n\tEnter Employee ID to delete: ";
    cin >> id;
    ifstream fin;
    ofstream fout;
    fin.open("emp.dat", ios::in | ios::binary);
    fout.open("temp.dat", ios::out | ios::binary);
    while (fin.read((char *)&rec, sizeof(emp))) {
        if (rec.emp_id != id) {
            fout.write((char *)&rec, sizeof(emp));
        }
    }
    fin.close();
    fout.close();
    remove("emp.dat");
    rename("temp.dat", "emp.dat");
    cout << "\n\tRecord Deleted";
}

int main() {
    Employee obj;
    int ch;
    char ans;
    do {
        cout << "\n\t***** Employee Information *****";
        cout << "\n\t1. Add Employee\n\t2. Display Employees\n\t3. Delete Employee\n\t4. Search Employee\n\t5. Exit";
        cout << "\n\tEnter Your Choice: ";
        cin >> ch;
        switch (ch) {
            case 1:
                obj.create();
                break;
            case 2:
                obj.display();
                break;
            case 3:
                obj.Delete();
                break;
            case 4:
                obj.search();
                break;
            case 5:
                break;
            default:
                cout << "\n\tInvalid choice!";
        }
        cout << "\n\tDo You Want to Continue (y/n)?: ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');
    return 0;
}
