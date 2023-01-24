//
// This is example code from Chapter 2.2 "The classic first program" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
// 
// keep_window_open() added for TDT4102, excercise 0

// This program outputs the message "Hello, World!" to the monitor

#include "std_lib_facilities.h"
#include "Graph.h"
#include "Simple_window.h"
//------------------------------------------------------------------------------'
void inputAndPrintInteger(){
	int num;
	cout<<"Skriv inn et tall: ";
	cin>>num;
	cout<<"Du skrev: "<<num<<"\n";
}
int inputInteger(){
	int num;
	cout<<"Skriv inn et tall: ";
	cin>>num;
	return num;
}
void inputIntegersAndPrintSum(){
	int num1= inputInteger();
	int num2=inputInteger();
	cout<<"Summen av tallene: "<<num1+num2<<"\n";

}
	//Brukte inputInteger da denne er en int, 
	//mens den andre er en void. Er også renere/mindre skrift.
bool isOdd(int n){
	if(n%2==1){
		return true;
	}
	return false;
}
void printHumanReadableTime(int seconds){
	int hours=seconds/3600;
	seconds=seconds%3600;
	int minutes=seconds/60;
	seconds=seconds%60;
	cout<<hours<<" timer, "<<minutes<<" minutter og ";
	cout<<seconds<<" sekunder.\n";
}
void sumNumbers(){
	cout<<"Hvor mange tall skal summeres?\n";
	int N = inputInteger();
	int sum=0;
	cout<<"Skriv inn tall som skal summeres.\n";
	for(int i=0;i<N;++i){
		sum+=inputInteger();
	}
	cout<<"Summen er "<<sum<<"\n";
}
void sumNumbersUntilZero(){
	cout<<"Summerer tall inntil 0 skrives inn.\n";
	int num=1;
	int sum=0;
	while(num!=0){
		num=inputInteger();
		sum+=num;
	}
	cout<<"Summen er "<<sum<<".\n";
}
	//Den ene summerer et antall ganger, for 
	//den andre summere inntil noe er oppfylt, while
double inputDouble(){
	double num;
	cout<<"Skriv inn et desimaltall: ";
	cin>>num;
	return num;
}
void nokToEuro(){
	double nok=-1.0;
	while(nok<0){
		cout<<"Skriv inn antall NOK som positiv desimaltall: ";
		cin>>nok;
		if(nok<0){cout<<"Prøv på nytt.";}
	}
	cout<<"Dette tilsvarer "<<nok/9.75<<" Euro.\n";
}
//De skal gi inn et desimaltall.
//Kunne brukt double om jeg skulle hatt ut svare, men det skal jeg ikke.
void multiplicationTable(){
	int size;
	cout<<"Table size: ";
	cin>>size;
	for(int i=1;i<size+1;++i){
		for(int j=1;j<size+1;++j){
		cout<<setw(4)<<i*j;
		}
		cout<<"\n";
	}
}

