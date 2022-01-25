/*
*Nombre del modulo: funciones.c
*Descripcion: En este modulo se implementan funciones ç
			  que hacen una copia de un entero, destruyen un entero
			  o imprimen un entero

*Autor: Marta Vaquerizo
*Fecha: 7/02/2019
*Modulos usados: funciones.h
*Mejoras pendientes: El programa funciona como se esperaba
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "funciones.h"

extern int errno ;

/*Se destruye un objeto que
guarda direcciones de entero*/
void int_destroy(void *n){
	if(n){
		free(n);
	}
}

/*Se hace una copia del 
argumento pasado, y se devuelve*/
void* int_copy(const void *n){
	int *aux = NULL;
	if(!n){
		return NULL;
	}

	aux = (int*)malloc(sizeof(int));
	if(aux == NULL){
		fprintf(stderr, "%s\n", strerror(errno));
		return NULL;
	}

	*(aux) = *((int*)n);
	
	return (void*)aux;

}

/*Se imprime el argumento pasado*/
int int_print(FILE *pf, const  void *n){
	int num = 0;

	if(!n || !pf){
		return -1;
	}

	num = fprintf(pf, "%d ", *((int*)n));

	return num;
}

/*Se comparan dos
elementos pasados
por argumento*/
int int_cmp(const void * ele1, const void *ele2){
	if(!ele1 || !ele2){
		return -2;
	}

	if( *((int*)ele1) < *((int*)ele2)){
		return -1;
	}
	else if( *((int*)ele1) > *((int*)ele2)){
		return 1;
	}
	
	return 0;

}
