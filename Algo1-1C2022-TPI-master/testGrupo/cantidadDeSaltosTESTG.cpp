#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(cantidadDeSaltosTEST, unSalto){
    grilla g = construirGrilla(puntoGps(3000,0),
                               puntoGps(0, 3000), 3, 3);

    gps p1 = puntoGps(2900, 10);
    gps p2 = puntoGps(10, 2800);

    viaje v = {medicion(1, p1),
               medicion(2, p2)};

    EXPECT_EQ(cantidadDeSaltos(g,v),1);
}

TEST(cantidadDeSaltosTEST, todosSaltosOrdenados2){
    grilla g = construirGrilla(puntoGps(3000,0),
                               puntoGps(0, 3000), 6, 6);

    gps p1 = puntoGps(1, 1);        // 6, 1
    gps p2 = puntoGps( 2000, 2000); // 3, 5
    gps p3 = puntoGps( 100, 100);   // 6, 1

    viaje v = {medicion(1.3, p1),
               medicion(2.1, p2),
               medicion(3, p3)};

    EXPECT_EQ(cantidadDeSaltos(g,v),2);
}

TEST(cantidadDeSaltosTEST, todosSaltosDesordenados){
    grilla g = construirGrilla(puntoGps(3000,0),
                               puntoGps(0, 3000), 6, 6);

    gps p1 = puntoGps(1, 1);        // 6, 1
    gps p2 = puntoGps( 2000, 2000); // 3, 5
    gps p3 = puntoGps( 100, 100);   // 6, 1

    viaje v = {medicion(2, p2),
               medicion(1, p1),
               medicion(3, p3),
               medicion(6, p3),
               medicion(10, p3),
               medicion(5, p3),
               medicion(8, p3)
    };

    EXPECT_EQ(cantidadDeSaltos(g,v),2);
}

TEST(cantidadDeSaltosTEST, sinSaltos){
    grilla g = construirGrilla(puntoGps(3000,0),
                               puntoGps(0, 3000), 6, 6);

    gps p1 = puntoGps(1, 1);        // 6, 1
    gps p2 = puntoGps( 150, 150);   // 6, 1
    gps p3 = puntoGps( 100, 100);   // 6, 1

    viaje v = {medicion(2, p2),
               medicion(1, p1),
               medicion(3, p3)};

    EXPECT_EQ(cantidadDeSaltos(g,v),0);
}

TEST(cantidadDeSaltosTEST, dosPuntosSinSaltos){
    grilla g = construirGrilla(puntoGps(80, 0),
                               puntoGps(0, 80), 2, 2);

    gps p1 = puntoGps(20, 30);
    gps p2 = puntoGps(70, 50);

    viaje v = {medicion(1, p1),
               medicion(2, p2)};

    EXPECT_EQ(cantidadDeSaltos(g, v), 0);
}

TEST(cantidadDeSaltosTEST, noTodosDesordenados){
    grilla g = construirGrilla(puntoGps(100, 0),
                               puntoGps(0, 100), 10, 10);

    gps p1 = puntoGps(1, 1);
    gps p2 = puntoGps(70, 50);
    gps p3 = puntoGps(10,  1);
    gps p4 = puntoGps(70, 40);

    viaje v = {medicion(1, p1),
               medicion(3, p3),
               medicion(4, p4),
               medicion(2, p2)};

    EXPECT_EQ(cantidadDeSaltos(g, v), 3);
}