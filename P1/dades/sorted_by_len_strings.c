#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compara(const void *p1, const void *p2){

	/** The function compara does a comparation
		between one string and another and returns a value that
		indicates which string is shorter and which is longer using
		the length of them.
	*/

	int value;
	char *str1, *str2;

	str1 = *((char **) p1);
	str2 = *((char **) p2);

	if(strlen(str1) < strlen(str2))
		return -1;
	else if(strlen(str1) >= strlen(str2))
		return 1;
	else
		return 0;
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
	int i = 0;

	printf("%i", MIDA);
	
	str_matrix = malloc(MIDA * sizeof(char *));

	while(fgets(str,MIDA, fp) != NULL && i < MIDA){
		str[strlen(str)-1] = '\0';
		str_matrix[i] = (char*) malloc(strlen(str)*sizeof(char));
		strcpy(str_matrix[i],str);
		i++; 
	}

	fclose(fp);

	qsort(str_matrix, MIDA, sizeof(char **), compara);

	for(int g = 0; g < MIDA; g++){
		printf("%s ", str_matrix[g]);
		printf("\n");
	}

	free(str_matrix);

}