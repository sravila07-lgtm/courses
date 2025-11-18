/*49017096*/

#include "../include/utils.h"
#include "../include/lista.h"
#include "../include/pila.h"
#include <assert.h>

// Implementacion de 'TPila'.
// struct _rep_pila;
// Declaración del tipo 'TPila'.
struct _rep_pila {
    TLista lst;
};

/* Operaciones de TPila */

/*
  Devuelve un elemento de tipo 'TPila' vacío (sin elementos).
 */
TPila crearPila() {
    TPila res = new _rep_pila;
    res->lst = crearLista();
    return res;
};

/*
  Devuelve 'true' si y solo si 'pila' no tiene elementos.
 */
bool esVaciaPila(TPila pila) {
    return longitud(pila->lst) == 0;
};

/*
  Si en 'pila' hay menos de MAX (definido en utils.h) elementos apila
  'nuevo' en 'pila'. En otro caso la operación no tiene efecto.
  Devuelve 'pila'.
 */
TPila apilar(info_t nuevo, TPila p) {
    p->lst = insertar(longitud(p->lst) + 1, nuevo, p->lst);
    return p;
};

/*
  Devuelve el tope de 'pila'.
  Precondición: 'pila' tiene elementos.
 */
info_t cima(TPila p) {
    assert(!esVaciaPila(p));
    return infoLista(longitud(p->lst), p->lst);
};

/*
  Si 'pila' tiene elementos desapila el tope de 'pila'.
  En otro caso la operación no tiene efecto.
  Devuelve 'pila'.
 */
TPila desapilar(TPila pila) {
    p->lst = remover(longitud(p->lst), p->lst);
};
