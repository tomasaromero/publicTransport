#include <algorithm>
#include "auxiliares.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

const double pi = 3.14;
double radioTierra = 6378;
// El line coverage de este archivo no llega al 95% porque en ningun test utilizamos guardarGrillaEnArchivo ni guardarRecorridosEnArchivo. Descontando esas funciones es del 100%.
double obtenerLatitud(gps posicion) {
    return get<0>(posicion);
}

double obtenerLongitud(gps posicion) {
    return get<1>(posicion);
}

gps obtenerPosicion(tuple<tiempo, gps> medicion) {
    return get<1>(medicion);
}

tiempo obtenerTiempo(tuple<tiempo, gps> medicion) {
    return get<0>(medicion);
}

double distEnKM(gps posicion1, gps posicion2) {
    double latitud1 = obtenerLatitud(posicion1);
    double latitud2 = obtenerLatitud(posicion2);
    double longitud1 = obtenerLongitud(posicion1);
    double longitud2 = obtenerLongitud(posicion2);

    // obtengo la distancia
    double distanciaLatitud = (latitud2 - latitud1) * pi / 180.0;
    double distanciaLongitud = (longitud2 - longitud1) * pi / 180.0;

    // paso las latitudes a radianes
    latitud1 = (latitud1) * pi / 180.0;
    latitud2 = (latitud2) * pi / 180.0;

    // aplico la formula
    double a = pow(sin(distanciaLatitud / 2), 2) +
               pow(sin(distanciaLongitud / 2), 2) *
               cos(latitud1) * cos(latitud2);

    double c = 2 * asin(sqrt(a));
    return radioTierra * c;
}

gps desviarPunto(gps p, double desvioMtsLatitud, double desvioMtsLongitud){
    double lat = obtenerLatitud(p);
    double lon = obtenerLongitud(p);

    double dx = desvioMtsLatitud / 1000;
    double dy = desvioMtsLongitud / 1000;
    double new_latitude = lat - (dx / radioTierra) * (180 / pi);            // Cambio de signo.
    double new_longitude = lon + (dy / radioTierra) * (180 / pi) / cos(lat * pi / 180);
    return puntoGps(new_latitude, new_longitude);

}

gps puntoGps(double latitud, double longitud) {
    return make_tuple(latitud, longitud);
}

tuple<tiempo, gps> medicion(tiempo t, gps g) {
    return make_tuple(t, g);
}

void guardarGrillaEnArchivo(grilla g, string nombreArchivo){
    ofstream myfile;
    float esq1_lat, esq2_lat, esq1_lng, esq2_lng;
    int name_0, name_1;

    myfile.open(nombreArchivo);
    myfile << std::fixed << std::setprecision(5);
    for(int i = 0; i < g.size(); i++){
        esq1_lat = get<0>(get<0>(g[i]));
        esq1_lng = get<1>(get<0>(g[i]));

        esq2_lat = get<0>(get<1>(g[i]));
        esq2_lng = get<1>(get<1>(g[i]));

        name_0 = get<0>(get<2>(g[i]));
        name_1 = get<1>(get<2>(g[i]));

        myfile << esq1_lat << "\t"
               << esq1_lng << "\t"
               << esq2_lat << "\t"
               << esq2_lng << "\t"
               << "(" << name_0 << "," << name_1 << ")"
               << endl;

    }
    myfile.close();

}

void guardarRecorridosEnArchivo(vector<recorrido> recorridos, string nombreArchivo){
    ofstream myfile;
    float lat, lng;

    myfile.open(nombreArchivo);
    myfile << std::fixed << std::setprecision(5);
    for(int i = 0; i < recorridos.size(); i++){
        for(int k = 0; k < recorridos[i].size(); k++){
            lat= get<0>(recorridos[i][k]);
            lng= get<1>(recorridos[i][k]);

            myfile << i << "\t"
                   << lat << "\t"
                   << lng << endl;
        }
    }
    myfile.close();

}

tuple<tiempo, tiempo> obtenerMinMaxTiempo(const viaje &v){               // |v| = n.  6 + n*(4+4+4) = 6 + 12n -> O(n) Complejidad de peor caso: Lineal
    int tMin=0,tMax=0;                                                   // 2
    for (int i = 0; i < v.size(); ++i) {                                 // 4, n
        if (obtenerTiempo(v[i]) < obtenerTiempo(v[tMin]))                // 3
            tMin = i;                                                    // 1
        else if (obtenerTiempo(v[i]) > obtenerTiempo(v[tMax]))           // 3
            tMax = i;                                                    // 1
    }
    return make_tuple(obtenerTiempo(v[tMin]), obtenerTiempo(v[tMax]));
}

