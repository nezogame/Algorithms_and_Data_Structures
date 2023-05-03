
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Employees {

public:
    string fullName;
    int day;
    int month;
    int year;
    int childrenAmount;
    Employees(string FullName, tm *Birth, int ChildrenAmount) {
        fullName = FullName;
        day = Birth->tm_mday;
        month = Birth->tm_mon;
        year = Birth->tm_year;
        childrenAmount = ChildrenAmount;
    }
    Employees() {
        fullName = "";
        day = 1;
        month = 1;
        year = 1;
        childrenAmount = 0;
    }
    Employees(Employees& deepCopy){
        fullName = deepCopy.fullName;
        day = deepCopy.day;
        month = deepCopy.month;
        year = deepCopy.year;
        childrenAmount = deepCopy.childrenAmount;
    }
    void printEmployee();
};
class Staff:Employees {
    Employees** employeesArr;
    int size;
public:
    time_t now = time(0);


    Staff() {
        
        size = 4;
        employeesArr = new Employees*[size];
    }
    Staff(int Size) {
        size = Size;
        employeesArr = new Employees * [size];
    }

    void fill();
    void del(int index);
    void printAll();
    void delAll();
    void add();
    void findEmpYear(int desiredYear);
    int Interface();

};

void Employees::printEmployee() {


    cout << "Name and surname: " << fullName << ", date of birth: " 
    << day <<":" <<  month <<":" << year << ", amount of children: "
    << childrenAmount << endl << endl;
}
void Staff::fill() {
    tm* ltm = localtime(&now);
    string tName, tSurname, tFullName;
    int tChildrenAmount;
    for (int i = 0; i < size; i++) {
        cout << "Enter name : " << endl;
        cin >> tName;
        cout << "Enter surname : " << endl;
        cin >> tSurname;
        tFullName = tName + " " + tSurname;
        cout << "Enter day in format(dd): " << endl;
        cin >> ltm->tm_mday;
        cout << "Enter month in format(mm): " << endl;
        cin >> ltm->tm_mon;
        cout << "Enter year in format(yyyy): " << endl;
        cin >> ltm->tm_year;
        cout << "Enter amount of children: " << endl;
        cin >> tChildrenAmount;
        employeesArr[i] = new Employees(tFullName, ltm, tChildrenAmount);
    }
}
void Staff::del(int index) {
    if ((index >= 0 && index <= size-1) &&size!=0) {
        for (int i = index; i < size - 1; i++)
        {
            employeesArr[i] = new Employees(*employeesArr[i + 1]);
        }
        delete employeesArr[size - 1];
        size--;
    }
    else {
        cout << "You enter the wrong number, try again" << endl;
    }
}
void Staff::printAll() {
    if (size == 0) {
        cout << "Size is zero so array is empty";
    }
    else {
        for (int i = 0; i < size; i++) {
            employeesArr[i]->printEmployee();
        }
    }
}
void Staff::delAll() {
    for (int i = 0; i < size; i++) {
        delete employeesArr[i];
    }
    delete[] employeesArr;
    size=0;
}
void Staff::add() {
    tm* ltm = localtime(&now);
    string tName, tSurname, tFullName;
    int tChildrenAmount;
    Employees** newEmployeesArr = new Employees*[size+1];
    if (size==0){
        cout << "Enter name : " << endl;
        cin >> tName;
        cout << "Enter surname : " << endl;
        cin >> tSurname;
        tFullName = tName + " " + tSurname;
        cout << "Enter day in format(dd): " << endl;
        cin >> ltm->tm_mday;
        cout << "Enter month in format(mm): " << endl;
        cin >> ltm->tm_mon;
        cout << "Enter year in format(yyyy): " << endl;
        cin >> ltm->tm_year;
        cout << "Enter amount of children: " << endl;
        cin >> tChildrenAmount;
        employeesArr[0] = new Employees(tFullName, ltm, tChildrenAmount);
    }
    else {
        for (int i = 0; i < size; ++i) {
            newEmployeesArr[i] = employeesArr[i];
        }

        delete[] employeesArr;

        employeesArr = newEmployeesArr;
        cout << "Enter name : " << endl;
        cin >> tName;
        cout << "Enter surname : " << endl;
        cin >> tSurname;
        tFullName = tName + " " + tSurname;
        cout << "Enter day in format(dd): " << endl;
        cin >> ltm->tm_mday;
        cout << "Enter month in format(mm): " << endl;
        cin >> ltm->tm_mon;
        cout << "Enter year in format(yyyy): " << endl;
        cin >> ltm->tm_year;
        cout << "Enter amount of children: " << endl;
        cin >> tChildrenAmount;
        employeesArr[size] = new Employees(tFullName, ltm, tChildrenAmount);
    }
    size++;
}
void  Staff::findEmpYear(int desiredYear) {
    for (int i = 0; i < size; i++) {
        if (employeesArr[i]->year== desiredYear) {
            employeesArr[i]->printEmployee();
        }
    }
}
int Staff::Interface() {
    int action, index, desiredYear;
    cout << "\n\nChoose your action (from 1 to 5).\n1 is add employee\n2 is print all employees\n3 is delete employee on some index\n4 is delete all employees\n5 is display employees who were born in the specified year (by you) \n0 0 If you want to finish the program: " << endl;
    cin >> action;
    switch (action) {
    case 1:
        add();
        break;
    case 2:
        printAll();
        break;
    case 3:
        cout << "\nInput the index of the employee to be deleted between 0 and "<<size-1<<": "<<endl;
        cin >> index;
        del(index);
        break;
    case 4:
        delAll();
        break;
    case 5:
        cout << "\nEnter the year of the employees you want to display: " << endl;
        cin >> desiredYear;
        findEmpYear( desiredYear);
        break;
    case 0:
        cout << "Thanks for using, bye bye";
        return 0;
        break;
    default:
        cout << "Wrong number!!!";
    }
    return 1;
}
int main()
{
    
    int n, result;

    do {
        cout << "Enter the amount of employees (more than  zero): \n";
        cin >> n;
    } while (!(n > 0));
    Staff* st = new Staff(3);
    /*Employees* emp = new Employees[n];*/
    st->fill();
    st->printAll();
    st->del(1);

    cout << "After del: " << endl;
    st->printAll();
    st->add();
    st->printAll();
    st->add();
    /*st->delAll();
    st->printAll();*/
    st->printAll();
    cout << "\nEmployees with desired year: " << endl;
    st->findEmpYear(1999);
    do {
        result = st->Interface();
    } while (result != 0);
    return 1;
}
/*
3
Ivan
Mihailov
    06
    12
    1999
    5
Danil
Kozlov
    11
    11
    2001
    2
Kostz
Cokolov
    23
    03
    1989
    3
Makcim
Inorov
    18
    08
    1900
    13
Denys
Huydmov
    16
    04
    1999
    1

    */