/* 4901709 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/abb.h"

struct _rep_abb {
    TInfo dato;
    _rep_abb *izq;
    _rep_abb *der;
};

TAbb crearAbb() { //test51, ok
    return NULL;
}

void liberarAbb(TAbb abb) { //test51, ok
    if(abb != NULL){
        //if (abb->izq == NULL && abb->der == NULL){
            liberarAbb(abb->izq);
            liberarAbb(abb->der);
            liberarInfo(abb->dato);
            delete abb;
            abb = NULL;
        //} else {
        //}
    }
}

bool esVacioAbb(TAbb abb) { //test51, ok
    return abb == NULL;
}

TAbb buscarSubarbol(nat elem, TAbb abb) { //test51 vacio, ok | 52, ok
    TAbb res = abb;
    if(esVacioAbb(abb)){
        res = NULL;//si llegue a vacio no lo encontre
    } else{
        if(natInfo(abb->dato) == elem){
            res = abb;
        } else{
            if(natInfo(abb->dato) < elem){
                res = buscarSubarbol(elem, abb->der);//si actual menor, busco en der
            } else{
                res = buscarSubarbol(elem, abb->izq);//si actual mayor, busco en izq
            }
        }
    }
    return res;
}

TInfo raiz(TAbb abb) { //test52, ok
    return abb->dato;
}

TAbb izquierdo(TAbb abb) { //test52, ok
     return abb->izq; 
}

TAbb derecho(TAbb abb) {  //test52, ok
    return abb->der;
}

TInfo menorEnAbb(TAbb abb) {
    if(abb->izq == NULL){
        return abb->dato;//si llegue a null en izq, tengo el menor
    } else{
        return menorEnAbb(abb->izq);
    }
}

TInfo mayorEnAbb(TAbb abb) {
    if(abb->der == NULL){
        return abb->dato;//si llegue a null en der, tengo el mayor
    } else{
        return mayorEnAbb(abb->der);
    }
}

TAbb consAbb(TInfo dato, TAbb izq, TAbb der) {
    TAbb res = crearAbb();
    res = insertarEnAbb(dato, res);
    res->izq = izq;
    res->der = der;
    return res;
}

void insertarAux(TInfo dato, TAbb &abb){
    if(esVacioAbb(abb)){//si llegue a vacio, inserto
        abb = new _rep_abb;
        abb->dato = dato;
        abb->izq = abb->der = NULL;
    } else{
        if(natInfo(abb->dato) > natInfo(dato)){//si el actual es mayor, voy a la izq
            insertarAux(dato, abb->izq);
        } else{
            if(natInfo(abb->dato) < natInfo(dato)){//si es menor der, no hago nada si es igual(que tampoco es posible que sea)
                insertarAux(dato, abb->der);
            }
        }
    }
}

TAbb insertarEnAbb(TInfo dato, TAbb abb) { //test52, vacio ok | test 53 mas de una cosa mal, pierde memo
    insertarAux(dato, abb);
    return abb;
}

TAbb abbMenorEnAbb(TAbb abb) {
    if(abb->izq == NULL){
        return abb;//si llegue a null en izq, tengo el menor
    } else{
        return abbMenorEnAbb(abb->izq);
    }
}
TAbb abbMayorEnAbb(TAbb abb) {
    if(abb->der == NULL){
        return abb;//si llegue a null en izq, tengo el menor
    } else{
        return abbMayorEnAbb(abb->der);
    }
}

TAbb removerDeAbb(nat clave, TAbb abb) { 
    // caso base, null.
    if (abb == NULL)
        return abb;
    //si menor, esta en izq
    if (clave < natInfo(abb->dato))
        abb->izq = removerDeAbb(clave, abb->izq);
    //si mayor, esta en der
    else if (clave > natInfo(abb->dato))
        abb->der = removerDeAbb(clave, abb->der);
    //si igual, borrar:
    else {
        // hoja:
        if (abb->izq==NULL and abb->der==NULL){
            liberarInfo(abb->dato);
            delete abb;
            return NULL;
        }
        // hijo solo
        else if (abb->izq == NULL) {
            TAbb auxd = abb->der;
            liberarInfo(abb->dato);
            delete abb;
            abb = auxd;
            return abb;
        }
        else if (abb->der == NULL) {
            TAbb auxi = abb->izq;
            liberarInfo(abb->dato);
            delete abb;
            abb = auxi;
            return abb;
        }
        //caso ninguno vacio, meto el izq como el menor de rama der
        //^^correccion: dejo el mas grande de la rama izquierda como raiz, con lado derecho como estaba.
        //TAbb auxizq = abb->izq;
        //TAbb auxder = abb->der;
        //TAbb mend = abbMenorEnAbb(abb->der);
        TAbb mayi = abbMayorEnAbb(abb->izq);
        //mend->izq = auxizq;
        liberarInfo(abb->dato);
        abb->dato = copiaInfo(mayi->dato);
        abb->izq = removerDeAbb(natInfo(abb->dato), abb->izq);
        return abb;
    }
    return abb;
}

TAbb copiaAbb(TAbb abb) {
    if (abb == NULL){
        return crearAbb();
    } else {
        TAbb copia = new _rep_abb;
        copia->dato = copiaInfo(abb->dato);
        copia->izq = copiaAbb(abb->izq);
        copia->der = copiaAbb(abb->der);
        return copia;
    }
}

void Rrot(TAbb &abb){//prec: caso t->i->i unicos nodos
    if(abb->izq != NULL){
        TAbb res = abb->izq;
        abb->izq = res->der;
        res->der = abb;
        abb = res;
    } 
}
void Lrot(TAbb &abb){//prec: caso t->i->i unicos nodos
    if(abb->der != NULL){
        TAbb res = abb->der;
        abb->der = res->izq;
        res->izq = abb;
        abb = res;
    }
}

void LRrot(TAbb &abb){
    Lrot(abb->izq);
    Rrot(abb);
}

void RLrot(TAbb &abb){
    Rrot(abb->der);
    Lrot(abb);
}


void auxlet(TAbb &abb, nat clave, char tipo[2]){
    if(natInfo(abb->dato) >= clave){
        if(natInfo(abb->dato) > clave){
            auxlet(abb->izq, clave, tipo);
        } else if (tipo[0] == 'L'){
            if (tipo[1] == 'L'){
                Rrot(abb);
            } else {
                if(abb->izq != NULL && abb->izq->der != NULL){
                    LRrot(abb);
                }
            }
        } else if(tipo[1] == 'R'){
            Lrot(abb);
        } else {
            if(abb->der != NULL && abb->der->izq != NULL){
                    RLrot(abb);
            }
        }
    } else {
        auxlet(abb->der, clave, tipo);
    }
}
TAbb rotar(nat clave, char tipo[2], TAbb abb) {
    if(buscarSubarbol(clave, abb) != NULL){
        auxlet(abb, clave, tipo);
    }
    return abb;
}