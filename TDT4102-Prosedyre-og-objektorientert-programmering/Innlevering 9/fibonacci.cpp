#include "fibonacci.h"
#include <iostream>
void fillInFibonacciNumbers(int results[],int length){
    for(int i{0};i<length;++i){
        if(i==0){
            results[i]=0;
        } 
        else if(i==1){
            results[i]=1;
        }
        else{
            results[i]=results[i-2]+results[i-1];
        }
    }
}

void printArray(int arr[],int length){
    for(int i{0};i<length;++i){
        std::cout<<arr[i];
        if(i%6==5 || i==length-1){
            std::cout<<"\n";
        }else{
            std::cout<<"\t";
        }
    }
}

void createFibonacci(){
    std::cout<<"Hvor mange tall skal genereres? ";
    int len=0;
    while(!(std::cin>>len)){
        std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout<<"Not valid input.\n";
    }
    std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    
    if(len<0) return;
    int *fibNums=new int[len]{};
    fillInFibonacciNumbers(fibNums,len);
    printArray(fibNums,len);
    delete[] fibNums;
    fibNums=nullptr;
}