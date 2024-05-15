#ifndef TRANSPORTEURBANO_AUXILIARES_H
#define TRANSPORTEURBANO_AUXILIARES_H

#include "definiciones.h"
#include "string"

double obtenerLatitud(gps posicion);
double obtenerLongitud(gps posicion);
gps obtenerPosicion(tuple<tiempo, gps> medicion);
tiempo obtenerTiempo(tuple<tiempo, gps> medicion);
double distEnKM(gps posicion1, gps posicion2);
gps desviarPunto(gps p, double desvioMtsLatitud, double desvioMtsLongitud);
gps puntoGps(double latitud, double longitud);
tuple<tiempo, gps> medicion(tiempo t, gps g);
void guardarGrillaEnArchivo(grilla g, string nombreArchivo);
void guardarRecorridosEnArchivo(vector<recorrido> recorridos, string nombreArchivo);
tuple<tiempo, tiempo> obtenerMinMaxTiempo(const viaje &v);
void insert(viaje &v, int i);
void insertionSort(viaje &v);
distancia distanciaViaje(viaje v);
double velocidad(tuple<tiempo, gps> v1, tuple<tiempo, gps> v2);
bool viajeEnFranjaHoraria(const viaje &v, tiempo t0, tiempo tf);
distancia distanciaEntreCeldas(nombre  n1, nombre n2);
bool esCeldaDeCoordenadas(gps p,celda c);
void insertionSortCeldas(vector<tuple<tuple<tiempo, gps>, nombre>> &c);
bool perteneceErrores(tiempo t, const vector<tiempo> &errores);
void corregirMedicion(viaje &v, int k,const vector<tiempo> &errores);
tuple<int, int> losDosPuntosMasCercanos(const viaje &v, int k, const vector<tiempo> &errores);
gps gpsCorregido(viaje v, int i, int p, int q);
#endif //TRANSPORTEURBANO_AUXILIARES_H
