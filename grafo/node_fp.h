
/*

 * Nombre del modulo: node_fp.h
 * Descripcion: se definen los prototipos de las funciones de node usando punteros a funciones
 * Author: Marta Vaquerizo
 * Fecha: 5/02/2019
 * Modulos usados:  types.h

 */

#ifndef NODE_E4_H
#define NODE_E4_H

#include "types.h"

typedef struct _Node Node;

typedef enum {
  BLANCO, NEGRO, ERROR_LABEL
} Label;

Node * node_ini();
void node_destroy(void * n);
int node_getId(const Node * n);
char* node_getName(const Node * n);
int node_getConnect(const Node * n);
Label node_getLabel(Node*);
int node_getAntecesor(Node *n);
Node * node_setId(Node * n, const int id);
Node * node_setName(Node * n, const char* name);
Node * node_setConnect(Node * n, const int cn);
Node *node_setLabel(Node *n, Label l);
Node *node_setAntecesor(Node *n, int id);
int node_cmp (const Node * n1, const Node * n2);
void * node_copy( void * src);
int node_print(FILE *pf,  void * n);
int node_printantecesor(FILE *pf, Node *n);

#endif /* NODE_E4_H */
