
/*

*Nombre del modulo: node.c

*Descripcion: En este modulo se implementan las funciones de node

*Autor: Marta Vaquerizo

*Fecha: 7/02/2019
*Modulos usados: node.h

*Mejoras pendientes: El programa funciona como se esperaba
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "node.h"

#define MAXCARACTER 128

struct _Node{
    char name[MAXCARACTER];
    int id;
    int nConnect;
};

extern int errno ;

/*Se inicializa el nodo*/
Node *node_ini(){

    Node *n;

    n = (Node*)malloc(sizeof(Node));
    if(n == NULL){
        fprintf(stderr, "%s\n", strerror(errno));
        return NULL;
    }

    (n->nConnect) = 0;

    return n;

}

/*Se libera el nodo*/
void node_destroy(Node * n){
    if(n){
        free(n);
    }
    
    return;
}

/*Se devuelve el Id del nodo*/
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

    name = (char*)malloc(((strlen(n->name))+1)*sizeof(char)); 
    if(name == NULL){
        fprintf(stderr, "%s\n", strerror(errno));
        return NULL;
    }
    strncpy(name, (n->name), MAXCARACTER-1);

    return name;

}

/*Se devuelve las conexiones del nodo recibido*/
int node_getConnect(const Node * n){

    if(n == NULL){
        return -1;
    }
                             
    return (n->nConnect);    

}

/*Se devuelve el puntero recibido 
por argumento con el Id cambiado*/
Node * node_setId(Node * n, const int id){

    if(n == NULL){         
        return NULL;     
    }                   
                        
    (n->id) = id;         
    return n;

}

/*Se devuelve el puntero recibido por 
argumento con el nombre cambiado*/
Node * node_setName(Node * n, const char* name){

    if(n == NULL){
        return NULL;               
    }                              
                                   
    strncpy(n->name, name, MAXCARACTER-1);         
    return n;

}

/*Se devuelve el puntero recibido por 
argumento con el numero de conexiones cambiado*/
Node * node_setConnect(Node * n, const int cn){

    if(n == NULL){
        return NULL;              
    }                             
                                  
    (n->nConnect) = cn;          
    return n;                    

}

/*Se comparan los Id's de los nodos pasados como argumento*/
int node_cmp (const Node * n1, const Node * n2){
    if((n1 == NULL) || (n2 == NULL)){
        return 2;
    }                               
                                    
    if((n1->id) == (n2->id)){         
        return 0;                   
    }
    else if((n1->id) < (n2->id)){     
        return -1;
    }
    else{                          
        return 1;
    }
}

/*Se devuelve una copia del nodo pasado como argumento*/
Node * node_copy(const Node * src){
    Node *n;

    if(src == NULL){           
        return NULL;         
    }

    n = node_ini();
    if(n == NULL){      
        fprintf(stderr, "%s\n", strerror(errno));       
        return NULL;         
    }                        
    

    (n->id) = (src->id);           
    strncpy(n->name, src->name, MAXCARACTER-1);  
    (n->nConnect) = (src->nConnect);

    return n;

}

/*Se imprimen los datos del nodo pasado como argemnto*/
int node_print(FILE *pf, const Node * n){
    if(!pf || !n){
      return 0;
    }
    return fprintf(pf, "[%d, %s, %d] ", (n->id), (n->name), (n->nConnect));
}
