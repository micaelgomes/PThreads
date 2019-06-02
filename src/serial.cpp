/**
 *	@author Micael Gomes
 *	Programa com aplicação de Threads
 */

#include <iostream>
#include <stdlib.h>

#define a 0
#define b 29999
#define TAM 4000

using namespace std;

int mat[TAM][TAM];
int quantPrime = 0;

void generateRandomMat();
bool isPrime(int num);
void findPrime();

int main(int argc, char *argv[]){ 
    int quantThread;
    vector<thread> threads;

    printf("Preenchendo Matriz...\n\n");
    generateRandomMat();
    findPrime();
    printf("Quant Primes: %d\n", quantPrime);
    
    return 0;
}

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

void generateRandomMat(){
    srand(time(NULL));
    for(int i=0; i<TAM; i++)
        for(int j=0; j<TAM; j++)
            mat[i][j] = rand() % b + a;
}

void findPrime(){
    for(int i=0; i<TAM; i++)
        for(int j=0; j<TAM; j++)
            if(isPrime(mat[i][j]))
                quantPrime = quantPrime + 1;        
}