#include "Arcs.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <utility>
#include <limits>
#include <cmath>

Arcs::Arcs(int num,std::string nom,std::string type,int depart,int arrive,int altd, int alta)
:m_numTrajet(num),m_nomTrajet(nom),m_type(type)
{
    if (m_type=="N")
    {
        m_duree=(float)abs(altd-alta)*2/100;
    }

    if (m_type=="R")
    {
        m_duree=(float)abs(altd-alta)*3/100;
    }

    if (m_type=="B")
    {
        m_duree=(float)abs(altd-alta)*4/100;
    }

    if (m_type=="V")
    {
        m_duree=(float)abs(altd-alta)*5/100;
    }

    if (m_type=="KL")
    {
        m_duree=(float)abs(altd-alta)/600;
    }

    if (m_type=="SURF")
    {
        m_duree=(float)abs(altd-alta)*10/100;
    }

    if (m_type=="TPH")
    {
        m_duree=4+(float)abs(altd-alta)*2/100;
    }

    if (m_type=="TC")
    {
        m_duree=2+(float)abs(altd-alta)*3/100;
    }

    if (m_type=="TSD")
    {
        m_duree=1+(float)abs(altd-alta)*3/100;
    }

    if (m_type=="TS")
    {
        m_duree=1+(float)abs(altd-alta)*4/100;
    }

    if (m_type=="TK")
    {
        m_duree=1+(float)abs(altd-alta)*4/100;
    }

    if (m_type=="BUS")
    {
        if ((depart==6)&&(arrive==29))
        {
            m_duree=40;
        }
         if ((depart==29)&&(arrive==6))
        {
            m_duree=40;
        }
         if ((depart==29)&&(arrive==35))
        {
            m_duree=30;
        }
         if ((depart==35)&&(arrive==29))
        {
            m_duree=30;
        }
    }


    m_SommetAdjacent.first=depart;
    m_SommetAdjacent.second=arrive;
}

Arcs::~Arcs()
{

}

float Arcs::getDuree()
{
    return m_duree;
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

