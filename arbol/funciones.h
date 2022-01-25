/*

 * Nombre del modulo: funciones.h
 * Descripcion: se definen los prototipos de las funciones de elestack
 * Author: Marta Vaquerizo
 * Fecha: 19/02/2019
 * Modulos usados: node.h, types.h
*/


#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "types.h"

void int_destroy(void *);
	
void* int_copy(const void *);

int int_print(FILE *, const void *);

int int_cmp(const void *, const void *);

#endif /* FUNCIONES_H */
