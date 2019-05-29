#include "prime.h"

bool isPrime(int num){
    bool flag = true;

    for(int i=2; i<=num/2; i++){
        if(num%i==0){
            flag = false;
            break;
        }
    }

    return flag;
}

void findPrime(){
    for(int i=0; i<TAM; i++)
        for(int j=0; j<TAM; j++)
            if(isPrime(mat[i][j]))
                quantPrime = quantPrime + 1;
}