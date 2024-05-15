#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

const gps P = puntoGps(-33, -34);
tiempo unaHora = 3600;


TEST(excesoDeVelocidadTEST, sin){
    viaje v = {medicion(0.0, P),
               medicion(unaHora, desviarPunto(P, 1000, 0)),
               medicion(unaHora*2, desviarPunto(P, 2000, 0))}; // 1 KM por hora.

    EXPECT_FALSE(excesoDeVelocidad(v));
}

TEST(excesoDeVelocidadTEST, TodosSuperan){
    viaje v = {medicion(0.0, P),
               medicion(unaHora, desviarPunto(P, 80001, 0)),
               medicion(unaHora*2, desviarPunto(P, 1600001, 0)),
               medicion(unaHora*3, desviarPunto(P, 2400001, 0))};

    EXPECT_TRUE(excesoDeVelocidad(v));
}

TEST(excesoDeVelocidadTEST, UnoSuperaDesordenado){
    viaje v = {medicion(unaHora, desviarPunto(P, 81, 0)),
               medicion(unaHora*2, desviarPunto(P, 80082, 0)),
               medicion(0.0, P),
               medicion(unaHora*3, desviarPunto(P, 201, 0))};

    EXPECT_TRUE(excesoDeVelocidad(v));
}


TEST(excesoDeVelocidadTEST, AlgunoSup){
    viaje v = {medicion(0.0, P),
               medicion(unaHora, desviarPunto(P, 821, 0)),
               medicion(unaHora*2, desviarPunto(P, 80231, 0)),
               medicion(unaHora*3, desviarPunto(P, 240, 0))};

    EXPECT_FALSE(excesoDeVelocidad(v));
}

TEST(excesoDeVelocidadTEST, justo80Km){
    viaje v = {medicion(0.0, P),
               medicion(unaHora, desviarPunto(P, 80000.0000, 0.0)),
               medicion(unaHora*2, desviarPunto(P, 90000.0, 0)),
               medicion(unaHora*3, desviarPunto(P, 100000.0, 0))};

    EXPECT_FALSE(excesoDeVelocidad(v));
}
TEST(excesoDeVelocidadTEST, justo80KmDesordenado){
    viaje v = {medicion(unaHora, P),
               medicion(0.0, desviarPunto(P, 80000.0000, 0.0)),
               medicion(unaHora*3, desviarPunto(P, 90000.0, 0)),
               medicion(unaHora*2, desviarPunto(P, 80000.0, 0))};

    EXPECT_FALSE(excesoDeVelocidad(v));
}