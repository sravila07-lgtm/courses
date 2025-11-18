import numpy as np

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
def miassert(   condicion, 
                mensajeFalse = "El resultado no es correcto. Revisar.", 
                mensajeTrue = "El resultado es correcto. Continuar." ):
    # Assert custom
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
    if isinstance(x1, np.ndarray):
        dif = np.sqrt(np.sum( ( x1 - x2 )**2 )) / x1.size
    elif isinstance(x1, float):
        dif = np.abs( x1 - x2 )
    return dif < threshold

""""
Función para validar resultado a invocar desde el notebook.
"""
def validar_resultado(*args, **kwargs):
    # _ES_CORRECTO = False
    _DEBUG = False

    # Abrir el carte del validación.
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
        print( "| Sin opciones para evaluar. Exit.                                        |" )
        print( "+-------------------------------------------------------------------------+" )
        return False

    ###########################################################
    # Práctico 1. Ejercicio 2b.
    ###########################################################
    if ( args[0] == "p01e02b" ):
        x2_w1_true = np.array([0.33333333,0.30612245,0.27891156,0.25170068,0.2244898,0.19727891,0.17006803,0.14285714,0.11564626,0.08843537,0.06122449,0.03401361,0.00680272,-0.02040816,-0.04761905,-0.07482993,-0.10204082,-0.1292517,-0.15646259,-0.18367347,-0.21088435,-0.23809524,-0.26530612,-0.29251701,-0.31972789,-0.34693878,-0.37414966,-0.40136054,-0.42857143,-0.45578231,-0.4829932,-0.51020408,-0.53741497,-0.56462585,-0.59183673,-0.61904762,-0.6462585,-0.67346939,-0.70068027,-0.72789116,-0.75510204,-0.78231293,-0.80952381,-0.83673469,-0.86394558,-0.89115646,-0.91836735,-0.94557823,-0.97278912,-1.])
        x2_w2_true = x2_w1_true
        x2_w1 = args[1]
        x2_w2 = args[2]
        miassert( all([
                    son_iguales( x2_w1_true, x2_w1 ), 
                    son_iguales( x2_w2_true, x2_w2 )
                    ]) )
        # if all( [
        #             son_iguales( x2_w1_true, x2_w1 ), 
        #             son_iguales( x2_w2_true, x2_w2 )
        #         ]
        #     ): 
        #     _ES_CORRECTO = True

    ###########################################################
    # Práctico 1. Ejercicio 3.
    ###########################################################
    elif (args[0] == "p01e03"):
        # print( "Revisa dimensiones." )
        d = 2
        N = 20
        w = args[1]
        X = args[2]
        y = args[3]
        y_pred = np.sign(np.dot(X, w))
        miassert( all([
                    w.shape == (d+1,), 
                    X.shape == (N, d+1),
                    y.shape == (N,),
                    son_iguales( y, y_pred),
                    son_iguales( X[:,0], np.ones(X.shape[0])),
                    np.all((X <= 1) & (X >= -1))
                    ]) )
        # if all( [
        #             w.shape == (d+1,), 
        #             X.shape == (N, d+1),
        #             y.shape == (N,)
        #         ]
        #     ): _ES_CORRECTO = True

    ###########################################################
    # Práctico 1. Ejercicio 4a.
    ###########################################################
    elif (args[0] == "p01e04a"):
        Prob = float( args[1] )
        Prob_true = 9.099999999999982e-09
        miassert( son_iguales( Prob_true, Prob, 10e-10) )
        # if son_iguales( Prob_true, Prob ):
        #     _ES_CORRECTO = True

    ###########################################################
    # Práctico 1. Ejercicio 4b.
    ###########################################################
    elif (args[0] == "p01e04b"):
        Cota_Hoeffding = float( args[1] )
        Cota_Hoeffding_true = 5.521545144074388e-06
        miassert( son_iguales( Cota_Hoeffding_true, Cota_Hoeffding ) )
        # if son_iguales( Cota_Hoeffding_true, Cota_Hoeffding):
        #     _ES_CORRECTO = True

    ###########################################################
    # Práctico 1. Ejercicio 4c.
    ###########################################################
    elif (args[0] == "p01e04c"):
        N = np.ceil(float(args[1]))
        N_true = 840.
        miassert( son_iguales( N_true, N ) )
        # if son_iguales( N_true, N):
        #     _ES_CORRECTO = True

    ###########################################################
    # Práctico 1. Ejercicio 5a.
    ###########################################################
    elif (args[0] == "p01e05a"):
        v0 = float( args[1] )
        v_rand = float( args[2] )
        v_min = float( args[3] )
        v0_true = 0.400000
        v0_true2 = 0.600000
        v0_true3 = 0.300000
        v_rand_true = 0.400000
        v_rand_true2 = 0.600000
        v_min_true = 0.
        v_min_true2 = 0.100000
        miassert( all([
            son_iguales( v0_true, v0 ) or son_iguales( v0_true2, v0 ) or son_iguales( v0_true3, v0 ),
            son_iguales( v_rand_true, v_rand ) or son_iguales( v_rand_true2, v_rand ),
            son_iguales( v_min_true, v_min ) or son_iguales( v_min_true2, v_min )
            ]) )
        # if all([
        #     son_iguales( v0_true, v0 ),
        #     son_iguales( v_rand_true, v_rand ),
        #     son_iguales( v_min_true, v_min ),
        # ]):
        #     _ES_CORRECTO = True
    elif (args[0] == "p01e05a2"):
        num_experimentos = 10000  #100000
        # Matriz que guarda los resultados de los experimentos
        V = np.zeros((num_experimentos, 3))
        np.random.seed(42)
        realizar_experimento_moneda = args[1]
        for i_exp in np.arange(num_experimentos):
            v0, v_rand, v_min = realizar_experimento_moneda()
            V[i_exp, 0] = v0
            V[i_exp, 1] = v_rand
            V[i_exp, 2] = v_min

        m_true = np.array([0.5,0.5,0.05])
        m_pred = np.mean(V,0)
        
        miassert( son_iguales(m_true, m_pred, 0.01) )

    ###########################################################
    # Práctico 2. Ejercicio 1.
    ###########################################################
    elif (args[0] == "p02e01"):
        w_ls = args[1]
        w_ls_true = np.array([[2.93888937], [4.57646455e-02], [1.88530017e-01], [-1.03749304e-03]])
        miassert( son_iguales( w_ls_true, w_ls ) )
        # if son_iguales( w_ls_true, w_ls ):
        #     _ES_CORRECTO = True

    ###########################################################
    # Práctico 2. Ejercicio 2a.
    ###########################################################
    elif (args[0] == "p02e02a"):
        w_perceptron = args[1]
        w_perceptron_true = np.array([ 8., 0.11141316, 50.38210239])
        miassert( son_iguales( w_perceptron_true, w_perceptron ) )
        # if son_iguales( w_perceptron_true, w_perceptron ):
        #     _ES_CORRECTO = True

    ###########################################################
    # Práctico 2. Ejercicio 2b.
    ###########################################################
    elif (args[0] == "p02e02b"):
        w_ls = args[1]
        w_ls_true = np.array([ 0.26562642, -0.00936137,  0.07850489])
        miassert( son_iguales( w_ls_true, w_ls ) )
        # if son_iguales( w_ls_true, w_ls ):
        #     _ES_CORRECTO = True

    ###########################################################
    # Práctico 2. Ejercicio 2c (pocket).
    ###########################################################
    elif (args[0] == "p02e02c"):
        w_pocket = args[1]
        w_procekt_true = np.array([-51., -4.91637769,  34.14227584])
        miassert( son_iguales( w_procekt_true, w_pocket ) )

    ###########################################################
    # Práctico 2. Transformación polinomio tercer grado.
    ###########################################################
    elif (args[0] == "p02tptg"):
        pts_t = args[1]
        pts_t_true = np.array([[ 1.,  1.,  1.,  1.,  1.,  1.,  1.,  1.,  1.,  1.],
                            [ 1.,  2.,  3.,  4.,  6.,  9.,  8., 12., 18., 27.],
                            [ 1.,  0.,  2.,  0.,  0.,  4.,  0.,  0.,  0.,  8.],
                            [ 1.,  2.,  0.,  4.,  0.,  0.,  8.,  0.,  0.,  0.]])
        miassert( pts_t.shape == pts_t_true.shape, \
            "La dimensión de la matriz de puntos transformados no es correcta.")
        miassert( son_iguales( pts_t_true, pts_t ), \
            "La transformación implementada no es correcta." )
        # if not (pts_t.shape == pts_t_true.shape):
        #     print( "|\x1b[31m La dimensión de la matriz de puntos transformados no es correcta.       \x1b[0m|" )
        # elif son_iguales( pts_t_true, pts_t ):
        #     _ES_CORRECTO = True
        # else: 
        #     print( "|\x1b[31m La transformación implementada no es correcta.                          \x1b[0m|" )

    ###########################################################
    # Práctico 2. Transformación polinomio tercer grado.
    ###########################################################
    elif (args[0] == "test"):
        condicion = args[1]
        mensaje = args[2]
        miassert( condicion, mensaje )

    ###########################################################
    # No hay ninguna opción de ejercicio.
    ###########################################################
    else:
        print( "| Ninguna opción revisada.                                                |" ) 

    # Cerrar el cartel.
    print( "+-------------------------------------------------------------------------+" )
            
# condicion = False
# mensaje = "Este ese el texto a mostrar en caso de condición falsa."
# validar_resultado( "test", condicion, mensaje )
