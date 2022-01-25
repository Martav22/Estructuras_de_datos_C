/*
*Nombre del modulo: tree.c
*Descripcion: En este modulo se implementan
		    las funciones implementadas en tree.c
*Autor: Marta Vaquerizo
*Fecha: 26/03/2019
*Modulos usados: tree.h
*Mejoras pendientes: El programa funciona como se esperaba
*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "tree.h"
#include "funciones.h"

extern int errno ;

typedef struct _NodeBT {
  void* info;
  struct _NodeBT* left;
  struct _NodeBT* right;
} NodeBT;

struct _Tree {
   NodeBT *root;
   destroy_element_function_type destroy_element_function;
   copy_element_function_type copy_element_function;
   print_element_function_type print_element_function;
   cmp_element_function_type cmp_element_function;
};

/*Prototipos de las funciones privadas */
NodeBT* nodeBT_ini();
void nodeBT_destroy(Tree *t, void *n);
void tree_free_rec(Tree *t, NodeBT *n);
int tree_depth_rec(NodeBT *n);
int max_depth(int a, int b);
int tree_numNodes_rec(NodeBT *n);
Status tree_insert_rec(Tree *t, NodeBT **n, const void *pe);
Status tree_preOrder_rec(FILE *f, const Tree *t, NodeBT *n);
Status tree_inOrder_rec(FILE *f, const Tree *t, NodeBT *n);
Status tree_postOrder_rec(FILE *f, const Tree *t, NodeBT *n);
Bool tree_find_rec(Tree *t, NodeBT *n, const void* pe);

/*Inicializamos un nodo del arbol*/
NodeBT* nodeBT_ini(){
    NodeBT *n;

    n = (NodeBT*)malloc(sizeof(NodeBT));
    if(n == NULL){
      fprintf(stderr, "%s\n", strerror(errno));
      return NULL;
    }

    n->left = NULL;
    n->right = NULL;

    return n;

}

/*Destruimos un nodo del arbol, pasado
por argumento, se le pasa tambien el 
arbol para poder liberar correctamente
la informacion del nodo*/
void nodeBT_destroy(Tree *t, void *n){
    if(n){
      t->destroy_element_function(((NodeBT*)n)->info);
      free(n);
    }
}

/*Se incializa el arbol con punteros a 
funciones definidos en el .h*/
Tree* tree_ini( destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3, cmp_element_function_type f4){
    Tree *t;

    t = (Tree*)malloc(sizeof(Tree));
    if(t == NULL){
      fprintf(stderr, "%s\n", strerror(errno));
      return NULL;
    }

    t->root = NULL;
    t->destroy_element_function = f1;
    t->copy_element_function = f2;
    t->print_element_function = f3;
    t->cmp_element_function = f4;

    return t;
}

/*Se comprueba si el arbol esta vacio, 
devolviendo TRUE en ese caso, y 
FALSE, en otro*/
Bool tree_isEmpty( const Tree *pa){
    if(!pa) return TRUE;

    if(!pa->root) return TRUE;

    return FALSE;
}

/*Para liberar el arbol usamos la recursividad*/
void tree_free(Tree *pa){
    if(!pa) return;

    tree_free_rec(pa, pa->root);

    free(pa);
}

/*En esta se pasa de nodo a nodo
hasta que se llega a uno que es NULL,
y se vuelve hacia atras liberando 
cada nodo*/
void tree_free_rec(Tree *t, NodeBT *n){
    if(!n){
      return;
    }

    if(n->left){
      tree_free_rec(t, n->left);
    }
    if(n->right){
      tree_free_rec(t, n->right);
    }
    nodeBT_destroy(t, n);
}

/*A la hora de insertar tambien hemos decidido
usar recursividad*/
Status tree_insert(Tree *pa, const void *pe){
    if(!pa || !pe){
      return ERROR;
    }

    return tree_insert_rec(pa, &(pa->root), pe);

}

/*Hemos usado un doble puntero, ya que nos 
parecia mas comodo.
El elemento pasado se compara con el nodo
raiz, y se va hacia un subarbol u otro, en funcion 
de si es menor que este (hacia la izq) 
o si es mayor(hacia la derecha), y asi
sucesivamente con los nodos raiz de los
subarboles a los que accede*/
Status tree_insert_rec(Tree *t, NodeBT **n, const void *pe){
    int cmp = 0;
    if( !t || !pe){
      return ERROR;
    }

    if(!(*n) ){
        *n = nodeBT_ini();
        if(!(*n)) return ERROR;

        (*n)->info = t->copy_element_function(pe);
        if(!(*n)->info){
            fprintf(stderr, "%s\n", strerror(errno));
            nodeBT_destroy(t, *n);
            return ERROR;
        }
        return OK;
    }

    cmp = t->cmp_element_function(pe, (*n)->info);
    if(cmp < 0){
        tree_insert_rec(t, &((*n)->left), pe);
    }
    else if(cmp > 0){
        tree_insert_rec(t, &((*n)->right), pe);
    }
    return OK;

}

