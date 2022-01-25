
/*
*Nombre del modulo: graph.c

*Descripcion: En este modulo se implementan las funciones de graph

*Autor: Ana Calzada

*Fecha: 17/02/2019
*Modulos usados: graph.h, stack_fp.h
*Comentarios: 
    Modificado por ultima vez el 16/03/2019 para realizar 
    la funcion de busqueda en profundidad
*Mejoras pendientes: El programa funciona como se esperaba
*/


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "graph.h"
#include "stack_fp.h"

struct _Graph{
    Node *nodes[MAXELEMENTS];
    int num_nodes;
    int numconnections;
    int connections[MAXELEMENTS][MAXELEMENTS];
};

extern int errno ;

int find_node_index(const Graph * g, int nId1);
int* graph_getConectionsIndex( Graph * g, int index) ;
Node *graph_findDeepSearch (Graph *g, int from_id, int to_id);

/*Busca el nodo con el Id pasado como argumento 
y devuelve la posicion del mismo en el
array node[MAXELEMENTS]*/
int find_node_index(const Graph *g, int nId1) {
   int i;

   if (!g) {
     return 0;
   }

   for(i=0; i < g->num_nodes; i++) {
      if (node_getId (g->nodes[i]) == nId1) return i;
   }

   return -1;
}

/*Se inicializa un grafo, poniendo a NULL
 las direcciones de cada nodo del array, y a 0
la matriz de adyacencia*/
Graph * graph_ini(){
    Graph *g;
    int i, j;

    g = (Graph*)malloc(sizeof(Graph));
    if(g == NULL){
        fprintf(stderr, "%s\n", strerror(errno));
        return NULL;
    }

    for(i = 0; i<MAXELEMENTS; i++){
        (g->nodes[i])=NULL;
    }

    for (i = 0; i<MAXELEMENTS; i++){
        for (j = 0; j<MAXELEMENTS; j++) {
            g->connections[i][j] = 0;
        }
    }

    (g->num_nodes) = (g->numconnections) = 0;

    return g;
}

/*Se libera el grafo*/
void graph_destroy(Graph * g){
    int i;
    if(g){

      for(i = 0; i < g->num_nodes; i++){
        free(g->nodes[i]);
      }

      free(g);
    }
    
}

/*Se inserta un nodo en el grafo, 
en caso de que no este ya en el grafo*/
Status graph_insertNode(Graph * g,  Node* n){
    int i;

    if(!g || !n) {
        return ERROR;
    }

    for(i=0; i < (g->num_nodes); i++){
        if(!(node_cmp(n, g->nodes[i]))){
            return ERROR;
        }
    }

    g->nodes[i] = node_copy(n);
    if(g->nodes[i] == NULL){
        fprintf(stderr, "%s\n", strerror(errno));
        return ERROR;
    }

    (g->num_nodes)++;

    return OK;
}

/*Se inserta una arista entre el nodo, 
con nId1, y el nodo, con nId2 */
Status graph_insertEdge(Graph * g, const int nId1, const int nId2){
    int i, j;

    if(g == NULL){
        return ERROR;
    }

    i = find_node_index(g, nId1);     
    j = find_node_index(g, nId2);

    if(i == -1 || j == -1){
        return ERROR;
    }

    g->connections[i][j] = 1;      
    
    (g->numconnections)++;
    node_setConnect(g->nodes[i], node_getConnect(g->nodes[i]) + 1);

    return OK;
}

/*Devuelve el nodo con el Id pasado como argumento.*/
Node *graph_getNode (const Graph *g, int nId){
    Node *n;
    int index;

    if(g == NULL){
        return NULL;
    }

    index = find_node_index(g, nId);     
    if(index == -1){                    
        return NULL;
    }

    n = node_copy(g->nodes[index]);   
    if(n == NULL){
        fprintf(stderr, "%s\n", strerror(errno));
        return NULL;
    }

    return n;
}

/*Se actualiza el estado del nodo que tiene
 el mismo Id que n y se pone la informacion de n*/
Status graph_setNode (Graph *g,  Node *n){
    int index;

    if(g == NULL){
        return ERROR;
    }

    index = find_node_index(g, node_getId(n));
    if(index == -1){
        return ERROR;
    }

    node_destroy(g->nodes[index]);

    (g->nodes[index]) = node_copy(n);
    if((g->nodes[index]) == NULL){
        fprintf(stderr, "%s\n", strerror(errno));
        return ERROR;
    }

    return OK;
}
/*Devuelve un array con el Id de cada
 nodo del grafo, en la misma posicion
 en la que estan los nodos en el grafo*/
int * graph_getNodesId (const Graph * g){
    int *array;
    int i;

    if(g == NULL){
        return NULL;
    }

    array = (int*)malloc((g->num_nodes)*sizeof(int));  
    if(array == NULL){
        fprintf(stderr, "%s\n", strerror(errno));
        return NULL;
    }

    for(i = 0; i<(g->num_nodes); i++){
        array[i] = node_getId(g->nodes[i]);        
        if(array[i] == -1){
            free(array);
            return NULL;
        }
    }

    return array;
}

