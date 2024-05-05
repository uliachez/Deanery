#include "Student.h"
#include "Group.h"
#include "Deanery.h"

#include <iostream>
#include <string>
#include <ctime>

const std::string studentsPathFile = "../bd/students.txt";
const std::string groupsPathFile = "../bd/groups.txt";

int main() {
    srand(time(0));

    Deanery deanery(studentsPathFile, groupsPathFile);

    deanery.createGroups();
    deanery.createStudents();

    deanery.moveStudent(2, "23КНТ6");

    //deanery.randomizeMarks();
    deanery.printStudentStat();
    deanery.printGroupStat();

    deanery.printGroups();
    deanery.printStudents();

    deanery.fireStudents(5); // измени среднюю оценку, по которой будут удаляться студенты 

    deanery.dumpGroups();
    deanery.dumpStudents();
}