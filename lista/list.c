/*
*Nombre del modulo: list.c

*Descripcion: En este modulo se implementan las funciones de list

*Autor: Marta Vaquerizo

*Fecha: 28/03/2019
*Modulos usados: list.h

*Mejoras pendientes: El programa funciona como se esperaba
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "list.h"

typedef struct _NodeList { /* EdD privada, necesaria para implementar lista */
	 void* info;
	 struct _NodeList *next;
} NodeList; /* Tipo NodeList privado */

struct _List {
	 NodeList *last; /*La LEC apunta al último nodo y el último al primero*/
	 destroy_element_function_typel destroy_element_function;
	 copy_element_function_typel copy_element_function;
	 print_element_function_typel print_element_function;
	 cmp_element_function_typel cmp_element_function;
};

/*Funciones privadas*/
NodeList* nodeList_ini();
void nodeList_destroy(void *nl);

/*Como las listas estan formadas
por nodos, se inicializan
con esta funcion */
NodeList* nodeList_ini(){
	NodeList * nl = NULL;

	nl = (NodeList*)malloc(sizeof(NodeList));
	if(!nl){
		fprintf(stderr, "%s\n", strerror(errno));
		return NULL;
	}

	nl->info = NULL;
	nl->next = NULL;

	return nl;
}

/*Se libera un nodo de una lista,
empezando por el elemento
que este contiene*/
void nodeList_destroy(void *nl){
	if(nl){
		free(((NodeList*)nl)->info);
		free(nl);
	}
}


/*Se inicializa la lista*/
List* list_ini (destroy_element_function_typel f1, copy_element_function_typel f2, print_element_function_typel f3,
cmp_element_function_typel f4){

	List *pl = NULL;

	pl = (List*)malloc(sizeof(List));
	if(!pl){
		fprintf(stderr, "%s\n", strerror(errno));
		return NULL;
	}

	pl->last = NULL;

	pl->destroy_element_function = f1;
	pl->copy_element_function = f2;
	pl->print_element_function = f3;
	pl->cmp_element_function = f4;

	return pl;
}

/*Se libera la lista, primero
sus nodos y luego ella*/
void list_destroy (List* list){
	void *aux = NULL;
	if(list){
		while(list_isEmpty(list) == FALSE){
			aux = list_extractFirst(list);
			list->destroy_element_function(aux);
		}

		free(list);
	}
}

/*Se inserta un nodo, con la informacion
pasada por argumento, tras 
el nodo last, que es el primero
al que la lista apunta*/
Status list_insertFirst (List* list, const void *pelem){
	NodeList *n = NULL;
	void *aux = NULL;

	if(!list || !pelem ) return ERROR;

	n = nodeList_ini();
	if(!n){
		return ERROR;
	}
	

	aux = list->copy_element_function(pelem);
	if(!aux){
		fprintf(stderr, "%s\n", strerror(errno));
		nodeList_destroy(n);
		return ERROR;
	}

	n->info = aux;

	if(list_isEmpty(list) == TRUE){
		n->next = n;
		list->last = n;
	}
	else{
		n->next = list->last->next;
		list->last->next = n;
	}

	 return OK;

}

/*Se inserta un nodo, con la informacion
pasada por argumento, en la posicion
de last, es decir, que la lista
va a puntar a ese nodo insertado*/
Status list_insertLast (List* list, const void *pelem){
	NodeList *n = NULL;
	void *aux = NULL;

	if(!list || !pelem) return ERROR;

	n = nodeList_ini();
	if(!n) return ERROR;

	aux = list->copy_element_function(pelem);
	if(!aux){
		fprintf(stderr, "%s\n", strerror(errno));
		nodeList_destroy(n);
		return ERROR;
	}

	n->info = aux;

	if(list_isEmpty(list) == TRUE){
		n->next = n;
		list->last = n;
	}
	else{
		n->next = (list->last)->next;
		(list->last)->next = n;
		list->last = n;
	}
	return OK;
}

