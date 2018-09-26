#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compara(const void *p1, const void *p2){

	/**
		The function compara does a comparation
		between one string and another and returns a value that
		indicates which string is "shorter" and which "longer" using
		the ascii value of them.
	*/

	int value;
	char *str1, *str2;

	str1 = *((char **) p1);
	str2 = *((char **) p2);

	return strcmp(str1,str2);
	
}

int main(){
	char **str_matrix;

	FILE *fp;
	char str[100];

	fp = fopen("strings.txt","r");
	if(fp == NULL){
		perror("Error al obrir el fitxer");
		return(-1);
	}

	if (fgets (str,100,fp) != NULL){
		puts(str);
	}
	
	int MIDA = atoi(str);
	int i = 0; // an 
	
	str_matrix = malloc(MIDA * sizeof(char *)); //we make the first malloc using number of lines

	while(fgets(str,MIDA, fp) != NULL && i < MIDA){
        int h = strlen(str);
		str[h-1] = '\0'; //turn the \n to 0
		str_matrix[i] = (char*) malloc(h*sizeof(char)); //this creates a row in the matrix where it'll store the string.
		strcpy(str_matrix[i],str); //this copy the string inside the row of the matrix of chars
		i++; 
	}

	fclose(fp);

	qsort(str_matrix, MIDA, sizeof(char **), compara);

	for(int g = 0; g < MIDA; g++){
		printf("%s ", str_matrix[g]);
		printf("\n");
        free(str_matrix[g]);
	}

	free(str_matrix);

}
