#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;
vector<viaje> flotaT = {{
                   medicion(2.1,puntoGps(2.5, 2.856)),
                   medicion(1.2,puntoGps(2.5, 2.89997)),
                   medicion(2.6,puntoGps(2.5, 2.89998))},
           {
                   medicion(2.45,puntoGps(2.5, 2.89996)),
                   medicion(2.6,puntoGps(2.5, 2.89997)),
                   medicion(2.7,puntoGps(2.5, 2.89998))},
           {
                   medicion(1.99,puntoGps(2.5, 2.89996)),
                   medicion(1.95,puntoGps(2.5, 2.89997)),
                   medicion(1.98,puntoGps(2.5, 2.89998))}
};

TEST(flotaTotalTEST, todosAntesDeFranja2){
    EXPECT_EQ(flota(flotaT,2.0,2.5),2);
}

TEST(flotaTotalTEST, fueraDeFranja){
    vector<viaje> f = {{medicion(10, puntoGps(0,0)),
                        medicion(50, puntoGps(0,0))}};
    EXPECT_EQ(flota(f, 20, 40),1);
}

TEST(flotaTotalTEST, igualFranja){
    vector<viaje> f = {{medicion(20, puntoGps(0,0)),
                        medicion(40, puntoGps(0,0))}};
    EXPECT_EQ(flota(f, 20, 40),1);
}

TEST(flotaTotalTEST, todosAntesFranja){
    vector<viaje> f = {{medicion(20, puntoGps(0,0)),
                        medicion(40, puntoGps(0,0))}};
    EXPECT_EQ(flota(f, 50, 60),0);
}

TEST(flotaTotalTEST, todosDespuesFranja){
    vector<viaje> f = {{medicion(20, puntoGps(0,0)),
                        medicion(40, puntoGps(0,0))}};
    EXPECT_EQ(flota(f, 10, 15),0);
}

