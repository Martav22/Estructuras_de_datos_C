
/* 

 * Nombre del modulo: node.h
 * Descripcion: se definen los prototipos de las funciones de node
 * Author: Marta Vaquerizo
 * Fecha: 5/02/2019
 * Modulos usados: node.h, types.h
 
 */

#ifndef NODE_H
#define NODE_H

#include "types.h"

typedef struct _Node Node;

Node * node_ini();
void node_destroy(Node * n);
int node_getId(const Node * n);
char* node_getName(const Node * n);
int node_getConnect(const Node * n);
Node * node_setId(Node * n, const int id);
Node * node_setName(Node * n, const char* name);
Node * node_setConnect(Node * n, const int cn);
int node_cmp (const Node * n1, const Node * n2);
Node * node_copy(const Node * src);
int node_print(FILE *pf, const Node * n);

#endif /* NODE_H */

