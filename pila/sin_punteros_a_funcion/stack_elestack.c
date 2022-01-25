/*

*Nombre del modulo: stack_elestack.c

*Descripcion: En este modulo se implementan las funciones de stack

*Autor: Marta Vaquerizo

*Fecha: 19/02/2019
*Modulos usados:  stack_elestack.h

*Mejoras pendientes: El programa funciona como se esperaba
*/


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "stack_elestack.h"

#define MAXSTACK 1024
#define ELETOPE -1


struct _Stack{
    int top;
 	EleStack *item[MAXSTACK];
};

extern int errno ;

/*Se inicializa la pila, y por lo tanto,
 se ponen a NULL los elementos(nos sera util
 en posteriores funciones), y se define
el valor de tope*/
Stack * stack_ini(){
	Stack *s;
	int i;

	s = (Stack*)malloc(sizeof(Stack));
	if(s == NULL){
		fprintf(stderr, "%s\n", strerror(errno));
		return NULL;
	}

	for(i = 0; i<MAXSTACK; i++){
		s->item[i] = NULL;
	}

	s->top = ELETOPE;

	return s;

}

/*Se libera la pila*/
void stack_destroy(Stack *s){
	int i;

	if(s == NULL){
		return;
	}

	for(i = 0; i< (s->top)+1; i++){
		EleStack_destroy(s->item[i]);
	}

	free(s);
}

/*Esta funcion comprueba si la pila esta llena,
 en ese caso devuelve TRUE*/
Bool stack_isFull( Stack *s){
	if(!s){
		return TRUE;
	}
	if(s->top == MAXSTACK-1){
		return TRUE;
	}
	return FALSE;
}

/*Esta funcion comprueba si la pila esta vacia, 
en ese caso devuelve TRUE*/
Bool stack_isEmpty( Stack *s){
	if(!s){
		return TRUE;
	}
	if(s->top == ELETOPE){
		return TRUE;
	}
	return FALSE;
}

/*Se inserta el elemento, pasado como
 argumento, en la pila,  si no esta llena y 
 no da problemas de reserva de memoria*/
Status stack_push(Stack *s, EleStack *ele){
	EleStack *fe;

	if(!s || !ele || stack_isFull(s) == TRUE){
		return ERROR;
	}

	(s->top)++;    

	fe = EleStack_copy(ele);
	if (fe == NULL) {
        fprintf(stderr, "%s\n", strerror(errno));
        return ERROR;
    }

	s->item[s->top] = fe;

	return OK;
}


/*Se extrae el ultimo elemento
introducido en la pila 
si no esta vacia, siguiendo la estrategia 
LIFO*/
EleStack * stack_pop(Stack *s){
	EleStack *ele = NULL;

	if(!s || stack_isEmpty(s) == TRUE){
		return NULL;
	}

	ele = (s->item[s->top]);

	s->item[s->top] = NULL;   

	(s->top)--;   

	return ele;

}

/*Se imprime la pila, su contenido empezando
 por el ultimo elemento hasta el primero introducido*/
int stack_print(FILE *pf, Stack *s){
	int i, num=0;

	if(!pf || !s){
		return -1;
	}

    for (i=s->top; i>=0; i--){
        num += EleStack_print(pf, s->item[i]);
    }
    
    return num;

}