void insertionSort(viaje &v){                                                            // 4n*7n*c1 -> O(n^2) Complejidad de peor caso: Cuadratica
    for (int i = 0; i < v.size(); i++) {                                                 // 4, n
        for (int j = i; j > 0 && obtenerTiempo(v[j]) < obtenerTiempo(v[j - 1]); j--) {   // 7, n
            swap(v[j], v[j - 1]);                                                        // c1 (tiempo constante)
        }                                                                                //
    }
}

distancia distanciaViaje(viaje v){                                         // 1 + n(5+3) -> 1 + 8n -> O(n) Complejidad de peor caso: Lineal
    distancia d=0;                                                         // 1
    for (int i = 0; i < v.size() - 1; i++) {                                 // 5, n
        d += distEnKM(obtenerPosicion(v[i]), obtenerPosicion(v[i+1]));     // 3 (distEnKm es O(1), es decir constante)
    }
    return d;
}

double velocidad(tuple<tiempo, gps> p1, tuple<tiempo, gps> p2){
    double distancia = distEnKM(obtenerPosicion(p2), obtenerPosicion(p1));
    double tiempo = (obtenerTiempo(p2)- obtenerTiempo(p1))/3600;
    double vel = distancia/tiempo;
    return vel;
}

bool viajeEnFranjaHoraria(const viaje &v, tiempo t0, tiempo tf){
    tuple<tiempo, tiempo> tiempos = obtenerMinMaxTiempo(v);
    return get<0>(tiempos) <= tf && get<1>(tiempos) >= t0;
}

distancia distanciaEntreCeldas(nombre n1, nombre n2){
    return sqrt(pow(get<0>(n1) - get<0>(n2), 2) + pow(get<1>(n1) - get<1>(n2), 2));
}

bool esCeldaDeCoordenadas(gps p,celda c){
    bool entreLatitudes  = obtenerLatitud(get<1>(c)) < obtenerLatitud(p) && obtenerLatitud(p) <= obtenerLatitud(get<0>(c));
    bool entreLongitudes = obtenerLongitud(get<0>(c)) <= obtenerLongitud(p) && obtenerLongitud(p) < obtenerLongitud(get<1>(c));
    return entreLatitudes && entreLongitudes;
}

void insertionSortCeldas(vector<tuple<tuple<tiempo, gps>, nombre>> &c){
    for (int i = 0; i < c.size(); i++) {
        for (int j = i; j > 0 && obtenerTiempo(get<0>(c[j])) < obtenerTiempo(get<0>(c[j - 1])); j--)
            swap(c[j], c[j - 1]);
    }
}

bool perteneceErrores(tiempo t, const vector<tiempo> &errores){
    bool pertenece = false;
    for (int i = 0; i < errores.size() && not(pertenece); ++i) {
        if (t == errores[i])
            pertenece = true;
    }
    return pertenece;
}

void corregirMedicion(viaje &v, int k, const vector<tiempo> &errores) {
    tuple<int, int> tiemposPQ = losDosPuntosMasCercanos(v, k, errores);
    gps correccion = gpsCorregido(v, k, get<0>((tiemposPQ)), get<1>(tiemposPQ));
    v[k] = make_tuple(obtenerTiempo(v[k]), correccion);
}

