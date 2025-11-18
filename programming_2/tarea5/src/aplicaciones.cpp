/* 4901709 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/aplicaciones.h"
#include "../include/colCadenas.h"
#include "../include/mapping.h"
#include <string.h>
#include <assert.h>



void lAux(TCadena &res, TAbb abb){
  if(!esVacioAbb(abb)){
    lAux(res, derecho(abb));//agrego todo lo derecho
    nat n = natInfo(raiz(abb));
    double r = realInfo(raiz(abb));
    res = insertarAlInicio(n, r, res);//agrego actual
    lAux(res, izquierdo(abb));//luego, todo lo izq
  }
}
TCadena linealizacion(TAbb abb) {
  TCadena lineal = crearCadena();
  lAux(lineal, abb);
  return lineal;
}


static void imprimirAux(nat nivel, TAbb b) {
  if (!esVacioAbb(b)) {
    imprimirAux(nivel + 1, derecho(b));
    for (nat i = 1; i <= nivel; i++){
      printf("-");
    };
    imprimirInfo(raiz(b));
    printf("\n");
    imprimirAux(nivel + 1, izquierdo(b));
  }
}
void imprimirAbb(TAbb abb) {
  imprimirAux(0, abb);
}

static nat max(nat a, nat b){ 
    if (a > b){
        return a;
    }else
        return b;
}

int alturaAbb(TAbb b) {
  if(esVacioAbb(b))
    return 0;
  else 
    return max(alturaAbb(izquierdo(b)),alturaAbb(derecho(b)))+1; 
}

bool esPerfecto(TAbb abb) {
  if(esVacioAbb(abb)){
    return true;
  } else return (alturaAbb(izquierdo(abb)) == alturaAbb(derecho(abb))) &&
                (esPerfecto(izquierdo(abb)) && esPerfecto(derecho(abb)));
}

void menAux(double limite, TAbb &res, TAbb abb){
  if (!esVacioAbb(abb)){
    if(realInfo(raiz(abb))<limite){
      res = insertarEnAbb(copiaInfo(raiz(abb)), res);
    }
      menAux(limite, res, derecho(abb));
      menAux(limite, res, izquierdo(abb));
  }
}

TInfo maxAbb (TAbb a){
  if (esVacioAbb(derecho(a))){
    return raiz(a);
  } else {
    return maxAbb(derecho(a));
  };
}

void removerMaxAbb(TAbb &a){
  if (esVacioAbb((derecho(a)))){
    /*
    liberarInfo(raiz(a));
    delete borrar;*/
    TAbb borrar = a;
    a = izquierdo(a);
    borrar = removerDeAbb(natInfo(raiz(borrar)),borrar);
  } else {
    a = derecho(a);
    removerMaxAbb(a);
  }
}

TAbb menores(double limite, TAbb abb) {
  TAbb fizq, fder, res;
  if (esVacioAbb(abb)){
    res = NULL;
  } else {
    fizq = menores(limite, izquierdo(abb));
    fder = menores(limite, derecho(abb));
    if (realInfo(raiz(abb)) < limite){
      TInfo a = copiaInfo(raiz(abb));//crearInfo(natInfo(raiz(abb)),realInfo(raiz(abb)));
      res = consAbb(a, fizq, fder);
    } else if(fizq == NULL){
      res = fder;
    } else if (fder == NULL){
      res = fizq;
    } else{
      TInfo mayor = copiaInfo(maxAbb(fizq));
      fizq = removerDeAbb(natInfo(mayor), fizq);
      //removerMaxAbb(fizq);
      res = consAbb(mayor, fizq, fder);
    }
  }
  return res;
}

TIterador caminoAux(nat clave, nat &i, nat k, TAbb abb, TIterador res){
  //si no encuentro y es menor voy a la derecha rec
  if(!esVacioAbb(abb)){
    if(natInfo(raiz(abb)) < clave){
      res = caminoAux(clave, i, k, derecho(abb), res);
      if(i < k){
        agregarAIterador(natInfo(raiz(abb)), res);
        i++;
        return res;
      };
    //si no encuentro y es mayor voy a la izquierda rec
    } else if (natInfo(raiz(abb)) > clave){
      res = caminoAux(clave, i, k, izquierdo(abb), res);
      if(i < k){
        agregarAIterador(natInfo(raiz(abb)), res);
        i++;
        return res;
      };
    //si encuentro i++, agrego, retorno
    } else if(natInfo(raiz(abb)) == clave && i<k){
        agregarAIterador(natInfo(raiz(abb)), res);
        i++;
        return res;
    };
  };
  return res;
  //si no es igual(ya volvi) e i<=k cuento i++, agrego, retorno
};

