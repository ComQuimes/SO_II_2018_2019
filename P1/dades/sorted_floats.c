#include <stdio.h>
#include <stdlib.h>

int compara(const void *p1, const void *p2){

	float *num1, *num2;

	num1 = (float *) p1;
	num2 = (float *) p2;

	if(*num1 < *num2)
		return -1;
	else if(*num1 > *num2)
		return 1;
	else
		return 0;
}

int main(){
	float *flo;
	
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
	
	float MIDA = atof(str);
	flo = malloc(MIDA * sizeof(float));

	for(int i = 0;  i < MIDA; i++){
		if( fgets (str,100,fp) != NULL){
			puts(str);
		}
		flo[i] = atof(str);
	}


	fclose(fp);

	qsort(flo, MIDA, sizeof(float), compara);

	for(int g = 0; g < MIDA; g++){
		printf("%f ", flo[g]);
		printf("\n");
	}

	free(flo);
	

}