#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "red-black-tree.h"
#include "linked-list.h"

int contador_destinos = 0;
char *aeropuerto;

// #############################################################################
// -- Aquesta funció ens retorna la posicio de la linia en la que comença la 
// columna desitjada.
// #############################################################################
char *get_posicio(char *linea, int col, int *tamany) {

	// -- Agafem la allargada de la linia, inicialitzem el contador, a mes 
	// creem les variables "i" i col.
	int tamany_linea = strlen(linea); /* Max lenght of the line */
	int n_columna = 0; /* Counter to keep track of the number of periods */
	int pos;
	int cont;

	// -- Aquest bucle for recorre tota la linia que s'ha pasat per parametre.
	for (cont = 0; cont < tamany_linea; cont++) { 

		// -- Si el caracter actual es una coma vol dir que estem en una
		// nova columna i incrementem el numero de columna en el que estem.
		if (linea[cont] == ',' || linea[cont] == '\n') { 
			n_columna++;
			
			// -- Comprovem si la nova columna es la desitjada i guardem 
			// en quina posicio s'inicia.			
			if (n_columna == col) { 
				pos = cont;
			}

			// -- Si estem en la seguent columna ja podem calcular el 
			// tamany de la paraula continguda en la columna i retornem 
			// la posicio en la que hi ha la primera lletra per referencia.
			else if (n_columna == col+1) { 
				*tamany = cont-pos; 
				return &linea[pos+1];
			}
		}
	}

	// -- En cas de no trobar la columna dessitjada retornem el valor 0.
	return 0;
}

// #############################################################################
// -- Aquesta funció ens permet emplenar el arbre binari amb tots els aeroports.
// #############################################################################
rb_tree *arbre_aeroport(char *fitxer) {
    
	// -- Creem les variables necessaries i obrim el fitxer passat per 
	// parametre.
	FILE *fp;
	char codi_IATA[4];
	int cont_linea = 0;
	int cont = 0;
	rb_tree *arbre;
	node_data *node;
	fp = fopen(fitxer, "r");
    	
	// -- Comprovem si s'ha pogut llegir el fitxer, so no es pot obrir 
	// informem via log.
	if (fp == NULL) {
		printf("\nError al obrir el fitxer.\n");
	        return 0;
	}

	// -- Agafem el nombre de aeroports que contenen les dades (aquesta
	// informacio esta en la primera linea del fitxer).
	if (fgets(codi_IATA, 4, fp) != NULL) {
	        cont_linea = atoi(codi_IATA);
	}
    
	// -- Creem un espai de memoria destinat per el arbre i l'inicialitzem.
	arbre = (rb_tree *)malloc(sizeof(rb_tree));
	init_tree(arbre);

	// -- Aquest bucle s'executara sempre que quedin linies per llegir o 
	// es llegeixi una linea sence informacio.
	while (fgets(codi_IATA, 100, fp) != NULL && cont < cont_linea) {
        
		// -- Eliminamos el salto de linea ('\n') con '\0', los codigos 
		// IATA estan formados por tres cararcteres.
	        codi_IATA[3] = '\0';
        
		// -- Buscamos el nodo actual en el arbol, si este no esta lo 
		// insertamos en el arbol.
	        node = find_node(arbre, codi_IATA);
	        if (node == NULL) {
            
			// -- Creem el espai de memoria necessaria per el nou node.
        		node = (node_data *)malloc(sizeof(node_data));
            
			// -- Creem el espai de memoria necessaria per enmagatzema 
			// la clau i la llista de vols i els guardem en el node.
        		node->key = (char *)malloc((4)*sizeof(char));
        		strcpy(node->key, codi_IATA);
        		node->vuelos = (list *)malloc(sizeof(list));
        		init_list(node->vuelos);

			// -- Afegim el nou node al arbre.
        		insert_node(arbre, node);
        	}
		// -- Actualitzem la linia que ens toca llegir.
        	cont++;
	}
    
	// -- Un cop tenim el arbre ple tanquem el fitxer i retornem el arbre creat.
	fclose(fp);
	return arbre;
}

