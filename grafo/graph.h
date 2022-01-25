/*

*Nombre del modulo: graph.h

*Descripcion: En este modulo se defiene el TAD de graph

*Autor: Marta Vaquerizo

*Fecha: 17/02/2019
*Modulos usados: node.h

*/
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef GRAPH_H
#define GRAPH_H
#include "node_fp.h"

#define MAX_LINE 256
#define MAXELEMENTS 4096
enum { NO_FILE_POS_VALUES = 2 };
typedef struct _Graph Graph;
/* Inicializa un grafo, reservando memoria y devolviendo la dirección del grafo
 * si lo ha hecho correctamente, o si no devuelve NULL e imprime el string
 * asociado al errorno en stderror */
Graph * graph_ini();
/* Libera la memoria dinámica reservada para el grafo */
void graph_destroy(Graph * g);
/* Se añade un nodo al grafo (reservando memoria nueva para dicho nodo) siempre
 * y cuando no hubiese ya otro nodo de igual id en el grafo. Actualiza
 * los atributos del grafo que sean necesarios. Devuelve OK o ERROR. */
Status graph_insertNode(Graph * g,  Node* n);
/* Se añade una arista entre los nodos de id "nId1" y "nId2".
 * Actualiza los atributos del grafo y de los nodos que sean necesarios.
 * Devuelve OK o ERROR. */
Status graph_insertEdge(Graph * g, const int nId1, const int nId2);
/* Devuelve una copia del nodp de id "nId" */
Node *graph_getNode (const Graph *g, int nId);
/* Actualiza el nodo del grafo que tiene el mismo id que el nodo n, con la
información de n */
Status graph_setNode (Graph *g, Node *n);
/* Devuelve la dirección de un array con los id de todos los nodos del grafo.
 * Reserva memoria para el array. */
int * graph_getNodesId (const Graph * g);
/* Devuelve el número de nodos del grafo. -1 si ha habido algún error*/
int graph_getNumberOfNodes(const Graph * g);
/* Devuelve el número de aristas del grafo. -1 si ha habido algún error*/
int graph_getNumberOfEdges(const Graph * g);
/* Determina si dos nodos están conectados*/
Bool graph_areConnected(const Graph * g, const int nId1, const int nId2);
/* Devuelve el número de conexiones del nodo de id fromId */
int graph_getNumberOfConnectionsFrom(const Graph * g, const int fromId);
/* Devuelve la dirección de un array con los id de todos los nodos del grafo.
 * Reserva memoria para el array. */
int* graph_getConnectionsFrom( Graph * g, const int fromId);
/* Imprime en el flujo pf los datos de un grafo, devolviendo el número de
caracteres impresos.
Programación II – Práctica 1
9
 * Comprueba si ha habido errorres en el flujo de salida. Si es así imprime
mensaje
 * de error en stderror y devuelve el valor -1.
 * El formato a seguir es: imprimir una linea por nodo con la información asociada
al nodo y
 * los id de sus conexiones. La salida para el grafo del ejercicio 2.3 de la parte
1 es:
 * [1, a, 2] 2 3
 * [2, b, 2] 1 3
 * [3, c, 2]] 1 2 */
int graph_print(FILE *pf,  Graph * g);
/* Lee de un flujo de entrada la información asociada a un grafo */
Status graph_readFromFile (FILE *fin, Graph *g);
Node *graph_findDeepSearch (Graph *g, int from_id, int to_id);
#endif /* GRAPH_H */