/*La busqueda en profundidad Pre-order, 
primero imprime el nodo, luego
se va al subarbol izq y luego al
derecho*/
Status tree_preOrder(FILE *f, const Tree *pa){
    if (!f || !pa || tree_isEmpty(pa) == TRUE) return ERROR;

    return tree_preOrder_rec(f, pa, pa->root);
}

Status tree_preOrder_rec(FILE *f, const Tree *t, NodeBT *n){
    if(!n) return OK;

    t->print_element_function(stdout, n->info);
    
    if(n->left){
      tree_preOrder_rec(f, t,  n->left);
    }
    if(n->right){
      tree_preOrder_rec(f, t,  n->right);
    }
    

    return OK;
}

/*En el caso de la profundidad in-order
primero se va al subarbol izq, luego 
se imprime y finalmente
al subarbol derecho*/
Status tree_inOrder(FILE *f, const Tree *pa){
    if(!f || !pa || tree_isEmpty(pa) == TRUE) return ERROR;

    return tree_inOrder_rec(f, pa,  pa->root);
}

Status tree_inOrder_rec(FILE *f, const Tree *t, NodeBT *n){
  if(!n) return OK;
  if(n->left){
     tree_inOrder_rec(f, t, n->left);
  }
 
  t->print_element_function(stdout, n->info);

  if(n->right){
    tree_inOrder_rec(f, t, n->right);
  }
  

  return OK;
}

/*Y por ultimo en la profundidad post-order,
primero se va al subarbol izq, luego
al derecho y finalmente se imrpime el 
nodo*/
Status tree_postOrder(FILE *f, const Tree *pa){
    if(!f || !pa) return ERROR;

    return tree_postOrder_rec(f, pa, pa->root);
}

Status tree_postOrder_rec(FILE *f, const Tree *t, NodeBT *n){
  if(!n) return OK;
  if(n->left){
    tree_postOrder_rec(f, t,  n->left);
  }
  if(n->right){
    tree_postOrder_rec(f, t, n->right);
  }
  
  t->print_element_function(stdout, n->info);

  return OK;
}

/*Se devuelve la profundidad del arbol
pasado por argumento, siendo
la profundidad de un arbol vacio = -1*/
int tree_depth(const Tree *pa){
    int depth = 0;

    if(!pa) return -1;

    depth = tree_depth_rec(pa->root);

    return depth;
}

int tree_depth_rec(NodeBT *n){
    int depth1 = 0, depth2 = 0, depth = 0;

    if(!n) return -1;

    depth1 = tree_depth_rec(n->left);
    depth2 = tree_depth_rec(n->right);

    depth = max_depth(depth1, depth2);

    return depth + 1;
}

/*Se usa para calcular el maximo*/
int max_depth(int a, int b){
    if(a < b){
      return b;
    }
    else{
      return a;
    }
}

/*Devuelve el numero de nodos que 
tiene un arbol*/
int tree_numNodes(const Tree *pa){
    if(!pa || tree_isEmpty(pa) == TRUE) return 0;

    return tree_numNodes_rec(pa->root);
}

int tree_numNodes_rec(NodeBT *n){
    int cont = 0;

    if(!n) return 0;

    cont = 1 + tree_numNodes_rec(n->left) + tree_numNodes_rec(n->right);
    return cont;
}

/*Devuelve TRUE si el elemento pasado por
argumento esta en el arbol o no*/
Bool tree_find(Tree* pa, const void* pe){
    if(!pa || !pe){
      return FALSE;
    }
    return tree_find_rec(pa, pa->root, pe);

}
Bool tree_find_rec( Tree *t, NodeBT *n, const void* pe){
    int cmp;
    if(!n) return FALSE;

    cmp = t->cmp_element_function(pe, n->info);
    if(cmp == 0){
       return TRUE;
    }
    else if(cmp < 0){
       return tree_find_rec(t, n->left, pe);
    }
    else{
      return tree_find_rec(t, n->right, pe);
    }


}
