#ifndef ARCS_H_INCLUDED
#define ARCS_H_INCLUDED



#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <utility>
#include <limits>

class Arcs
{
    private:
        int m_num;
        std::string m_nomTrajet;
        std::string m_type;
        float m_duree;
        std::pair<int,int> m_SommetAdjacent;
    public:
        Arcs(int num,std::string nom,std::string type,int depart,int arrivee);
        ~Arcs();
        int getDepart();
        int getArrivee();
        std::string getNomTrajet();
        std::string getType();
};

#endif // ARCS_H_INCLUDED
