/*
  M�dulo de definici�n de 'TBinario'.

  Los elementos de tipo 'TBinario' son �rboles binario de b�squeda cuyos
  elementos son de tipo 'TInfo'.
  La propiedad de orden de los �rboles es definida por el componente natural de
  sus elementos.

  Laboratorio de Programaci�n 2.
  InCo-FIng-UDELAR
 */

#include "../include/info.h"
#include "../include/usoTads.h"
#include "../include/utils.h"
#include "../include/cadena.h"
#include "../include/binario.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

 // Representaci�n de 'TBinario'.
 // Se debe definir en binario.cpp.
 // struct _rep_binario;
 // Declaraci�n del tipo 'TBinario'
struct _rep_binario {
    TInfo dato;
    _rep_binario *izq;
    _rep_binario *der;
};

//02.in: esVacioBinario, insertarEnBinario, raiz, izquierdo, derecho, buscarSubarbol
/*
  Devuelve un 'TBinario' vac�o (sin elementos).
  El tiempo de ejecuci�n es O(1).
 */
TBinario crearBinario() {
    TBinario res = NULL;
    return res;
}

/*
  Inserta 'i' en 'b' respetando la propiedad de orden definida.
  Devuelve 'b'.
  Precondici�n: esVacioBinario(buscarSubarbol(natInfo(i), b).
  El tiempo de ejecuci�n es O(log n) en promedio, siendo 'n' la cantidad de
  elementos de 'b'.
 */
TBinario insertarEnBinario(TInfo i, TBinario b) {
    if (esVacioBinario(b)) {//crear binario devuelve puntero AB null
        TBinario a = new _rep_binario; //nodo nuevo
        a->dato = i; //asigno i
        a->der = NULL;
        a->izq = NULL;//inicializo
        b = a;
        return b;
    }
    else {
        if (natInfo(b->dato) > natInfo(i)) { //si clave del arbol es mayor, voy a iz
            b->izq = insertarEnBinario(i, b->izq);
        }
        else {
            if (natInfo(b->dato) < natInfo(i)) {
                b->der = insertarEnBinario(i, b->der); //si clave ab es menor, voy a der
            }
        }
    }
    return b;
}


/*
  Devuelve 'true' si y solo si 'b' es vac�o (no tiene elementos).
  El tiempo de ejecuci�n es O(1).
 */
bool esVacioBinario(TBinario b) {
    return (b == NULL);
};

/*
  Devuelve el elemento asociado a la ra�z de 'b'.
  Precondici�n: ! esVacioBinario(b).
  El tiempo de ejecuci�n es O(1).
 */
TInfo raiz(TBinario b) {
    return b->dato;
}

/*
  Devuelve el sub�rbol izquierdo de 'b'.
  Precondici�n: ! esVacioBinario(b).
  El tiempo de ejecuci�n es O(1).
 */
TBinario izquierdo(TBinario b) {
    return b->izq;
}

/*
  Devuelve el sub�rbol derecho de 'b'.
  Precondici�n: ! esVacioBinario(b).
  El tiempo de ejecuci�n es O(1).
 */
TBinario derecho(TBinario b) {
    return b->der;
}

/*
  Devuelve el sub�rbol que tiene como ra�z al nodo con el elemento cuyo
  componente natural es 'elem'.
  Si 'elem' no pertenece a 'b', devuelve el �rbol vac�o.
  El tiempo de ejecuci�n es O(log n) en promedio, siendo 'n' la cantidad de
  elementos de 'b'.
 */
TBinario buscarSubarbol(nat elem, TBinario b) {
    if (esVacioBinario(b)){
        return b;
    }
    else {
        if (natInfo(b->dato) == elem) {
            return b;
        }
        else
            if (natInfo(b->dato) < elem) {
                return buscarSubarbol(elem, b->der);
            }
            else {
                return buscarSubarbol(elem, b->izq);
            }
    }
    return b;
}

/*
  Devuelve el elemento mayor (seg�n la propiedad de orden definida) de 'b'.
  Precondici�n: ! esVacioBinario(b).
  El tiempo de ejecuci�n es O(log n) en promedio, siendo 'n' la cantidad de
  elementos de 'b'.
 */
TInfo mayor(TBinario b) {
    TInfo res;
    if (b->der == NULL) {
        if (b!=NULL)
        res = b->dato; //izq<raiz<der
    }
    else {
        res = mayor(b->der);
    }
    return res;
} //OK

/*
  Libera la memoria asociada a 'b' y todos sus elementos.
  El tiempo de ejecuci�n es O(n), siendo 'n' es la cantidad de elementos de 'b'.
 */
void liberarBinario(TBinario b) {
    if (!esVacioBinario(b)) {
        liberarBinario(b->der);
        liberarBinario(b->izq);
        liberarInfo(b->dato);
        delete b;
        b = NULL;
    };
}//OK
//pronto el print
// Prueba de mayor, removerMayor, removerDeBinario