/*Se obtiene el numero de nodos que tiene un grafo*/
int graph_getNumberOfNodes(const Graph * g){

    if (g == NULL)
        return -1;

    return (g->num_nodes);
}

/*Devuelve el numero de aristas/conexiones entre nodos*/
int graph_getNumberOfEdges(const Graph * g) {

    if (g == NULL)
        return -1;

    return (g->numconnections);
}
/*Se mira si dos nodos estan conectados*/
Bool graph_areConnected(const Graph * g, const int nId1, const int nId2){
    int index1, index2;

    if (g == NULL){
        return FALSE;
    }

    index1 = find_node_index(g, nId1);   
    index2 = find_node_index(g, nId2);   

    if(index1 == -1 || index2 == -1){
        return FALSE;
    }

    /*Debido a que es un grafo dirigido,
     solo se mira si va en un sentido la conexion*/
    if ((g->connections)[index1][index2] == 0){   
        return FALSE;
    }
    else{
        return TRUE;
    }
}

/*Se pasa un Id, y se busca las conexiones,
 que tiene el nodo con ese id en el grafo*/
int graph_getNumberOfConnectionsFrom(const Graph * g, const int fromId) {
    int index;

    if (g == NULL)
        return -1;

    index = find_node_index(g, fromId);
    if(index == -1)
        return -1;

    return node_getConnect(g->nodes[index]);  
}

/*Se devuelve la direccion de un array 
con las conexiones que tiene el nodo en 
la posicion del array pasada como
argumento*/
int* graph_getConectionsIndex(Graph * g, int index) {
     int *array = NULL, i, j=0, size;

    if (!g) return NULL;
    if (index < 0 || index > g->num_nodes) return NULL;

     /* get memory for the array with the connected nodes index*/

    size = node_getConnect (g->nodes[index]);
    array = (int *) malloc(size*sizeof(int) );
    if (!array) {
     /* print errorr message*/
        fprintf (stderr, "%s\n", strerror(errno));
        return NULL;
     }

     /*asigno valores al array con los indices de los nodos conectados*/
    for(i = 0; i< g->num_nodes; i++) {
      if (g->connections[index][i] == TRUE) {
         array[j] = i;
         j++;
      }
    }
     
     return array;
}

/*Se devuelve la direccion de un array
 con los ids de los nodos que estan 
 conectados al nodo con el Id pasado 
 como argumento*/
int* graph_getConnectionsFrom(Graph * g, const int fromId) {
    int n, *array, index, i, id, indice;

    if (!g)
        return NULL;

    n = graph_getNumberOfConnectionsFrom(g, fromId);
    if(n == -1)
        return NULL;

    index = find_node_index(g, fromId);
    if(index == -1){
      return NULL;
    }

    array = graph_getConectionsIndex(g, index);
    if(array == NULL){
      fprintf(stderr, "%s\n", strerror(errno));
      return NULL;
    }
        
    for(i = 0; i< n; i++){
        indice = array[i];

        id = node_getId(g->nodes[indice]);
        if(id == -1){
            fprintf(stderr, "%s\n", strerror(errno));
            return NULL;
        }
        array[i] = id;        
    }

    return array;
}
/*Se imprime en grafo de la siguiente manera: 
 [nombre del nodo, Id, Conexiones] Ids de los
 nodo con los que tiene conexion*/
int graph_print(FILE *pf, Graph * g) {
    int i, j, retorno=0, *array = NULL, num;
    char *name;

    if (pf == NULL || g == NULL)
        return 0;

    for (i = 0; i < g->num_nodes; i++) {
        name = node_getName(g->nodes[i]);
        if(name == NULL){
            return 0;
        }

        retorno += fprintf(pf, "\n[%s, %d, %d] ", name, node_getId(g->nodes[i]), node_getConnect(g->nodes[i]));

        array = graph_getConnectionsFrom(g, node_getId(g->nodes[i]));
        if(array == NULL){
            free(name);
            return 0;
        }

        num = graph_getNumberOfConnectionsFrom(g, node_getId(g->nodes[i]));
        if(num == -1){
            free(name);
            free(array);
            return 0;
        }

        for (j = 0; j < num; j++){
            retorno += fprintf(pf, " %d ", array[j]);
        }

        free(name);    
        free(array);
    }
    printf("\n");

    return retorno;
}

