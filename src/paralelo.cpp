/**
 *	@author Micael Gomes
 *	Programa com aplicação de Threads
 */

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <thread>
#include <mutex>

#define a 0
#define b 29999
#define TAM 20000

using namespace std;

int mat[TAM][TAM];
int quantPrime = 0;
vector<int> visited(TAM, 0);
mutex m;

void generateRandomMat();
vector<thread> createThreads(int quantThread);
bool isPrime(int num);
void findPrime(int line);

void checkPrime(){ 
    while(true){
        if(visited[TAM-1] == 1)
            break;
        else {
            int line = 0;
            for(line = 0; line<TAM; line++)
                if(visited[line] == 0)
                    break;

            m.lock();
            visited[line] = 1;
            m.unlock();
            findPrime(line);
        }
    }
}

int main(int argc, char *argv[]){ 
    int quantThread;
    vector<thread> threads;

    printf("Preenchendo Matriz...\n\n");
    generateRandomMat();

    if(argv[1]!=NULL) {
        quantThread = strtol(argv[1], NULL, 10);
        threads = createThreads(quantThread);

        for(thread & th: threads)
            if(th.joinable())
                th.join();

        printf("Quant Primes: %d\n", quantPrime);
    } else {
        printf("Argumentos não encontrados.\n");
    }

    return 0;
}

vector<thread> createThreads(int quantThread){
    vector<thread> threads;

    while(quantThread > 0){
        threads.push_back(thread(checkPrime));
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

void findPrime(int line){
    for(int i=0; i<TAM; i++)
        if(isPrime(mat[line][i]))
            quantPrime = quantPrime + 1;        
}