/*49017096*/

#include "../include/lista.h"
#include "../include/utils.h"
#include "../include/mapping.h"
#include <assert.h>

// Implementacion de 'TMapping'.
// Se debe definir en mapping.cpp.
// struct _rep_mapping;
// Declaración del tipo 'TMapping'.
struct _rep_mapping {
    TLista lst;
};

/*  Operaciones de TMapping */

/*
  Devuelve un elemento de tipo 'TMapping' vacío (sin elementos).
 */
TMapping crearMapping() {
    TMapping res = new _rep_mapping;
    res->lst = crearLista;
    return res;
};

/*
  Si en 'map' hay menos de MAX (definido en utils.h) asociaciones y 'clave'
  no tiene un valor asociado en 'map' agrega en 'map' la asociación
  (clave,valor). En otro caso la operación no tiene efecto.
  Devuelve 'map'.
 */
TMapping asociar(nat clave, double valor, TMapping map) {
    assert((longitud(map->lst) >= MAX) && posNat(clave, map->lst) != 0);
    TMapping res = crearMapping();
    res->lst = insertar(posNat(clave, map->lst), valor, map->lst);
    return res;
};

/*
  Devuelve 'true' si y solo si 'clave' tiene un valor asociado en 'map'.
 */
bool esClave(nat clave, TMapping map) {
    return posNat(clave, map->lst) != 0;
};

/*
  Devuelve el valor que en 'map' está asociado a 'clave'.
  Precondición: esClave(clave, map)
 */
double valor(nat clave, TMapping map) {
    return infoLista(posNat(clave, map->lst), map->lst);
};

/*
  Si 'clave' tiene un valor asociado en 'map' remueve de `map' la asociación de
  'clave'. En otro caso la operación no tiene efecto.
  Devuelve 'map'.
 */
TMapping desasociar(nat clave, TMapping map) {
    TMapping res = crearMapping;
    res->lst = remover(posNat(clave, map->lst), map->lst);
    return res;
};