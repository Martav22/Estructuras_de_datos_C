
/*
*Nombre del modulo: node_p4.c
*Descripcion: En este modulo se implementan las funciones de node
*Autor: Marta Vaquerizo
*Fecha: 7/02/2019
*Modulos usados: node_p4.h, types.h
*Mejoras pendientes: El programa funciona como se esperaba
*Modificaciones: 23/04/2019 se cambio la estructura
                 de nodo, en el sentido de que el nombre
                 se guarda con memoria dinamica, lo que 
                 produce cambios en la implementacion
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "node_p4.h"

struct _Node {
    char *name;
    int id;
};

extern int errno;
/*Se inicializa el nodo*/
Node *node_ini(char *cadena){

    Node *n;
    int size = 0;

    n = (Node*)malloc(sizeof(Node));
    if(n == NULL){
        fprintf(stderr, "%s\n", strerror(errno));
        return NULL;
    }

    size = strlen(cadena);

    n->name = (char*)malloc((size+1)*sizeof(char));
    if(n->name == NULL){
        fprintf(stderr, "%s\n", strerror(errno));
        return NULL;
    }

    return n;

}

/*Se libera la memoria reservada*/
void node_destroy(void * n){
    if(n){
        free(((Node*)n)->name);
        free(n);
    }

    return;
}

/*Se devuelve un -1
si el puntero recibido es NULL,
sino, el Id del nodo*/
int node_getId(const Node * n){

    if(n == NULL){
        return -1;
    }
    return (n->id);
}

/*Se devuelve el nombre del nodo.
declaramos un objeto tipo char, en el que vamos
a copiar el nombre guardado en n, y para
ello reservamos memoria para una cadena
de caracteres del mismo tamanio que el nombre de n*/
char *node_getName(const Node *n){
    if(!n){
        return NULL;
    }

    return n->name;

}

/*esta funcion devuleve NULL si el puntero
recibido es NULL,y sino devuelve el puntero n,
pero con id igual al
entero pasado por argumento*/
Node * node_setId(Node * n, const int id){

    if(n == NULL){
        return NULL;
    }

    (n->id) = id;
    return n;

}

/*Se devuelve NULL si el puntero recibido
es NULL,y si no devuelve el puntero n*/
Node * node_setName(Node * n, const char* name){
  
    if(n == NULL){
        return NULL;
    }

    strcpy(n->name, name);
    return n;

}


/*Se comparan los Id de los nodos pasados como argumentos*/
int node_cmp (const void * n1, const void * n2){
    if((n1 == NULL)||(n2 == NULL)){
        return 2;
    }

    if((((Node*)n1)->id) == (((Node*)n2)->id)){
        return 0;
    }
    else if((((Node*)n1)->id)<(((Node*)n2)->id)){
        return -1;
    }
    else{
        return 1;
    }
}

/*Se realiza una copia del obejto pasado como argumento*/
void * node_copy( const void * src){
    void *n;

    if(src == NULL){
        return NULL;
    }

    n = node_ini(((Node*)src)->name);
    if(n == NULL){
        return NULL;
    }

    (((Node*)n)->id) = (((Node*)src)->id);
    strcpy(((Node*)n)->name, ((Node*)src)->name);

    return n;

}

/*Se imprime los datos del nodo*/
int node_print(FILE *pf, const void * n){
    if(!pf || !n){
      return 0;
    }
    return fprintf(pf, "[%d, %s] ", (((Node*)n)->id), (((Node*)n)->name));
}
