/*
*Nombre del modulo: queuel.c

*Descripcion: En este modulo se implementan las funciones de queue

*Autor: Marta Vaquerizo

*Fecha: 26/03/2019
*Modulos usados: queuel.h

*Mejoras pendientes: El programa funciona como se esperaba
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "queuel.h"
#include "list.h"


struct _Queue {
  List *list;
};

/*Se inicializa la cola,
poniendo los elementos
de la misma a NULL, e inicializando
el front, el rear, y los punteros
a funcion*/
Queue* queue_ini(destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3, cmp_element_function_type f4){
    Queue *pq = NULL;

    pq = (Queue*)malloc(sizeof(Queue));
    if(!pq){
      fprintf(stderr, "%s\n", strerror(errno));
      return NULL;
    }

    pq->list = list_ini(f1, f2, f3, f4);
    if(!pq->list){
      queue_destroy(pq);
      return NULL;
    }
   

    return pq;

}


/*Se libera la cola,
desde el front hasta el rear, 
liberando la lista*/
void queue_destroy(Queue *q){
    if(q){
      list_destroy(q->list);
      free(q);
    }

}

/*Se comprueba si la cola está vacia*/
Bool queue_isEmpty(const Queue *q){
    if(!q) return TRUE;

    if(list_isEmpty(q->list) == TRUE){
      return TRUE;
    }

    return FALSE;
}

/*Se comprueba si la cola esta llena*/
Bool queue_isFull(const Queue* q){
    if(!q) return TRUE;
    return FALSE;

}

/*Se inserta el elemento pasado por
argumento, por el rear, por lo que
como se usa una lista circular, se 
inserta por el last*/
Status queue_insert(Queue *q, const void* pElem){

    if(!q || !pElem || queue_isFull(q) == TRUE) return ERROR;

    if(list_insertLast(q->list, pElem) == ERROR){
      return ERROR;
    }

    return OK;
}

/*Se extrae el primer elemento
de la cola, siguiendo la estrategia
FIFO, por lo que se extrae por el
first en la lista*/
void * queue_extract(Queue *q){
   void *aux = NULL;
   if(!q || queue_isEmpty(q) == TRUE) return NULL;

   aux = list_extractFirst(q->list);
   if(!aux){
    return NULL;
   }

   return aux;

}

/*Se devuelve la cantidad de 
elementos que tiene la cola*/
int queue_size(const Queue *q){
    if(!q) return -1;

    return list_size(q->list);
}

/*Se imprime la cola del front al 
rear*/
int queue_print(FILE *pf, const Queue *q){
    int cont = 0, num = 0;
    if(!pf || !q) return 0;

    num = queue_size(q);

    if(num == 0){
      fprintf(pf, "Queue vacia.");
    }
    else{
      fprintf(pf, "Cola con %d elementos:\n" , num);
      list_print(pf, q->list);
    }
  
    fprintf(pf, "\n" );

    return cont;

}
