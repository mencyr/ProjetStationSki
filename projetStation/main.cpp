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




int main()
{

    Graphe Station("Graphe.txt");

    Station.interface0(); // Interface utilisateur

    return 0;
}



