/**
 *	@author Micael Gomes
 *	Trabalho para Disciplina de Sistemas Operacionais
 *	Multithread com PThreads
 */

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <thread>
#include <mutex>

#define a 0
#define b 29999
#define TAM 100

using namespace std;

int mat[TAM][TAM];
int quantPrime = 0;
int quantPrimeThread = 0;
vector<int> lineVisited(TAM, 0);
mutex m;

void generateRandomMat();
vector<thread> createThreads(int quantThread);
bool isPrime(int num);
void findPrime();
void findPrimeInLine(int line);

void checkPrimeInLine(){
    while(true){
        if(lineVisited[TAM-1] == 1)
            break;
        else {
            m.lock();
            int line = 0;
            for(line = 0; line<TAM; line++)
                if(lineVisited[line] == 0)
                    break;

            if(lineVisited[line] == 0)
                lineVisited[line] = 1;
                
            m.unlock();
            findPrimeInLine(line);
        }
    }
}

int main(int argc, char *argv[]){
    int quantThread;
    vector<thread> threads;

    if(argv[1]!=NULL) {
        printf("Preenchendo Matriz...\n\n");
        generateRandomMat();
  
        if(!strcmp(argv[1], "serial")){
            printf("SERIAL Start!\n");
            findPrime();
        } else if(!strcmp(argv[1], "paralelo")){
            if(argv[2]!=NULL){
                printf("PARALELO Start!\n");
                quantThread = strtol(argv[2], NULL, 10);
                threads = createThreads(quantThread);

                for(thread & th: threads)
                    if(th.joinable())
                        th.join();

                printf("Quant Primes: %d\n", quantPrimeThread);
                return 0;
            } else {
                printf("Há Argumentos, mas... não consigo entender\n");
                return 0;    
            }
        } else if(!strcmp(argv[1], "ambos")){
            if(argv[2]!=NULL){
                quantThread = strtol(argv[2], NULL, 10);
                threads = createThreads(quantThread);

                printf("Buscar de forma ::SERIAL::\n");
                findPrime();
                printf("Quant Primes: %d\n", quantPrime);
                // printf("TEMPO SERIAL: %lf\n", timeSerialEnd-timeSerialStart);

                printf("\n==============================\n\n");
                printf("Buscar de forma ::PARALELA::\n");
                
                for(thread & th: threads)
                    if(th.joinable())
                        th.join();             
                printf("Quant Primes: %d\n", quantPrimeThread);
                // printf("TEMPO PARALELO: %lf\n", timeParaleloEnd-timeParaleloStart);
                
                return 0;
            } else {
                printf("Há Argumentos, mas... não consigo entender\n");
                return 0;    
            }
        }

        printf("Quant Primes: %d\n", quantPrime);
    
    }else{
        printf("Argumentos não encontrado!\n");
    }
    
    return 0;
}

vector<thread> createThreads(int quantThread){
    vector<thread> threads;

    while(quantThread > 0){
        threads.push_back(thread(checkPrimeInLine));
        quantThread--;
    }

    return threads;
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

void findPrimeInLine(int line){
    for(int i=0; i<TAM; i++)
        if(isPrime(mat[line][i]))
            quantPrimeThread = quantPrimeThread + 1;        
}