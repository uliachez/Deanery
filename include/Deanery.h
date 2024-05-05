#pragma once

#include "Student.h"
#include "Group.h"

#include <vector>
#include <string>

class Deanery {
private:
   std::vector <Student*> students;
   std::vector <Group*> groups;
   std::string studentsPathFile;
   std::string groupsPathFile;

public:
   Deanery(const std::string &studentsPathFile, const std::string &groupsPathFile);
   void createStudents();
   void createGroups();
   void dumpStudents();
   void dumpGroups();
   void printStudents();
   void printGroups();
   void randomizeMarks();
   void printStudentStat() const;
   void printGroupStat() const;
   void moveStudent(int studentId, const std::string &toGroupTitle);
   void fireStudents(int averageMark);
};