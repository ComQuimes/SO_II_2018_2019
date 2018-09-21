#include <stdio.h>
#include <stdlib.h>

int compara(const void *p1, const void *p2){

	double *num1, *num2;

	num1 = (double *) p1;
	num2 = (double *) p2;

	if(*num1 < *num2)
		return -1;
	else if(*num1 > *num2)
		return 1;
	else
		return 0;
}

int main(){
	double *dble;
	
	FILE *fp;
	char str[100];

	fp = fopen("float.txt","r");
	if(fp == NULL){
		perror("Error al obrir el fitxer");
		return(-1);
	}

	if( fgets (str,100,fp) != NULL){
		puts(str);
	}
	
	int MIDA = atoi(str);
	dble = malloc(MIDA * sizeof(double));

	for(int i = 0;  i < MIDA; i++){
		if( fgets (str,100,fp) != NULL){
			puts(str);
		}
		dble[i] = atof(str);
	}

	fclose(fp);

	qsort(dble, MIDA, sizeof(double), compara);

	for(int g = 0; g < MIDA; g++){
		printf("%lf ", dble[g]);
		printf("\n");
	}

	free(dble);

}