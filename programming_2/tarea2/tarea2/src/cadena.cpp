
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct nodoCadena {
  TInfo dato;
  TLocalizador anterior;
  TLocalizador siguiente;
};

struct _rep_cadena {
  TLocalizador inicio;
  TLocalizador final;
};

/*
  Devuelve 'true' si y solo si 'loc' es un 'TLocalizador' válido.
  En cadenas enlazadas un 'TLocalizador' es válido si y solo si no es 'NULL'.
  El tiempo de ejecución en el peor caso es O(1).
 */
bool esLocalizador(TLocalizador loc) { return loc != NULL; }

/*
  Devuelve la 'TCadena' vacía (sin elementos).
  El tiempo de ejecución en el peor caso es O(1).
 */
TCadena crearCadena() {
  TCadena res = new _rep_cadena;
  res->inicio = res->final = NULL;
  return res;
}

/*
  Libera la memoria asignada a 'cad' y la de todos sus elementos.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
 */
void liberarCadena(TCadena cad) {
    if (!esVaciaCadena(cad)) {
        TLocalizador loc1 = cad->inicio;
        TLocalizador loc2 = loc1;
        while (loc1 != NULL) {
            loc2 = loc1->siguiente;
            delete loc1;
            loc1 = loc2;
        };
    };

    delete cad;
}

/*
  Devuelve 'true' si y solo si 'cad' es vacía (no tiene elementos).
  El tiempo de ejecución en el peor caso es O(1).
 */
bool esVaciaCadena(TCadena cad) {
    return (cad->inicio == NULL) && (cad->final == NULL);
}

/*
  Devuelve el 'TLocalizador' con el que se accede al inicio de 'cad'.
  Si esVaciaCadena(cad) devuelve un 'TLocalizador' no válido.
  El tiempo de ejecución en el peor caso es O(1).
 */
TLocalizador inicioCadena(TCadena cad) {
  /*
  // versión que sigue la especificación
    TLocalizador res;
    if (esVaciaCadena(cad)) {
      res = NULL;
    } else {
      res = cad->inicio;
    }
    return res;
  */
  
  // versión conociendo la implementación:
  // esVaciaCadena(cad) => cad->inicio == NUL
  assert(!esVaciaCadena(cad) || cad->inicio == NULL);
  return cad->inicio;
}

/*
  Devuelve el 'TLocalizador' con el que se accede al final de 'cad'.
  Si es_vacia_cadena(cad) devuelve un 'TLocalizador' no válido.
  El tiempo de ejecución en el peor caso es O(1).
 */
TLocalizador finalCadena(TCadena cad) {
    assert(!esVaciaCadena(cad) || cad->final == NULL);
    return cad->final;
}

/*
  Devuelve el elemento de 'cad' al que se accede con 'loc'.
  Precondición: localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(1).
 */
TInfo infoCadena(TLocalizador loc, TCadena cad) {
    assert(localizadorEnCadena(loc, cad));
    return loc->dato;
}

/*
  Devuelve el 'TLocalizador' con el que se accede al elemento de 'cad'
  inmediatamente siguiente a 'loc'.
  Si esFinalCadena(loc, cad) devuelve un 'TLocalizador' no válido.
  Precondición: localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(1).
 */
TLocalizador siguiente(TLocalizador loc, TCadena cad) {
    assert(localizadorEnCadena(loc, cad));
    if (loc->siguiente == NULL) {
        return NULL;
    }
    else {
        return loc->siguiente;
    };
}

/*
  Devuelve el 'TLocalizador' con el que se accede al elemento de 'cad'
  inmediatamente anterior a 'loc'.
  Si esInicioCadena(loc, cad) devuelve un 'TLocalizador' no válido.
  Precondición: localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(1).
 */
TLocalizador anterior(TLocalizador loc, TCadena cad) {
    assert(localizadorEnCadena(loc, cad));
    if (!esInicioCadena(loc, cad)) { return loc->anterior; }
    else { return NULL; };
}

/*
  Devuelve 'true' si y solo si con 'loc' se accede al último elemento de 'cad'.
  Si esVaciaCadena (cad) devuelve 'false'.
  El tiempo de ejecución en el peor caso es O(1).
 */
bool esFinalCadena(TLocalizador loc, TCadena cad) {
    if (esVaciaCadena(cad)) { return false; }
    else { return (loc == cad->final); };
}

