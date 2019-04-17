/**
 *	@author Micael Gomes
 *	Sistemas Operacionais
 */

#include <stdlib.h>
#include <stdio.h>

#define TRUE 1

void shell_loop(){
	char* buffer;
	size_t tam_buffer = 1024;
	size_t character;

	buffer = (char*)malloc(tam_buffer*sizeof(char));

	while(TRUE){
		printf("$ ");
		character = getline(&buffer, &tam_buffer, stdin);
		system(buffer);
	}
}

int main(){
	system("clear");
	
	// loop to read user commands
	shell_loop();

	return 1;
}
