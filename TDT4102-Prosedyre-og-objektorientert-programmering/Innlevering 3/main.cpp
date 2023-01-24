//
// This is example code from Chapter 2.2 "The classic first program" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
// 
// keep_window_open() added for TDT4102, excercise 0

// This program outputs the message "Hello, World!" to the monitor

#include "std_lib_facilities.h"
#include "cannonball.h"
#include "utilities.h"
#include "cstdlib"
#include "ctime"
#include "cannonball_viz.h"

//------------------------------------------------------------------------------'
void testDeviation(double compareOperand, double toOperand, double maxError, string name);
void playTargetPractice();
// C++ programs start by executing the function main
int main()
{	
	srand(static_cast<unsigned int>(time(nullptr)));

	int caseNum;
	bool quit =false;
	while(!quit){
		cout<<"0)Avslutt  1)Cannonball  2)Rand  3)Target practice\n";
		cin>>caseNum;

		switch(caseNum){
			case 0:{
				quit=true;
				break;
			}
			case 1:{
				cout<<setw(7)<<""<<setw(7)<<"T = 0"<<setw(7)<<"T=2.5"<<setw(7)<<"T=5.0"<<"\n";
				cout<<setw(7)<<"acclX"<<setw(7)<<acclX()<<setw(7)<<acclX()<<setw(7)<<acclX()<<"\n";
				cout<<setw(7)<<"acclY"<<setw(7)<<acclY()<<setw(7)<<acclY()<<setw(7)<<acclY()<<"\n";
				cout<<setw(7)<<"velX"<<setw(7)<<velX(50,0)<<setw(7)<<velX(50,2.5)<<setw(7)<<velX(50,5)<<"\n";
				cout<<setw(7)<<"velY"<<setw(7)<<velY(25,0)<<setw(7)<<velY(25,2.5)<<setw(7)<<velY(25,5)<<"\n";
				cout<<setw(7)<<"posX"<<setw(7)<<posX(0,50,0)<<setw(7)<<posX(0,50,2.5)<<setw(7)<<posX(0,50,5)<<"\n";
				cout<<setw(7)<<"posY"<<setw(7)<<posY(0,25,0)<<setw(7)<<posY(0,25,2.5)<<setw(7)<<posY(0,25,5)<<"\n";

				printTime(3661);

				testDeviation(velY(25,5),-24.05, 0.0001,"velY(25,5)");
				testDeviation(posX(0,50,5),250,0.0001,"posX(0,50,5)");
				testDeviation(posY(0,25,5),2.375,0.0001,"posY(0,25,5)");

				double absVelocity=getUserInputAbsVelocity();
				double theta=getUserInputTheta();
				vector<double> velocity(2);
				velocity=getVelocityVector(theta,absVelocity);
				double distanceToTarget;
				cout<<"Hvor langt unna er målet: ";
				cin>>distanceToTarget;
				cout<<"Avstand til målet: "<<targetPractice(distanceToTarget,velocity[0],velocity[1])<<"\n";
				break;
			}
			case 2:{
				for(int i=0; i<10;++i){
					cout<<randWithLimits(0,2)<<"\n";
				}
				break;
			}
			case 3:{
				playTargetPractice();
				break;
			}
		}
	}
}

//------------------------------------------------------------------------------

void playTargetPractice(){
	double distanceToTarget=randWithLimits(100,1000);
	cout<<"Målet er "<<distanceToTarget<<" unna.\n";
	bool hit=false;
	for(int lives=10;lives!=0;--lives){
		double absVelocity=getUserInputAbsVelocity();
		double theta=getUserInputTheta();
		vector<double> velocity(2);
		velocity=getVelocityVector(theta,absVelocity);
        cannonBallViz(distanceToTarget,1000,velocity[0],velocity[1],5);
		double missDistance=targetPractice(distanceToTarget,velocity[0],velocity[1]);
		if(missDistance<-5){
			cout<<-missDistance<<" for kort.\n";
		} else if(missDistance>5){
			cout<<missDistance<<" for langt.\n";
		} else{
			cout<<"Treff.\n";
			hit=true;
			break;
		}		
	}
	if(hit){
		cout<<"Bra jobba.\n";
	}
	else{
		cout<<"Bedre lykke neste gang\n";
	}
	
}

void testDeviation(double compareOperand, double toOperand, double maxError, string name){
	if(abs(compareOperand-toOperand)<maxError){
		cout<<name<<" er nær nok.\n";
	} else{
		cout<<name<<" er ikke nær nok.\n";
	}
}