/*
  Devuelve 'true' si y solo si con 'loc' se accede al primer elemento de 'cad'.
  Si esVaciaCadena (cad) devuelve 'false'.
  El tiempo de ejecución en el peor caso es O(1).
 */
bool esInicioCadena(TLocalizador loc, TCadena cad) {
    if (esVaciaCadena(cad)) { return false; }
    else { return loc == cad->inicio; };
}

/*
  Se inserta 'i' como último elemento de 'cad'.
  Devuelve 'cad'.
  Si esVaciaVadena (cad) 'i' se inserta como único elemento de 'cad'.
  El tiempo de ejecución en el peor caso es O(1).
 */
TCadena insertarAlFinal(TInfo i, TCadena cad) {
    nodoCadena* nod = new nodoCadena;
    nod->dato = i;
    if (!esVaciaCadena(cad)) {
        nod->siguiente  = cad->final->siguiente;
        nod->anterior = cad->final;
        cad->final->siguiente = nod;
    }
    else {
        nod->siguiente = cad->final;
        nod->anterior = cad->inicio;
        cad->inicio = nod;
        ;
    };
    cad->final = nod;
    nod = NULL;
    delete nod;
    return cad;
}

/*
  Se inserta 'i' como un nuevo elemento inmediatamente antes de 'loc'.
  Devuelve 'cad'.
  Precondición: localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(1).
 */
TCadena insertarAntes(TInfo i, TLocalizador loc, TCadena cad) {
    nodoCadena* nodo = new nodoCadena;
    nodo->siguiente = loc;
    nodo->dato = i;
    if (!esInicioCadena(loc, cad)) {
        loc->anterior->siguiente = nodo;
        nodo->anterior = loc->anterior;
        loc->anterior = nodo;
        //nodo = NULL;
        //delete nodo;
        return cad;
    }
    else {
        loc->anterior = nodo;
        nodo->anterior = NULL;
        cad->inicio = nodo;
        //nodo = NULL;
        //delete nodo;
        return cad;
    };
}

/*
  Se remueve el elemento al que se accede desde 'loc' y se libera la memoria
  asignada al mismo y al nodo apuntado por el localizador.
  Devuelve 'cad'.
  El valor de 'loc' queda indeterminado.
  Precondición: localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(1).
 */
TCadena removerDeCadena(TLocalizador loc, TCadena cad) {
    if (!esVaciaCadena(cad)) {
        if (cad->inicio == cad->final) {
            liberarInfo(loc->dato);
            delete loc;
            cad->inicio = cad->final = NULL;
        }
        else {
            if (!esInicioCadena(loc, cad) && !esFinalCadena(loc, cad)) {
                TLocalizador ant = loc->anterior;
                TLocalizador sig = loc->siguiente;
                ant->siguiente = sig;
                sig->anterior = ant;
                liberarInfo(loc->dato);
                delete loc;
                loc = NULL;
            };
            if (esInicioCadena(loc, cad) && !esFinalCadena(loc, cad)) {
                TLocalizador sig = loc->siguiente;
                liberarInfo(loc->dato);
                delete loc;
                loc = NULL;
                cad->inicio = sig;
                sig->anterior = NULL;
            };
            if (esFinalCadena(loc, cad) && !esInicioCadena(loc, cad)) {
                TLocalizador ant = loc->anterior;
                liberarInfo(loc->dato);
                delete loc;
                loc = NULL;
                cad->final = ant;
                ant->siguiente = NULL;
            };
        };
    };
    return cad;
}

/*
  Imprime los elementos de 'cad' de la siguiente forma:
  (n de pos1,r de pos1)(n de pos2,r de pos2) ...
  donce 'n` es el componente natural y 'r' es el componente real.
  Antes de terminar, se debe imprimir un fin de linea.
  Si esVaciaCadena(cad) sólo se imprime el fin de línea.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
 */
void imprimirCadena(TCadena cad) {
  if (!esVaciaCadena(cad)) {
      TLocalizador loc = cad->inicio;
      int i = 1;
      while (loc != NULL) {
          printf("(%d,%.2f)", natInfo(loc->dato), realInfo(loc->dato));//printf("(%d de pos%d,%.2f de pos%d)", natInfo(loc->dato), i, realInfo(loc->dato), i);
          i++;
          loc = loc->siguiente;
      };
    };
  printf("\n");
}

