#include "coursecatalog.h"
#include "std_lib_facilities.h"


void CourseCatalog::addCourse(string code, string name){
    catalog[code]=name;
    //catalog.insert(pair<string,string>(code,name));
}   // [] erstatter, insert gjør det ikke.
void CourseCatalog::removeCourse(string code){
    catalog.erase(code);
}
string CourseCatalog::getCourse(string code){
    return catalog.at(code);
}
ostream& operator<<(ostream& os,const CourseCatalog& courseCatalog){
    for(auto const& course: courseCatalog.catalog){
        os<<course.first<<": "<<course.second<<"\n";
    }
    return os;
}
void testCourseCatalog(){
    CourseCatalog ntnuCourses;
    ntnuCourses.readFromFile("3ein.txt");
    cout<<ntnuCourses;
    cout<<"\n";
    ntnuCourses.addCourse("TDT4110", "Informasjonsteknologi grunnkurs");
    ntnuCourses.addCourse("TDT4102","Prosedyre- og objektorientert programmering");
    ntnuCourses.addCourse("TMA4100","Matematikk 1");
    ntnuCourses.addCourse("TDT4102","C++");
    cout<<ntnuCourses;
    ntnuCourses.writeToFile("3e.txt");
}
void CourseCatalog::writeToFile(string file){
    ofstream ost{file};
    bool firstLine=true;
    for(auto const& course: catalog){
        if(firstLine){
            firstLine=false;
        }else{
            ost<<"\n";    
        }
        ost<<course.first<<": "<<course.second;
    }
}
void CourseCatalog::readFromFile(string file){
    ifstream ist{file};
    for(string course; getline(ist,course);){
        string code;
        string name;
        code=course.substr(0,course.find(": "));
        course.erase(0,course.find(": ")+2);
        name=course;
        addCourse(code,name);
    }
}