#include "Meeting.h"


int Meeting::get_day() const{
    return day;
}
int Meeting::get_startTime() const{
    return startTime;
}
int Meeting::get_endTime() const{
    return endTime;
}
Campus Meeting::get_location() const{
    return location;
}
string Meeting::get_subject() const{
    return subject;
}
const Person* Meeting::get_leader() const{
    return leader;
}
void Meeting::addParticipant(const Person* p){
    participants.insert(p);
}
Meeting::Meeting(int day,int startTime, int endTime,Campus location,string subject,const Person* leader)
    :
    day{day},startTime{startTime},endTime{endTime},
    location{location},subject{subject},leader{leader}
    {   
        meetings.insert(this);
        participants.insert(leader);
    }
Meeting::~Meeting(){
    meetings.erase(this);
}
vector<string> Meeting::getParticipantsList(){
    vector<string> participantList;
    for(auto participant:participants){
        participantList.push_back(participant->get_name());
    }
    return participantList;
}

ostream& operator<<(ostream& os,Campus c){
    os<<campusMap.at(c);
    return os;
}
ostream& operator<<(ostream& os,Meeting m){
    os<<"Meeting\n-----------------------\n";
    os<<"Subject: "<<m.get_subject()<<"\n";
    os<<"Location: "<<m.get_location()<<"\n";
    os<<"From: "<<m.get_startTime()<<"\n";
    os<<"To: "<<m.get_endTime()<<"\n";
    os<<"Leader: "<<m.get_leader()->get_name()<<"\n";
    os<<"Participants:\n";
    for(auto p:m.getParticipantsList()){
        os<<"\t"<<p<<"\n";
    }
    return os;
}

vector<const Person*> Meeting::findPotentialCoDriving(){
    vector<const Person*> potentials;
    for(const Meeting* m:meetings){
        if( m->get_location()==location 
            && m->get_day()==day 
            &&(m->get_startTime()>=startTime-1 || m->get_startTime()<=startTime+1) 
            &&(m->get_endTime()>=endTime-1||m->get_endTime()<=endTime+1))
            {
            for(const Person*p:m->participants){
                if(p->hasAvailableSeats()){
                    potentials.push_back(p);
                }
            }
        }
    }
    return potentials;
}