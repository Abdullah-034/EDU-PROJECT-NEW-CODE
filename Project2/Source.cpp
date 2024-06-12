#include <iostream>
#include <string>
#include <fstream>
#include <vector>


using namespace std;

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define RESET "\033[0m"
#define MAGENTA "\033[35m"
#define BLUE "\033[34m"

struct Person
{
    string name;
    string cnic;
    string contact_number;
    int age;

    Person() : name(""), cnic(""), contact_number(""), age(0) {}

    void inputPersonDetails()
    {
        cout << CYAN"\t\t\t\t\tEnter name: ";
        getline(cin, name);
        cout << CYAN"\t\t\t\t\tEnter CNIC: ";
        getline(cin, cnic);
        cout << CYAN"\t\t\t\t\tEnter contact number: ";
        getline(cin, contact_number);
        cout << CYAN"\t\t\t\t\tEnter age: ";
        while (!(cin >> age) || age <= 0)
        {
            cout << RED "\t\t\t\t\tInvalid input! Try again: " RESET;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cin.ignore(10000, '\n');
    }

    void displayPersonDetails() const
    {
        cout << GREEN "\t\t\t\t\tName: " RESET << name << endl;
        cout << GREEN "\t\t\t\t\tCNIC: " RESET << cnic << endl;
        cout << GREEN "\t\t\t\t\tContact number: " RESET << contact_number << endl;
        cout << GREEN "\t\t\t\t\tAge: " RESET << age << endl;
    }

    void savePersonDetails(ofstream& file) const
    {
        file << name << endl << cnic << endl << contact_number << endl << age << endl;
    }

    void loadPersonDetails(ifstream& file)
    {
        getline(file, name);
        getline(file, cnic);
        getline(file, contact_number);
        file >> age;
        file.ignore();
    }
};

struct Teacher
{
    Person person;
    string course;
    int employee_id;
    double salary;

    Teacher() : course(""), employee_id(0), salary(0.0) {}

