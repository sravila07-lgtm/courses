/* 4901709 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/colCadenas.h"


struct _rep_colCadenas {//test21
  TCadena *arreglo;
  nat l;
};

TColCadenas crearColCadenas(nat tamanio) {//test21
  TColCadenas res = new _rep_colCadenas;
  res->arreglo = new TCadena[tamanio];
  res->l = tamanio;
  for (nat i=0; i < tamanio; i++){
    res->arreglo[i] = crearCadena(); 
  };
  return res;
};

nat tamanioColCadenas(TColCadenas col){
  return col->l;
};

void liberarColCadenas(TColCadenas col) {//test21
  for (nat i=0; i < col->l; i++){
    liberarCadena(col->arreglo[i]);
  };
  if (col != NULL) {delete[] col->arreglo;}
  delete col;
};

TCadena cadenaDeColCadenas(nat pos, TColCadenas col) {//test
  return col->arreglo[pos];
}

nat cantidadColCadenas(nat pos, TColCadenas col) {//test21
  return cantidadEnCadena(col->arreglo[pos]); 
}

bool estaEnColCadenas(nat natural, nat pos, TColCadenas col) {//test21
  bool esta;
  esta = estaEnCadena(natural, col->arreglo[pos]);
  return esta;
}

TColCadenas insertarEnColCadenas(nat natural, double real, nat pos,
                                 TColCadenas col) {//test22
  col->arreglo[pos] = insertarAlInicio(natural, real, col->arreglo[pos]);
  return col;
}

TInfo infoEnColCadenas(nat natural, nat pos, TColCadenas col) {
  return infoCadena(natural, col->arreglo[pos]);
}

TColCadenas removerDeColCadenas(nat natural, nat pos, TColCadenas col) {
  col->arreglo[pos] = removerDeCadena(natural, col->arreglo[pos]);
  return col;
}
