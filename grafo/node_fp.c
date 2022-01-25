
/*

*Nombre del modulo: node_fp.c

*Descripcion: En este modulo se implementan las funciones de node

*Autor: Marta Vaquerizo

*Fecha: 7/02/2019
*Modulos usados: node_e4_opcional.h
*Comentarios: 
    Ultima modificacion: 16/03/2019, se modificaron la funcion:
    node_copy, y se implementaron otras:
    node_getAntecesor, node_setAntecesor

*Mejoras pendientes: El programa funciona como se esperaba
*/


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "node_fp.h"

#define NAME_L 64

struct _Node {
  char name[NAME_L];
  int id;
  int nConnect;

  Label etq;
  int antecesor_id;
};

extern int errno;

/*Se inicializa el nodo*/
Node *node_ini(){

    Node *n;

    n = (Node*)malloc(sizeof(Node));
    if(n == NULL){
        fprintf(stderr, "%s\n", strerror(errno));
        return NULL;
    }

    (n->nConnect) = 0;
    (n->etq) = BLANCO;
    (n->antecesor_id) = 0;

    return n;

}

/*Se libera la memoria reservada*/
void node_destroy(void * n){

    free(n);
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

/*declaramos un objeto tipo char, en el que vamos
a copiar el nombre guardado en n, y para
ello reservamos memoria para una cadena
de caracteres del mismo tamanio que el nombre de n*/
char *node_getName(const Node *n){

    char *name;

    if(n == NULL){
        return NULL;
    }

    name  =(char*)malloc(((strlen(n->name))+1)*sizeof(char)); /*sumamos uno para el 0 tras la cadena*/
    if(name == NULL){
        fprintf(stderr, "%s", strerror(errno));
        return NULL;
    }
    strncpy(name, (n->name), NAME_L-1);

    return name;

}

/*La funcion devuelve -1 si el puntero 
es NULL,y sino, devuelve las conexiones
 del nodo recibido*/
int node_getConnect(const Node * n){

    if(n == NULL){
        return -1;
    }

    return (n->nConnect);

}

/*Se devuelve la etiqueta del
node pasado por argumentp*/
Label node_getLabel(Node *n){
    if(!n){
      return ERROR_LABEL;
    }
    return n->etq;
}

/*Se devuelve le id del
nodo antecesor*/
int node_getAntecesor(Node *n){
    if(!n){
        return -1;
    }

    return n->antecesor_id;
}

/*Devuleve NULL si el puntero recibido
 es NULL,y sino devuelve el puntero n,
 pero con id igual al
 entero pasado por argumento*/
Node * node_setId(Node * n, const int id){

    if(n == NULL){
        return NULL;
    }

    (n->id) = id;
    return n;

}

/*Se devuelve NULL si el puntero 
recibido es NULL,y si no devuelve el puntero n*/
Node * node_setName(Node * n, const char* name){

    if(n == NULL){
        return NULL;
    }

    strncpy(n->name, name, NAME_L-1);
    return n;

}

/*Se devuelve NULL si el puntero
 recibido es NULL, y sino devuelve
el puntero n con el numero de 
conexiones igual
al pasado*/
Node * node_setConnect(Node * n, const int cn){

    if(n == NULL){
        return NULL;
    }

    (n->nConnect) = cn;
    return n;

}

/*Se actualiza el nodo pasado
por argumento ,cambiando
su etiqueta*/
Node *node_setLabel(Node *n, Label l){
      if(!n){
        return NULL;
      }

      n->etq = l;

      return n;
}

/*Se actualiza el id del antecesor
del nodo pasado por agumento*/
Node *node_setAntecesor(Node *n, int id){
    if(!n){
        return NULL;
    }

    n->antecesor_id = id;

    return n;

}

/*Se comparan los Id de los 
nodos pasados como argumentos*/
int node_cmp (const Node * n1, const Node * n2){
    if((n1 == NULL)||(n2 == NULL)){
        return 2;
    }

    if((n1->id) == (n2->id)){
        return 0;
    }
    else if((n1->id)<(n2->id)){
        return -1;
    }
    else{
        return 1;
    }
}

/*Se realiza una copia del 
objeto pasado como argumento*/
void * node_copy( void * src){
    void *n;

    if(src == NULL){
        return NULL;
    }

    n = node_ini();
    if(n == NULL){
         fprintf(stderr, "%s", strerror(errno));
        return NULL;
    }


    (((Node*)n)->id) = (((Node*)src)->id);
    strncpy(((Node*)n)->name, ((Node*)src)->name, NAME_L-1);
    (((Node*)n)->nConnect) = (((Node*)src)->nConnect);
    (((Node*)n)->etq) = (((Node*)src)->etq);
    (((Node*)n)->antecesor_id) = (((Node*)src)->antecesor_id);
    return n;

}

/*Se imprime los datos del nodo*/
int node_print(FILE *pf,  void * n){
    if(!pf || !n){
      return 0;
    }

    return fprintf(pf, "[%d, %s, %d] ", (((Node*)n)->id), (((Node*)n)->name), (((Node*)n)->nConnect));
}

