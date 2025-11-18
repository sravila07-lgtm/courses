/* 4901709 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/cola.h"

struct _nodo{
    TInfo dato;
    _nodo *siguiente;
};

struct _rep_cola {
    _nodo *primero;
    _nodo *ultimo;
    nat cantidad;
};

typedef struct _nodo *TNodo;

TCola crearCola() { return NULL; }

void liberarCola(TCola c) {
    if (c != NULL){
        c = desencolar(c);
        liberarCola(c);
    }
}

nat cantidadEnCola(TCola c) {
    if (c != NULL){
        return c->cantidad;
    } else return 0;
}

TCola encolar(TInfo info, TCola c) {
    if (c != NULL){
        TNodo nodo = new _nodo;
        TInfo i = copiaInfo(info);
        nodo->dato = i;
        nodo->siguiente = NULL;
        c->cantidad = c->cantidad + 1;
        c->ultimo->siguiente = nodo;
        c->ultimo = nodo;
    } else {
        TNodo nodo = new _nodo;
        nodo->siguiente = NULL;
        TInfo i = copiaInfo(info);
        nodo->dato = i;
        TCola res = new _rep_cola;
        c = res;
        c->primero = nodo;
        c->ultimo = nodo;
        c->cantidad = 1;
    }
    return c;
}

TInfo frente(TCola c) {
    return c->primero->dato;
}

TCola desencolar(TCola c) {
    if (c!=NULL) {
        if(c->cantidad > 1){
            liberarInfo (c->primero->dato);
            TNodo eliminar = c->primero;
            c->primero = c->primero->siguiente;
            delete eliminar;
            c->cantidad = c->cantidad - 1;
        } else {
            liberarInfo(c->primero->dato);
            delete c->primero;
            delete c;
            c = NULL;
        }
    }
    return c;
}