/*Sirve para leer un grafo que esta en un archivo de texto*/
Status graph_readFromFile (FILE *fin, Graph *g) {
     Node *n;
     char buff[MAX_LINE], name[MAX_LINE];
     int i, nnodes = 0, id1, id2;
     Status flag = ERROR;

     /* read number of nodes*/
     if ( fgets (buff, MAX_LINE, fin) != NULL)
     if ( sscanf(buff, "%d", &nnodes) != 1) return ERROR;

     /* init buffer_node*/
     n = node_ini();
     if (!n) return ERROR;


     /*read nodes line by line*/
     for(i=0; i < nnodes; i++) {
      if ( fgets(buff, MAX_LINE, fin) != NULL)
        if (sscanf(buff, "%d %s", &id1, name) != NO_FILE_POS_VALUES) break;

      /* set node name and node id*/
      node_setName (n, name);
      node_setId (n, id1);

      /* insert node in the graph*/
      if ( graph_insertNode (g, n) == ERROR) break;
     }

     /* Check if all node have been inserted*/
     if (i < nnodes) {
      node_destroy(n);
      return ERROR;
     }

     /* read connections line by line and insert it*/
     while ( fgets(buff, MAX_LINE, fin) ) {
      if ( sscanf(buff, "%d %d", &id1, &id2) == NO_FILE_POS_VALUES )
        if (graph_insertEdge(g, id1, id2) == ERROR)
          break;
     }

     /* check end of file*/
     if (feof(fin)) flag = OK;

     /* clean up, free resources*/
     node_destroy (n);
     return flag;
}

/*Se devuelve el nodo destino tras haber 
empezado desde el nodo inicio. 
La funcion se basa en :
meter el nodo inicio en una pila auxiliar,
e ir sacando nodos de la pila,
ver si se ha visitado (etiqueta negra)
o si es el nodo destino, ver sus vecinos, 
y repetir el proceso*/
Node *graph_findDeepSearch (Graph *g, int from_id, int to_id){

    Stack *s = NULL;
    void *n1 = NULL;
    void *n = NULL;
    int *arrayids = NULL;
    int i, numconex, id;
    Node *vecino = NULL;
    Label label;

    
    if( !g){
      return NULL;
    }

    s = stack_ini(node_destroy, node_copy, node_print);
    if(!s){
      fprintf(stderr, "%s\n", strerror(errno));
      return NULL;
    }

    n = graph_getNode (g, from_id);
    if(!n){
      stack_destroy(s);
      fprintf(stderr, "%s\n", strerror(errno));
      return NULL;
    }

    if(stack_push(s, n) == ERROR){
      stack_destroy(s);
      node_destroy(n);
      fprintf(stderr, "%s\n", strerror(errno));
      return NULL;
    }

    node_destroy(n);
    
    n = graph_getNode (g, to_id);
    if(!n){
      stack_destroy(s);
      fprintf(stderr, "%s\n", strerror(errno));
      return NULL;
    }

    while( stack_isEmpty(s) == FALSE){
        n1 = stack_pop(s);

        label = node_getLabel((Node*)n1);
        if(label == ERROR_LABEL){
          stack_destroy(s);
          node_destroy(n1);
          node_destroy(n);
          fprintf(stderr, "%s\n", strerror(errno));
          return NULL;
        }

        if( label == BLANCO){
          /*Sabemos que n1 no es NULL, 
          y por eso no se hace control 
          de errores en node_setLabel*/ 
          node_setLabel((Node*)n1, NEGRO);

          if(graph_setNode(g, n1) == ERROR){
            stack_destroy(s);
            node_destroy(n1);
            node_destroy(n);
            fprintf(stderr, "%s\n", strerror(errno));
            return NULL;
          }

          /*node_getId devuelve NULL 
          si n1 es NULL, por eso
          no hacemos control de errores*/
          id = node_getId((Node*)n1); 

          numconex = graph_getNumberOfConnectionsFrom( g,  id);
          if(numconex == -1){
            stack_destroy(s);
            node_destroy(n1);
            node_destroy(n);
            fprintf(stderr, "%s\n", strerror(errno));
            return NULL;
          }
          
          arrayids = graph_getConnectionsFrom(g, id);
          if(!arrayids){
            stack_destroy(s);
            node_destroy(n1);
            node_destroy(n);
            fprintf(stderr, "%s\n", strerror(errno));
            return NULL;
          }
        
          for(i = 0; i < numconex ; i++){
            id = arrayids[i];

            vecino = graph_getNode (g, id);
            if(!vecino){
              stack_destroy(s);
              node_destroy(n1);
              node_destroy(n);
              fprintf(stderr, "%s\n", strerror(errno));
              return NULL;
            }

            if( node_cmp(vecino, n) == 0){
              node_destroy(n);
              stack_destroy(s);
              node_destroy(n1);
              free(arrayids);
              return vecino;
            }
            else if(node_getLabel(vecino) == BLANCO){
                if(stack_push(s, (void*)vecino) == ERROR){
                  stack_destroy(s);
                  node_destroy(n1);
                  node_destroy(n);
                  node_destroy((void*)vecino);
                  free(arrayids);
                  fprintf(stderr, "%s\n", strerror(errno));
                  return NULL;
                }
            }
            node_destroy((void*)vecino);
          }
        }
        node_destroy((void*)n1);
        free(arrayids);
    }

    stack_destroy(s);
    node_destroy(n);
    return NULL;

}
