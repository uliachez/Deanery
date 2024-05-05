#pragma once

#include "Student.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>


class Group {
private:
   std::string title;
   std::string spec;
   std::vector <Student*> students;
   Student *head;
public:
   Group(const std::string &title, const std::string &spec);
   void addStudent(Student *student);
   void removeStudent(Student *student);
   Student* findStudent(const std::string &fio);
   Student* findStudent(int id);
   void selectHead(Student *head);
   int getAverageMark() const;
   std::string getTitle() const;
   std::string getSpec() const;
   const std::vector<Student*>& getStudents() const;
   friend std::ostream& operator<< (std::ostream& os, const Group& group);
};