#ifndef PERSONNE_H_INCLUDED
#define PERSONNE_H_INCLUDED


#include "Sommet.h"
#include "Arcs.h"
#include "Graphe.h"


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <utility>
#include <limits>
#include <windows.h>




class Personne
{
private:
        std::string m_pseudo;
        std::string m_mdp;
        std::vector<bool> m_preference;


public:
        Personne(std::string m_pseudo,std::vector<bool> inteface4);
        ~Personne();


        void enregistrerNouveauProfils();
        void chargerProfils();


};











#endif // PERSONNE_H_INCLUDED
