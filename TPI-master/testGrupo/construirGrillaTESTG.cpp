#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

int cantidadApariciones(tuple<gps,gps, nombre> e, grilla g) {
    int apariciones = 0;
    for (int i = 0; i < g.size(); ++i) {
        if (e == g[i])
            apariciones++;
    }
    return apariciones;
}

bool sonGrillasIguales(grilla g1, grilla g2) {
    if (g1.size() != g2.size())
        return false;
    bool res = true;
    vector<int> apariciones1(g1.size(), 0), apariciones2(g2.size(), 0);
    for (int i = 0; i < g1.size(); i++){
        if (not(cantidadApariciones(g1[i], g1) ==  cantidadApariciones(g1[i], g2) && cantidadApariciones(g2[i], g2) ==  cantidadApariciones(g2[i], g1)))
            res = false;
    }
    return res;
}

TEST(construirGrillaTEST, grillaCuadrada){

    int n = 3;
    int m = 3;

    gps esq1 = puntoGps(55.0,102.0);
    gps esq2 = puntoGps(37.0,120.0);

    grilla gres = {make_tuple(puntoGps(55.0,102.0), puntoGps(49.0,108.0), make_tuple(1,1)),
                   make_tuple(puntoGps(55.0,108.0), puntoGps(49.0,114.0), make_tuple(1,2)),
                   make_tuple(puntoGps(55.0,114.0), puntoGps(49.0,120.0), make_tuple(1,3)),
                   make_tuple(puntoGps(49.0,102.0), puntoGps(43.0,108.0), make_tuple(2,1)),
                   make_tuple(puntoGps(49.0,108.0), puntoGps(43.0,114.0), make_tuple(2,2)),
                   make_tuple(puntoGps(49.0,114.0), puntoGps(43.0,120.0), make_tuple(2,3)),
                   make_tuple(puntoGps(43.0,102.0), puntoGps(37.0,108.0), make_tuple(3,1)),
                   make_tuple(puntoGps(43.0,108.0), puntoGps(37.0,114.0), make_tuple(3,2)),
                   make_tuple(puntoGps(43.0,114.0), puntoGps(37.0,120.0), make_tuple(3,3))
    };


    grilla g = construirGrilla(esq1,esq2,n,m);

    EXPECT_EQ(n*m, g.size());
    EXPECT_TRUE(sonGrillasIguales(gres, g));
}

TEST(construirGrillaTEST, grillaSingular){

    int n = 1;
    int m = 1;

    gps esq1 = puntoGps(12.0,43.0);
    gps esq2 = puntoGps(4.5,47.5);

    grilla gres = {make_tuple(puntoGps(12.0,43.0), puntoGps(4.5,47.5), make_tuple(1,1))};


    grilla g = construirGrilla(esq1,esq2,n,m);

    EXPECT_EQ(n*m, g.size());
    EXPECT_TRUE(sonGrillasIguales(gres, g));
}

TEST(construirGrillaTEST, grilla2por2){

    int n = 2;
    int m = 2;

    gps esq1 = puntoGps(12.0,43.0);
    gps esq2 = puntoGps(4.5,47.5);


    grilla gres = {make_tuple(puntoGps(12.0,43.0), puntoGps((4.5+12.0)/2, (43+47.5)/2), make_tuple(1,1)),
                   make_tuple(puntoGps(12.0,(43+47.5)/2), puntoGps((4.5+12.0)/2,47.5), make_tuple(1,2)),
                   make_tuple(puntoGps((4.5+12.0)/2,43.0), puntoGps(4.5,(43+47.5)/2), make_tuple(2,1)),
                   make_tuple(puntoGps((4.5+12.0)/2,(43+47.5)/2), puntoGps(4.5,47.5), make_tuple(2,2))};


    grilla g = construirGrilla(esq1,esq2,n,m);

    EXPECT_EQ(n*m, g.size());
    EXPECT_TRUE(sonGrillasIguales(gres, g));
}

TEST(construirGrillaTEST, nombresCorrectosDistanciaParNParMImparArgComparar){

    int n = 2;
    int m = 3;

    gps esq1 = puntoGps(-33.0,-58.0);
    gps esq2 = puntoGps(-33.9,-57.1);

    grilla gres = {make_tuple(puntoGps(-33.0,-58.0), puntoGps(-33.45,-57.7), make_tuple(1,1)),
                   make_tuple(puntoGps(-33.0,-57.7), puntoGps(-33.45,-57.4), make_tuple(1,2)),
                   make_tuple(puntoGps(-33.0,-57.4), puntoGps(-33.45,-57.1), make_tuple(1,3)),
                   make_tuple(puntoGps(-33.45,-58.0), puntoGps(-33.9,-57.7), make_tuple(2,1)),
                   make_tuple(puntoGps(-33.45,-57.7), puntoGps(-33.9,-57.4), make_tuple(2,2)),
                   make_tuple(puntoGps(-33.45,-57.4), puntoGps(-33.9,-57.1), make_tuple(2,3))
    };


    grilla g = construirGrilla(esq1,esq2,n,m);

    EXPECT_EQ(n*m, g.size());
    EXPECT_TRUE(sonGrillasIguales(gres, g));
}
