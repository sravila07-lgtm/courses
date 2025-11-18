/* 4901709 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/colaDePrioridad.h"
#include "../include/info.h"
#include <assert.h>

struct repT{
  int dato;
  double orden;
};

typedef struct repT *T;

struct _rep_colaDePrioridad{
  T *heap;
  nat tope;
  int *posiciones;
  nat capacidad;
  bool criterio;//true si ordeno por mas chico arriba
//inicializar bool
};

TColaDePrioridad crearCP(nat N) {
    TColaDePrioridad cp = new _rep_colaDePrioridad;
    cp->heap = new T[N+1];
    int *pos = new int[N+1];
    cp->posiciones = pos;
    for (nat i=0;i<=N;i++){
      cp->heap[i] = NULL;///////DEFINIR VACIO
    }
    for (nat i = 0; i<=N; i++){
      cp->posiciones[i] = 0;
    }
    cp->tope = 0;
    cp->capacidad = N;
    cp->criterio = 1;
    return cp;
}

//auxs
bool criterio(TColaDePrioridad &cp, T padre, T hijo){
  if(cp->criterio && padre->orden > hijo->orden){//caso polaridad = 1, la raiz es el menor
  return true;
  }
  if(!cp->criterio && padre->orden < hijo->orden){//caso polaridad = 0, la raiz es el mayor 
    return true;
  }
  return false;
}


void filtradoDescendente(TColaDePrioridad &cp, nat pos){
  if(2*pos <= cp->tope){
    nat hijo = 2*pos;
    if(hijo+1<=cp->tope && criterio(cp, cp->heap[hijo], cp->heap[hijo+1])){  ////si polaridad = 1, cambio en caso de hijo+1 < hijo
      hijo = hijo+1;
    }
    if(criterio(cp, cp->heap[pos], cp->heap[hijo])){  ////
      T swap = cp->heap[pos];
      //intercambiar nodos
      cp->heap[pos] = cp->heap[hijo];
      cp->heap[hijo] = swap;
      //posiciones
      cp->posiciones[cp->heap[pos]->dato] = pos;
      cp->posiciones[cp->heap[hijo]->dato] = hijo;
      filtradoDescendente(cp, hijo);
    }
  }
}
void filtradoAscendente(TColaDePrioridad &cp, nat pos){
  if(pos > 1 && pos < cp->capacidad+1 && criterio(cp, cp->heap[pos/2], cp->heap[pos])){  ////
    T swaph = cp->heap[pos];//nodo
    //intercambiar nodos
    cp->heap[pos] = cp->heap[pos/2];
    cp->heap[pos/2] = swaph;
    //editar posiciones
    cp->posiciones[cp->heap[pos]->dato] = pos;
    cp->posiciones[cp->heap[pos/2]->dato] = pos/2;

    filtradoAscendente(cp, pos/2);
  } 
}
/*
void filtradoAscendente(TColaDePrioridad &cp, nat pos){
  T swap = cp->heap[pos];
  while((pos>1) && (cp->heap[pos/2]->orden > swap->orden)){
    cp->heap[pos] = cp->heap[pos/2];
    cp->heap[pos/2] = swap;
    pos = pos/2;
  }
  cp->heap[pos] = swap;
  cp->posiciones[swap->dato - 1] = pos;
}
*/


void modificarOrden(int dato, double orden, TColaDePrioridad &cp){//(int dato, double orden){
  int pos = cp->posiciones[dato];
  double orden_anterior = cp->heap[pos]->orden;
  cp->heap[pos]->orden = orden;
  if(orden > orden_anterior){
    filtradoDescendente(cp, pos);
  } else filtradoAscendente(cp, pos);
}

TColaDePrioridad invertirPrioridad(TColaDePrioridad cp) {
  cp->criterio = !cp->criterio;
  nat i = cp->tope;
  TColaDePrioridad res = crearCP(cp->capacidad);
  res->criterio = cp->criterio;
  while (i>= 1){
    res = insertarEnCP(cp->heap[i]->dato, cp->heap[i]->orden, res);
    i = i-1;
  }
  liberarCP(cp);
  return res;
}
/*

*/

  
void liberarCP(TColaDePrioridad cp) {
  for (nat i=0;i<=cp->capacidad;i++){
    delete cp->heap[i];
    //i = i+1;
  }
  delete [] cp->heap;
  delete[] cp->posiciones;
  delete cp;
} // encolarColaPrioridad
/*
TColaDePrioridad insertarEnCPAux(nat elem, double valor, TColaDePrioridad &cp) {
  if(cp->tope<cp->capacidad && elem>0 && elem<=cp->capacidad){
    //llamo a filtradoascendente
    cp->tope = cp->tope+1;
    T nodo = new repT;
    nodo->dato = elem;
    nodo->orden = valor;
    cp->heap[cp->tope] = nodo;
    cp->posiciones[elem] = cp->tope;
    filtradoAscendente(cp, cp->tope);
  }
  return cp;
}
TColaDePrioridad insertarEnCP(nat elem, double valor, TColaDePrioridad cp) {
  return insertarEnCPAux(elem, valor, cp);
} // encolarColaPrioridad

*/
TColaDePrioridad insertarEnCP(nat elem, double valor, TColaDePrioridad cp) {
  if(cp->tope<=cp->capacidad && elem>0 && elem<=cp->capacidad){
    if(cp->posiciones[elem] != 0){  
      cp->heap[cp->posiciones[elem]]->orden = valor;
      filtradoAscendente(cp, cp->posiciones[elem]);
      filtradoDescendente(cp, cp->posiciones[elem]);
      return cp;
    }
    if (cp->tope == cp->capacidad){
      return cp;
    }
    //llamo a filtradoascendente
    cp->tope = cp->tope+1;
    T nodo = new repT;
    nodo->dato = elem;
    nodo->orden = valor;//creo nodo
    cp->heap[cp->tope] = nodo;
    cp->posiciones[elem] = cp->tope;
    filtradoAscendente(cp, cp->tope);
  }
  return cp;
} // encolarColaPrioridad

bool estaVaciaCP(TColaDePrioridad cp) {
  return cp->tope == 0;
}

nat prioritario(TColaDePrioridad cp)  {
  //if(cp->tope>0){
    assert(!estaVaciaCP(cp));
    return cp->heap[1]->dato;
  //}
}

TColaDePrioridad eliminarPrioritario(TColaDePrioridad cp)  {
  if (!estaVaciaCP(cp)){
    //libero tope
    nat ntope = cp->heap[cp->tope]->dato;
    double ptope = cp->heap[cp->tope]->orden;
    cp->posiciones[ntope] = 1;
    cp->posiciones[cp->heap[1]->dato] = 0;
    cp->heap[1]->dato = ntope;
    cp->heap[1]->orden = ptope;
    delete cp->heap[cp->tope];
    cp->heap[cp->tope] = NULL;
    cp->tope = cp->tope-1;
    //filtrado descendente del primero
    if(!estaVaciaCP(cp)){
      filtradoDescendente(cp, 1);
    }
  }
  return cp;
}

bool estaEnCP(nat elem, TColaDePrioridad cp)  {
  if(cp != NULL && elem<=cp->capacidad && cp->tope != 0){
    return (cp->posiciones[elem] != 0);
  } else return NULL;
}

double prioridad(nat elem, TColaDePrioridad cp)  {
  //if (cp->heap[cp->posiciones[elem]] != NULL){
    return cp->heap[cp->posiciones[elem]]->orden;
  //}
}
