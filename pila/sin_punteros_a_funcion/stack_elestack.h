/*

*Nombre del modulo: stack_elestack.h

*Descripcion: En este modulo se define el TAD de stack

*Autor: Marta Vaquerizo

*Fecha: 19/02/2019
*Modulos usados: node.h, types.h, elestack.h
*/

#ifndef STACK_H
#define STACK_H

#include "elestack_node.h"

typedef struct _Stack Stack;

/**------------------------------------------------------------------
Inicializa la pila reservando memoria. Salida: NULL si ha habido error o el puntero a la pila si ha ido bien
------------------------------------------------------------------*/
Stack * stack_ini();
/**------------------------------------------------------------------
Elimina la pila Entrada: puntero a la pila que se desea eliminar
------------------------------------------------------------------*/
void stack_destroy(Stack *);
/**------------------------------------------------------------------
Inserta un elemento en la pila. Entrada: elemento a insertar y pila donde insertarlo. Salida: OK si logra insertarlo o ERROR
si no.
------------------------------------------------------------------*/
Status stack_push(Stack *,  EleStack *);
/**------------------------------------------------------------------
Extrae un elemento de la pila. Entrada: la pila de donde extraerlo. Salida: NULL si no logra extraerlo, o el elemento
extraído si lo logra. Nótese que la pila quedará modificada.
------------------------------------------------------------------*/
EleStack * stack_pop(Stack *);
/**------------------------------------------------------------------
Comprueba si la pila esta vacía. Entrada: puntero a la pila. Salida: TRUE si está vacía o FALSE si no lo esta
------------------------------------------------------------------*/
Bool stack_isEmpty( Stack *);
/**------------------------------------------------------------------
Comprueba si la pila esta llena. Entrada: puntero a la pila. Salida: TRUE si está llena o FALSE si no lo esta
------------------------------------------------------------------*/
Bool stack_isFull( Stack *);
/**------------------------------------------------------------------
Imprime toda la pila, comenzando por el último elemento insertado (aquel en la cima o tope) y terminando por el primero
que se insertó. Imprime un elemento por línea. Entrada: pila y fichero abierto donde imprimir. Salida: número de
caracteres escritos en total.
------------------------------------------------------------------*/
int stack_print(FILE*, Stack*);


#endif /* ELESTACK_H */
