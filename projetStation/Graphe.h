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
        std::pair<Sommet *,Sommet *> m_SourcePuit;
        int m_ordre,m_taille;
    public:
        Graphe(std::string nom,std::vector<bool> choix);
        ~Graphe();

        std::vector<std::pair<Sommet*,Arcs *>> getSuccesseur(int i);

        void afficherTrajet();
        void afficherVoisins();

        std::vector<std::pair<int,float>> dijkstra(int depart);
        void afficherPredDijkstraAll(std::vector<std::pair<int,float>> pred);
        void afficherPredDijkstra(std::vector<std::pair<int,float>> pred,int fin);

        std::vector<int> BFS(int depart);
        void afficherPredBFSAll(std::vector<int> pred);
        void afficherPredBFS(std::vector<int> pred,int fin);

        void reseau();
        void FordFulkerson();
};

void gotoligcol( int lig, int col );


#endif // GRAPHE_H_INCLUDED
