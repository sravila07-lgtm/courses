/* 4901709 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/cadena.h"

struct _rep_cadena {
  TInfo dato;
  _rep_cadena *siguiente;
  _rep_cadena *anterior;
};

TCadena crearCadena() {
  return NULL;
}

void liberarCadena(TCadena cad) {  
  if (cad != NULL){//si no esta vacia
    TCadena inicio = cad;
    cad = cad->anterior;
    cad->siguiente = NULL; //corto circular al final
    while (inicio != cad){//salgo cuando llego a cad
      inicio = inicio->siguiente;
      liberarInfo(inicio->anterior->dato);
      delete inicio->anterior;
    };
    inicio = NULL;
    if (cad != NULL){
      liberarInfo(cad->dato);
    };
    delete cad;
    cad = NULL; 
  };
}

nat cantidadEnCadena(TCadena cad) {//test11
  nat i = 0;
  if (cad != NULL) {
    TCadena aux = cad;
    i++;//si no es null tiene un nodo
    while (aux->siguiente != cad){//cuento hasta llegar al ultimo
      i++;
      aux = aux->siguiente;
    };
  };
  return i;
}

bool estaEnCadena(nat natural, TCadena cad) {//test11
  if (cad == NULL){return false;};
  TCadena aux = cad;
  while (aux->siguiente != cad && natInfo(aux->dato) != natural) {
     aux = aux->siguiente;
  };// salgo con el ultimo, o salgo apuntando lo que busco
  return (natInfo(aux->dato) == natural);//solo distinguir de caso vacio, y ver si esta
};

TCadena insertarAlInicio(nat natural, double real, TCadena cad) {//test12
  //caso vacia:
  TCadena nueva = new _rep_cadena;//creo nodo
  nueva->dato = crearInfo(natural, real);
  if (cad != NULL){
    nueva->siguiente = cad;
    nueva->anterior = cad->anterior;
    cad->anterior->siguiente = nueva;
    cad->anterior = nueva;
  } else {
      nueva->anterior = nueva;
      nueva->siguiente = nueva;
  };
  cad = nueva;
  return cad;
}

TInfo infoCadena(nat natural, TCadena cad) {
  while (natInfo(cad->dato) != natural) { //busco el nodo
     cad = cad->siguiente;
  };//salgo con cad apuntando al nodo de nat
  return cad->dato;
}

TInfo primeroEnCadena(TCadena cad) {//test15
  return cad->dato;//cad ya apunta al primero
};

TCadena cadenaSiguiente(TCadena cad) {//test15
  if (cad != NULL && cad->siguiente != cad){//defino nodo unico autoreferenciandose
    TCadena res = cad->siguiente;
    return res;
  };
  return cad;//se soluciona con if (cad != NULL) {return cad->siguiente}
};

TCadena removerDeCadena(nat natural, TCadena cad) {//test14
  if (cad != NULL) {
    if (natInfo(cad->dato) == natural){
      liberarInfo(cad->dato);
      if(cad->siguiente == cad){
        delete cad;
        cad = NULL;
        return cad;
      }
      cad->anterior->siguiente = cad->siguiente;
      cad->siguiente->anterior = cad->anterior;
      TCadena aux = cad;
      cad = cad->siguiente;
      delete aux;
      return cad;
  };
  cad->siguiente = removerDeCadena(natural, cad->siguiente);//el elemento esta, no hay que prevenir
 };
  return cad;
}

void imprimirCadena(TCadena cad) {//test12
  int i = 0;
  TCadena inicio = cad;
  while(cad != NULL && cad->siguiente != inicio) {
    i++;
    imprimirInfo(cad->dato);
    cad = cad->siguiente;
  };
  if (cad != NULL) {imprimirInfo(cad->dato);};
  printf("\n");
}

TCadena insertarAlFinal(nat natural, double real, TCadena cad) { 
  cad = insertarAlInicio(natural, real, cad);
  cad = cad->siguiente;
  return cad;
}

TCadena removerPrimero(TCadena cad) {
  if (cad != NULL){
    liberarInfo(cad->dato);
      if(cad->siguiente == cad){
        delete cad;
        cad = NULL;
        return cad;
      }
      cad->anterior->siguiente = cad->siguiente;
      cad->siguiente->anterior = cad->anterior;
      TCadena aux = cad;
      cad = cad->siguiente;
      delete aux;
      return cad;
  }
  return cad;
}

TCadena copiaCadena(TCadena cad) { 
  if (cad != NULL){
    TCadena iter = cad;
    TCadena res = crearCadena();
    //primer nodo, porque si es unico se autoreferencia
    res = insertarAlFinal(natInfo(iter->dato), realInfo(iter->dato), res); 
    iter = iter->siguiente;//si es unico vuelve a apuntar a el
    while (iter != cad){
      res = insertarAlFinal(natInfo(iter->dato), realInfo(iter->dato), res);
      iter = iter->siguiente;
    };
    return res;
  } else return NULL;
}