/*Se inserta un nodo con la informacion
pasada por argumento, en el orden
que le corresponde*/
Status list_insertInOrder (List *list, const void *pelem){
	NodeList *n = NULL, *paux = NULL;
	/*int size = 0, i;*/
	void *aux = NULL;

	if(!list || !pelem) return ERROR;

	n = nodeList_ini();
	if(!n) return ERROR;

	aux = list->copy_element_function(pelem);
	if(!aux){
		fprintf(stderr, "%s\n", strerror(errno));
		nodeList_destroy(n);
		return ERROR;
	}

	n->info = aux;

	if(list_isEmpty(list) == TRUE){
		list->last = n;
		n->next = n;
	}
	else{
	
		for(paux = list->last; list->cmp_element_function(paux->info, n->info) <=0 && (paux->next != list->last); paux = paux->next);

		/*Si se sale del bucle porque se ha llegado a list->last,
		si es mayor la info de paux, el nodo se ha de meter por
		el first, en caso contrario por el last*/
 		if(paux == list->last && list->cmp_element_function(paux->info, n->info) >0){
 			nodeList_destroy(n);
			list_insertFirst(list, pelem);
			return OK;
 		}
 		else if(paux == list->last && list->cmp_element_function(paux->info, n->info) <=0){
 			nodeList_destroy(n);
			list_insertLast(list, pelem);
			return OK;
 		}
 		/*Sino, se mete tras el mayor*/
		n->next = paux->next;
		paux->next = n;
		
	}

	return OK;	
}

/*Se extrae el nodo siguiente a
last, devolviendo la informacion
de mismo*/
void * list_extractFirst (List* list){
	void *ele = NULL;
	NodeList *aux = NULL;

	if(!list || list_isEmpty(list) == TRUE) return NULL;

	ele = ((list->last)->next)->info;
	((list->last)->next)->info = NULL;

	if((list->last)->next == list->last){
		nodeList_destroy(list->last);
		list->last = NULL;
	}
	else{
		aux = (list->last)->next;
		((list->last)->next) = aux->next ;
		nodeList_destroy(aux);
	}
	

	return ele;

}

/*Se extrae el last, devolviendo
su informacion*/
void * list_extractLast (List* list){
	void *ele = NULL;
	NodeList *n = NULL;

	if(!list || list_isEmpty(list) == TRUE) return NULL;

	ele = (list->last)->info;
	(list->last)->info = NULL;

	if((list->last)->next == list->last){
		nodeList_destroy(list->last);
		list->last = NULL;
	}
	else{
		for(n = list->last; n->next != list->last;  n = n->next);

		n->next = (list->last)->next;
		nodeList_destroy(list->last);
		list->last = n;

	}
	return ele;
}


/*Se comprueba si la lista esta
vacia*/
Bool list_isEmpty (const List* list){
	if(!list) return TRUE;

	if(list->last == NULL){
		return TRUE;
	}

	return FALSE;
}

/*Se obtiene la informacion de un nodo
en la posicion index*/
 void* list_get (const List* list, int index){
 	NodeList *n = NULL;
 	void *ele = NULL;
 	int i;

 	if(!list || list_isEmpty(list) == TRUE) return NULL;

 	if(index >= list_size (list)){
 		return NULL;
 	}

 	n = list->last;
 	for(i = 0; i < index; i++){
 		n = n->next;
 	}

 	ele = (n->info);
 	return ele;

}

/*Se devuelve el numero de nodos
que tiene una lista*/
int list_size (const List* list){
	int cont = 0;
	NodeList *aux = NULL;

	if(!list) return -1;

	/*Si aux es NULL -> lista vacia*/
	aux = list->last;
	if(!aux ){
		return 0;
	}

	cont++;

	while(aux->next != list->last){
		aux = aux->next;
		cont++;
	}

	
	return cont;
}

/*Se imprime la lista.
Debido a que tenemos una funcion list_size
y se trata de una lista circular, hemos visto
mas viable, realizar la funcion de manera
iterada*/
int list_print (FILE *fd, const List* list){
	int cont = 0;
	NodeList *aux = NULL;

	if(!list || !fd || list_isEmpty(list)) return 0;

	/*Se para en el list->last, y luego se imprime aparte el list->last*/
	for(aux = list->last->next; aux != list->last; aux = aux->next){
		cont += list->print_element_function(fd, aux->info);
	}

	cont += list->print_element_function(fd, aux->info);

	return cont;
}