TIterador caminoAscendente(nat clave, nat k, TAbb abb) {
  nat i = 0;
  TIterador res = crearIterador();
  res = caminoAux(clave, i, k, abb, res);
  return res;
}

nat largoPalabra(TPalabras pal){
  nat i = 0;
  while (subarboles(pal) && letra(subarboles(pal)) != '\0'){
    i++;
  }
  return i;
}

void imprimirAux(ArregloChars prefijo, nat i, nat largo, TPalabras secuencia) {
  if (letra(secuencia) == '\0') {
    //prefijo[i] = '\0';
    for (nat j=0; j < i; j++){
      printf("%c", prefijo[j]);
    }
    printf("\n");
  } else if (i<largo){
    prefijo[i] = letra(secuencia);
    imprimirAux(prefijo, i + 1, largo, subarboles(secuencia));
  }
  if (siguientes(secuencia) != NULL){
    imprimirAux(prefijo, i, largo, siguientes(secuencia));
  }
}

//imprimir palabras:
//paso prefijo(palabra que tengo hasta ahora)
//paso el arbol, y largo
//condicion: largomaximo, imprimir mientras que el largo (que le paso i++) que voy contando sea menor al largo maximo

void imprimirPalabrasCortas(nat k, TPalabras palabras) {
  if (palabras != NULL){
    nat i = 0;
    char imp[k];
    //imprimirCortas(i, k, imp, subarboles(palabras));
    imprimirAux(imp, i, k, subarboles(palabras));
  }
}

//retorno null si:
//llego a un vacio
//las letras difieren y el siguiente es null
//si me pase de i
//retorno bien si:
//i+1 = largo prefijo y las letras son iguales
//recurso cuando:
//si son distintas las palabras voy al siguiente con i
//si son iguales voy al de abajo con i++
TPalabras buscarFinAux(ArregloChars prefijo, nat i, TPalabras palabras) {
  if (palabras != NULL){
    if (letra(palabras) == prefijo[i]) //la letra actual es igual
    {
      if (i+1 == strlen(prefijo)) //llegue al final
      {
        return palabras;
      } else 
      {
        TPalabras abajo = buscarFinAux(prefijo, i+1, subarboles(palabras));
        if (abajo != NULL){
          return abajo;
        } else return buscarFinAux(prefijo, i+1, siguientes(palabras));
      }
    } else return buscarFinAux(prefijo, i, siguientes(palabras));//la letra no es igual(puebo con el hermano, sin cambiar i)
  } else return NULL;
}

TPalabras buscarFinPrefijo(ArregloChars prefijo, TPalabras palabras) {
  return buscarFinAux(prefijo, 0, subarboles(palabras));
}
/*
bool cordAux(TCadena primero, TCadena actual, TCadena cad){
  if (primero != actual){
    return (natInfo(primeroEnCadena(actual)) > natInfo(primeroEnCadena(cad)) && cordAux(primero, cadenaSiguiente(actual), cadenaSiguiente(cad)));
  }
  else return true;
}

bool estaOrdenada(TCadena cad) { 
  TCadena primero = cad;
  TCadena actual = cadenaSiguiente(cad);
  return cordAux(primero, actual, cad);
}//test 61, pero no test de tiempos. ver iter
*/
bool estaOrdenada(TCadena cad) { 
  nat n = cantidadEnCadena(cad);
  while(n > 1){
    if (natInfo(primeroEnCadena(cadenaSiguiente(cad))) <= natInfo(primeroEnCadena(cad))){
      return false;
    }
    cad = cadenaSiguiente(cad);
    n = n-1;
  }
  return true;
}