double discriminant(double a, double b, double c){
	return pow(b,2)-4*a*c;
}
void printRealRoots(double a,double b,double c){
	double d=discriminant(a,b,c);
	if(d==0){
		double root=(-b)/(2*a);
		cout<<"Den reelle roten er: "<<root<<".\n";
	}else if(d>0){
		double root1=(-b+pow(d,0.5))/(2*a);
		double root2=(-b-pow(d,0.5))/(2*a);
		cout<<"De reelle røttene er: "<<root1<<" og "<<root2<<".\n";
	}else{
		cout<<"Ingen reelle røtter.\n";
	}
}
void solveQuadraticEquation(){
	cout<<"Skriv in a: ";
	double a;
	cin>>a;
	cout<<"Skriv in b: ";
	double b;
	cin>>b;
	cout<<"Skriv in c: ";
	double c;
	cin>>c;
	printRealRoots(a,b,c);
}
void pythagorasGraphic(){
	using namespace Graph_lib;
	Simple_window win{Point{100,100},700,700,"Pythagoras"};
	Polygon rightTriangle;
	rightTriangle.add(Point{200,400});
	rightTriangle.add(Point{400,400});
	rightTriangle.add(Point{200,300});
	rightTriangle.set_fill_color(Color::black);
	win.attach(rightTriangle);
	Polygon bRectangle;
	bRectangle.add(Point{200,300});
	bRectangle.add(Point{200,400});
	bRectangle.add(Point{100,400});
	bRectangle.add(Point{100,300});
	bRectangle.set_fill_color(Color::green);
	win.attach(bRectangle);
	Polygon cRectangle;
	cRectangle.add(Point{200,300});
	cRectangle.add(Point{400,400});
	cRectangle.add(Point{500,200});
	cRectangle.add(Point{300,100});
	cRectangle.set_fill_color(Color::blue);
	win.attach(cRectangle);
	Polygon aRectangle;
	aRectangle.add(Point{200,400});
	aRectangle.add(Point{400,400});
	aRectangle.add(Point{400,600});
	aRectangle.add(Point{200,600});
	aRectangle.set_fill_color(Color::red);
	win.attach(aRectangle);

	win.wait_for_button();
}
vector<int> calculateBalance(int balance, int interest,int year){
	vector<int> temp(year+1);
	for(int i=0;i<year+1;++i){
		temp[i]=balance*pow(1+static_cast<double>(interest)/100,i);
	}
	return temp;
}
void printBalance(vector<int> balance){
	cout<<setw(3)<<"Ar:"<<setw(7)<<"Saldo:"<<"\n";
	for(int i=0; i<size(balance);++i){
		cout<<setw(3)<<i<<setw(7)<<balance[i]<<"\n";
	}
}
// C++ programs start by executing the function main
int main()
{   
	while(true){
		cout<<"Velg funksjon:\n";
		cout<<"0) Avslutt\n";
		cout<<"1) Skriv og print heltall\n";
		cout<<"2) Skriv inn heltall\n";
		cout<<"3) Summer 2 heltall\n";
		cout<<"4) Sjekk oddetall\n";
		cout<<"5) Lesbar tid\n";
		cout<<"6) Summer n heltall\n";
		cout<<"7) Summmer heltall til 0 skrives inn\n";
		cout<<"8) Skriv inn desimaltall\n";
		cout<<"9) Konverter NOK til Euro\n";
		cout<<"10) Gangetabellen\n";
		cout<<"11) Reelle røtter\n";
		cout<<"12) Pythagoras\n";
		cout<<"13) Renter\n";

		int casenum;
		cout<<"Velg tall (1-n): ";
		cin>>casenum;
		switch (casenum) {
			case 1:{
				cout<<"Oppgave 1a:\n";
				inputAndPrintInteger();
				break;
				}
			case 2:{
				cout<<"Oppgave 1b:\n";
				int number = inputInteger();
				cout << "Du skrev: " << number <<"\n";
				break;
				}
			case 3:{
				cout<<"Oppgave 1c:\n";
				inputIntegersAndPrintSum();
				break;
				}
			case 4:{
				cout<<"Oppgave 1e:\n";
				for(int i=0;i<16;++i){
					if(isOdd(i)){
						cout<<i<<" er oddetall\n";
					} else{
						cout<<i<<" er partall\n";
					}
				}
				break;
				}
			case 5:{
				cout<<"Oppgave 1f:\n";
				cout<<"Angi sekunder:\n";
				printHumanReadableTime(inputInteger());
				break;
				}
			case 6:{
				cout<<"Oppgave 2a:\n";
				sumNumbers();
				break;
				}
			case 7:{
				cout<<"Oppgave 2b:\n";
				sumNumbersUntilZero();
				break;
				}
			case 8:{
				cout<<"Oppgave 2d:\n";
				double number = inputDouble();
				cout << "Du skrev: " << number <<"\n";
				break;
				}
			case 9:{
				cout<<"Oppgave 2e:\n";
				nokToEuro();
				break;
				}
			case 10:{
				cout<<"Oppgave 3b:\n";
				multiplicationTable();
				break;
			}
			case 11:{
				cout<<"Oppgave 4c:\n";
				solveQuadraticEquation();
				break;
			}
			case 12:{
				cout<<"Oppgave 5: \n";
				pythagorasGraphic();
				break;
			}
			case 13:{
				cout<<"Oppgave 6:\n";
				int balance=inputInteger();
				int interest=inputInteger();
				int year=inputInteger();
				printBalance(calculateBalance(balance,interest,year));
			}
			default:
				break;
		} if(casenum==0){break;}
	}
}

//------------------------------------------------------------------------------