/*
  Remueve el nodo en el que se localiza el elemento mayor de 'b'
  (libera la memoria  asignada al nodo, pero no la del elemento).
  Devuelve 'b'.
  Precondici�n: ! esVacioBinario(b).
  El tiempo de ejecuci�n es O(log n) en promedio, siendo 'n' la cantidad de
  elementos de 'b'.
 */
TBinario removerMayor(TBinario b) {

    if (b->der != NULL){
        TBinario der = b->der;
        if (der->der == NULL){
            b->der = der->izq;
            delete der;
        }else{
            removerMayor(b->der);
        }
    }else{
        delete b;
    }
    return b;
}

    //assert(!esVacioBinario(b));
    //para encontrar el mayor voy siempre hacia la derecha
    //hasta llegar a b->der == NULL
    /*if (b->der == NULL) {

        //borro nodo sin perder izq, der ya es null
        TBinario izq = b->izq;
        
        b->dato = NULL;
        delete (b);
        b=izq;
    } // si no es null voy al derecho
    else 
        removerMayor(b->der);
    return b;
    */

//} //OK

/*
  Remueve de 'b' el nodo en el que el componente natural de su elemento es
  'elem'.
  Si los dos sub�rboles del nodo a remover son no vac�os, en sustituci�n del
  elemento removido debe quedar el que es el mayor (segun la propiedad de orden
  definida) en el sub�rbol izquierdo.
  Devuelve 'b'.
  Precondici�n: !esVacioBinario(buscarSubarbol(elem, b).
  Libera la memoria del nodo y del elemento.
  El tiempo de ejecuci�n es O(log n) en promedio, siendo 'n' la cantidad de
  elementos de 'b'.
 */
TBinario removerDeBinario(nat elem, TBinario b) {
    if (b != NULL) {
        if (natInfo(b->dato) != elem) {
            if (natInfo(b->dato) > elem) {
                b->izq = removerDeBinario(elem, b->izq);
            }
            else {
                if (natInfo(b->dato) < elem) {
                    b->der = removerDeBinario(elem, b->der);
                }
            }
        }
        else {
            if (b != NULL) {
                if (b->izq != NULL) {
                    if (b->der == NULL) { //1. derecho null, izq no null
                        TBinario aux = b;
                        b = b->izq;
                        liberarInfo(aux->dato);
                        delete aux;
                    }
                    else {
                        TBinario derizq = b->der;//2. derecho no null izquierdo no null
                        while (derizq->izq != NULL) {  //voy al mas izquierdo de la derecha
                            derizq = derizq->izq;
                        }
                        derizq->izq = b->izq;
                        TBinario aux = b;
                        b = b->der;
                        liberarInfo(aux->dato);
                        delete aux;
                    }
                }
                else {//b->izq == NULL
                    if (b->der != NULL) { //izquierdo null derecho no null
                        TBinario aux = b;
                        b = b->der;
                        liberarInfo(aux->dato);
                        delete aux;
                    }
                    else {
                        TBinario aux = b;
                        liberarInfo(aux->dato); //derecho e izq null
                        delete aux;
                        b = NULL;
                    }
                }
            }
        }
    }
    return b;
}//OKK



/*
  Devuelve 'true' si y solo si cada nodo de 'b' cumple la condici�n de balanceo
  AVL. El �rbol vac�o cumple la condici�n.
  Un nodo cumple la condici�n de balanceo AVL si el valor absoluto de la
  diferencia de las alturas de sus sub�rboles izquierdo y derecho en menor o
  igual a 1.
  Cada nodo se puede visitar una sola vez.
  El tiempo de ejecuci�n es O(n), siendo 'n' la cantidad de elementos de 'b'.
 */
bool esAvl(TBinario b) {
    if (b == NULL) return true;
    else return (esAvl(b->izq) && esAvl(b->der) && (alturaBinario(b->izq) - alturaBinario(b->der) <= 1 || alturaBinario(b->der) - alturaBinario(b->izq) <= 1));
};

/*
  Devuelve la altura de 'b'.
  La altura de un �rbol vac�o es 0.
  El tiempo de ejecuci�n es O(n), siendo 'n' la cantidad de elementos de 'b'.
 */
nat max(nat a, nat b) {
    if (a > b) return a;
    else return b;
}
nat alturaBinario(TBinario b) {
    if (b == NULL) return 0;
    else return 1 + max(alturaBinario(b->izq), alturaBinario(b->der));
}

/*
  Devuelve la cantidad de elementos de 'b'.
  El tiempo de ejecuci�n es O(n), siendo 'n' la cantidad de elementos de 'b'.
 */
nat cantidadBinario(TBinario b) {
    if (b == NULL) return 0;
    else return 1 + alturaBinario(b->izq) + alturaBinario(b->der);
}

