#include "Deanery.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <ctime>

Deanery::Deanery(const std::string &studentsPathFile, const std::string &groupsPathFile) {
    this->studentsPathFile = studentsPathFile;
    this->groupsPathFile = groupsPathFile;
}

void Deanery::createStudents() {
    std::ifstream file(studentsPathFile);
    if (!file.is_open()) {
        std::cout << "unable to open file \"" << studentsPathFile << "\"" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        //std::cout << line << std::endl;
        std::stringstream strStream(line);
        std::string segment;
        std::string fio;
        Group *group = nullptr;
        int id;
        std::vector<int> marks;
        int step = 0;

        while (std::getline(strStream, segment, ' ')) {
            if (step == 0) {
                id = std::stoi(segment);
            } else if (step == 1) {
                fio = segment;
            } else if (step == 2) {
                fio += " " + segment;
            } else if (step == 3) {
                std::vector<Group*>::iterator it =
                    std::find_if(
                        groups.begin(), groups.end(),
                        [segment] (const Group *g) {
                            return g->getTitle() == segment;
                        }
                    );
                if (it != groups.end()) {
                    group = *it;
                }
            } else {
                int mark = std::stoi(segment);
                marks.push_back(mark);
            }

            step++;
        }

        Student *student = new Student(id, fio);
        for (const auto mark : marks) {
            student->addMark(mark);
        }
        if (group != nullptr) {
            student->addToGroup(group);
        }
        std::cout << "add student: " << *student << std::endl;

        students.push_back(student);
    }
    file.close();
}

void Deanery::createGroups() {
    std::ifstream file(groupsPathFile);
    if (!file.is_open()) {
        std::cout << "unable to open file \"" << groupsPathFile << "\"" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        //std::cout << line << std::endl;
        std::stringstream strStream(line);
        std::string segment;
        std::string title;
        std::string spec;
        int step = 0;

        while (std::getline(strStream, segment, ' ')) {
            if (step == 0) {
                title = segment;
            } else {
                if (step > 1) {
                    spec += " ";
                }
                spec += segment;
            }

            step++;
        }

        Group *group = new Group(title, spec);
        groups.push_back(group);
        std::cout << "add group: " << *group << std::endl;
    }
    file.close();
}

void Deanery::dumpStudents() {
    std::ofstream file(studentsPathFile);
    if (!file.is_open()) {
        std::cout << "unable to open file \"" << studentsPathFile << "\"" << std::endl;
        return;
    }

    for (const auto student : this->students) {
        file << *student << std::endl;
    }
    file.close();
}

void Deanery::dumpGroups() {
    std::ofstream file(groupsPathFile);
    if (!file.is_open()) {
        std::cout << "unable to open file \"" << groupsPathFile << "\"" << std::endl;
        return;
    }

    for (const auto group : this->groups) {
        file << *group << std::endl;
    }
    file.close();
}

void Deanery::printStudents() {
    for (const auto student : this->students) {
        std::cout << *student << std::endl;
    }
}

void Deanery::printGroups() {
    for (const auto group : this->groups) {
        std::cout << *group << std::endl;
    }
}

void Deanery::randomizeMarks() {
    const int minMark = 0;
    const int maxMark = 10;
    const int minNewMarks = 10;
    const int maxNewMarks = 10;

    for (const auto student : this->students) {
        int newMarks = minNewMarks + rand() % maxNewMarks;
        for (int i = 0; i < newMarks; ++i) {
            int mark = minMark + rand() % maxMark;
            student->addMark(mark);
        }
    }
}

void Deanery::printStudentStat() const {
    int averageMark = 0;
    int markNum = 0;
    for (const auto student : this->students) {
        averageMark += student->getAverageMark();
        markNum += student->getMarks().size();
    }
    averageMark /= this->students.size();

    std::cout << "Total number of students: " << this->students.size() << ", average mark: " << averageMark << ", number of marks: " << markNum << std::endl;

    for (const auto student : this->students) {
        std::cout << student->getId() << " " << student->getFio() << ": average mark: " << student->getAverageMark()
            << ", number of marks: " << student->getMarks().size() << std::endl;
    }
}

void Deanery::printGroupStat() const {
    int averageMark = 0;
    for (const auto group : this->groups) {
        averageMark += group->getAverageMark();
    }
    averageMark /= this->groups.size();

    std::cout << "Total number of groups: " << this->groups.size() << ", average mark: " << averageMark << std::endl;
    for (const auto group : this->groups) {
        std::cout << "Group \"" << group->getTitle() << "\": has " << group->getStudents().size() << " students" << std::endl;
    }
}

void Deanery::moveStudent(int studentId, const std::string &toGroupTitle) {
    Student *student = nullptr;
    std::vector<Student*>::iterator it =
        std::find_if(
            this->students.begin(), this->students.end(),
            [studentId] (const Student *s) {
                return s->getId() == studentId;
            }
        );
    if (it == this->students.end()) {
        std::cout << "Student with ID " << studentId << " wasn't found" << std::endl;
        return;
    }
    student = *it;

    Group *toGroup = nullptr;
    std::vector<Group*>::iterator it2 =
        std::find_if(
            this->groups.begin(), this->groups.end(),
            [toGroupTitle] (const Group *g) {
                return g->getTitle().compare(toGroupTitle) == 0;
            }
        );
    if (it2 == this->groups.end()) {
        std::cout << "Group with title \"" << toGroupTitle << "\" wasn't found" << std::endl;
        return;
    }
    toGroup = *it2;

    Group *fromGroup = student->getGroup();
    student->removeFromGroup();
    student->addToGroup(toGroup);
    std::cout << student->getGroup()->getTitle() << std::endl;

    std::cout << "Student with ID " << student->getId() << " was moved from " << fromGroup->getTitle() << " to " << toGroup->getTitle() << std::endl;
}

void Deanery::fireStudents(int averageMark) {
    std::vector<Student*> studentsToFire;

    for (const auto student : this->students) {
        if (student->getAverageMark() < averageMark) {
            studentsToFire.push_back(student);
        }
    }

    for (const auto student : studentsToFire) {
        std::vector<Student*>::iterator it =
            std::find_if(
                this->students.begin(), this->students.end(),
                [student] (const Student *s) {
                    return s->getId() == student->getId();
                }
            );
        this->students.erase(it);
        student->removeFromGroup();
        delete student;
    }
}
