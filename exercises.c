#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "arraylist.h"
#include "stack.h"

//#include "exercises.h"

//Funciones auxiliares que puedes utilizar para debuggear tus ejercicios
//NO MODIFICAR
void imprime_lista(List *L) {
   int *dato;
   dato = (int*)first(L);
   printf("[");
   while(dato != NULL) {
      printf("%d ", *dato);
      dato = (int*)next(L);
   }
   printf("]\n");

}

//Ojo que la pila se vacía al imprimir y se imprime en orden inverso
//NO MODIFICAR
void imprime_y_vacia_pila(Stack *P) {
   void *dato;
   printf("[");
   while((dato = pop(P)) != NULL) {
      printf("%d ", *(int*)dato);
   } 
   printf("]\n");
}

/* 
Ejercicio 1.
Crea una Lista y agrega punteros a elementos del 1 al 10.
Recuerda que la lista almacena punteros, por lo que
debes reservar memoria para cada elemento que agregues.
Al finalizar retorna la lista creada.
*/

List* crea_lista() {
   List* L = create_list();
   int i;
   for (i = 1; i <= 10; i++) {
       int* num = (int*)malloc(sizeof(int)); // reservo la mem para cada elemento
       *num = i;
       pushBack(L, num); // pushback porque sino la lista quedaria  10,9,8,7,6,5,4,3,2,1 entonces con pushback quedaria 1,2,3,4,5,6,7,8,9,10
   }
   return L; //retorno la lista 
}

/*
Ejercicio 2.
Crea una función que reciba una lista de enteros (int*) y 
retorne la suma de sus elementos.
*/
int sumaLista(List *L) {
   int suma = 0;
   int *dato = (int*)first(L);
   while (dato != NULL) {    //mientras la lista no termine entonces...
       suma += *dato;   // a la sumatoria le sumo el dato actual
       dato = (int*)next(L); // avanzo al siguente dato
   }
   return suma; //retorno la suma total
}

/*
Ejercicio 3.
Crea una función que reciba una lista de punteros a int (int*) y
un entero elem. La función debe eliminar todos los elementos 
de la lista que sean iguales a elem.
Asume que popCurrent luego de eliminar un elemento se
posiciona en el elemento anterior.
*/

void eliminaElementos(List *L, int elem) {
   int *dato = first(L);
   while (dato != NULL) { 
       if (*dato == elem) {
           popCurrent(L); 
       }
       dato = next(L); 
   }
}


/*
Ejercicio 4.
La función copia los punteros de la pila P1 en la pila P2.
El orden de ambas pilas se debe mantener.
Puedes usar una pila auxiliar.
*/

void copia_pila(Stack* P1, Stack* P2) {
   Stack* aux = create_stack();
   void* dato;


   while ((dato = pop(P1)) != NULL) {
       push(aux, dato); // paso los datos a la aux (se invierte)
   }

   while ((dato = pop(aux)) != NULL) {
       push(P1, dato); // como ya esta invertida al devolverla a p1 y p2 en caso de p1 vuelve a la normalidad
       push(P2, dato); // y en caso de p2 queda igual a p1
   }

   free(aux); //limpio la aux
}

/*
Ejercicio 5.
La función verifica si la cadena de entrada tiene sus 
paraéntesis balanceados. Retorna 1 si están balanceados,
0 en caso contrario.
*/

int parentesisBalanceados(char *cadena) {
   Stack* P = create_stack();
   int i; 

   for (i = 0; cadena[i] != '\0'; i++) {
       if (cadena[i] == '(' || cadena[i] == '{' || cadena[i] == '[') {
           char *p = (char*)malloc(sizeof(char)); 
           *p = cadena[i]; 
           push(P, p);
       } else if (cadena[i] == ')' || cadena[i] == '}' || cadena[i] == ']') {
           char *topElem = (char*)pop(P);
           if (topElem == NULL) {
               free(P);
               return 0;
           }

           if ((cadena[i] == ')' && *topElem != '(') ||
               (cadena[i] == '}' && *topElem != '{') ||
               (cadena[i] == ']' && *topElem != '[')) {
               free(topElem);
               free(P);
               return 0; //no hay balace
           }
           free(topElem);
       }
   }


   if (top(P) != NULL) { //si quedan es porq no esta balanceado
       free(P); 
       return 0;
   }

   free(P); 
   return 1; 
}
