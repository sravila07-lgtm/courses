/*
  Módulo de definición de 'TIterador'.

  Los elementos de tipo 'TIterador' son estructuras para recorrer colecciones
  de elementos de tipo 'nat'.
  Tiene implcícita una posición actual.

  La vida de un 'TIterador' tiene dos fases: en la primera se le puede agregar
  elementos pero no se puede recorrer; luego de que se reinicia se puede
  recorrer tantas veces como sea pero no se puede agregar elementos.

  La posición actual no está definida en la fase inicial ni, en la segunda,
  si la colección es vacía o si se avanza cuando la posición es la última.

  Seudocódigo de una recorrida de un iterador:
  reiniciar
  mientras la posición actual está definida
    procesar el elemento definido por la posición actual
    avanzar

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */


#include "../include/utils.h"
#include "../include/iterador.h"
#include "../include/cadena.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

 // Representación de 'TIterador',
 // Se debe definir en iterador.cpp
 // struct _rep_iterador;
 // Declaración del tipo 'TIterador'
struct _rep_iterador{
//    nat n;
//    TIterador sig;
};

/*
  Crea un 'TIterador' vacío (sin elementos) cuya posición actual no está
  definida.
  Se le puede agregar elementos.
  El tiempo de ejecución en el peor caso es O(1).
 */
TIterador crearIterador() {
/*    TIterador iter = new _rep_iterador;
    iter = NULL;
    return iter;*/
    return NULL;
}

/*
  Agrega 'elem' al final de 'iter' si y solo si nunca se reinicio.
  Devuelve 'iter'.
  La posición actual sigue indefinida.
  El tiempo de ejecución en el peor caso es O(1).
 */
TIterador agregarAIterador(nat elem, TIterador iter) {
/*    TIterador nav = iter;
    if (nav == NULL) {
        nav = new _rep_iterador;
        nav->n = elem;
        nav->sig = crearIterador();
    }
    else { nav = nav->sig; };
    return iter;*/
    return NULL;
}

/*
  Mueve la posición actual de 'iter' al primero si y solo si 'iter' tiene
  elementos.
  Devuelve 'iter'.
  No se podrán agregar más elementos (aunque no hubiera ninguno).
  El tiempo de ejecución en el peor caso es O(1).
 */
TIterador reiniciarIterador(TIterador iter) {
    return NULL;
}

/*
  Avanza la posición actual de 'iter' hacia el siguiente si y solo si'
  estaDefinidaActual(iter).
  Devuelve 'iter'.
  Si la posición actual es la última posición entonces la posición actual
  queda indefinida.
  El tiempo de ejecución en el peor caso es O(1).
 */
TIterador avanzarIterador(TIterador iter) {
    return NULL;
}

/*
  Devuelve el elemento de la posición actual de 'iter'.
  Precondición: estaDefinidaActual(iter).
  El tiempo de ejecución en el peor caso es O(1).
 */
nat actualEnIterador(TIterador iter) {
    return 0;
}

/*
  Devuelve 'true' si y solo si la posición actual de 'iter' está definida.
  El tiempo de ejecución en el peor caso es O(1).
 */
bool estaDefinidaActual(TIterador iter) {
    return false;
}

/*
  Libera la memoria asignada a 'iter'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad
  de elementos de 'iter'.
 */
void liberarIterador(TIterador iter) {
}