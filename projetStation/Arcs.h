#ifndef ARCS_H_INCLUDED
#define ARCS_H_INCLUDED

#include "Sommet.h"

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
        int m_numTrajet;
        std::string m_nomTrajet;
        std::string m_type;
        int m_duree;
        std::pair<Sommet,Sommet> m_SommetAdjacent;
    public:
        Arcs();
        ~Arcs();
};

#endif // ARCS_H_INCLUDED
