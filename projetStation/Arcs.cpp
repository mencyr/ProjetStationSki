#include "Arcs.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <utility>
#include <limits>

Arcs::Arcs(int num,std::string nom,std::string type,int depart,int arrivee)
    :m_num(num), m_nomTrajet(nom), m_type(type), m_duree()
{

}

Arcs::~Arcs()
{

}




int Arcs::getDepart() const
{

    return m_depart;
}

int Arcs::getArrivee() const
{

    return m_arrivee;
}

