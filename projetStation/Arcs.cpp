#include "Arcs.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <utility>
#include <limits>

Arcs::Arcs(int num,std::string nom,std::string type,int depart,int arrive)
:m_numTrajet(num),m_nomTrajet(nom),m_type(type)
{
    m_SommetAdjacent.first = depart;
    m_SommetAdjacent.second = arrive;
}

Arcs::~Arcs()
{

}

float Arcs::getDuree()
{
    return m_duree;
}
