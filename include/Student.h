#pragma once

#include <string>
#include <vector>

class Group;

class Student {
private:
   int id;
   std::string fio;
   Group *group;
   std::vector<int> marks;
public:
   Student(int id, const std::string &fio);
   void addToGroup(Group *group);
   void removeFromGroup();
   void addMark(int mark);
   int getAverageMark() const;
   int getId() const;
   std::string getFio() const;
   Group *getGroup() const;
   const std::vector<int>& getMarks() const;
   friend std::ostream& operator<< (std::ostream& stream, const Student& student);
};