#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

template<typename T>
bool included(T elem, vector<T> container){
    for (int i = 0; i < container.size(); ++i) {
        if (container[i] == elem){return true;}
    }
    return false;
}

template<typename T>
void ASSERT_ELEMENTS(vector<T> container, vector<T> elems) {
    for(int i = 0; i < elems.size(); i++ ) {
        ASSERT_TRUE(included(elems[i], container));
    }

}

using namespace std;

const gps P = puntoGps(-31.465027, -64.212973);
const recorrido R = {P,
                     desviarPunto(P, 1000, 0),
                     desviarPunto(P, 2000, 0),
                     desviarPunto(P, 3000, 0),
                     desviarPunto(P, 4000, 0),
                     desviarPunto(P, 5000, 0),
                     desviarPunto(P, 6000, 0),
                     desviarPunto(P, 7000, 0),
                     desviarPunto(P, 8000, 0),
                     desviarPunto(P, 9000, 0),
                      };

TEST(recorridoNoCubiertoTEST, todosCubiertos){
    viaje v = {};
    vector<int> desvios(R.size(), 0);
    desvios[0] = 90;
    desvios[1] = 30;
    desvios[2] = -90;
    desvios[3] = -30;

    for(int i = 0; i < R.size(); i++){
        v.push_back(medicion(i, desviarPunto(R[i], 0, desvios[i])));
    }

    vector<gps> res = recorridoNoCubierto(v, R, 0.1);
    EXPECT_EQ(res.size(), 0);
    ASSERT_ELEMENTS(res, {});

}

TEST(recorridoNoCubiertoTEST, todosNoCubiertos){
    viaje v = {};
    vector<int> desvios(R.size(), 0);
    desvios[0] = 99;
    desvios[1] = 901;
    desvios[2] = 2040;
    desvios[3] = 70000;

    for(int i = 0; i < R.size(); i++){
        v.push_back(medicion(i, desviarPunto(R[i], 0, desvios[i])));
    }

    vector<gps> res = recorridoNoCubierto(v, R, 0.1);
    EXPECT_EQ(res.size(), 3);
    ASSERT_ELEMENTS(res, {R[1],R[2],R[3]});

}

TEST(recorridoNoCubiertoTEST, imperfecto){
    const recorrido Rec = {P,
                          desviarPunto(P, 1000, 0),
                          desviarPunto(P, 2000, 0),
                          desviarPunto(P, 3000, 0),
    };
    viaje v = {};
    vector<int> desvios(Rec.size(), 0);
    desvios[0] = 1000;
    desvios[1] = 7000;
    desvios[2] = 901;
    desvios[3] = 0;

    for(int i = 0; i < Rec.size(); i++){
        v.push_back(medicion(i, desviarPunto(Rec[i], desvios[i], 0)));
    }

    vector<gps> res = recorridoNoCubierto(v, Rec, 0.1);
    EXPECT_EQ(res.size(), 2);
    ASSERT_ELEMENTS(res, {Rec[0], Rec[2]});
}