/*
  Devuelve el 'TLocalizador' con el que se accede al k-esimo elemento de 'cad'.
  Si 'k' es 0 o mayor a la cantidad de elementos de 'cad' devuelve un
  localizdor  no válido.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
 */
TLocalizador kesimo(nat k, TCadena cad) {
    TLocalizador loc;
    loc = cad->inicio;
    nat i = 1;
    if (k != 0) {
        while (i < k && loc != NULL) {
            i++;
            loc = loc->siguiente;
        };
    }
    else { return NULL; };
    return loc;
}

/*
  Se inserta en 'cad' la 'TCadena' 'sgm' inmediatamente después de 'loc',
  manteniendo los elementos originales y el orden relativo entre ellos.
  Devuelve 'cad'.
  No se debe obtener memoria (los nodos de 'sgm' pasan a ser parte de 'cad').
  Se libera la memoria asignada al resto de las estructuras de 'sgm'.
  El valor de 'sgm' queda indeterminado.
  Si esVaciaCadena(cad) 'loc' es ignorado y el segmento queda insertado.
  Precondición: esVaciaCadena(cad) o localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(1).
 */
TCadena insertarSegmentoDespues(TCadena sgm, TLocalizador loc, TCadena cad) {
    if (esVaciaCadena(cad)) {
        cad->inicio = sgm->inicio;
        cad->final = sgm->final;
        sgm->inicio = sgm->final = NULL;
    }
    else {
        if (!esVaciaCadena(sgm)) {
            if (esFinalCadena(loc, cad)) {
                loc->siguiente = sgm->inicio;
                cad->final = sgm->final;
            }
            else {
                sgm->inicio->anterior = loc;
                sgm->final->siguiente = loc->siguiente;
                loc->siguiente->anterior = sgm->final;
                loc->siguiente = sgm->inicio;
            };
        };
        sgm->final = sgm->inicio = NULL;
        delete sgm;
    };
    return cad;
}

/*
  Devuelve una 'TCadena' con los elementos de 'cad' que se encuentran entre
  'desde' y 'hasta', incluidos.
  La 'TCadena' resultado no comparte memoria con 'cad'.
  Si esVaciaCadena(cad) devuelve la 'TCadena' vacia.
  Precondición: esVaciaCadena(cad) o precedeEnCadena(desde, hasta, cad).
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en la cadena resultado.
 */
TCadena copiarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad) {
    TCadena res = crearCadena();
    if (!esVaciaCadena(cad)) {
        if (precedeEnCadena(desde, hasta, cad)) {
            TLocalizador loc = desde;
            while (precedeEnCadena(loc, hasta, cad) && loc != NULL) {
                insertarAlFinal(loc->dato, res);
                loc = loc->siguiente;
            };
        };
    };
    return res;
}

/*
  Remueve de 'cad' los elementos que se encuentran  entre 'desde' y 'hasta',
  incluidos y libera la memoria que tenían asignada y la de sus nodos.
  Devuelve 'cad'.
  Si esVaciaCadena(cad) devuelve la 'TCadena' vacía.
  Precondición: esVaciaCadena(cad) o precedeEnCadena(desde, hasta, cad).
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en la cadena resultado.
 */
TCadena borrarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad) {
    if (!esVaciaCadena(cad) && precedeEnCadena(desde, hasta, cad)) {
        TLocalizador loc = desde;
        if (esInicioCadena(desde, cad)) {
            if (esFinalCadena(hasta, cad)) {
                cad->inicio = cad->final = NULL;
            }
            else {
                hasta->siguiente->anterior = NULL;
                cad->inicio = hasta->siguiente;
            };
        }
        else {
            if (esFinalCadena(hasta, cad)) {
                desde->anterior->siguiente = NULL;
                cad->final = desde->anterior;
            }
            else {
                desde->anterior->siguiente = hasta->siguiente;
                hasta->siguiente->anterior = desde->anterior;
            };
        };
        while (precedeEnCadena(loc, hasta, cad)) {
            loc = loc->siguiente;
            delete hasta;
            hasta = loc;
        };
    };
    return cad;
}

/*
  Sustituye con 'i' el elemento de 'cad' al que se accede con 'loc'.
  Devuelve 'cad'.
  No destruye el elemento al que antes se accedía con 'loc'.
  Precondición: localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(1).
 */
TCadena cambiarEnCadena(TInfo i, TLocalizador loc, TCadena cad) {
    assert(localizadorEnCadena(loc, cad));
    loc->dato = i;
    return cad;
}