tuple<int, int> losDosPuntosMasCercanos(const viaje &v, int k, const vector<tiempo> &errores){
    int P=0, Q=0;
    tiempo max = get<1>(obtenerMinMaxTiempo(v));
    tiempo minP = max;
    tiempo minQ = max;
    tiempo actual;
    for (int i = 0; i < v.size(); i++) {
        actual = abs(obtenerTiempo(v[k]) - obtenerTiempo(v[i]));
        if (not(perteneceErrores(obtenerTiempo(v[i]), errores))) {
            if (actual < minP) {
                P = i;
                minP = actual;
            }
            if (i != P && actual < minQ) {
                Q = i;
                minQ = actual;
            }
        }
    }
    return make_pair(P, Q);
}
/*
gps gpsCorregido(viaje v, int K, int P, int Q){ // P es el punto mas cercano a K.
    gps        pP = obtenerPosicion(v[P]),  pQ = obtenerPosicion(v[Q]);
    tiempo     tP = obtenerTiempo(v[P]),    tQ = obtenerTiempo(v[Q]),   tK = obtenerTiempo(v[K]);
    tiempo     intT         = (tK < tP ? -1.0 : 1.0) * abs(tK - tP) / abs(tQ - tP);//
    distancia  latPQ        = (tP < tQ) ? obtenerLatitud(pQ) - obtenerLatitud(pP) : obtenerLatitud(pP) - obtenerLatitud(pQ);
    distancia  lonPQ        = (tP < tQ) ? obtenerLongitud(pQ) - obtenerLongitud(pP) : obtenerLongitud(pP) - obtenerLongitud(pQ);
    distancia  latDiff      = latPQ * intT;
    distancia  lonDiff      = lonPQ * intT;
    gps        pK           = puntoGps(obtenerLatitud(pP) + latDiff,obtenerLongitud(pP) + lonDiff);

    return pK;
}

/*/
gps gpsCorregido(viaje v, int K, int P, int Q){ // P es el punto mas cercano a K.
    gps        pP = obtenerPosicion(v[P]),  pQ = obtenerPosicion(v[Q]);
    tiempo     tP = obtenerTiempo(v[P]),    tQ = obtenerTiempo(v[Q]),   tK = obtenerTiempo(v[K]);
    distancia  latDiffEntrePyQ        = (tP < tQ) ? obtenerLatitud(pQ) - obtenerLatitud(pP) : obtenerLatitud(pP) - obtenerLatitud(pQ);
    distancia  lonDiffEntrePyQ        = (tP < tQ) ? obtenerLongitud(pQ) - obtenerLongitud(pP) : obtenerLongitud(pP) - obtenerLongitud(pQ);
    tiempo     intervaloTiempo         = (tK < tP ? -1.0 : 1.0) * abs(tK - tP) / abs(tQ - tP);//no se modifica
    distancia  latPQ        = (tP < tQ) ? obtenerLatitud(pQ) - obtenerLatitud(pP) : obtenerLatitud(pP) - obtenerLatitud(pQ);
    distancia  lonPQ        = (tP < tQ) ? obtenerLongitud(pQ) - obtenerLongitud(pP) : obtenerLongitud(pP) - obtenerLongitud(pQ);
    distancia  latDiff      = latPQ * intervaloTiempo;
    distancia  lonDiff      = lonPQ * intervaloTiempo;
    //SOHCAHTOA; quiero saber angulo de inclinacion de la recta entre los puntos P y Q.
    double anguloRectaDePyQ= atan(latDiffEntrePyQ/lonDiffEntrePyQ);
    double anguloRectaDePyK= atan(latDiff /lonDiff );
    double velMedia_CAH= (lonDiffEntrePyQ/ cos(anguloRectaDePyQ))/abs(tP-tQ);//velocidad en coordenadas/seg, no en m/s o km/h
    double velMedia_SIN= (latDiffEntrePyQ/ sin(anguloRectaDePyQ))/abs(tP-tQ);//velocidad en coordenadas/seg

    //
    gps        pK           = puntoGps(obtenerLatitud(pP) + latDiff,obtenerLongitud(pP) + lonDiff);
    distancia  latDiffEntrePyK        = (tP < tK) ? obtenerLatitud(pK) - obtenerLatitud(pP) : obtenerLatitud(pP) - obtenerLatitud(pK);
    distancia  lonDiffEntrePyK        = (tP < tK) ? obtenerLongitud(pK) - obtenerLongitud(pP) : obtenerLongitud(pP) - obtenerLongitud(pK);
    //
    distancia hipotenusaDePyK_SOHCAHTOA=(lonDiff/ cos(anguloRectaDePyQ));//si  lon  no varía da 0
    distancia hipotenusaDePyK_DistKM= distEnKM(get<1>(v[P]),pK);//solo referencia
    distancia hipotenusaDePyK_DistCoord= sqrt(pow(latDiffEntrePyK ,2)+ pow(lonDiffEntrePyK ,2));
    //calculo Alernativo:si varian tanto lon y lat, sólo datos dados
    distancia hipotenusaDePyK_VelMedia_CAH=velMedia_CAH*abs(tP-tK);
    distancia hipotenusaDePyK_VelMedia_SIN=velMedia_SIN*abs(tP-tK);
    distancia latDiffpPypK=(hipotenusaDePyK_VelMedia_CAH*sin(anguloRectaDePyQ));
    distancia lonDiffpPyPk=(hipotenusaDePyK_VelMedia_CAH*(cos(anguloRectaDePyQ)));
    //por relacion trigonometrica
    distancia lonDiffpPyPk_relTrig=(hipotenusaDePyK_VelMedia_CAH*(sin(pi/2-anguloRectaDePyQ)));
    gps pK2= puntoGps(obtenerLatitud(pP) + latDiffpPypK,obtenerLongitud(pP) + lonDiffpPyPk);

     return pK2;
}
