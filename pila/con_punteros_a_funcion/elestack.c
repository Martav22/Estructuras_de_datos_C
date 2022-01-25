/*
*Nombre del modulo: elestack.c

*Descripcion: En este modulo se implementan las funciones de elestack

*Autor: Marta Vaquerizo

*Fecha: 7/02/2019
*Modulos usados:  elestack.h

*Mejoras pendientes: El programa funciona como se esperaba
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "elestack.h"

struct _EleStack{
    int *e;
};
extern int errno ;

/*Se inicia el elemento de la pila*/
EleStack * EleStack_ini(){
    EleStack *ele;

    ele = (EleStack*)malloc(sizeof(EleStack));
    if( ele == NULL){
        fprintf(stderr, "%s\n", strerror(errno));
        return NULL;
    }

    ele->e = (int*)malloc(sizeof(int));
    if((ele->e) == NULL){
        fprintf(stderr, "%s\n", strerror(errno));
      return NULL;
    }

    return ele;

}

/*Se libera el elemento de la pila, 
primero el objeto tipo int y
 depues el elemento como tal, 
 si ele no es NULL*/
void EleStack_destroy(EleStack *ele){
  if(ele){
    free(ele->e);
    free(ele);
  }
}

/*La informacion(void) que se pasa como argumento,
se asigna al elemento,y para ello, declaramos
una variable tipo int(ya que el elemento en 
este caso es un int), y a este se le asigna 
una copia de info. Y esa
copia es asignada al elemento*/
Status EleStack_setInfo(EleStack *ele, void *info){
    int *aux ;

    if( !ele || !info){
      return ERROR;
    }

    aux = (int*)malloc(sizeof(int));
    if(aux == NULL){
        fprintf(stderr, "%s\n", strerror(errno));
        return ERROR;
    }

    *aux = *(int*)info;
    *ele->e = *aux;
    
    if((ele->e) == NULL){
	      free(aux);
        fprintf(stderr, "%s\n", strerror(errno));
        return ERROR;
    }

    free(aux);

    return OK;

}

/*Se obtiene la informacion del 
elemento pasado por argumento, devolviendola*/
void * EleStack_getInfo(EleStack *ele){
    void *n;

    if(ele == NULL){
      return NULL;
    }

    n = (int*)malloc(sizeof(int));
    if((n) == NULL){
        fprintf(stderr, "%s\n", strerror(errno));
        return NULL;
    }

    *(int*)n = *(ele->e);
    if(n == NULL){
        free(n);
        fprintf(stderr, "%s\n", strerror(errno));
        return NULL;
    }

    return n;

}

/*Se devuelve una copia del 
elemento pasado como argumento.*/
EleStack * EleStack_copy( EleStack *ele){
    EleStack *copia;
    void *e;

    if( ele == NULL){
      return NULL;
    }

    copia = EleStack_ini();
    if( copia == NULL){
      fprintf(stderr, "%s\n", strerror(errno));
      return NULL;
    }

    e = EleStack_getInfo(ele);
    if(e == NULL){
      EleStack_destroy(copia);
       fprintf(stderr, "%s\n", strerror(errno));
      return NULL;
    }

    if( EleStack_setInfo(copia, e) == ERROR){
        EleStack_destroy(copia);
	    free(e);
        fprintf(stderr, "%s\n", strerror(errno));
        return NULL;
    }

    free(e);
    return copia;

}

/*Se comparan los dos elementos, 
que se pasan como argumento, 
viendo si son iguales*/
Bool EleStack_equals( EleStack *ele1,  EleStack *ele2){
    void *e1, *e2;

    if(!ele1 || !ele2){
      return FALSE;
    }
    e1 =  EleStack_getInfo(ele1);
    if(e1 == NULL){
      return FALSE;
    }

    e2 =  EleStack_getInfo(ele2);
    if(e2 == NULL){
      EleStack_destroy(e1);
      return FALSE;
    }

    if(*(int*)e1 != *(int*)e2){
      return FALSE;
    }

    /*Como no hemos creado un TAD
    de entero, liberamos memoria de 
    un entero directamente*/
    free(e1);
    free(e2);


    return TRUE;

}

/*Se imprime el elemento, y devuelve 
el numero de caracteres imprimidos*/
int EleStack_print(FILE *pf, EleStack *ele){
    int num;
    void *e;

    if(!pf || !ele){
      return 0;
    }

    e =  EleStack_getInfo(ele);
    if(e == NULL){
      return 0;
    }

    num = fprintf(pf, "[%d]\n", *(int*)e);

    if(!num){
        return 0;
    }

    free(e);
    return num;
}
