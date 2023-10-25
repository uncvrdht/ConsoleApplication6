#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

enum class Specialization {
    ComputerScience,
    Mathematics,
    Physics,
    Chemistry
};

class Student {
public:
    Student(string name, string lastName) : name(name), lastName(lastName) {}

    string GetName() const {
        return name;
    }

    string GetLastName() const {
        return lastName;
    }

private:
    string name;
    string lastName;
};

class Group {
public:
    static const int MAX_STUDENTS = 100; // Максимальное количество студентов в группе

    Group() : groupName(""), specialization(Specialization::ComputerScience), course(1), studentCount(0) {
        students = new Student * [MAX_STUDENTS];
    }

    Group(const Group& other) : groupName(other.groupName), specialization(other.specialization), course(other.course), studentCount(other.studentCount) {
        students = new Student * [MAX_STUDENTS];
        for (int i = 0; i < studentCount; ++i) {
            students[i] = new Student(*other.students[i]);
        }
    }
    Group(const string& groupName, Specialization specialization, int course)
        : groupName(groupName), specialization(specialization), course(course), studentCount(0) {
        students = new Student * [MAX_STUDENTS];
    }

    ~Group() {
        for (int i = 0; i < studentCount; ++i) {
            delete students[i];
        }
        delete[] students;
    }

    string GetGroupName() const {
        return groupName;
    }

    void SetGroupName(const string& name) {
        groupName = name;
    }

    Specialization GetSpecialization() const {
        return specialization;
    }

    void SetSpecialization(Specialization spec) {
        specialization = spec;
    }

    int GetCourse() const {
        return course;
    }

    void SetCourse(int c) {
        course = c;
    }

    // Метод для добавления студента в группу
    void AddStudent(const Student& student) {
        if (studentCount < MAX_STUDENTS) {
            students[studentCount++] = new Student(student);
        }
        else {
            cerr << "Group is full. Cannot add more students." << endl;
        }
    }

    // Метод для вывода информации о группе и студентах
    void DisplayGroup() const {
        cout << "Group Name: " << groupName << endl;
        cout << "Specialization: " << static_cast<int>(specialization) << endl;
        cout << "Course: " << course << endl;
        cout << "Students:" << endl;
        for (int i = 0; i < studentCount; ++i) {
            cout << students[i]->GetLastName() << ", " << students[i]->GetName() << endl;
        }
    }

    // Метод для слияния двух групп
    void MergeGroups(const Group& other) {
        for (int i = 0; i < other.studentCount; ++i) {
            if (studentCount < MAX_STUDENTS) {
                students[studentCount++] = new Student(*other.students[i]);
            }
            else {
                cerr << "Group is full. Cannot add more students." << endl;
            }
        }
    }

    // Метод для перевода студента из одной группы в другую
    void TransferStudent(Group& other, int studentIndex) {
        if (studentIndex >= 0 && studentIndex < studentCount) {
            if (other.studentCount < other.MAX_STUDENTS) {
                other.students[other.studentCount++] = students[studentIndex];
                for (int i = studentIndex; i < studentCount - 1; ++i) {
                    students[i] = students[i + 1];
                }
                --studentCount;
            }
            else {
                cerr << "Destination group is full. Cannot transfer the student." << endl;
            }
        }
        else {
            cerr << "Invalid student index." << endl;
        }
    }

    // Метод для отчисления всех студентов, не сдавших сессию (есть хоть один не сданный экзамен)
    void ExpelFailedStudents() {
        for (int i = 0; i < studentCount; ++i) {
            // Здесь должна быть проверка на сессию (например, экзамен не сдан)
            // Если студент не сдал, то выполняется отчисление.
            // В данной реализации просто удаляем всех студентов.
            delete students[i];
        }
        studentCount = 0;
    }

    // Метод для отчисления одного студента с худшим средним баллом по ДЗ
    void ExpelStudentWithLowestAverage() {
        if (studentCount > 0) {
            int lowestIndex = 0;
            // Здесь должен быть код для поиска студента с самым низким средним баллом по ДЗ.
            for (int i = 1; i < studentCount; ++i) {
                // Здесь должен быть код сравнения средних баллов.
                // Если текущий студент имеет более низкий балл, обновляем lowestIndex.
            }
            delete students[lowestIndex];
            for (int i = lowestIndex; i < studentCount - 1; ++i) {
                students[i] = students[i + 1];
            }
            --studentCount;
        }
    }

private:
    string groupName;
    Specialization specialization;
    int course;
    Student** students;
    int studentCount;
};

int main() {
    // Создаем и заполняем исходную группу
    Group group1("Group A", Specialization::ComputerScience, 2);

    group1.AddStudent(Student("John", "Doe"));
    group1.AddStudent(Student("Alice", "Smith"));
    group1.AddStudent(Student("Bob", "Johnson"));

    // Создаем копию группы с использованием конструктора копирования
    Group group1Copy = group1;

    // Изменяем оригинальную группу
    group1.AddStudent(Student("Charlie", "Brown"));

    cout << "Original Group:" << endl;
    group1.DisplayGroup();

    cout << "\nCopy of Group:" << endl;
    group1Copy.DisplayGroup();

    return 0;
}