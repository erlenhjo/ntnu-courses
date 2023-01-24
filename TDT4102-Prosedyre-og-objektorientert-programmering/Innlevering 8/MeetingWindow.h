#pragma once
#include "Meeting.h"
#include "std_lib_facilities.h"
#include "GUI.h"
#include "Car.h"

using namespace Graph_lib;

constexpr int xMax=600;
constexpr int yMax=400;
constexpr int pad=yMax/30;
constexpr int btnW=xMax/8;
constexpr int btnH=yMax/9;
constexpr int fieldW=xMax/2;
constexpr int fieldH=yMax/15;
constexpr int fieldPad=xMax/6;


class MeetingWindow : public Window{
    public:
        MeetingWindow(Point xy, int w, int h, const string& title);
        void addPerson();
        ~MeetingWindow();
        void printPersons();
        void displayPeople();
        void showPersonPage();
        void showMeetingPage();
        void addMeeting();
        void displayMeetings();
        void testSubjects();
    private:
        static void cb_quit(Address,Address);
        static void cb_newPerson(Address,Address);
        static void cb_meetings(Address,Address);
        static void cb_persons(Address,Address);
        static void cb_newMeeting(Address,Address);
        Button quitBtn;
        In_box personName;
        In_box personEmail;
        vector<Person*> people;
        Button personNewBtn;
        In_box personSeats;
        vector<Car*> cars;
        Multiline_out_box personData;
        Menu pageMenu;
        In_box meetingSubject;
        In_box meetingDay;
        In_box meetingStart;
        In_box meetingEnd;
        Button meetingNewBtn;
        Multiline_out_box meetingData;
        vector<Meeting*> meetings;
        Choice meetingLocation;
        Choice meetingLeader;
};