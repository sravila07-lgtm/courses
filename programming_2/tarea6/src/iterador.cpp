/* 4901709 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/iterador.h"

struct nodo{//test31
  nat natural;
	nodo *siguiente;	
};

struct _rep_iterador {//test31
  nodo *primero;//para reiniciar
  nodo *actual;//donde estoy
  nodo *ultimo;
};

TIterador crearIterador() {//test31
  TIterador res = new _rep_iterador;
  res->primero = NULL;
  res->ultimo = res->primero;
  res->actual = NULL;
  return res;
}

void liberarIterador(TIterador iter) {//test31
  if (iter->primero != NULL){//vacio si primero es null
  nodo *aux;
  aux = iter->primero;
  while(aux->siguiente != NULL){
    nodo *borrar = aux;
    aux = aux->siguiente;
    delete borrar;
  };
  delete aux;//cubre la salida del while y el caso de 1 solo
  };
  delete iter;
}

bool estaDefinidaActual(TIterador iter) {//test31
  return iter->actual != NULL;
}

void agregarAIterador(nat elem, TIterador const iter) {//test32
  if(iter->primero != NULL){
    nodo *nuevo = new nodo;
    iter->ultimo->siguiente = nuevo;
    iter->ultimo->siguiente->natural = elem;
    iter->ultimo = iter->ultimo->siguiente;//redefino ultimo
    iter->ultimo->siguiente = NULL;//el ultimo tiene qu tener sig=null
  } else {
      nodo *nuevo = new nodo;
      iter->primero = nuevo;
      iter->primero->natural = elem;
      iter->primero->siguiente = NULL;
      iter->ultimo = iter->primero;
  };
}

void reiniciarIterador(TIterador const iter) {//test33
	//if(iter->primero->siguiente != NULL){//si es un solo nodo, no hace nada
	if (iter->primero != NULL) {
    iter->actual = iter->primero;
  }
	//};
}

void avanzarIterador(TIterador const iter) {//test35
  if(iter->actual != NULL && iter->primero != NULL){
    iter->actual = iter->actual->siguiente;
  };
}

nat actualEnIterador(TIterador iter) {//34
  return iter->actual->natural;
}
