#include "Graphe.h"


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <utility>
#include <limits>


Graphe::Graphe(std::string nom)  ///CONSTRUCTEUR DU GRAPHE AVEC OUVERTURE DU FICHIER
{
    int w,x,y,z;
    std::string passage, passage2;
    std::vector<std::pair<int,int>> passage3;
    std::ifstream fichier(nom);
    if(fichier)
    {
        fichier >> w;
        m_ordre = w;
        for(int i=0;i<w;i++)
        {
            fichier >> x >> passage >> y;
            m_listeSommet.push_back(new Sommet(i,passage,y));
        }
        fichier >> w;
        m_taille =w;
        for(int i=0;i<w;i++)
        {
            fichier >> x >> passage >> passage2 >> y >> z;
            passage3.push_back(std::make_pair(y-1,z-1));
            m_listeArcs.push_back(new Arcs(i,passage,passage2,y-1,z-1));
        }
        for(int i=0;i<m_taille;i++)   //affectation des adjacences
        {
            std::cout << i + 1<< " ";  ///temporaire
            x=passage3[i].first;
            y=passage3[i].second;
            std::cout << x + 1<< " " <<  y + 1 << std::endl;  ///temporaire
            m_listeSommet[x]->setAdjacence(m_listeSommet[y],m_listeArcs[i]);
        }
    }
}


Graphe::~Graphe()    ///DECONSTRUCTEURS DU GRAPHE
{
    for(auto elem : m_listeArcs)
    {
        delete elem;
    }
    for(auto elem : m_listeSommet)
    {
        delete elem;
    }
}




void Graphe::afficherTrajet()
{

    int numero;

    std::cout<< "Choisir un numero de trajet pour savoir son point d'arrivee et son point de depart"<<std::endl;
    std::cout<<"Mon choix :  ";
    std::cin>> numero;
    numero=numero-1;



    std::cout<<"Le point de depart du trajet est:";
    std::cout<< m_listeArcs[numero]->getDepart() << std::endl;
    std::cout<<"Le point d'arrivee du trajet est:";
    std::cout<< m_listeArcs[numero]->getArrivee() << std::endl;

}


void Graphe::afficherVoisins()
{
    int numero;

    std::cout<<"Choisir un point pour connaitre les trajets qui y partent et qui y arrivent"<<std::endl;
    std::cout<<"Mon choix :  ";
    std::cin>>numero;
    numero=numero-1;

    for(int i=0;i< m_taille;i++)
    {
        if(numero==m_listeArcs[i]->getDepart())
        {
            std::cout<<" => Un des trajets qui part du point numero  "<< numero+1 <<"  est:  ";
            std::cout<<m_listeArcs[i]->getNomTrajet()<<std::endl;
            std::cout<<"    Le type du trajet est ";
            std::cout<<m_listeArcs[i]->getType()<<std::endl;
        }

        if(numero==m_listeArcs[i]->getArrivee())
        {   std::cout<<" => Un des trajets qui arrive au point numero  "<< numero+1 <<"  est:  ";
            std::cout<<m_listeArcs[i]->getNomTrajet()<<std::endl;
            std::cout<<"    Le type du trajet est ";
            std::cout<<m_listeArcs[i]->getType()<<std::endl;
        }
    }

}



std::vector<Sommet *> Graphe::dijkstra(int depart,int arrivee)
{
    std::vector<Sommet *> pred;
    return pred;
}


void Graphe::afficherPred(std::vector<Sommet *> pred)
{

}
