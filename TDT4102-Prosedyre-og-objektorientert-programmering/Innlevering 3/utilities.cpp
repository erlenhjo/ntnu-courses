#include "utilities.h"
#include "cstdlib"

int randWithLimits(int a, int b){
    return a+rand()%(b-a+1);
}
