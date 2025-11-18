/* 4901709 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/pila.h"


struct _nodo {
    TInfo dato;
    _nodo *abajo;
};

typedef struct _nodo *nodo;

struct _rep_pila {
    nodo tope;
    nat cantidad;
};

TPila crearPila() { return NULL; }

void liberarPila(TPila p) {
    if(p!=NULL){
        p = desapilar(p);
        liberarPila(p);
    }
}

nat cantidadEnPila(TPila p) {
    if (p != NULL){
        return p->cantidad;
    } else return 0;
}

TPila apilar(TInfo info, TPila p) {
    nodo nodo = new _nodo;
    TInfo i = copiaInfo(info);
    nodo->dato = i;
    if (p!= NULL){
        p->cantidad = p->cantidad + 1;
        nodo->abajo = p->tope;
    } else {
        p = new _rep_pila;
        p->cantidad = 1;
        nodo->abajo = NULL;
    };
    p->tope = nodo;
    return p;
}

TInfo cima(TPila p) {
    return p->tope->dato;
}

TPila desapilar(TPila p) {
    if(p != NULL){
        if (cantidadEnPila(p) > 1){
            liberarInfo(p->tope->dato);
            nodo eliminar = p->tope;
            p->tope = p->tope->abajo;
            delete eliminar ;
            p->cantidad = p->cantidad - 1;
        } else {
            liberarInfo(p->tope->dato);
            delete p->tope;
            delete p;
            p = NULL;
        }
    }
    return p;
}
