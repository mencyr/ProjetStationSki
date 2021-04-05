#include "Arcs.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <utility>
#include <limits>

Arcs::Arcs(int num,std::string nom,std::string type,int depart,int arrivee)
    :m_num(num), m_nomTrajet(nom), m_type(type)
{
    m_SommetAdjacent.first = depart;
    m_SommetAdjacent.second = arrivee;

}

Arcs::~Arcs()
{

}




int Arcs::getDepart()
{

    return m_SommetAdjacent.first;
}

int Arcs::getArrivee()
{

    return m_SommetAdjacent.second;
}

std::string Arcs::getNomTrajet()
{
    return m_nomTrajet;
}

std::string Arcs::getType()
{
    return m_type;
}

