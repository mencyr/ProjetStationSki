#include "Personne.h"
#include "Arcs.h"
#include "Graphe.h"
#include "Sommet.h"
#include "Gotoligcol.h"


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <utility>
#include <limits>
#include <windows.h>


#include <algorithm>
#include <conio.h>
#include <ios>

#define NombreChemin 12




Personne::Personne(std::string m_pseudo,std::vector<bool> interface4)
{
    int menuprofil;
    m_preference=interface4;
    std::cout << "                            -----Enregistrement ou choix du profil-----\n\n";
    std::cout << "Si vous voulez enregistrer un nouveau profil en fonction des parametres que vous venez d'entrer, tapper 1:" << std::endl;
    std::cout << "Si vous voulez charger votre profil deja enregistre, tapper 2:" << std::endl;
    std::cout << "Pour continuer et connaitre le chemin le plus rapide en fonction de vos preferences, tapper 4:" << std::endl;
    std::cin>>menuprofil;


    switch(menuprofil)
    {
    case 1 :
        gotoligcol(0,33);
        system("cls");
        enregistrerNouveauProfils();
        //system("cls");
        break;

    case 2 :
        gotoligcol(0,39);
        system("cls");
        chargerProfils();
        system("cls");
        break;

    case 4 :
        std::cout << "t'es le best" << std::endl;
        break;
        system("cls");
    }



}



void Personne::enregistrerNouveauProfils()
{

    std::cout << "Selectionner votre nom : " << std::endl;
    std::cin >> m_pseudo;
    std::cout << "mot de passe : " << std::endl;
    std::cin >> m_mdp;
    std::ofstream monFlux;
    monFlux.open("Profils.txt",std::ios_base::app | std::ios_base::out);

    if(monFlux)
    {
    monFlux << "Pseudo: " << m_pseudo << " ";
    monFlux << "|| Mot de passe: " << m_mdp << " ";
    monFlux << "|| Preference du profil: ";
        for(int i=0; i<NombreChemin; i++)
        {
            if(m_preference[i] == true)
                monFlux << "1";
            else
                monFlux << "0";
        }
    }
    monFlux << std::endl;
    monFlux.close();
}




void Personne::chargerProfils()
{

    std::cout << "Selectionner votre nom : " << std::endl;
    std::cin >> m_pseudo;
    std::cout << "Selectionner votre mot de passe : " << std::endl;
    std::cin >> m_mdp;


    std::ifstream fichier;
    fichier.open("Profils.txt");
    std::ofstream flux;
    flux.open("Profils.txt",std::ios_base::app | std::ios_base::out);
    std::vector<std::string> pseudo;
    std::vector<std::string> motDePasse;
    std::string PS;
    std::string MDP;
    std::string ligne;
    std::string nouv;
    int j=0;
    if (fichier)
    {
        do
        {
        fichier >> PS;
        fichier >> MDP;
        pseudo.push_back(PS);
        motDePasse.push_back(MDP);
        j++;
        }while(getline(fichier,ligne));
    }
    for(int i=0; i<j; i++)
    {
         if(pseudo[i]==m_pseudo)
         {
             for(int j=0;j<NombreChemin;j++)
             {
//                 if(m_preference[i][j]=='1')
//                 {
//                     m_pseudo[j]==fichier(true);
//                 }
             }
         }
     }
        fichier.close();
    flux.close();
}

//if(m_preference[i] == true)
//                monFlux << "1";


Personne::~Personne()
{

}
