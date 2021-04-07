#include "Sommet.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <utility>
#include <limits>

Sommet::Sommet(int num,std::string nom,int alt)
:m_numSommet(num),m_nom(nom),m_altitude(alt)
{

}

Sommet::~Sommet()
{

}

int Sommet::getnbr()
{
    return m_numSommet;
}

void Sommet::setAdjacence(Sommet * som,Arcs * arc)
{
    m_adjacent.push_back(std::make_pair(som,arc));
}

std::vector<std::pair<Sommet*,Arcs *>> Sommet::getVectAdjda()
{
    return m_adjacent;    // getteur du vecteur de pair, le conteneur d'adjacent
}

float Sommet::getpoids(float num)
{
    for(auto elem : m_adjacent)
    {
        if(elem.first->getnbr() == num)
        {
            return elem.second->getDuree();
        }
    }
    return 0;
}


int Sommet::GetAlt()
{
    return m_altitude;
}