    void inputTeacherDetails()
    {
        person.inputPersonDetails();
        cout << CYAN "\t\t\t\t\tEnter course: ";
        getline(cin, course);
        cout << CYAN "\t\t\t\t\tEnter employee ID: ";
        while (!(cin >> employee_id) || employee_id <= 0)
        {
            cout << RED "\t\t\t\t\tInvalid input! Try again: " RESET;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cout << "\t\t\t\t\tEnter salary: ";
        while (!(cin >> salary) || salary < 0)
        {
            cout << RED "\t\t\t\t\tInvalid input! Try again: " RESET;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cin.ignore(10000, '\n');
    }

    void displayTeacherDetails() const
    {
        person.displayPersonDetails();
        cout << GREEN "\t\t\t\t\tCourse: " RESET << course << endl;
        cout << GREEN "\t\t\t\t\tEmployee ID: " RESET << employee_id << endl;
        cout << GREEN "\t\t\t\t\tSalary: " RESET << salary << endl;
    }

    void saveTeacherDetails(ofstream& file) const
    {
        person.savePersonDetails(file);
        file << course << endl << employee_id << endl << salary << endl;
    }

    void loadTeacherDetails(ifstream& file)
    {
        person.loadPersonDetails(file);
        getline(file, course);
        file >> employee_id;
        file >> salary;
        file.ignore();
    }
};

struct Student
{
    Person person;
    double cgpa;
    string degree;

    Student() : cgpa(0.0), degree("") {}

    void inputStudentDetails()
    {
        person.inputPersonDetails();
        cout << "\t\t\t\t\tEnter CGPA: ";
        while (!(cin >> cgpa) || cgpa < 0 || cgpa > 4)
        {
            cout << RED "\t\t\t\t\tInvalid input! Try again: " RESET;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cin.ignore(10000, '\n');
        cout << "\t\t\t\t\tEnter degree: ";
        getline(cin, degree);
    }

    void displayStudentDetails() const
    {
        person.displayPersonDetails();
        cout << GREEN "\t\t\t\t\tDegree: " RESET << degree << endl;
        cout << GREEN "\t\t\t\t\tCGPA: " RESET << cgpa << endl;
    }

    void saveStudentDetails(ofstream& file) const
    {
        person.savePersonDetails(file);
        file << cgpa << endl << degree << endl;
    }

    void loadStudentDetails(ifstream& file)
    {
        person.loadPersonDetails(file);
        file >> cgpa;
        file.ignore();
        getline(file, degree);
    }
};

struct Login
{
    string id;
    string password;
};

struct Admin
{
    Login login;
    vector<Teacher> teachers;
    vector<Student> students;

    Admin(const string& id, const string& password)
    {
        login.id = id;
        login.password = password;
    }

    string getId() const
    {
        return login.id;
    }

    string getPassword() const
    {
        return login.password;
    }

    void createTeacher()
    {
        Teacher t;
        t.inputTeacherDetails();
        teachers.push_back(t);
    }

    void createStudent()
    {
        Student s;
        s.inputStudentDetails();
        students.push_back(s);
    }

    void modifyTeacherDetails(Teacher& teacher)
    {
        int choice;
        cout << YELLOW "\t\t\t\t\t1. Modify Name" RESET << endl;
        cout << YELLOW"\t\t\t\t\t2. Modify CNIC" << endl;
        cout << YELLOW"\t\t\t\t\t3. Modify Contact Number" << endl;
        cout << YELLOW"\t\t\t\t\t4. Modify Age" << endl;
        cout << YELLOW"\t\t\t\t\t5. Modify Salary" << endl;
        cout << YELLOW"\t\t\t\t\t6. Modify Course" << endl;
        cout << YELLOW"\t\t\t\t\t7. Modify Employee ID" << endl;
        cout << YELLOW"\t\t\t\t\t8. Exit" << endl;
        cout << CYAN "\t\t\t\t\tChoice: " RESET;
        while (!(cin >> choice) || choice < 1 || choice > 8)
        {
            cout << RED "\t\t\t\t\tInvalid input! Try again: " RESET;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cin.ignore(10000, '\n');

        switch (choice)
        {
        case 1:
            cout << CYAN "\t\t\t\t\tEnter new name: " RESET;
            getline(cin, teacher.person.name);
            break;
        case 2:
            cout << CYAN "\t\t\t\t\tEnter new CNIC: " RESET;
            getline(cin, teacher.person.cnic);
            break;
        case 3:
            cout << CYAN "\t\t\t\t\tEnter new contact number: " RESET;
            getline(cin, teacher.person.contact_number);
            break;
        case 4:
            cout << CYAN "\t\t\t\t\tEnter new age: " RESET;
            while (!(cin >> teacher.person.age) || teacher.person.age <= 0)
            {
                cout << RED "\t\t\t\t\tInvalid input! Try again: " RESET;
                cin.clear();
                cin.ignore(10000, '\n');
            }
            cin.ignore(10000, '\n');
            break;
        case 5:
            cout << CYAN "\t\t\t\t\tEnter new salary: " RESET;
            while (!(cin >> teacher.salary) || teacher.salary < 0)
            {
                cout << RED "\t\t\t\t\tInvalid input! Try again: " RESET;
                cin.clear();
                cin.ignore(10000, '\n');
            }
            cin.ignore(10000, '\n');
            break;
        case 6:
            cout << CYAN "\t\t\t\t\tEnter new course: " RESET;
            getline(cin, teacher.course);
            break;
        case 7:
            cout << CYAN "\t\t\t\t\tEnter new employee ID: " RESET;
            while (!(cin >> teacher.employee_id) || teacher.employee_id <= 0)
            {
                cout << RED "\t\t\t\t\tInvalid input! Try again: " RESET;
                cin.clear();
                cin.ignore(10000, '\n');
            }
            cin.ignore(10000, '\n');
            break;
        case 8:
            return;
        }
    }

    void modifyStudentDetails(Student& student)
    {
        int choice;
        cout << YELLOW "\t\t\t\t\t1. Modify Name" RESET << endl;
        cout << YELLOW"\t\t\t\t\t2. Modify CNIC" << endl;
        cout << YELLOW"\t\t\t\t\t3. Modify Contact Number" << endl;
        cout << YELLOW"\t\t\t\t\t4. Modify Age" << endl;
        cout << YELLOW"\t\t\t\t\t5. Modify CGPA" << endl;
        cout << YELLOW"\t\t\t\t\t6. Modify Degree" << endl;
        cout << YELLOW"\t\t\t\t\t7. Exit" << endl;
        cout << CYAN "\t\t\t\t\tChoice: " RESET;
        while (!(cin >> choice) || choice < 1 || choice > 7)
        {
            cout << RED "\t\t\t\t\tInvalid input! Try again: " RESET;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cin.ignore(10000, '\n');

        switch (choice)
        {
        case 1:
            cout << CYAN "\t\t\t\t\tEnter new name: " RESET;
            getline(cin, student.person.name);
            break;
        case 2:
            cout << CYAN "\t\t\t\t\tEnter new CNIC: " RESET;
            getline(cin, student.person.cnic);
            break;
        case 3:
            cout << CYAN "\t\t\t\t\tEnter new contact number: " RESET;
            getline(cin, student.person.contact_number);
            break;
        case 4:
            cout << CYAN "\t\t\t\t\tEnter new age: " RESET;
            while (!(cin >> student.person.age) || student.person.age <= 0)
            {
                cout << RED "\t\t\t\t\tInvalid input! Try again: " RESET;
                cin.clear();
                cin.ignore(10000, '\n');
            }
            cin.ignore(10000, '\n');
            break;
        case 5:
            cout << CYAN "\t\t\t\t\tEnter new CGPA: " RESET;
            while (!(cin >> student.cgpa) || student.cgpa < 0 || student.cgpa > 4)
            {
                cout << RED "\t\t\t\t\tInvalid input! Try again: " RESET;
                cin.clear();
                cin.ignore(10000, '\n');
            }
            cin.ignore(10000, '\n');
            break;
        case 6:
            cout << CYAN "\t\t\t\t\tEnter new degree: " RESET;
            getline(cin, student.degree);
            break;
        case 7:
            return;
        }
    }

    void modify()
    {
        int choice, index;
        do
        {
            cout << MAGENTA "\t\t\t\t\t1. Modify Teacher" RESET << endl;
            cout << MAGENTA"\t\t\t\t\t2. Modify Student" << endl;
            cout << MAGENTA"\t\t\t\t\t3. Exit" << endl;
            cout << CYAN "\t\t\t\t\tChoice: " RESET;
            while (!(cin >> choice) || choice < 1 || choice > 3)
            {
                cout << RED "\t\t\t\t\tInvalid input! Try again: " RESET;
                cin.clear();
                cin.ignore(10000, '\n');
            }
            cin.ignore(10000, '\n');

            if (choice == 1 && !teachers.empty())
            {
                cout << CYAN "\t\t\t\t\tEnter teacher number: " RESET;
                while (!(cin >> index) || index < 1 || index > teachers.size())
                {
                    cout << RED "\t\t\t\t\tInvalid input! Try again: " RESET;
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                cin.ignore(10000, '\n');
                modifyTeacherDetails(teachers[index - 1]);
            }
            else if (choice == 2 && !students.empty())
            {
                cout << CYAN "\t\t\t\t\tEnter student number: " RESET;
                while (!(cin >> index) || index < 1 || index > students.size())
                {
                    cout << RED "\t\t\t\t\tInvalid input! Try again: " RESET;
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                cin.ignore(10000, '\n');
                modifyStudentDetails(students[index - 1]);
            }
            else if (choice == 1 || choice == 2)
            {
                cout << RED "\t\t\t\t\tNo records found!" RESET << endl;
            }
        } while (choice != 3);
    }

    void displayAllTeachers() const
    {
        if (teachers.empty())
        {
            cout << RED "\t\t\t\t\tNo teachers found!" RESET << endl;
            return;
        }
        for (const auto& teacher : teachers)
        {
            teacher.displayTeacherDetails();
            cout << string(80, '-') << endl;
        }
    }

    void displayAllStudents() const
    {
        if (students.empty())
        {
            cout << RED "\t\t\t\t\tNo students found!" RESET << endl;
            return;
        }
        for (const auto& student : students)
        {
            student.displayStudentDetails();
            cout << string(80, '-') << endl;

        }
    }

    void deleteTeacher()
    {
        int index;
        if (teachers.empty())
        {
            cout << RED "\t\t\t\t\tNo teachers to delete!" RESET << endl;
            return;
        }
        cout << CYAN "\t\t\t\t\tEnter teacher number to delete: " RESET;
        while (!(cin >> index) || index < 1 || index > teachers.size())
        {
            cout << RED "\t\t\t\t\tInvalid input! Try again: " RESET;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cin.ignore(10000, '\n');
        teachers.erase(teachers.begin() + index - 1);
        cout << GREEN "\t\t\t\t\tTeacher deleted successfully!" RESET << endl;
    }

    void deleteStudent()
    {
        int index;
        if (students.empty())
        {
            cout << RED "\t\t\t\t\tNo students to delete!" RESET << endl;
            return;
        }
        cout << CYAN "\t\t\t\t\tEnter student number to delete: " RESET;
        while (!(cin >> index) || index < 1 || index > students.size())
        {
            cout << RED "\t\t\t\t\tInvalid input! Try again: " RESET;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cin.ignore(10000, '\n');
        students.erase(students.begin() + index - 1);
        cout << GREEN "\t\t\t\t\tStudent deleted successfully!" RESET << endl;
    }

    void saveRecords() const
    {
        ofstream tFile("teachers.txt");
        ofstream sFile("students.txt");
        for (const auto& teacher : teachers)
        {
            teacher.saveTeacherDetails(tFile);
        }
        for (const auto& student : students)
        {
            student.saveStudentDetails(sFile);
        }
        tFile.close();
        sFile.close();
    }

    void loadRecords()
    {
        ifstream tFile("teachers.txt");
        ifstream sFile("students.txt");
        while (tFile)
        {
            Teacher t;
            t.loadTeacherDetails(tFile);
            if (tFile) teachers.push_back(t);
        }
        while (sFile)
        {
            Student s;
            s.loadStudentDetails(sFile);
            if (sFile) students.push_back(s);
        }
        tFile.close();
        sFile.close();
    }
};

int main()
{
    Admin admin("admin", "password");
    admin.loadRecords();
    string id, password;
    cout << BLUE"\t\t\t\t\tEnter ID: ";
    getline(cin, id);
    cout << BLUE"\t\t\t\t\tEnter Password: ";
    getline(cin, password);
    cout << endl;


    cout << YELLOW "\t\t\t*****************************************************************\n";
    cout << YELLOW "\t\t\t*\tW   W  EEEEE  L      CCCCC  OOOOO  M     M  EEEEE\t*\n";
    cout << YELLOW "\t\t\t*\tW   W  E      L     C       O   O  MM   MM  E    \t*\n";
    cout << YELLOW "\t\t\t*\tW W W  EEEE   L     C       O   O  M M M M  EEEE \t*\n";
    cout << YELLOW "\t\t\t*\tWW WW  E      L     C       O   O  M  M  M  E    \t*\n";
    cout << YELLOW "\t\t\t*\tW   W  EEEEE  LLLLL  CCCCC  OOOOO  M     M  EEEEE\t*\n";
    cout << YELLOW "\t\t\t*\t\t\t\t" << BLUE"To admin portal" << YELLOW"\t\t\t* \n";
    cout << YELLOW "\t\t\t*****************************************************************\n";
    cout << RESET;
    cout << endl;

    int choice;
    do
    {
        cout << endl;
        cout << MAGENTA "\t\t\t\t\t1. Create Teacher" RESET << endl;
        cout << MAGENTA"\t\t\t\t\t2. Create Student" << endl;
        cout << MAGENTA"\t\t\t\t\t3. Modify Records" << endl;
        cout << MAGENTA"\t\t\t\t\t4. Display All Teachers" << endl;
        cout << MAGENTA"\t\t\t\t\t5. Display All Students" << endl;
        cout << MAGENTA"\t\t\t\t\t6. Delete Teacher" << endl;
        cout << MAGENTA"\t\t\t\t\t7. Delete Student" << endl;
        cout << MAGENTA"\t\t\t\t\t8. Save Records" << endl;
        cout << MAGENTA"\t\t\t\t\t9. Exit" << endl;
        cout << CYAN "\t\t\t\t\tChoice: " RESET;
        while (!(cin >> choice) || choice < 1 || choice > 9)
        {
            cout << RED "\t\t\t\t\tInvalid input! Try again: " RESET;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cin.ignore(10000, '\n');

        switch (choice)
        {
        case 1:
            admin.createTeacher();
            break;
        case 2:
            admin.createStudent();
            break;
        case 3:
            admin.modify();
            break;
        case 4:
            admin.displayAllTeachers();
            break;
        case 5:
            admin.displayAllStudents();
            break;
        case 6:
            admin.deleteTeacher();
            break;
        case 7:
            admin.deleteStudent();
            break;
        case 8:
            admin.saveRecords();
            break;
        case 9:
            break;
        }
    } while (choice != 9);

    return 0;
}
