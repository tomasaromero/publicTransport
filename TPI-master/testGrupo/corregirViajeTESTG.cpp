#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(corregirViajeTEST, sinErrores){
    viaje v = {medicion(T0+0, puntoGps(-34.588910, -58.405075)),
               medicion(T0+30, puntoGps(-34.591586, -58.401064)),
               medicion(T0+1051, puntoGps(0, 0))};

    viaje res = {medicion(T0+0, puntoGps(-34.588910, -58.405075)),
                 medicion(T0+30, puntoGps(-34.591586, -58.401064)),
                 medicion(T0+1051, puntoGps(0, 0))};
    vector<tiempo> errores = {};

    corregirViaje(v, errores);
    EXPECT_EQ(v.size(),res.size());

    for (int i = 0; i < res.size(); ++i) {
        EXPECT_NEAR(obtenerLatitud(obtenerPosicion(v[i])),
                    obtenerLatitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_NEAR(obtenerLongitud(obtenerPosicion(v[i])),
                    obtenerLongitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_EQ(obtenerTiempo(v[i]),obtenerTiempo(res[i]));
    }
}

TEST(corregirViajeTEST, faltaElUltimoYElPrimero){
    viaje v = {medicion(T0+0, puntoGps(0, 0)),
               medicion(T0+30, puntoGps(-34.591586, -58.401064)),//mas cercano  en tiempo
               medicion(T0+494, puntoGps(-34.563746, -58.436637)),
               medicion(T0+999, puntoGps(-34.549657, -58.437327)),
               medicion(T0+92, puntoGps(-34.594553, -58.402426)),
               medicion(T0+65, puntoGps(-34.590787, -58.402222)),//
               medicion(T0+230, puntoGps(-34.584572, -58.416942)),
               medicion(T0+873, puntoGps(-34.559236, -58.427499)),
               medicion(T0+675, puntoGps(-34.578941, -58.424878)),
               medicion(T0+1051, puntoGps(0, 0))};

    viaje res = {medicion(T0+0, puntoGps(-34.592270,  -58.400071)),// calcule en base a lo pensado en gpscorregido,pero faltaria chequearlo mejor cn la especif
                 medicion(T0+30, puntoGps(-34.591586, -58.401064)),
                 medicion(T0+494, puntoGps(-34.563746, -58.436637)),
                 medicion(T0+999, puntoGps(-34.549657, -58.437327)),
                 medicion(T0+92, puntoGps(-34.594553, -58.402426)),
                 medicion(T0+65, puntoGps(-34.590787, -58.402222)),
                 medicion(T0+230, puntoGps(-34.584572, -58.416942)),
                 medicion(T0+873, puntoGps(-34.559236, -58.427499)),
                 medicion(T0+675, puntoGps(-34.578941, -58.424878)),
                 medicion(T0+1051, puntoGps(-34.545704, -58.441383))};
    vector<tiempo> errores = {T0+1051,T0+0};

    corregirViaje(v, errores);
    EXPECT_EQ(v.size(),res.size());

    for (int i = 0; i < res.size(); ++i) {
        EXPECT_NEAR(obtenerLatitud(obtenerPosicion(v[i])),
                    obtenerLatitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_NEAR(obtenerLongitud(obtenerPosicion(v[i])),
                    obtenerLongitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_EQ(obtenerTiempo(v[i]),obtenerTiempo(res[i]));
    }
}

TEST(corregirViajeTEST, 3SeguidosDe10){
    viaje v = {};
    for(int i = 0; i < 10; i++){
        v.push_back(medicion(i*3600, desviarPunto(puntoGps(0,0), i * 1000, 0)));
    }
    viaje res = v;
    v[1] = medicion(3600, puntoGps(0,0));
    v[2] = medicion(7200, puntoGps(0,0));
    v[3] = medicion(10800, puntoGps(0,0));

    vector<tiempo> errores = {3600, 7200, 10800};

    corregirViaje(v, errores);

    EXPECT_EQ(v.size(),res.size());

    for (int i = 0; i < res.size(); ++i) {
        EXPECT_NEAR(obtenerLatitud(obtenerPosicion(v[i])),
                    obtenerLatitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_NEAR(obtenerLongitud(obtenerPosicion(v[i])),
                    obtenerLongitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_EQ(obtenerTiempo(v[i]),obtenerTiempo(res[i]));
    }
}

TEST(corregirViajeTEST, 2ErroresSeguidos){
    viaje v = {};
    for(int i = 0; i < 10; i++){
        v.push_back(medicion(i*3600, desviarPunto(puntoGps(0,0), i * 1000, 0)));
    }
    viaje res = v;
    v[1] = medicion(3600, puntoGps(0,0));
    v[2] = medicion(7200, puntoGps(0,0));

    vector<tiempo> errores = {3600, 7200};

    corregirViaje(v, errores);

    EXPECT_EQ(v.size(),res.size());

    for (int i = 0; i < res.size(); ++i) {
        EXPECT_NEAR(obtenerLatitud(obtenerPosicion(v[i])),
                    obtenerLatitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_NEAR(obtenerLongitud(obtenerPosicion(v[i])),
                    obtenerLongitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_EQ(obtenerTiempo(v[i]),obtenerTiempo(res[i]));
    }
}

TEST(corregirViajeTEST, 30SeguidosDe100){
    viaje v = {};
    for(int i = 0; i < 100; i++){
        v.push_back(medicion(i*3600, desviarPunto(puntoGps(0,0), i * 1000, 0)));
    }
    viaje res = v;

    for(int i = 10; i < 40; i++){
        v[i] = medicion(i*3600, puntoGps(0,0));
    }

    vector<tiempo> errores;
    for(int i = 10; i < 40; i++){
        errores.push_back(i*3600);
    }
    corregirViaje(v, errores);

    EXPECT_EQ(v.size(),res.size());

    for (int i = 0; i < res.size(); ++i) {
        EXPECT_NEAR(obtenerLatitud(obtenerPosicion(v[i])),
                    obtenerLatitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_NEAR(obtenerLongitud(obtenerPosicion(v[i])),
                    obtenerLongitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_EQ(obtenerTiempo(v[i]),obtenerTiempo(res[i]));
    }
}

TEST(corregirViajeTEST, 1Cada5ErrorLatyLon){
    viaje v = {};
    for(int i = 0; i < 100; i++){
        v.push_back(medicion(i*3600, desviarPunto(puntoGps(0,0), i * 1000, i * 1500)));
    }
    viaje res = v;

    for(int i = 10; i < 100; i = i + 5){
        v[i] = medicion(i*3600, puntoGps(0,0));
    }

    vector<tiempo> errores;
    for(int i = 10; i < 100; i = i + 5){
        errores.push_back(i*3600);
    }
    corregirViaje(v, errores);

    EXPECT_EQ(v.size(),res.size());

    for (int i = 0; i < res.size(); ++i) {
        EXPECT_NEAR(obtenerLatitud(obtenerPosicion(v[i])),
                    obtenerLatitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_NEAR(obtenerLongitud(obtenerPosicion(v[i])),
                    obtenerLongitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_EQ(obtenerTiempo(v[i]),obtenerTiempo(res[i]));
    }
}

TEST(corregirViajeTEST, 250De1000EnRecta){ // Estos tests son en base a un viaje recto y ordenado. Se podrian testear viajes con otras formas.
    viaje v = {};
    for(int i = 0; i < 1000; i++){
        v.push_back(medicion(i*3600, desviarPunto(puntoGps(0,0), i * 1200 + 100, i * 2350 + 300)));
    }
    viaje res = v;

    for(int i = 1; i < 1000; i = i + 4){
        v[i] = medicion(i*3600, puntoGps(0,0));
    }
    // desordenar(viaje);
    vector<tiempo> errores;
    for(int i = 1; i < 1000; i = i + 4){
        errores.push_back(i*3600);
    }
    corregirViaje(v, errores);

    EXPECT_EQ(v.size(),res.size());

    for (int i = 0; i < res.size(); ++i) {
        EXPECT_NEAR(obtenerLatitud(obtenerPosicion(v[i])),
                    obtenerLatitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_NEAR(obtenerLongitud(obtenerPosicion(v[i])),
                    obtenerLongitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_EQ(obtenerTiempo(v[i]),obtenerTiempo(res[i]));
    }
}

TEST(corregirViajeTEST, 20De100EnRecta){
    viaje v = {};
    for(int i = 0; i < 100; i++){
        v.push_back(medicion(i*36, desviarPunto(puntoGps(0,0), i * 120 + 100, i * 2350 + 300)));
    }
    viaje res = v;

    for(int i = 1; i < 100; i = i + 5){
        v[i] = medicion(i*36, puntoGps(0,0));
    }
    // desordenar(viaje);
    vector<tiempo> errores;
    for(int i = 1; i < 100; i = i + 5){
        errores.push_back(i*36);
    }
    corregirViaje(v, errores);

    EXPECT_EQ(v.size(),res.size());

    for (int i = 0; i < res.size(); ++i) {
        EXPECT_NEAR(obtenerLatitud(obtenerPosicion(v[i])),
                    obtenerLatitud(obtenerPosicion(res[i])), 0.0000001);
        EXPECT_NEAR(obtenerLongitud(obtenerPosicion(v[i])),
                    obtenerLongitud(obtenerPosicion(res[i])), 0.0000001);
        EXPECT_EQ(obtenerTiempo(v[i]),obtenerTiempo(res[i]));
    }
}
