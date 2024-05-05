#include "Student.h"
#include "Group.h"

Student::Student(int id, const std::string &fio): id(id), fio(fio), group(nullptr) {}

void Student::addToGroup(Group *group) {
    if (this->group != nullptr) {
        this->group = nullptr;
        this->group->removeStudent(this);
    }

    this->group = group;
    this->group->addStudent(this);
}

void Student::removeFromGroup() {
    if (this->group == nullptr) {
        return;
    }
    this->group->removeStudent(this);
    this->group = nullptr;
}

void Student::addMark(int mark)  {
    this->marks.push_back(mark);
}

int Student::getAverageMark() const {
    int sum = 0;
    for (int mark : this->marks) {
        sum += mark;
    }
    return sum / this->marks.size();
}

int Student::getId() const {
    return this->id;
}

std::string Student::getFio() const {
    return this->fio;
}

Group* Student::getGroup() const {
    return this->group;
}

const std::vector<int>& Student::getMarks() const {
    return this->marks;
}

std::ostream& operator<< (std::ostream& os, const Student& student) {
    std::string groupTitleStr = (student.getGroup() == nullptr) ? "" : student.getGroup()->getTitle();
    std::string marksStr = (student.getMarks().size() == 0) ? "-" : "";

    for (const auto mark : student.getMarks()) {
        marksStr += std::to_string(mark) + " ";
    }

    return os << student.getId() << " " << student.getFio() << " " << groupTitleStr << " " << marksStr;
}