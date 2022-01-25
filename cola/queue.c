/*
*Nombre del modulo: queue.c

*Descripcion: En este modulo se implementan las funciones de queue

*Autor: Marta Vaquerizo

*Fecha: 26/03/2019
*Modulos usados: queue.h

*Mejoras pendientes: El programa funciona como se esperaba
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "queue.h"
#define MAXQUEUE 255

struct _Queue {
  void* items [MAXQUEUE];
  int front;
  int rear;
  destroy_element_function_type destroy_element_function;
  copy_element_function_type copy_element_function;
  print_element_function_type print_element_function;
};

/*Se inicializa la cola,
poniendo los elementos
de la misma a NULL, e inicializando
el front, el rear, y los punteros
a funcion*/
Queue* queue_ini(destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3){
    Queue *pq = NULL;
    int i;

    pq = (Queue*)malloc(sizeof(Queue));
    if(!pq){
      fprintf(stderr, "%s\n", strerror(errno));
      return NULL;
    }

    pq->front = 0;
    pq->rear = 0;
    pq->destroy_element_function = f1;
    pq->copy_element_function = f2;
    pq->print_element_function = f3;

    for(i = 0; i < MAXQUEUE; i++){
       pq->items[i] = NULL;
    }

    return pq;

}


/*Se libera la cola,
desde el front hasta el rear*/
void queue_destroy(Queue *q){
     int i;
    if(q){
      i = q->front;
      while(i != q->rear){
        q->destroy_element_function(q->items[i]);
        i = (i+1) %MAXQUEUE;
      }
      free(q);
    }

}

/*Se comprueba si la pila está vacia*/
Bool queue_isEmpty(const Queue *q){
    if(!q) return TRUE;

    if(q->rear == q->front){
        return TRUE;
    }

    return FALSE;
}

/*Se comprueba si la pila esta llena*/
Bool queue_isFull(const Queue* q){
    if(!q) return TRUE;

    if(q->front == (q->rear +1) % MAXQUEUE ){
        return TRUE;
    }
    return FALSE;

}

/*Se inserta el elemento pasado por
argumento por el rear(FIFO)*/
Status queue_insert(Queue *q, const void* pElem){
    void *ele = NULL;

    if(!q || !pElem || queue_isFull(q) == TRUE) return ERROR;

    ele  = q->copy_element_function(pElem);
    if(!ele){
      fprintf(stderr, "%s\n", strerror(errno));
      return ERROR;
    }

    q->items[q->rear] = ele;

    q->rear = (q->rear + 1) % MAXQUEUE;

    return OK;
}

/*Se extrae el primer elemento
de la cola, siguiendo la estrategia
FIFO*/
void * queue_extract(Queue *q){
   void *aux = NULL;
   if(!q || queue_isEmpty(q) == TRUE) return NULL;

   aux = q->items[q->front];

   q->items[q->front] = NULL;

   q->front = (q->front +1) % MAXQUEUE;

   return aux;

}

/*Se devuelve el numero de elementos 
de la cola, y como se puede
acceder a la estructura de datos, 
podemos implementarla asi*/
int queue_size(const Queue *q){
    if(!q) return -1;

    if(q->front <= q->rear ){
      return (q->rear - q->front);
    }
    else{
      return (MAXQUEUE - (q->front - q->rear));
    }
}

/*Se impromen todos los elementos de
la cola*/
int queue_print(FILE *pf, const Queue *q){
    int cont = 0, i, num = 0;
    if(!pf || !q) return 0;

    /*Debido a como es la salida esperada
    en el ejercicio, se usa el queue_size*/
    num = queue_size(q);

    if(num == 0){
      fprintf(pf, "Queue vacia.");
    }
    else{
      fprintf(pf, "Cola con %d elementos:\n" , num);
      i = q->front;
      while(i != q->rear){
          cont += q->print_element_function(pf, q->items[i]);
          i = (i+1) % MAXQUEUE;
      }
    }
  
    fprintf(pf, "\n" );

    return cont;

}