TCadena mezclaCadenas(TCadena cad1, TCadena cad2) {//test 63
  TCadena res = crearCadena();
  TCadena aux1 = copiaCadena(cad1);
  TCadena aux2 = copiaCadena(cad2);
  TCadena actual = aux1;
  //nat n1 = cantidadEnCadena(cad1);
  //nat n2 = cantidadEnCadena(cad2);
  if (aux1 == NULL)
  {//caso cad1 vacia
    //res = copiaCadena(cad2);
    return aux2;
  } else if (aux2 == NULL)
  {//caso cad2 vacia
    //res = copiaCadena(cad1);
    return aux1;
  }
  
  while (aux1 != NULL || aux2 != NULL){
    actual = aux1;
    if(aux1 == NULL && aux2 != NULL){
      actual = aux2;
    } else if(aux2 == NULL && aux1 != NULL){
      actual = aux1;
    } else if (natInfo(primeroEnCadena(aux1)) > natInfo(primeroEnCadena(aux2))){
      actual = aux2;
    }
    if (actual != NULL){
      nat na = natInfo(primeroEnCadena(actual));
      double re = realInfo(primeroEnCadena(actual));
      res = insertarAlFinal(na, re, res);
    }
    if (actual == aux1){
      if (aux2 != NULL && natInfo(primeroEnCadena(aux1)) == natInfo(primeroEnCadena(aux2))){
        aux2 = removerPrimero(aux2);
      }
      aux1 = removerPrimero(aux1);
    } else if(actual == aux2){
      aux2 = removerPrimero(aux2);
    }
  }
  return res;
} 

void balanAux(TAbb &res, TInfo *arreglo, int inicio, int final){
  if (!(inicio > final)){
    int med = (inicio + final) / 2;
    TInfo info = copiaInfo(arreglo[med]);
    res = insertarEnAbb(info, res);
    balanAux(res, arreglo, inicio, med-1);
    balanAux(res, arreglo, med+1, final);
  }
}

TAbb crearBalanceado(TInfo *arreglo, nat n) {//test 62
  TAbb res = crearAbb();
  balanAux(res, arreglo, 0, n-1);
  return res;
}

TAbb unionAbbs(TAbb abb1, TAbb abb2) {
  if (abb1 == NULL && abb2 == NULL){ return NULL; }
    TCadena cad1 = linealizacion(abb1);
    TCadena cad2 = linealizacion(abb2);
    TCadena u = mezclaCadenas(cad1, cad2);
    nat l = cantidadEnCadena(u);
    TInfo *arr = new TInfo[l];
    nat i = 0;
    while (i<l) {
      arr[i] = primeroEnCadena(u);
      //u = removerPrimero(u);
      u = cadenaSiguiente(u);
      i = i+1;
    }
    liberarCadena(cad1);
    liberarCadena(cad2);
    TAbb res = crearBalanceado(arr, l);
    delete[] arr;
    liberarCadena(u);
    return res;
}

TCola ordenadaPorModulo(nat p, TCadena cad) {
  //creo un colcadenas de tamaño p
  TCadena *col = new TCadena[p];
  for (nat i=0; i<p ; i++){
    col[i] = crearCadena();
  }
  TCola res = crearCola();
  //recorro la cadena, agregando en el lugar [resto] cada nodo
  nat t = cantidadEnCadena(cad);
  nat j = 0;
  while(j < t){
    col[natInfo(primeroEnCadena(cad))%p] = insertarAlFinal(natInfo(primeroEnCadena(cad)), realInfo(primeroEnCadena(cad)), col[natInfo(primeroEnCadena(cad))%p]);
    cad = cadenaSiguiente(cad);
    j = j+1;
  }
  //recorro el colcadenas agregando el primero del primero, el segundo dle primero ...hasta terminar, el primero del segundo, el segundo del segundo.....
  //todo eso agregandolo a la cola de una 
  nat i = 0;
  while (i < p){
    while (col[i] != NULL){
      res = encolar(primeroEnCadena(col[i]), res);
      col[i] = removerPrimero(col[i]);
    }
    i = i+1;
  }
  //libero colcadenas
  for (nat i=0; i<p ; i++){
    liberarCadena(col[i]);
  }
  delete [] col;
  return res;
}

TPila menoresQueElResto(TCadena cad, nat cantidad) {
  if (cantidad != 0){
    TCadena auxp = cad;
    //TCadena auxs = cadenaSiguiente(cad);
    TPila res = crearPila();
    if (cantidad == 1){
      //TInfo info = copiaInfo(primeroEnCadena(auxp));
      res = apilar(primeroEnCadena(auxp), res);
      return res;
    }
    //TInfo info = copiaInfo(primeroEnCadena(auxp));
    res = apilar(primeroEnCadena(auxp), res);
    auxp = cadenaSiguiente(auxp);
    cantidad = cantidad - 1;
    while (cantidad > 0){
      //recorro cadena: agrego, si el que esta atras mio es menor que yo, agrego y me muevo
      //si el que esta en la cima de la pila es mayor, desapilo hasta que el de la cima sea menor que yo
      while (res != NULL && natInfo(primeroEnCadena(auxp)) <= natInfo(cima(res))){
        res = desapilar(res);
      }
      if (natInfo(primeroEnCadena(auxp)) < natInfo(primeroEnCadena(cadenaSiguiente(auxp))) || cantidad == 1){
        //TInfo info = copiaInfo(primeroEnCadena(auxp));
        res = apilar(primeroEnCadena(auxp), res);
        auxp = cadenaSiguiente(auxp);
      } else {
        auxp = cadenaSiguiente(auxp);
      }
      cantidad = cantidad - 1;
    }
    return res;
  } else return NULL; 
}

