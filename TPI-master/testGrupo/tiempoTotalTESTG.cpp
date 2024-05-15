#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

const gps P = puntoGps(-33.5, -58.89996);
const gps Q = puntoGps(-40, 23.46);


TEST(tiempoTotalTEST, viajeConMinimoDistintoAlPrimero){
    viaje v = {medicion(1.1, P),
               medicion(1.5, Q),
               medicion(1.135, Q),
               medicion(5.5, P),
               medicion(9, Q),
               medicion(2.5, P)};
    EXPECT_DOUBLE_EQ(tiempoTotal(v),7.9);
}

TEST(tiempoTotalTEST, viajeDesordenado){
    viaje v = {medicion(T0+90, Q),
               medicion(T0+1.5, Q),
               medicion(T0+900, Q),
               medicion(T0+5.5, P),
               medicion(T0+0, P),
               medicion(T0+2.5, P)};
    EXPECT_DOUBLE_EQ(tiempoTotal(v),900);
}