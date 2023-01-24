#include "MeetingWindow.h"
#include "Meeting.h"
#include "std_lib_facilities.h"
#include "GUI.h"
#include "Car.h"



MeetingWindow::MeetingWindow(Point xy, int w, int h, const string& title)
    : Window{xy,w,h,title}, 
    quitBtn{Point{w-btnW-pad,pad},btnW,btnH,"Quit",cb_quit},
    personName{Point{fieldPad,pad},fieldW,fieldH,"Name"},
    personEmail{Point{fieldPad,2*pad+fieldH},fieldW,fieldH,"Email"},
    personNewBtn{Point{fieldPad,4*pad+3*fieldH},btnW,btnH,"Add person",cb_newPerson},
    personSeats{Point{fieldPad,3*pad+2*fieldH},fieldW,fieldH,"Seats"},
    personData{Point{fieldPad,5*pad+3*fieldH+btnH},fieldW,fieldH*7,"Persons"},
    pageMenu{Point{w-btnW-pad,2*pad+btnH},btnW,btnH,Menu::vertical,"Menu"},
    meetingSubject{Point{fieldPad,pad},fieldW,fieldH,"Subject"},
    meetingDay{Point{fieldPad,2*pad+fieldH},fieldW,fieldH,"Day"},
    meetingStart{Point{fieldPad,3*pad+2*fieldH},fieldW,fieldH,"Start"},
    meetingEnd{Point{fieldPad,4*pad+3*fieldH},fieldW,fieldH,"End"},
    meetingNewBtn{Point{fieldPad,6*pad+5*fieldH},btnW,btnH,"Add meeting",cb_newMeeting},
    meetingData{Point{fieldPad,7*pad+5*fieldH+btnH},fieldW,fieldH*4,"Meetings"},
    meetingLocation{Point{fieldPad,5*pad+4*fieldH},fieldW/3,fieldH,"Location"},
    meetingLeader{Point{fieldPad+fieldW*2/3,5*pad+4*fieldH},fieldW/3,fieldH,"Leader"}
    {
        pageMenu.attach(new Button{Point{0,0},0,0,"Persons",cb_persons});
        pageMenu.attach(new Button{Point{0,0},0,0,"Meetings",cb_meetings});
        attach(quitBtn);
        attach(personName);
        attach(personEmail);
        attach(personNewBtn);
        attach(personSeats);
        attach(personData);
        attach(pageMenu);
        attach(meetingSubject);
        attach(meetingDay);
        attach(meetingStart);
        attach(meetingEnd);
        attach(meetingNewBtn);
        attach(meetingData);
        attach(meetingLocation);
        meetingLocation.add("Trondheim");
        meetingLocation.add("Gjoevik");
        meetingLocation.add("Aalesund");
        attach(meetingLeader);
        testSubjects();
        showPersonPage();
    }
void MeetingWindow::cb_quit(Address,Address pw){
    reference_to<MeetingWindow>(pw).hide();
}
void MeetingWindow::addPerson(){
    string n{personName.get_string()};
    string e{personEmail.get_string()};
    int s{personSeats.get_int()};
    Person* p{nullptr};
    if(n!=""&&e!=""){
        if(s>0){
            Car* c{new Car{s}};
            cars.push_back(c);
            p=new Person{n,e,c};
            people.push_back(p);
            c->reserveFreeSeat();
        }else{
            p=new Person{n,e};
            people.push_back(p);
        }
    }
    personName.clear_value();
    personEmail.clear_value();
    personSeats.clear_value();
    meetingLeader.add(p->get_name());
    displayPeople();
}
MeetingWindow::~MeetingWindow(){
    for(Person* p:people){
        delete p;
    }
    for(Car* c:cars){
        delete c;
    }
    for(Meeting* m:meetings){
        delete m;
    }
}
void MeetingWindow::cb_newPerson(Address,Address pw){
    reference_to<MeetingWindow>(pw).addPerson();
}
void MeetingWindow::printPersons(){
    for(Person* p:people){
        cout<<*p<<"\n";
    }
}
void MeetingWindow::displayPeople(){
    stringstream ss;
    for(Person* p:people){
        ss<<*p<<"\n";
    }
    personData.put(ss.str());
}
void MeetingWindow::showPersonPage(){
    personName.show();
    personEmail.show();
    personNewBtn.show();
    personSeats.show();
    personData.show();
    meetingSubject.hide();
    meetingDay.hide();
    meetingStart.hide();
    meetingEnd.hide();
    meetingNewBtn.hide();
    meetingData.hide();
    meetingLocation.hide();
    meetingLeader.hide();
    displayPeople();
}
void MeetingWindow::showMeetingPage(){
    personName.hide();
    personEmail.hide();
    personNewBtn.hide();
    personSeats.hide();
    personData.hide();
    meetingSubject.show();
    meetingDay.show();
    meetingStart.show();
    meetingEnd.show();
    meetingNewBtn.show();
    meetingData.show();
    meetingLocation.show();
    meetingLeader.show();
    displayMeetings();
}
void MeetingWindow::cb_persons(Address,Address pw){
    reference_to<MeetingWindow>(pw).showPersonPage();
}
void MeetingWindow::cb_meetings(Address,Address pw){
    reference_to<MeetingWindow>(pw).showMeetingPage();
}
void MeetingWindow::displayMeetings(){
    stringstream ss;
    for(Meeting* m:meetings){
        ss<<m->get_subject()<<"; ";
        ss<<m->get_day()<<"; ";
        ss<<m->get_startTime()<<"-";
        ss<<m->get_endTime()<<"; ";
        ss<<m->get_location()<<"; ";
        ss<<m->get_leader()->get_name()<<"\n";
    }
    meetingData.put(ss.str());
}
void MeetingWindow::cb_newMeeting(Address,Address pw){
    reference_to<MeetingWindow>(pw).addMeeting();
}
void MeetingWindow::addMeeting(){
    string sub{meetingSubject.get_string()};
    int day{meetingDay.get_int()};
    int s{meetingStart.get_int()};
    int e{meetingEnd.get_int()};
    Campus loc{Campus(meetingLocation.value())};
    Person* lead{people[meetingLeader.value()]};
    if(sub!=""){
        meetings.push_back(new Meeting{day,s,e,loc,sub,lead});
    }
    meetingSubject.clear_value();
    meetingDay.clear_value();
    meetingStart.clear_value();
    meetingEnd.clear_value();
    displayMeetings();
}

void MeetingWindow::testSubjects(){
    Car* c{new Car{2}};
    cars.push_back(c);
    Person* p=new Person{"Abe","abe@mail.com",c};
    people.push_back(p);
    c->reserveFreeSeat();
    meetingLeader.add(p->get_name());

    p=new Person{"Bob","bob@mail.com"};
    people.push_back(p);
    meetingLeader.add(p->get_name());

    c=new Car{3};
    cars.push_back(c);
    p=new Person{"Cal","cal@mail.com",c};
    people.push_back(p);
    c->reserveFreeSeat();
    meetingLeader.add(p->get_name());
    
    c=new Car{1};
    cars.push_back(c);
    p=new Person{"Dan","dan@mail.com",c};
    people.push_back(p);
    c->reserveFreeSeat();
    meetingLeader.add(p->get_name());

    p=new Person{"Eli","eli@mail.com"};
    people.push_back(p);
    meetingLeader.add(p->get_name());
}