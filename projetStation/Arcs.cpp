#include "Arcs.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <utility>
#include <limits>

Arcs::Arcs(int num,std::string nom,std::string type,int depart,int arrive)
:m_numTrajet(num),m_nomTrajet(nom),m_type(type)//,m_duree()
{

if (m_type=="N")
{
    m_duree=abs(depart-arrive)*2/100;
}

if (m_type=="R")
{
    m_duree=abs(depart-arrive)*3/100;
}

if (m_type=="B")
{
    m_duree=abs(depart-arrive)*4/100;
}

if (m_type=="V")
{
    m_duree=abs(depart-arrive)*5/100;
}

if (m_type=="KL")
{
    m_duree=abs(depart-arrive)*(1/6)/100;
}

if (m_type=="SURF")
{
    m_duree=abs(depart-arrive)*10/100;
}

if (m_type=="TPH")
{
    m_duree=4+abs(depart-arrive)*2/100;
}

if (m_type=="TC")
{
    m_duree=2+abs(depart-arrive)*3/100;
}

if (m_type=="TSD")
{
    m_duree=1+abs(depart-arrive)*3/100;
}

if (m_type=="TS")
{
    m_duree=1+abs(depart-arrive)*4/100;
}

if (m_type=="TK")
{
    m_duree=1+abs(depart-arrive)*4/100;
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
std::cout << m_duree << std::endl;


m_SommetAdjacent.first=depart;
m_SommetAdjacent.second=arrive;
}

Arcs::~Arcs()
{

}