void reversoAux(TIterador iter, TIterador res){
  if (estaDefinidaActual(iter)){
    nat a = actualEnIterador(iter);
    avanzarIterador(iter);
    reversoAux(iter, res);
    agregarAIterador(a, res);
  }
}

TIterador reversoDeIterador(TIterador iter) { 
  TIterador res = crearIterador();
  reiniciarIterador(iter);
  reversoAux(iter, res);
  return res;
}

/* -------------------- NUEVAS -----------------------*/

bool esAvl(TAbb abb) {
  if(esVacioAbb(abb)){
    return true;
  } else return (alturaAbb(izquierdo(abb)) - alturaAbb(derecho(abb)) >= -1 && alturaAbb(izquierdo(abb)) - alturaAbb(derecho(abb)) <= 1) &&
                (esAvl(izquierdo(abb)) && esAvl(derecho(abb)));
}


int AVLnodes(int height)
{
    // Base Conditions
    if (height == 0)
        return 1;
    else if (height == 1)
        return 2;
 
    // Recursive function call
    // for the recurrence relation
    return (1 + AVLnodes(height - 1) + AVLnodes(height - 2));
}

TAbb minAux(nat &n, nat h){
  if(h == 1){
    TInfo info = crearInfo(n, 0.0);
    n = n+1;
    return consAbb(info, NULL, NULL);
     
  } else if (h > 1){
    TAbb izq = minAux(n, h-1);
    TInfo info = crearInfo(n, 0.0);//h
    n = n+1;
    TAbb der = minAux(n, h-2);
    return consAbb(info, izq, der);  
  } else return NULL;
}
TAbb avlMin(nat h) {
  TAbb res = crearAbb();
  nat n = 1;
  res = minAux(n, h);
  return res;
}


TCadena filtradaOrdenada(TCadena cad, TIterador it) {
  if (cad == NULL){return NULL;}
  TCadena res = crearCadena();

  
  TCadena inicio = cad;
  inicio = cadenaSiguiente(inicio);
  nat m = 1;
  while (inicio != cad){
    m = m+1;
    inicio = cadenaSiguiente(inicio);
  }//ncad

  TColCadenas col = crearColCadenas(m);
  TCadena aux = cadenaSiguiente(cad);
  nat nc = natInfo(primeroEnCadena(cad));
  col = insertarEnColCadenas(nc, realInfo(primeroEnCadena(cad)), nc % m, col);
  while(aux!=cad){
    nat nc = natInfo(primeroEnCadena(aux));
    col = insertarEnColCadenas(nc, realInfo(primeroEnCadena(aux)), nc % m, col);
    aux = cadenaSiguiente(aux);
  }//ncad
  reiniciarIterador(it);
  while (estaDefinidaActual(it)){
    double sum = 0;
    bool entro = false;
    nat ait = actualEnIterador(it);
    if (ait > 0){
      TCadena mov = cadenaDeColCadenas(ait % m, col); 
      if (mov != NULL){
        if (mov != NULL && natInfo(primeroEnCadena(mov)) == ait){
          sum = realInfo(primeroEnCadena(mov)) + sum;
          entro = true;
          cad = cadenaSiguiente(cad);
          //mov = removerPrimero(mov);
          //mov = cad;
        }
        mov = cadenaSiguiente(mov);
        while((mov != NULL) && mov != cadenaDeColCadenas(ait % m, col)){
          if (natInfo(primeroEnCadena(mov)) == ait){
            sum = realInfo(primeroEnCadena(mov)) + sum;
            entro = true;
            //removerPrimero(mov);
          }
          /*
          if (mov!=NULL && natInfo(primeroEnCadena(mov)) != ait){
            cad = mov;
            mov = cadenaSiguiente(mov);
          }*/
          if (mov != NULL){
            mov = cadenaSiguiente(mov);
          }
        }
      }
    }
    if(entro){
      res = insertarAlFinal(ait, sum, res);
    }
    avanzarIterador(it);
  }//nit

  liberarColCadenas(col);//orden maximo nat de cadena
  
  return res;
}