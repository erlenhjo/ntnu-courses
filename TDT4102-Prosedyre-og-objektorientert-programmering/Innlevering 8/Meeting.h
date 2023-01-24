#pragma once
#include "std_lib_facilities.h"
#include "Person.h"

enum class Campus{
    Trondheim,Gjøvik,Ålesund
};
const map<Campus,string> campusMap{
    {Campus::Trondheim,"Trondheim"},
    {Campus::Gjøvik,"Gjoevik"},
    {Campus::Ålesund,"Aalesund"}
};
ostream& operator<<(ostream& os,Campus c);

class Meeting{
    public:
        int get_day() const;
        int get_startTime() const;
        int get_endTime() const;
        Campus get_location() const;
        string get_subject() const;
        const Person* get_leader() const;
        void addParticipant(const Person* p);
        Meeting(int day,int startTime, int endTime,Campus location,string subject,const Person* leader);
        ~Meeting();
        vector<string> getParticipantsList();
        vector<const Person*> findPotentialCoDriving();
    private:
        static inline set<const Meeting*> meetings{};
        int day;
        int startTime;
        int endTime;
        Campus location;
        string subject;
        const Person* leader;
        set<const Person*> participants;
};
ostream& operator<<(ostream& os,Meeting m);