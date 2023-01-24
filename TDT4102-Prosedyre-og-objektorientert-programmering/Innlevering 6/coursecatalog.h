#pragma once
#include "std_lib_facilities.h"

class CourseCatalog{
    private:
        map<string,string> catalog;
    public:
        void addCourse(string code, string name);
        void removeCourse(string code);
        string getCourse(string code);
        friend ostream& operator<<(ostream& os,const CourseCatalog& courseCatalog);
        void writeToFile(string file);
        void readFromFile(string file);
};


void testCourseCatalog();
