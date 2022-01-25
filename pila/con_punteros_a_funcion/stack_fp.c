/*

*Nombre del modulo: stack_pf.c

*Descripcion: En este modulo se implementan las funciones de stack usando punteros a funciones

*Autor: Marta Vaquerizo

*Fecha: 19/02/2019
*Modulos usados: node.h, types.h, elestack.h, stack_ph.h

*Mejoras pendientes: El programa funciona como se esperaba
*/


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "stack_fp.h"

#define MAXSTACK 1024
#define EMPTY_STACK -1


struct _Stack{
    int top;
 	  void *item[MAXSTACK];

 	  P_stack_ele_destroy pf_destroy;
	  P_stack_ele_copy pf_copy;
	  P_stack_ele_print pf_print;

};

extern int errno ;

/*Se inicializa la pila 
usando punteros a funciones*/
Stack *stack_ini (P_stack_ele_destroy fd, P_stack_ele_copy fc, P_stack_ele_print fp) {
	 Stack *s;
	 int i;

	 s = (Stack*) malloc(sizeof(Stack));
	 if (!s) {
		 fprintf(stderr, "%s", strerror(errno));
		 return NULL;
	 }
	 /* Inicializo tope y asigno los punteros a función*/
	 s->top = -1;
	 s->pf_copy = fc;
	 s->pf_destroy = fd;
	 s->pf_print = fp;

	 /*Asigno los punteros de los elementos*/
	 for (i=0; i< MAXSTACK; i++)
	 	s->item[i] = NULL;

	 return s;
}

void stack_destroy(Stack* stc) {
 	if (!stc) return;

 	while (stc->top != EMPTY_STACK) {
 		stc->pf_destroy( stc->item[stc->top]); /* Llamada a la función cuyo
 												 puntero se almacenó como campo*/
		stc->top --;							/* de la pila, es decir, 
												utilizando el puntero a la función*/
 	}

 	free(stc);
}

/*Se comprueba si la pila
esta llena, y en ese caso, 
se devueve TRUE*/
Bool stack_isFull( Stack *s){
	if(!s){
		return TRUE;
	}
	if(s->top == MAXSTACK-1){
		return TRUE;
	}
	return FALSE;
}

/*Se comprueba si la pila
esta vacia, y en ese caso, 
se devueve TRUE*/
Bool stack_isEmpty( Stack *s){
	if(!s){
		return TRUE;
	}
	if(s->top == EMPTY_STACK){
		return TRUE;
	}
	return FALSE;
}

/*Se inserta un elemento en la 
pila en el caso de que no este 
llena y no haya problemas de 
reserva de memoria*/
Status stack_push(Stack *s, void *ele){
	void *fe;

	if(!s || !ele || stack_isFull(s) == TRUE){
		return ERROR;
	}

	(s->top)++;

	fe = s->pf_copy(ele);
	if (fe == NULL) {
        fprintf(stderr, "%s\n", strerror(errno));
        return ERROR;
  }

	s->item[s->top] = fe;

	return OK;
}

/*Se extrae el ultimo elemento 
introducido en la pila si
esta no esta vacia,
siguiendo la estrategia
LIFO */
void * stack_pop(Stack *s){
	void *ele = NULL;

	if(!s || stack_isEmpty(s) == TRUE){
		return NULL;
	}

	ele = (s->item[s->top]);

	s->item[s->top] = NULL;

	(s->top)--;

	return ele;

}

/*Se imprime la pila */
int stack_print(FILE *pf, Stack *s){
	int i, num=0;

	if(!pf || !s){
		return -1;
	}

    for (i=s->top; i>=0; i--){
        num += s->pf_print(pf, (void*)s->item[i]);
        
    }

    return num;

}
