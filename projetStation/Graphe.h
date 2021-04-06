#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include "Sommet.h"
#include "Arcs.h"



#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <utility>
#include <limits>

class Graphe
{
    private:
        std::vector<Sommet *> m_listeSommet;
        std::vector<Arcs *> m_listeArcs;
        int m_ordre,m_taille;
    public:
        Graphe(std::string nom);
        ~Graphe();

        void afficherTrajet();
        void afficherVoisins();
        std::vector<Sommet *> dijkstra(int depart,int arrivee);
        void afficherPred(std::vector<Sommet *> pred);
        int interface0();
        std::vector<bool> interface4();

};

#endif // GRAPHE_H_INCLUDED
