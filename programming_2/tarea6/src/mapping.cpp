/* 4901709 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/mapping.h"
#include "../include/info.h"

struct _rep_mapping {
    TInfo *str;
    nat cant;
    nat tam;
};

TMapping crearMap(nat M) {
    TMapping res = new _rep_mapping;
    res->str = new TInfo[M+1];
    for (nat i = 0; i <= M; i++){
        res->str[i] = NULL;
    }
    res->cant = 0;
    res->tam = M;
    return res;
}

void liberarMap(TMapping map) {
    for (nat i = 0; i<map->tam; i++){
        if(map->str[i] != NULL){
            liberarInfo(map->str[i]);
            //delete map->str[i];
            map->str[i] = NULL;
        }
    }
    delete[] map->str;
    delete map;
}

TMapping asociarEnMap(nat clave, double valor, TMapping map) {
    if(map != NULL){
        if(map->str[clave % map->tam] != NULL){
            liberarInfo(map->str[clave % map->tam]);
        }
        TInfo info = crearInfo(clave, valor); 
        map->str[clave % map->tam] = info;
        map->cant = map->cant + 1;
    }
    return map;
}

TMapping desasociarEnMap(nat clave, TMapping map) {
    if(map != NULL){
        if(map->str[clave % map->tam] != NULL){
            liberarInfo(map->str[clave % map->tam]);
            //delete map->str[clave - 1];
            map->cant = map->cant - 1;
        }
        map->str[clave % map->tam] = NULL; 
    }
    return map;
}

bool esClaveEnMap(nat clave, TMapping map) {
    if(map != NULL){
        if(map->str[clave % map->tam] != NULL){
            return true;
        } else return false;
    } else return false;
}

double valorEnMap(nat clave, TMapping map) {
    //if(map != NULL){
    //    if(map->str[clave - 1] != NULL){
    return realInfo(map->str[clave % map->tam]);
    //    } else return NULL;
    //}
}

bool estaLlenoMap(TMapping map) {
    return map->cant == map->tam;
}


