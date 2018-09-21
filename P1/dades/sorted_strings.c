#include <stdio.h>
#include <stdlib.h>

int compara(const void *p1, const void *p2){

	/**
		This time, the function compara does a comparation
		between one string and another and returns a value that
		indicates which string is "greater" and which "lesser".
	*/

	int value;
	char *str1, *str2;

	str1 = *[[ char **] p1];
	str2 = *[[ char **] p2];

	return value;

}

int main(){
	double *dble;
	
	FILE *fp;
	char str[100];

	fp = fopen("strings.txt","r");
	if(fp == NULL){
		perror("Error al obrir el fitxer");
		return(-1);
	}

	if( fgets (str,100,fp) != NULL){
		puts(str);
	}
	
	int MIDA = atoi(str);
	dble = malloc(MIDA * sizeof(char **));

	for(int i = 0;  i < MIDA; i++){
		if( fgets (str,100,fp) != NULL){
			puts(str);
		}
		dble[i] = atof(str);
	}

	fclose(fp);

	qsort(dble, MIDA, sizeof(char **), compara);

	for(int g = 0; g < MIDA; g++){
		printf("%lf ", dble[g]);
		printf("\n");
	}

	free(dble);

}