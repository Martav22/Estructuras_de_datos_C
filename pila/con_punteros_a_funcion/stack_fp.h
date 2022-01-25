
/*

*Nombre del modulo: stack_pf.h

*Descripcion: En este modulo se define el TAD de stack usando punteros a funciones

*Autor: Marta Vaquerizo

*Fecha: 19/02/2019
*Modulos usados: node.h
*/

#ifndef STACK_H
#define STACK_H

#include "node_fp.h"

typedef struct _Stack Stack;

/* Tipos de los punteros a función soportados por la pila */
typedef void (*P_stack_ele_destroy)(void*);
typedef void* (*P_stack_ele_copy)( void*);
typedef int (*P_stack_ele_print)(FILE *, void*);
/* La función stack_ini recibirá los valores para los campos de la pila que son punteros a función, es decir, recibirá las
funciones para, respectivamente, destruir, copiar e imprimir los elementos de la pila creada*/
Stack * stack_ini (P_stack_ele_destroy f1, P_stack_ele_copy f2, P_stack_ele_print f3);
void stack_destroy(Stack *);
Status stack_push(Stack *, void *);
void * stack_pop(Stack *);
Bool stack_isEmpty( Stack *);
Bool stack_isFull( Stack *);
int stack_print(FILE*, Stack*);


#endif /* STACK_H */
