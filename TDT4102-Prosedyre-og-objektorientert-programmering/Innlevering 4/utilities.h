#include "std_lib_facilities.h"

int incrementByValueNumTimes(int startValue, int increment, int numTimes);
int incrementByValueNumTimesRef(int& startValue, int increment, int numTimes);
void swapNumbers(int& x, int& y);
struct Student{ 
    string name;
    string studyProgram;
    int age;
};
void printStudent(Student subject);
bool isInProgram(Student subject, string program);
string randomizeString(int length, char lower, char upper);
string readInputToString(int n, char lower, char upper);
int countChar(string theString, char character);