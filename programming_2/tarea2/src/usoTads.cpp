#include "../include/cadena.h"
#include "../include/utils.h"
#include "../include/info.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
  Devuelve 'true' si y solo si en 'cad' hay un elemento cuyo campo natural es
  'elem'.
  El tiempo de ejecuci�n en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
bool pertenece(nat elem, TCadena cad) {
    if (!esVaciaCadena(cad)) {
        TLocalizador bus;
        bus = inicioCadena(cad);
        while ((bus != NULL)) {
            if ((natInfo(infoCadena(bus, cad))) == elem) {
                return true;
            };
            bus = siguiente(bus, cad);
        };
    };
    return false;
}

/*
  Devuelve la cantidad de elementos de 'cad'.
  El tiempo de ejecuci�n en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
nat longitud(TCadena cad) {
    int n;
    TLocalizador bus;
    bus = inicioCadena(cad);
    n = 0;
    while (bus != NULL) {
        n++;
        bus = siguiente(bus, cad);
    };
    return n;
}

/*
  Devuelve 'true' si y solo si 'cad' est� ordenada de forma no dereciente
  (creciente de manera no estricta) seg�n las campos naturales de sus elementos.
  Si esVaciaVadena(cad) devuelve 'true'.
  El tiempo de ejecuci�n en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
bool estaOrdenadaPorNaturales(TCadena cad) {
    nat numeroAnterior;
    if (!esVaciaCadena(cad)) {
        numeroAnterior = natInfo(infoCadena(inicioCadena(cad), cad));
        TLocalizador loc = siguiente(inicioCadena(cad), cad);
        while (loc != NULL) {
            if (natInfo(infoCadena(loc, cad)) < numeroAnterior) {
                return false;
            };
            numeroAnterior = natInfo(infoCadena(loc, cad));
            loc = siguiente(loc, cad);
        };
    };
    return true;
}

/*
  Devuelve 'true' si y solo si los componentes naturales de alg�n par de
  elementos de 'cad' son iguales.
  El tiempo de ejecuci�n en el peor caso es O(n^2), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
bool hayNatsRepetidos(TCadena cad) {
    bool res = false;
    if (esVaciaCadena(cad)) { return false; }
    else {
        TLocalizador loc = inicioCadena(cad);
        while (localizadorEnCadena(loc, cad)){
            TLocalizador loc2 = siguiente(loc, cad);
            while (localizadorEnCadena(loc2, cad) && natInfo(infoCadena(loc2, cad)) != natInfo(infoCadena(loc, cad))){
                loc2 = siguiente(loc2, cad);
            };
            if (localizadorEnCadena(loc2, cad) && (natInfo(infoCadena(loc2, cad)) == natInfo(infoCadena(loc, cad)))) {return true;}
            loc = siguiente(loc, cad);
        };
    return res;
    }
}


/*
  Devuelve 'true' si y solo si 'c1' y 'c2' son iguales (es decir, si los
  elementos son iguales y en el mismo orden).
  Si esVaciaCadena(c1) y esVaciaCadena(c2) devuelve 'true'.
  El tiempo de ejecuci�n en el peor caso es O(n1 + n2), siendo 'n1' u 'n2' la
  cantidad de elementos de 'c1' y 'c2' respectivamente.
 */
bool sonIgualesCadena(TCadena c1, TCadena c2) {
    bool res = true;
    if(esVaciaCadena(c1) && esVaciaCadena(c2)) {return true;} //son vacias true
    else{
        if(esVaciaCadena(c1) || esVaciaCadena(c2)) { return false; }; //si las dos no son vacias pero una si, es false
        if (longitud(c1) != longitud(c2)) {
            return false;//caso que longitudes sean distintas ya retorna false.
        }; 
        TLocalizador loc1 = inicioCadena(c1);//al inicio c1
        TLocalizador loc2 = inicioCadena(c2);//al inicio c2
        while(esLocalizador(loc1) && esLocalizador(loc2)) {
            if ((natInfo(infoCadena(loc1, c1)) != natInfo(infoCadena(loc2, c2))) || (realInfo(infoCadena(loc1, c1)) != realInfo(infoCadena(loc2, c2)))) {
            return false;
            };
            loc1 = siguiente(loc1, c1);
            loc2 = siguiente(loc2, c2);
        };
    };
    return res;
}

