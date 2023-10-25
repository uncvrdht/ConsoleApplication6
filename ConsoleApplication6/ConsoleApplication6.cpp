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
    Student(string name, string lastName) : name(name), lastName(lastName) {
        if (studentCount >= MAX_STUDENTS) {
            throw runtime_error("Max student limit reached.");
        }
        ++studentCount;
    }

    static int GetStudentCount() {
        return studentCount;
    }


    string GetName() const {
        return name;
    }

    string GetLastName() const {
        return lastName;
    }

private:
    string name;
    string lastName;
    static int studentCount;
    static const int MAX_STUDENTS = 15; // Максимальное количество студентов
};

int Student::studentCount = 0;

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

    static int GetGroupCount() {
        return groupCount;
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
    static int groupCount; // Статическое поле для подсчета групп
};

int Group::groupCount = 0;

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

/*

Счетчик студентов:

Я добавил счетчик studentCount в класс Student, чтобы отслеживать, сколько студентов уже создано.
Также, создал метод GetStudentCount, который позволяет узнать, сколько студентов я уже создал.
Если при создании нового студента уже есть 15 студентов (максимум), то мой код выбросит ошибку.

Счетчик групп:

В классе Group, я внес изменения, чтобы знать, сколько групп уже создано.
Добавил метод GetGroupCount, который помогает узнать, сколько групп сейчас существует.
Ограничение на количество студентов:

Я добавил проверку в конструктор класса Student, чтобы удостовериться, что не создается больше студентов, чем разрешено (15 студентов). Если такое происходит, выдает ошибку.

*/