// #############################################################################
// -- Aquesta funció ens permet emplenar els nodes del arbre binari amb la 
// llista dels vols que te cada aeroport.
// #############################################################################
void lista_vuelos(rb_tree *arbre, char *fitxer) {

	// -- Creem les variables necessaries i obrim el fitxer passat per 
	// parametre.
	FILE *fp;
	char str[500];
	list_data *lista_data;
	char *destino;
	char *retard;
	char *origen;
	node_data *node;
	list *llista_vols;
	int tamany;
	char *posicio;   
	fp = fopen(fitxer, "r");

	// -- Comprovem si s'ha pogut llegir el fitxer, so no es pot obrir 
	// informem via log.
    	if (fp == NULL) { 
        	perror("\nError al obrir el fitxer.\n");
	}
	
	// -- La primera linea de les dades conte el nom de les columnes, 
	// aquesta la linea no la necessitem.    
    	fgets(str, 500, fp);
        
	// -- -- Aquest bucle s'executara sempre que quedin linies per llegir.
	while (fgets(str, 500, fp) != NULL) {

		// -- Mitjançant el metode get_posicio tenim el punter linea 
		// apuntant al primer caracter de la columna dessitjada, i 
		// mitjançant memcpy copiem la columna desitjada, aquest proces ç
		// es repeteix per les columnes 14, 16 i 17.
	        posicio = get_posicio(&str[0], 14, &tamany);
	        retard = (char *)malloc(tamany*sizeof(char));
	        memcpy(retard, posicio, tamany);
	        retard[tamany-1] = '\0';
		posicio = get_posicio(&str[0], 16, &tamany);
		origen = (char *)malloc(tamany*sizeof(char));
		memcpy(origen, posicio, tamany);
		origen[tamany-1] = '\0';
		posicio = get_posicio(&str[0], 17, &tamany);
		destino = (char *)malloc(tamany*sizeof(char));
		memcpy(destino, posicio, tamany);
		destino[tamany-1] = '\0';
		
		// -- Busquem el aeroport en el arbre com ha node, si aquest
		// existeix en el arbre creat previament actualitzem la seva
		// llista de vols y el seu retard.
		node = find_node(arbre, origen);
		if (node != NULL) {
		
			// -- Agafem la llista de vols del node aeroport origen 
			// i busquem el aeroport desti en la llista.
			llista_vols = node->vuelos;
			lista_data = find_list(llista_vols, destino);

			// -- Si el desti existeix en el node desti sumem 1 al
			// numero de vols i sumem el retard al retard acomulat.
			if (lista_data != NULL) {
			    lista_data->num_vols++;
			    lista_data->retard += atoi(retard);
			    free(destino);
			}
			// -- Si el desti no existeix en el node desti es 
			// necessari crear-lo.
			else {
				
				// -- Creem la llista de vols i guardem el aeroport
				// desti com ha clau, el numero de vols (s'inicialitza
				// a 1) i guardem el valor del retart.
				lista_data = malloc(sizeof(lista_data));
				lista_data->key = destino;
				lista_data->num_vols = 1;
				lista_data->retard = atoi(retard);

				// -- Guardem la nova llista de vols en el node origen.
				insert_list(llista_vols, lista_data);
			}
		}
		
		// -- Alliberem la memoria de les variables origen i retard.
	        free(origen);
		free(retard);
	}
	
	// -- Tanquem el fitxer de dades que conte el vols.
	fclose(fp);
}

// #############################################################################
// -- Aquesta funció ens permet saber quin es el aeroport amb més vols. 
// (aixo es fa explorant el arbre en postorde)
// #############################################################################
void vuelos_maximos(node *x) {
	
	// --Agafem el numero de vols del node pasat per parametre.
	int n_destins = x->data->vuelos->num_items;

	// -- Mirem el node fill de la dreta.
	if (x->right != NIL)
	vuelos_maximos(x->right);

	// -- Mirem el node fill de l'esquerra.
	if (x->left != NIL)
	vuelos_maximos(x->left);

	// -- Comprovem si el node actual te més vols que els aeroports ja 
	// visitats, en aquest cas actualitzem el contador de deestins i el 
	// aeroport.
	if (n_destins > contador_destinos) {
		contador_destinos = n_destins;
		aeropuerto = x->data->key;
	}
}

// #############################################################################
// -- Aquesta funció es el main, crida les funcions implementades anteriorment 
// per tal de cumplir el objectius establerts.
// #############################################################################
int main(int argc, char **argv) {

	// -- Creem el arbre balancejat amb els aeroports que estan en el fitxer 
	// passat per parametre. (1er parametre) 
	rb_tree *arbre_aeroports = arbre_aeroport(argv[1]); 

	// -- Competem el arbre balancejat amb els vols que estan en el fitxer 
	// passat per parametre. (2on parametre)
	lista_vuelos(arbre_aeroports, argv[2]); 
    
	// -- Busquem el aeroport origen (3er parametre) en el arbre creat anteriorment.
	node_data *n_data = find_node(arbre_aeroports, argv[3]);
    
	// -- Si el node existeix en el arbre procedim a computar els objectius
	// establerts. (Mostrar vols d'un aeroport i el aeroport amb més vols)
	if (n_data != NULL) { 

		// -- Creem la llista que contindra la informació dels vols,
		// la variable reterd_promig y agafem la llista de vols del node
		// pasat per parametre. (3er parametre)
		list_data *l_data;
		float avg_delay;
		list_item *l_item = n_data->vuelos->first;
		

		// -- Comprovem si l'aeroport origen te vols.
		if (l_item == NULL) { 
			printf("\nAquest aeroport no te vols.\n");
		} else {
			printf("\n");

			// -- Aquest bucle s'executara sempre que quedin vols a computar.
			while (l_item != NULL) { 

				// -- Agafem la informació del vol actual, calculem 
				// el retard_promig i mostrem el vol per consola.
				l_data = l_item->data;
				avg_delay = (float)l_data->retard/l_data->num_vols;
				printf("Aeroport desti ==> %s\t Retard promig dels vols ==>: %f\n", l_data->key, avg_delay);

				// -- Seleccionem el seguent vol de la llista.
				l_item = l_item->next;
		    	}
		}
	}
	else {
		
		// -- Mostrem un missatje indicant que aquest aeroport no existeix en el arbre.
		printf("Aquest aeroport no existeix en la nostra base de dades.\n");
	}
    
	// -- Mitjançant la funcio de vols_maxim trobem el aeroport del arbre amb mes vols.
	vuelos_maximos(arbre_aeroports->root);
	printf("\nL'aeroport %s te un total de %d destins diferents.\n\n", aeropuerto, contador_destinos);
    
	// -- Eliminem el arbre d'aeroports i alliberem la memoria.
	delete_tree(arbre_aeroports);
	free(arbre_aeroports);
    	
	return 0;
}
