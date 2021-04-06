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
            //std::cout << i + 1<< " ";  ///temporaire
            x=passage3[i].first;
            y=passage3[i].second;
            //std::cout << x + 1<< " " <<  y + 1 << std::endl;  ///temporaire
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

    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<< "    Choisir un numero de trajet pour savoir son point d'arrivee et son point de depart"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"     Mon choix :  ";
    std::cin>> numero;
    numero=numero-1;



    std::cout<<"        Le point de depart du trajet est:";
    std::cout<< m_listeArcs[numero]->getDepart() << std::endl;
    std::cout<<"        Le point d'arrivee du trajet est:";
    std::cout<< m_listeArcs[numero]->getArrivee() << std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;

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
            std::cout<<"       => Un des trajets qui part du point numero  "<< numero+1 <<"  est:  ";
            std::cout<<m_listeArcs[i]->getNomTrajet()<<std::endl;
            std::cout<<"    Le type du trajet est ";
            std::cout<<m_listeArcs[i]->getType()<<std::endl;
        }

        if(numero==m_listeArcs[i]->getArrivee())
        {   std::cout<<"       => Un des trajets qui arrive au point numero  "<< numero+1 <<"  est:  ";
            std::cout<<m_listeArcs[i]->getNomTrajet()<<std::endl;
            std::cout<<"    Le type du trajet est ";
            std::cout<<m_listeArcs[i]->getType()<<std::endl;
        }
    }
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;

}


int Graphe::interface4()
{
        int preferences;
        std::cout<<std::endl;
        std::cout<<"          CHOISIR SES PREFERENCES"<<std::endl;
        std::cout<<std::endl;
        std::cout<<"          0.   N"<<std::endl;
        std::cout<<std::endl;
        std::cout<<"          1.   R"<<std::endl;
        std::cout<<std::endl;
        std::cout<<"          2.   B"<<std::endl;
        std::cout<<std::endl;
        std::cout<<"          3.   V"<<std::endl;
        std::cout<<std::endl;
        std::cout<<"          4.   KL"<<std::endl;
        std::cout<<std::endl;
        std::cout<<"          5.   SURF"<<std::endl;
        std::cout<<std::endl;
        std::cout<<"          6.   TDH"<<std::endl;
        std::cout<<std::endl;
        std::cout<<"          7.   TC"<<std::endl;
        std::cout<<std::endl;
        std::cout<<"          8.   TSD"<<std::endl;
        std::cout<<std::endl;
        std::cout<<"          9.   TS"<<std::endl;
        std::cout<<std::endl;
        std::cout<<"          10.  TK"<<std::endl;
        std::cout<<std::endl;
        std::cout<<"          11.  BUS"<<std::endl;
        std::cout<<std::endl;
        std::cout<<std::endl;
        std::cout<< "Votre choix:";
        std::cin>>preferences;

        if(preferences==0)
        {
            std::cout<<"   =>Voulez-vous emprunter une piste noire ?";
                int i=0;
                std::cout<<"    1. oui        2. non  :";
                std::cin>>i;
                if (i==1)
                    {

                    }
                if (i==2)
                    {

                    }

        }

        if(preferences==1)
            {
                std::cout<<"   =>Voulez-vous emprunter une piste rouge ?";
                int i=0;
                std::cout<<"    1. oui        2. non  :";
                std::cin>>i;
                if (i==1)
                    {

                    }
                if (i==2)
                    {

                    }

            }

        if(preferences==2)
        {
            std::cout<<"   =>Voulez-vous emprunter une piste bleue ?";
            int i=0;
            std::cout<<"    1. oui        2. non  :";
            std::cin>>i;
                if (i==1)
                    {

                    }
                if (i==2)
                    {

                    }

        }

        if(preferences==3)
        {
            std::cout<<"   =>Voulez-vous emprunter une piste verte ?";
            int i=0;
            std::cout<<"    1. oui        2. non  :";
            std::cin>>i;
                if (i==1)
                    {

                    }
                if (i==2)
                    {

                    }

        }

        if(preferences==4)
        {
            std::cout<<"   =>Voulez-vous emprunter un KL ? ";
            int i=0;
            std::cout<<"    1. oui        2. non  :";
            std::cin>>i;
                if (i==1)
                    {

                    }
                if (i==2)
                    {

                    }

        }

        if(preferences==5)
        {
             std::cout<<"   =>Voulez-vous emprunter une piste pour les surfs ?";
             int i=0;
            std::cout<<"    1. oui        2. non  :";
            std::cin>>i;
                if (i==1)
                    {

                    }
                if (i==2)
                    {

                    }

        }

        if(preferences==6)
        {
            std::cout<<"   =>Voulez-vous emprunter un TDH ?";
            int i=0;
            std::cout<<"    1. oui        2. non  :";
            std::cin>>i;
                if (i==1)
                    {

                    }
                if (i==2)
                    {

                    }

        }

        if(preferences==7)
        {
            std::cout<<"   =>Voulez-vous emprunter un TC ?";
            int i=0;
            std::cout<<"    1. oui        2. non  :";
            std::cin>>i;
                if (i==1)
                    {

                    }
                if (i==2)
                    {

                    }

        }

        if(preferences==8)
        {
            std::cout<<"   =>Voulez-vous emprunter un TSD ?";
            int i=0;
            std::cout<<"    1. oui        2. non  :";
            std::cin>>i;
                if (i==1)
                    {

                    }
                if (i==2)
                    {

                    }

        }

        if(preferences==9)
        {
            std::cout<<"   =>Voulez-vous emprunter un TS ?";
            int i=0;
            std::cout<<"    1. oui        2. non  :";
            std::cin>>i;
                if (i==1)
                    {

                    }
                if (i==2)
                    {

                    }

        }

        if(preferences==10)
        {
            std::cout<<"   =>Voulez-vous emprunter un TK ?";
            int i=0;
            std::cout<<"    1. oui        2. non  :";
            std::cin>>i;
                if (i==1)
                    {

                    }
                if (i==2)
                    {

                    }

        }

        if(preferences==11)
        {
            std::cout<<"   =>Voulez-vous emprunter un Bus ?";
            int i=0;
            std::cout<<"    1. oui        2. non  :";
            std::cin>>i;
                if (i==1)
                    {

                    }
                if (i==2)
                    {

                    }

        }




 return 0;
}


std::vector<Sommet *> Graphe::dijkstra(int depart,int arrivee)
{
    std::vector<Sommet *> pred;
    return pred;
}


void Graphe::afficherPred(std::vector<Sommet *> pred)
{

}


int Graphe::interface()
{
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<"       INTERFACE UTILISATEUR"<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<"    1.    Choisir un numero de trajet pour savoir son point d'arrivee et son point de depart"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"    2.    Choisir un point pour connaitre les trajets qui y partent et qui y arrivent"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"    3.    Connaitre l'itineraire le plus rapide entre deux points de la station"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"    4.    Connaitre le chemin le plus rapide en fonction de mes preferences"<<std::endl;
    std::cout<<std::endl;


    int choix;
    std::cout<<std::endl;
    std::cout<<"   Saisir votre choix"<<std::endl;
    std::cin>>choix;

    switch(choix)
    {
        case 1:
            system("CLS");
            afficherTrajet();
            interface();
            break;

        case 2:
            system("CLS");
            afficherVoisins();
            interface();
            break;

        case 3:
            system("CLS");
            break;

        case 4:
            system("CLS");
            interface4();
            break;


        default:
            system("CLS");
            interface();
            break;
    }
        return 0;
}
