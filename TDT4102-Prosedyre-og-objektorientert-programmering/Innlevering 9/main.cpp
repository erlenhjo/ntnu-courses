//
// This is example code from Chapter 2.2 "The classic first program" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
// 
// keep_window_open() added for TDT4102, excercise 0

// This program outputs the message "Hello, World!" to the monitor

#include "fibonacci.h"
#include "iostream"
#include "Matrix.h"
#include "Dummy.h"
//------------------------------------------------------------------------------'
//3b) Krasj grunnet mer enn en sletting av pointer verdi.



// C++ programs start by executing the function main
int main()
{
	int caseNum{-1};
	constexpr int quit{0};
	while(caseNum!=quit){
		std::cout<<"0)Avslutt 1)Fibonacci 2)Matrix get/set 3)Matrix index/cout\n";
		std::cout<<"4)Dummy 5) Matrix copy 6) Matrix add\n";
		while(!(std::cin>>caseNum)){
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
			std::cout<<"Not valid input.\n";
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

		switch(caseNum){
			case quit:{
				break;
			}
			case 1:{
				createFibonacci();
				break;
			}
			case 2:{
				Matrix M{2};
				M.set(1,0,2.4);
				std::cout<<M.get(0,0)<<"\t"<<M.get(0,1)<<"\n";
				std::cout<<M.get(1,0)<<"\t"<<M.get(1,1)<<"\n";
				break;
			}
			case 3:{ 
				Matrix M{3,2};
				M[0][1]=1;
				M[1][1]=2;
				M[2][1]=3;
				std::cout<<M;
				std::cout<<"Rows: "<<M.getRows()<<"\n";
				std::cout<<"Coloumns: "<<M.getColoumns()<<"\n";
				break;
			}
			case 4:{
				dummyTest();
				break;
			}
			case 5:{
				Matrix A{2};
				A[0][0]=1;
				A[0][1]=2;
				A[1][0]=3;
				A[1][1]=4;
				Matrix B{2};
				B[0][0]=4;
				B[0][1]=3;
				B[1][0]=2;
				B[1][1]=1;
				Matrix C{A};
				std::cout<<"A:\n"<<A;
				std::cout<<"B:\n"<<B;
				std::cout<<"C:\n"<<C;
				std::cout<<"C{A} er gjort. Videre: A=B, A+=C\n";
				A=B;			
				A+=C;
				std::cout<<"A:\n"<<A;
				std::cout<<"B:\n"<<B;
				std::cout<<"C:\n"<<C;
				break;
			}
			case 6: {
				Matrix A{2};
				A[0][0]=1;
				A[0][1]=2;
				A[1][0]=3;
				A[1][1]=4;
				Matrix B{2};
				B[0][0]=4;
				B[0][1]=3;
				B[1][0]=2;
				B[1][1]=1;
				Matrix C{2};
				C[0][0]=1;
				C[0][1]=3;
				C[1][0]=1.5;
				C[1][1]=2;
				A+=B+C;
				std::cout<<"A:\n"<<A;
				std::cout<<"B:\n"<<B;
				std::cout<<"C:\n"<<C;
				break;
			}
			default:{
				std::cout<<"Not valid case.\n";
			}
		}
	}
}

//------------------------------------------------------------------------------
