/*49017096*/

#include "../include/lista.h"
#include "../include/utils.h"
#include "../include/cola.h"
#include <assert.h>
// Implementacion de 'TCola'.
// Se debe definir en cola.cpp.
// struct _rep_cola;
// Declaración del tipo 'TCola'.
struct _rep_cola {
    TLista lst;
};

/* Operaciones de TCola */

/*
  Devuelve un elemento de tipo 'TCola' vacío (sin elementos).
 */
TCola crearCola() {
    TCola res = new _rep_cola;
    res->lst = crearLista();
    return res;
};

/*
  Devuelve 'true' si y solo si 'cola' no tiene elementos.
 */
bool esVaciaCola(TCola cola) {
    return (longitud(cola->lst) == 0);
};

/*
  Si en 'cola' hay menos de MAX (definido en utils.h) elementos encola
  'nuevo' en 'cola'. En otro caso la operación no tiene efecto.
  Devuelve 'cola'.
 */
TCola encolar(info_t nuevo, TCola cola) {
    insertar(longitud(cola->lst) + 1, nuevo, cola->lst);
};

/*
  Devuelve el frente de 'cola'.
  Precondición: 'cola' tiene elementos.
 */
info_t frente(TCola cola) {
    return infoLista(1, cola->lst);
};

/*
  Si 'cola' tiene elementos desapila el frente de 'cola'.
  En otro caso la operación no tiene efecto.
  Devuelve 'cola'.
 */
TCola desencolar(TCola c) {
    TCola res = crearCola();
    res->lst = remover(1, c->lst);
    return res;
};
