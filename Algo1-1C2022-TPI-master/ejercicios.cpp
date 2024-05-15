#include "ejercicios.h"
#include "auxiliares.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

/******++++**************************** EJERCICIO tiempoTotal ***********+++***********************/
tiempo tiempoTotal(viaje v) {                               // |v| = n.  n+3 -> O(n) Complejidad de peor caso: Lineal
    tuple<tiempo, tiempo> tiempos = obtenerMinMaxTiempo(v); // n
    return get<1>(tiempos) - get<0>(tiempos);               // 3
}

/************++*********************** EJERCICIO distanciaTotal ************++*********************/
distancia distanciaTotal(viaje v) { // |v| = n.  n^2 + n -> O(n^2) Complejidad de peor caso: Cuadratica
    insertionSort(v);               // n^2
    return distanciaViaje(v);       // n
}

/*****************************+***** EJERCICIO excesoDeVelocidad **********************************/
bool excesoDeVelocidad(viaje v) {
    bool superaVel = false;
    double tolerancia = 0.00001;
    insertionSort(v);
    for (int i = 0; i < v.size()-1; ++i) {
        superaVel |= (velocidad(v[i], v[i + 1]) - 80) > tolerancia; // Requiere tolerancia para los errores de aritmetica de punto flotante.
    }
    return superaVel;
}

/************************************ EJERCICIO recorridoNoCubierto *******************************/
vector<gps> recorridoNoCubierto(viaje v, recorrido r, distancia u) { // 1 + 4 + m * (3 + 1 + n * (3+4) + 4)= 5 + 8m + 7*n*m -> O(n*m) Complejidad de peor caso: n*m
    vector<gps> noCubiertos = {};                                    // 1
    unsigned long n = v.size(), m = r.size();                        // 4
    for (int i = 0; i < m; i++) {                                    // 3, m
        bool cubierto = false;                                       // 1
        for (int j = 0; j < n; j++) {                                // 3, n
            cubierto |= distEnKM(obtenerPosicion(v[j]), r[i]) < u;   // 4
        }
        if (not cubierto)                                            // 2
            noCubiertos.push_back(r[i]);                             // 2
    }
    return noCubiertos;
}

/***************************************** EJERCICIO flota ***************************************/
int flota(vector<viaje> f, tiempo t0, tiempo tf) {
    int resp = 0;
    for (int i = 0; i < f.size(); ++i) {
        if (viajeEnFranjaHoraria(f[i], t0, tf))
            resp++;
    }
    return resp;
}

/************************************** EJERCICIO construirGrilla *******************************/
grilla construirGrilla(gps esq1, gps esq2, int n, int m) {
    grilla resp = {};
    double esq1Latitud = obtenerLatitud(esq1), esq1Longitud = obtenerLongitud(esq1);
    double esq2Latitud = obtenerLatitud(esq2), esq2Longitud = obtenerLongitud(esq2);
    double altoCelda = (esq1Latitud - esq2Latitud) / n;
    double anchoCelda = (esq2Longitud - esq1Longitud) / m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            celda c = {puntoGps(esq1Latitud - altoCelda * i, esq1Longitud + anchoCelda * j),
                       puntoGps(esq1Latitud - altoCelda * (i + 1), esq1Longitud + anchoCelda * (j + 1)),
                       make_tuple(i + 1, j + 1)};
            resp.push_back(c);
        }
    }
    return resp;
}

/************************************* EJERCICIO cantidadDeSaltos ******************************/
int cantidadDeSaltos(grilla g, viaje v) {
    int resp=0;
    // Guardamos los puntos del viaje con el nombre de su celda correspondiente.
    vector<tuple<tuple<tiempo, gps>, nombre>> celdasDeViaje;
    for (int i = 0; i < g.size(); ++i) {
        for (int j = 0; j < v.size(); ++j) {
            if(esCeldaDeCoordenadas(get<1>(v[j]),g[i])){
                celdasDeViaje.push_back(make_tuple(v[j], get<2>(g[i]) ));
            }
        }
    }
    insertionSortCeldas(celdasDeViaje);
    for (int i = 0; i < celdasDeViaje.size() - 1; ++i) {
        if (distanciaEntreCeldas(get<1>(celdasDeViaje[i]),get<1>(celdasDeViaje[i+1])) >= 2){
            resp++;
        }
    }
    return resp;
}

/************************************* EJERCICIO corregirViaje ******************************/
void corregirViaje(viaje& v, vector<tiempo> errores){
    for (int i = 0; i < v.size(); ++i) {
        if (perteneceErrores(obtenerTiempo(v[i]), errores)){
            corregirMedicion(v, i, errores);
        }
    }
}
