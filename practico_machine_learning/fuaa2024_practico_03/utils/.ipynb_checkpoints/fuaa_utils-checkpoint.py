#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Aug 12 07:52:52 2021

@author: fuaa
"""
import numpy as np
from matplotlib import pyplot as plt

_THRESHOLD = 10e-9

"""
Función para imprimir en colores y con el formato de interés.
"""
def printcolor( mensaje, color="k" ):
    if   (color == "r"): mensajeColor = "\x1b[31m" + mensaje + "\x1b[0m"
    elif (color == "g"): mensajeColor = "\x1b[32m" + mensaje + "\x1b[0m"
    elif (color == "y"): mensajeColor = "\x1b[33m" + mensaje + "\x1b[0m"
    elif (color == "b"): mensajeColor = "\x1b[34m" + mensaje + "\x1b[0m"
    elif (color == "p"): mensajeColor = "\x1b[35m" + mensaje + "\x1b[0m"
    elif (color == "c"): mensajeColor = "\x1b[36m" + mensaje + "\x1b[0m"
    else: mensajeColor = mensaje
    mensaje_out = " " + mensajeColor 
    print ( mensaje_out )

"""
Función similar al assert.
"""
def fuaa_assert(   condicion, 
                mensajeFalse = "El resultado no es válido.", 
                mensajeTrue = "Resultado validado." ):

    # Custom assert.
    if ( condicion ):
        printcolor( mensajeTrue, "g" )
    else:
        printcolor( mensajeFalse, "r" )
    
    # Assert tradicional
    # assert condicion, mensajeFalse
    
    return

"""
Evaluar si dos elementos son iguales o no, con una tolerancia dada (threshold).
"""
def son_iguales(x1, x2, threshold = _THRESHOLD):
    if x1.shape == x2.shape:
        if isinstance(x1, np.ndarray):
            dif = np.sqrt(np.sum( ( x1 - x2 )**2 )) / x1.size
        elif isinstance(x1, float):
            dif = np.abs( x1 - x2 )
        condicion = (dif < threshold)
    else:
        condicion = False
    return condicion

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
Validar número de parámetros.
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
def validar_parametros( parametros, min_params ):
    condicion = (len( parametros ) >= min_params)
    if not condicion:
        printcolor( "[validar_resultado] Insuficientes parámetros (\"%s\"), se necesitan %d,  hay %d." % \
            (parametros[0], min_params, len(parametros)), "r" )
    return condicion

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
Función para validar resultado a invocar desde el notebook.
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
def validar_resultado(*args, **kwargs):
    # _ES_CORRECTO = False
    _DEBUG = False

    # Abrir el cartel del validación.
    print( "+-------------------------------------------------------------------------+" )
    print( "|\x1b[34m FuAA: validar resultado                                                 \x1b[0m|" )
    print( "+-------------------------------------------------------------------------+" )
    for key, value in kwargs.items():
        if key == "debug":
            _DEBUG = value
    if _DEBUG: 
        print('args:', args)
        print('kwargs:', kwargs)

    if ( len(args) == 0 ):
        print( "| Sin opciones para evaluar.                                              |" )
        print( "+-------------------------------------------------------------------------+" )
        return False

    ###########################################################
    # Test.
    ###########################################################
    elif (args[0] == "test"):
        if validar_parametros( args, 4 ):
            condicion = args[1]
            mensajeF = args[2]
            mensajeT = args[3]
            fuaa_assert( condicion, mensajeFalse = mensajeF, mensajeTrue = mensajeT )

    ###########################################################
    # No hay ninguna opción de ejercicio.
    ###########################################################
    else:
        printcolor( "Ninguna opción revisada." ) 

    # Cerrar el cartel.
    print( "+-------------------------------------------------------------------------+" )
            
# condicion = False
# mensaje = "Este ese el texto a mostrar en caso de condición falsa."
# validar_resultado( "test", condicion, mensaje )

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
Visualización de la función a optimizar en rango de interés.
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
def visualizar_funcional(grid_step = 0.1, rango = 2):
    xs = np.arange(-rango, rango, grid_step)
    yes = np.arange(-rango, rango, grid_step)
    xx, yy = np.meshgrid(xs, yes)
    z = xx**2 + 2*yy**2 + 2*np.sin(2*np.pi*xx) * 2*np.sin(2*np.pi*yy)

    fig = plt.figure( figsize = (5,5) )
    ax = fig.add_subplot( 111, projection='3d' )
    ax.plot_surface( xx, yy, z )
    plt.xlabel( 'x' )
    plt.ylabel( 'y' )
    plt.title( 'Funcional con grid_step = %.2f' % grid_step )
    plt.tight_layout()
    
    return True


"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
Visualización del conjunto de entrenamiento.
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
def visualizar_conjunto_entrenamiento(X, y):
    '''
    Entrada: 
        X: matriz de tamaño Nx3 que contiene el conjunto de puntos de 
        entrenamiento expresados en coordenadas homogeneas. La primera 
        coordenada de cada punto es uno.
        y: etiquetas asignadas a los puntos.
    '''
    plt.figure(figsize=(8, 8))

    # Se grafican los puntos sorteados
    plt.scatter(X[y == -1, 1],
                X[y == -1, 2],
                s=40,
                color='r',
                marker='*',
                label='etiqueta -1')
    plt.scatter(X[y == 1, 1],
                X[y == 1, 2],
                s=40,
                color='b',
                marker='o',
                label='etiqueta 1')

    plt.legend()
    plt.axis('equal')
    plt.xlabel('x1')
    plt.ylabel('x2')
    plt.title('Conjunto de entrenamiento generado')


"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
Visualización del modelo lineal.
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
def visualizar_modelo_lineal(X, y, w_g):
    '''
    Entrada: 
        X: matriz de tamaño Nx3 que contiene el conjunto de puntos de 
        entrenamiento expresados en coordenadas homogeneas. La primera 
        coordenada de cada punto es uno.
        y: etiquetas asignadas a los puntos.
        w_g: parámetros del modelo lineal encontrados.
    '''
    plt.figure(figsize=(8, 8))

    # Se grafican los puntos sorteados
    plt.scatter(X[y == -1, 1],
                X[y == -1, 2],
                s=40,
                color='r',
                marker='*',
                label='etiqueta -1')
    plt.scatter(X[y == 1, 1],
                X[y == 1, 2],
                s=40,
                color='b',
                marker='o',
                label='etiqueta 1')

    x1_min = X[:, 1].min()
    x1_max = X[:, 1].max()
    x1 = np.linspace(x1_min, x1_max)

    # Se grafica la superficie de decisión encontrada
    x2_g = -w_g[1] / w_g[2] * x1 + -w_g[0] / w_g[2]
    plt.plot(x1, x2_g, label='funcion encontrada')

    plt.legend()
    plt.axis('equal')
    plt.xlabel('x1')
    plt.ylabel('x2')
    plt.title('Conjunto de entrenamiento y modelo lineal encontrado')


"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
Check https://pyob.oxyry.com/
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
def transformar_usando_polinomio_de_grado_g(OO00OOOOO0OO000OO,
                                            OO0O0OOO00O00000O):
    O0O0000OO0OO00OO0 = []
    OO00O0OOO0OOOO00O = OO00OOOOO0OO000OO.copy()
    for O0OOOOO0O00O0OOO0 in range(2, OO0O0OOO00O00000O + 1):
        O0O0000OO0OO00OO0.append(
            OO00O0OOO0OOOO00O[:, 1:2] *
            OO00O0OOO0OOOO00O[:, (OO00O0OOO0OOOO00O.shape[1] -
                                  O0OOOOO0O00O0OOO0):])
        O0O0000OO0OO00OO0.append(OO00O0OOO0OOOO00O[:, 2:3] *
                                 OO00O0OOO0OOOO00O[:, -1:])
        OO00O0OOO0OOOO00O = np.concatenate(
            (OO00O0OOO0OOOO00O, np.hstack((O0O0000OO0OO00OO0))), axis=1)
        O0O0000OO0OO00OO0 = []
    return OO00O0OOO0OOOO00O

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
Visualización de la frontera de decisión.
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
def visualizar_frontera_decision(X, y, w, grado):
    '''
    Entrada:
        X: matriz de Nx3 que contiene los puntos en el espacio original
        y: etiquetas de los puntos
        w: vector de tamaño 10 que contiene los parámetros encontrados
    '''

    # Se construye una grilla de 50x50 en el dominio de los datos
    xs = np.linspace(X[:, 1].min() - 20, X[:, 1].max() + 20)
    ys = np.linspace(X[:, 2].min() - 20, X[:, 2].max() + 20)

    XX, YY = np.meshgrid(xs, ys)
    Z = np.zeros_like(XX)

    # se transforman los puntos de la grilla
    pts_grilla = np.vstack((np.ones(XX.size), XX.ravel(), YY.ravel())).T
    pts_grilla_transformados = transformar_usando_polinomio_de_grado_g(
        pts_grilla, grado)

    # los puntos transformados son proyectados utilizando el w
    Z = pts_grilla_transformados @ w
    Z = Z.reshape(XX.shape)  #
    # se grafica la frontera de decisión, es decir, la línea de nivel 0
    plt.figure(figsize=(8, 8))
    plt.axis('equal')
    plt.pcolor(XX, YY, Z < 0, cmap='bwr', alpha=0.3, shading='auto')
    plt.contour(XX, YY, Z, [0])
    #bien = np.sign(np.dot(transformar_usando_polinomio_de_grado_g(X,12),w))==y
    #mal = np.sign(np.dot(transformar_usando_polinomio_de_grado_g(X,12),w))!=y
    plt.scatter(X[:, 1][y == 1],
                X[:, 2][y == 1],
                s=40,
                color='b',
                marker='o',
                label='etiqueta -1')
    plt.scatter(X[:, 1][y == -1],
                X[:, 2][y == -1],
                s=40,
                color='r',
                marker='x',
                label='etiqueta 1')
    plt.title(
        'Frontera de decision obtenida mediante transformación no lineal de datos'
    )
    plt.ylim(-30, 30)
    plt.legend()


"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
Generar semianillos.
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
def generar_semianillos(N, radio, ancho, separacion, semilla=None):
    '''
    Entrada:
        N: número de muestras a generar
        radio: radio interior del semicírculo
        ancho: diferencia entre el radio exterior e interior
        separación: separación entre los semicírculos
        semilla: valor que se le asigna al método random.seed()

    Salida:
        X: matriz de dimensión  (N,3) que contiene los datos generados en coordenadas homogéneas
        y: etiquetas asociadas a los datos. Tienen dimensión (N,)
    '''

    if semilla is not None:
        np.random.seed(semilla)

    X = np.ones((N, 3))
    # se sortea a que clase pertenecen las muestras
    y = 2 * (np.random.rand(N) < 0.5) - 1

    # radios y ángulos del semicírculo superior
    radios = radio + ancho * np.random.rand(N)
    thetas = np.pi * np.random.rand(N)
    # coordenadas en x de ambos semicírculos
    X[:, 1] = radios * np.cos(thetas) * y + (radio + ancho / 2) * (y == -1)
    # coordenadas en y de ambos semicírculos
    X[:, 2] = radios * np.sin(thetas) * y - separacion * (y == -1)

    return X, y    