/*
  Devuelve la suma de los componentes reales de los �ltimos 'i' elementos
  (considerados seg�n la propiedad de orden de los �rboles TBinario)
  de 'b' cuyos componentes reales sean mayores que 0.
  Si en 'b' hay menos de 'i' elementos que cumplan esa condici�n devuelve la
  suma de los componenetes reales de ellos.
  No se deben crear colecciones auxiliares.
  No se deben visitar nuevos nodos despu�s que se hayan encontrado los
  'i' elementos.
  El tiempo de ejecuci�n es O(n), siendo 'n' la cantidad de elementos de 'b'.
 */


double sumaUltimosPositivosAux (nat & i, TBinario b){
    if (b == NULL)
        return 0;
    double suma = 0;
    if (i > 0 && b->der != NULL){
        suma = suma + sumaUltimosPositivos(i, b->der);
    }
    if ( i > 0 && realInfo(b->dato) > 0){
        suma = suma + realInfo(b->dato);
        i--;
    }
    if (i > 0 && b->izq != NULL){
        suma = suma + sumaUltimosPositivos(i, b->izq);
    }
    return suma;
}

double sumaUltimosPositivos(nat i, TBinario b) {
    nat cont = i;
    return sumaUltimosPositivosAux (cont, b);
}

/*
  Devuelve una 'TCadena' con los elementos de 'b' en orden creciente seg�n
  sus componentes naturales.
  La 'TCadena' devuelta no comparte memoria con 'b'.
  El tiempo de ejecuci�n es O(n), siendo 'n' la cantidad de elementos de 'b'.
 */
TCadena linealizacion(TBinario b) { //capaz anda
    TCadena lini = crearCadena();//null
    if (b != NULL) {
        //subarbol izq linealizado
        lini = linealizacion(b->izq);
        //subarbol der linealizado
        TCadena lind = linealizacion(b->der);
        //nodo actual
        TCadena med = crearCadena();
        med = insertarAlFinal(b->dato, med);
        lini = concatenar(lini, med);//(lini)->med
        lini = concatenar(lini, lind);//(lini->med)->lind
    }
    return lini;//si no entra en el if devuelve null
}

/*
  Devuelve un �rbol con copias de los elementos de 'b' que cumplen la condici�n
  "realInfo(elemento) < cota".
  La estructura del �rbol resultado debe ser an�loga a la de 'b'. Esto
  significa que dados dos nodos 'U' y 'V' de 'b' en los que se cumple la
  condici�n y tal que 'U' es ancestro de 'V', en el �rbol resultado la copia de
  'U' debe ser ancestro de la copia de 'V' cuando sea posible. Esto no siempre
  se puede lograr y al mismo tiempo mantener la propiedad de orden del �rbol
  en el caso en el que en un nodo 'V' no se cumple la condici�n y en sus dos
  sub�rboles hay nodos en los que se cumple. En este caso, la copia del nodo
  cuyo elemento es el mayor (seg�n la propiedad de orden definida) de los que
  cumplen la condici�n en el sub�rbol izquierdo de 'V' deber� ser ancestro de
  las copias de todos los descendientes de 'V' que cumplen la condici�n.
  Ver ejemplos en la letra.
  El �rbol resultado no comparte memoria con 'b'. *)
  El tiempo de ejecuci�n es O(n), siendo 'n' es la cantidad de elementos de 'b'.
 */
TBinario menores(double cota, TBinario b) { //andara? cero fe
    TBinario res = crearBinario();
    if (b != NULL) {
        if (realInfo(b->dato) < cota) {
            TInfo copi = copiaInfo(b->dato);
            res = insertarEnBinario(copi, res);
        }
        if (res != NULL) {
            res->izq = menores(cota, b->izq);
            res->der = menores(cota, b->der);
        }
        else {
            res = menores(cota, b->izq);
            res = menores(cota, b->der);
        }
    }
    return res;
}



void imprimirAux(TBinario b, int cont) {
    if (!esVacioBinario(b)) {
        imprimirAux(b->der, cont + 1);//cuando cae en vacio la linea no cuenta
        for (int i = 0; i < cont; i++)
            printf("-");
        ArregloChars res = infoATexto(b->dato);
        printf("%s\n", res);
        delete[] (res);
        imprimirAux(b->izq, cont + 1);//este tampoco
    }
}

/*
  Imprime los elementos de 'b', uno por l�nea, en orden descendente de la
  propiedad de orden de los �rboles 'TBinario'.
  Antes del elemento imprime una cantidad de guiones igual a su profundidad.
  El elemento se imprime seg�n la especificaci�n dada en 'infoATexto'.
  La profundidad de la ra�z es 0.
  Antes del primer elemento, se debe imprimir un fin de linea.
  Si esVacioBinario(b) solo se imprime el fin de l�nea.
  El tiempo de ejecuci�n es O(n . log n) en promedio, siendo 'n' la cantidad
  de elementos de 'b'.
 */
void imprimirBinario(TBinario b) {
    printf("\n");
    int cont = 0;
    imprimirAux(b, cont);
};