/*
  Intercambia los elementos a los que se accede con 'loc1' y 'loc2'.
  'loc1' y 'loc2' mantienen su relación de precedencia.
  Devuelve 'cad'.
  Precondición:
    localizadorEnCadena (loc1, cad)
  y localizadorEnCadena (loc2, cad).
  El tiempo de ejecución en el peor caso es O(1).
 */
TCadena intercambiar(TLocalizador loc1, TLocalizador loc2, TCadena cad) {
    assert(localizadorEnCadena(loc1, cad) && localizadorEnCadena(loc2, cad));
    TInfo aux;
    aux = infoCadena(loc1, cad);
    loc1->dato = loc2->dato;
    loc2->dato = aux;
    //aux = NULL;
    //delete aux
    return cad;
}

/*
  Devuelve 'true' si y solo si con 'loc' se accede a un elemento de 'cad',
  (o sea, si apunta a un nodo de 'cad').
  Si esVaciaCadena (cad) devuelve 'false'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
 */
bool localizadorEnCadena(TLocalizador loc, TCadena cad) {
    if (!esVaciaCadena(cad)) {
        TLocalizador aux = cad->inicio;
        while (aux != loc && aux != NULL) {
            aux = aux->siguiente;
        };
        return ((loc != NULL) && (aux == loc));
    }
    else { return false; };
}

/*
  Devuelve 'true' si y solo si  en 'cad' 'loc1' es igual o precede a 'loc2'.
  Si esVaciaCadena (cad) devuelve 'false'.
  Si con 'loc1' o 'loc2' no se accede a un elemento de 'cad' devuelve 'false'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
 */
bool precedeEnCadena(TLocalizador loc1, TLocalizador loc2, TCadena cad) {
    bool res;
    res = localizadorEnCadena(loc1, cad);
    if (res) {
        TLocalizador aux = loc1;
        while (esLocalizador(aux) && (aux != loc2)) {
            aux = siguiente(aux, cad);
            res = esLocalizador(aux);
            assert(!res || localizadorEnCadena(loc2, cad));
        };
    }
    return res;
}

/*
  Devuelve el primer 'TLocalizador' con el que se accede a un elemento cuyo
  componente natural es igual a 'clave', buscando desde 'loc' (inclusive) hacia
  el final de 'cad'. Si no se encuentra o 'cad' es vacía devuelve un
  'TLocalizador' no válido.
  Precondición: esVaciaCadena(cad) o localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
 */
TLocalizador siguienteClave(nat clave, TLocalizador loc, TCadena cad) { //CORE DUMPED ------ver
    if (!esVaciaCadena(cad)) {
        while (loc!=NULL && (clave != natInfo(loc->dato))) {
            loc = siguiente(loc, cad);
        };
        return loc;
    }
    else { return NULL; };
};



/*
  Devuelve el primer 'TLocalizador' con el que se accede a un elemento cuyo
  componente natural es igual a 'clave', buscando desde 'loc' (inclusive) hacia
  el inicio de 'cad'. Si no se encuentra o 'cad' es vacía devuelve un
  'TLocalizador' no válido.
  Precondición: esVaciaCadena(cad) o localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
 */
TLocalizador anteriorClave(nat clave, TLocalizador loc, TCadena cad) { //CORE DUMPED ----a ver
    if (esVaciaCadena(cad)) { return NULL; }
    else {
        while (loc!=NULL && (clave != (natInfo(infoCadena(loc, cad))))) {
                loc = anterior(loc, cad);
            };
            return loc;
    };
}

/*
  Devuelve el 'TLocalizador' con el que se accede al elemento cuyo componente
  natural es el menor en el segmento que va desde 'loc' hasta finalCadena(cad).
  Si hay más de un elemento cuyo valor es el menor el resultado accede al que
  precede a los otros.
  Precondición: localizadorEnCadena(loc, cad).
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos en 'cad'.
 */
TLocalizador menorEnCadena(TLocalizador loc, TCadena cad) {
    if (esVaciaCadena(cad)) { return NULL; }
    else {
        if (localizadorEnCadena(loc, cad)) {
            TLocalizador aux = cad->final;
            TLocalizador res = aux;
            while (aux != loc) {
                if (natInfo(res->dato) >= natInfo(aux->anterior->dato)) { res = aux->anterior; };
                aux = aux->anterior;
            };
            return res;
        }
        else { return NULL; };
    };
}
