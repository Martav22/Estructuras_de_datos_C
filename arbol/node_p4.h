
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

typedef enum {
  BLANCO, NEGRO, GRIS, ERROR_LABEL
} Label;

Node * node_ini(char *);
void node_destroy(void * n);
int node_getId(const Node * n);
char* node_getName(const Node * n);
int node_getConnect(const Node * n);
Label node_getLabel(Node*);
int node_getAntecesor(Node *n);
Node * node_setId(Node * n, const int id);
Node* node_setName(Node * n, const char* name);
Node * node_setConnect(Node * n, const int cn);
Node *node_setLabel(Node *n, Label l);
Node *node_setAntecesor(Node *n, int id);
int node_cmp (const void * n1, const void * n2);
void * node_copy(const void * src);
int node_print(FILE *pf, const void * n);

#endif /* NODE_H */
