/**
 *	@author Micael Gomes
 *	Trabalho para Disciplina de Sistemas Operacionais
 *	Multithread com PThreads
 */

#include <iostream>
#include <stdlib.h>
#include <thread>
#include <string.h>

#define a 0
#define b 29999
#define TAM 10000

/*  TAM == 10000 => Quant Primes: 10825260
    Time => ./exe serial: 397,95s user - 0,58s system - 99% cpu - 6:41,73 total
*/

using namespace std;

int mat[TAM][TAM];
int quantPrime = 0;

bool isPrime(int num);
void generateRandomMat();
void findPrime();

int main(int argc, char *argv[]){       
    generateRandomMat();

    if(!strcmp(argv[1], "serial")){
        findPrime();
    }   
    
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