#include <stdio.h>
#include <stdlib.h>

int compara(const void *p1, const void *p2){
	/**
	* La funció compara, en aquest cas ha sigut modificada de tal manera
	* que quan compari els dos elements retorni 1 si es mes petit o -1
	* si es més gran el element 1 que el element 2.
	*/
	
	int *num1, *num2;

	num1 = (int *) p1;
	num2 = (int *) p2;

	if(*num1 < *num2)
		return 1;
	else if(*num1 > *num2)
		return -1;
	else
		return 0;
}

int main(){
	int *inters;
	
	FILE *fp;
	char str[100];

	fp = fopen("integers.txt","r");
	if(fp == NULL){
		perror("Error al obrir el fitxer");
		return(-1);
	}

	if( fgets (str,100,fp) != NULL){
		puts(str);
	}
	
	int MIDA = atoi(str);
	inters = malloc(MIDA * sizeof(int));

	for(int i = 0;  i < MIDA; i++){
		if( fgets (str,100,fp) != NULL){
			puts(str);
		}
		inters[i] = atoi(str);
	}


	fclose(fp);

	qsort(inters, MIDA, sizeof(int), compara);

	for(int g = 0; g < MIDA; g++){
		printf("%d ", inters[g]);
		printf("\n");
	}

	free(inters);
	

}

	

	