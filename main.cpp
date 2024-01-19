#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

class Student {
public:
    Student(std::string name) : name(name) {}

    const std::string& getName() const {
        return name;
    }

    void addMark(int mark) {
        marks.push_back(mark);
    }

    bool isExcellentStudent() const {
        return calculateAverageMark() >= 4.5;
    }

private:
    double calculateAverageMark() const {
        if (marks.empty()) {
            return 0.0;
        }

        double sum = 0.0;
        for (int mark : marks) {
            sum += mark;
        }

        return sum / marks.size();
    }

private:
    std::string name;
    std::vector<int> marks;
};

class SchoolSystem {
public:
    void addStudent(Student& student) {
        students.push_back(&student);
    }

    void addMark(Student& student, int mark) {
        student.addMark(mark);
        std::cout << "Преподаватель добавил оценку " << mark << " студенту " << student.getName() << std::endl;
    }

    void determineExcellentStudents() const {
        std::cout << "Отличники: ";
        for (const Student* student : students) {
            if (student->isExcellentStudent()) {
                std::cout << student->getName() << " ";
            }
        }
        std::cout << std::endl;
    }

private:
    std::vector<Student*> students;
};

int main() {
    std::srand(std::time(0));
    setlocale(LC_ALL, "Russian");

    SchoolSystem schoolSystem;

    Student student1("Иванов");
    Student student2("Петров");

    schoolSystem.addStudent(student1);
    schoolSystem.addStudent(student2);

    schoolSystem.addMark(student1, 5);
    schoolSystem.addMark(student2, 4);

    schoolSystem.determineExcellentStudents();

    return 0;
}
