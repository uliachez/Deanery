#include "Group.h"
#include <cstddef>
#include <iterator>

Group::Group(const std::string &title, const std::string &spec): title(title), spec(spec), head(nullptr) {}

void Group::addStudent(Student *student) {
    students.push_back(student);
}

void Group::removeStudent(Student *student) {
    std::vector<Student*>::iterator it = std::find(this->students.begin(), this->students.end(), student);
    if (it == this->students.end()) {
        std::cout << "Student with ID " << student->getId() << " wasn't found in group " << this->getTitle() << std::endl; 
        return;
    }

    this->students.erase(it);
}

void Group::selectHead(Student *student) {
    std::vector<Student*>::iterator it = std::find(students.begin(), students.end(), student);
    if (it == this->students.end()) {
        std::cout << "Student with ID " << student->getId() << " wasn't found in group " << this->getTitle() << std::endl;
        return;
    }

    this->head = student;
}

Student* Group::findStudent(const std::string &fio) {
    std::vector<Student*>::iterator it =
        std::find_if(
            students.begin(), students.end(),
            [fio] (const Student *s) {
                return s->getFio().compare(fio) == 0;
            }
        );
    if (it == students.end()) {
        return nullptr;
    }
    return *it;
}



Student* Group::findStudent(int id) {
    std::vector<Student*>::iterator it =
        std::find_if(
            students.begin(), students.end(),
            [id] (const Student *s) {
                return s->getId() == id;
            }
        );
    if (it == students.end()) {
        return nullptr;
    }
    return *it;
}

int Group::getAverageMark() const {
    int sum = 0;
    for (const auto s : this->students) {
        sum += s->getAverageMark();
    }
    return sum / this->students.size();
}

std::string Group::getTitle() const {
    return title;
}

std::string Group::getSpec() const {
    return spec;
}

const std::vector<Student*>& Group::getStudents() const {
    return this->students;
}

std::ostream& operator<< (std::ostream& os, const Group& group) {
    return os << group.getTitle() << " " << group.getSpec();
}