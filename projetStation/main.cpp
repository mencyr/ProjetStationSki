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


int main()
{
    Graphe Station("Graphe.txt");
    std::vector<int> t;
    t= Station.dijkstra(1);
    return 0;
}