/*
  Devuelve el resultado de concatenar 'c2' despu�s de 'c1'.
  La 'TCadena' resultado no comparte memoria ni con 'c1' ni con 'c2'.
  El tiempo de ejecuci�n en el peor caso es O(n1 + n2), siendo 'n1' u 'n2' la
  cantidad de elementos de 'c1' y 'c2' respectivamente.
 */
TCadena concatenar(TCadena c1, TCadena c2) {
    TCadena res = crearCadena();
    if (!esVaciaCadena(c1)) {
        TCadena cp1 = copiarSegmento(inicioCadena(c1), finalCadena(c1), c1);
        insertarSegmentoDespues(cp1, finalCadena(res), res);
        //liberarCadena(cp1);
    };
    if (!esVaciaCadena(c2)) {
        TCadena cp2 = copiarSegmento(inicioCadena(c2), finalCadena(c2), c2);
        insertarSegmentoDespues(cp2, finalCadena(res), res);
        //		res->final = finalCadena(cp2);
        //liberarCadena(cp2);
    };
    return res;
}

/*
  Se ordena 'cad' de manera creciente seg�n los componentes naturales de sus
  elementos.
  Devuelve 'cad'
  Precondici�n: ! hayNatsRepetidos(cad)
  No se debe obtener ni devolver memoria de manera din�mica.
  Se debe mantener las relaciones de precedencia entre localizadores.
  Si esVaciaCadena(cad) no hace nada.
  El tiempo de ejecuci�n en el peor caso es O(n^2), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
TCadena ordenar(TCadena cad) {
    if (!esVaciaCadena(cad)) {
        TLocalizador loc = inicioCadena(cad);
        while (loc != finalCadena(cad)) {
            intercambiar(loc, menorEnCadena(loc, cad), cad);
            loc = siguiente(loc, cad);
        };
    };
    return cad;
}

/*
  Cambia todas las ocurrencias de 'original' por 'nuevo' en los elementos
  de 'cad'.
  Devuelve 'cad'
  No debe quedar memoria inaccesible.
  El tiempo de ejecuci�n en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
TCadena cambiarTodos(nat original, nat nuevo, TCadena cad) {
    TLocalizador loc;
    loc = inicioCadena(cad);
    while (loc != NULL) {
        if (natInfo(infoCadena(loc, cad)) == (original)) {
            TInfo i = crearInfo(nuevo, realInfo(infoCadena(loc, cad)));
            liberarInfo(infoCadena(loc,cad));
            cambiarEnCadena(i , loc, cad);
            loc = siguiente(loc, cad);
        } else {loc = siguiente(loc,cad);};
    };
    return cad;
}

/*
  Devuelve la 'TCadena' de elementos de 'cad' que cumplen
  "menor <= natInfo (elemento) <= mayor".
  El orden relativo de los elementos en la 'TCadena' resultado debe ser el mismo
  que en 'cad'.
  Precondici�n: estaOrdenadaPorNaturales (cad), 'menor' <= 'mayor',
  pertenece (menor, cad), pertenece (mayor, cad).
  La 'TCadena' resultado no comparte memoria con 'cad'.
  El tiempo de ejecuci�n en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
TCadena subCadena(nat menor, nat mayor, TCadena cad) { //diff 24
    TLocalizador aux = inicioCadena(cad);
    TCadena res = crearCadena();
    while (esLocalizador(aux)) {
        nat n = natInfo(infoCadena(aux, cad));
        if ((menor <= n) && (n <= mayor)) {
            TInfo info = crearInfo(natInfo(infoCadena(aux, cad)), realInfo(infoCadena(aux, cad)));
            insertarAlFinal(info, res);
        }
        aux = siguiente(aux, cad);
    }
    return res;
}

