#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include "Arcs.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <utility>
#include <limits>

class Sommet
{
    private:
        std::vector<std::pair<Sommet *,Arcs *>> m_adjacent;
        std::string m_nom;
        int m_altitude;
        int m_numSommet;
    public:
        Sommet(int num,std::string nom,int alt);
        ~Sommet();

        int getnbr();
        std::vector<std::pair<Sommet*,Arcs *>> getVectAdjda();
        void setAdjacence(Sommet * som,Arcs * arc);
        float getpoids(float num);
        int GetAlt();
};

#endif // SOMMET_H_INCLUDED
