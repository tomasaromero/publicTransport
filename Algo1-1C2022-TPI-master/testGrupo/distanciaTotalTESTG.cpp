#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(distanciaTotalTEST, viajeDesordenado2){
    gps p1 = puntoGps(0, 0);
    gps p2 = desviarPunto(p1, 2000, 0);
    gps p3 = desviarPunto(p2, 2000, 0);
    gps p4 = desviarPunto(p3, 0, 2000);
    viaje v = { medicion(3.0, p3),
                medicion(1.0, p1),
                medicion(2.0, p2),
                medicion(4.0, p4)};

    EXPECT_NEAR(distanciaTotal(v), 6, 0.01);
}

TEST(distanciaTotalTEST, desvioNegativo){
    gps p1 = puntoGps(-46.860001, -63.860001);
    gps p2 = desviarPunto(p1, -10, 0);
    gps p3 = desviarPunto(p2, 10, 0);

    viaje v = {medicion(2.0, p2),
               medicion(1.0, p1),
               medicion(3.0, p3)};


    EXPECT_NEAR(distanciaTotal(v), 0.02 , 0.001);
}

TEST(distanciaTotalTEST, viajeLargo){
    gps p1 = puntoGps(10, 18);
    gps p2 = puntoGps(18,18);
    gps p3 = puntoGps(18,18);

    viaje v = { medicion(1.0, p1),
                medicion(2.0, p2),
                medicion(3.0, p3)};

    EXPECT_NEAR(distanciaTotal(v), 890.42, 0.5);
}

TEST(distanciaTotalTEST, noSeMueve){
    gps p1 = puntoGps(10, 18);

    viaje v = { medicion(5.0, p1),
                medicion(2.0, p1),
                medicion(3.0, p1)};

    EXPECT_NEAR(distanciaTotal(v), 0, 0.001);
}