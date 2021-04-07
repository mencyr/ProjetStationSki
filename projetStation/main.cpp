#include "Graphe.h"
#include "Sommet.h"
#include "Arcs.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <utility>
#include <limits>
#include <windows.h>



#define NombreChemin 12

int main()
{
    std::vector<bool> choix;
    for(int i=0;i<NombreChemin;i++)
        choix.push_back(false);
    choix[0]=true;
    Graphe Station("Graphe.txt",choix);
    Station.afficherPred(Station.dijkstra(10),10,0);
    return 0;
}



