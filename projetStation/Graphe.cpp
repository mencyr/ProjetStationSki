#include "Graphe.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <utility>
#include <limits>
#include <windows.h>

#define NombreChemin 12

Graphe::Graphe(std::string nom,std::vector<bool> choix)  ///CONSTRUCTEUR DU GRAPHE AVEC OUVERTURE DU FICHIER
{
    int w,x,y,z,ctp;
    std::vector<std::string> type{"N","R","B","V","KL","SURF","TPH","TC","TSD","TS","TK","BUS"};
    std::vector<std::string> elimination;
    for(int i=0;i<NombreChemin;i++)
    {
        if(choix[i])
        {
            elimination.push_back(type[i]);
        }
    }
    int tailleElimation= elimination.size(); //necessaire si l'on veut eviter les warnings
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
            m_listeArcs.push_back(new Arcs(i,passage,passage2,y-1,z-1,m_listeSommet[y-1]->GetAlt(),m_listeSommet[z-1]->GetAlt()));
        }
        for(int i=0;i<m_taille;i++)   //affectation des adjacences
        {
            ctp=0;
            //std::cout << i + 1<< " ";  ///temporaire
            x=passage3[i].first;
            y=passage3[i].second;
            //std::cout << x + 1<< " " <<  y + 1 << std::endl;  ///temporaire
            for(int j=0;j<tailleElimation;j++)
            {
                if(elimination[j]==m_listeArcs[i]->getType())
                {
                    ctp++;
                }
            }
            if(ctp==0)
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
    std::cout<<"        Le sommet de depart du trajet est : ";
    std::cout<< m_listeArcs[numero]->getDepart() << std::endl;
    std::cout<<"        Le sommet d'arrivee du trajet est : ";
    std::cout<< m_listeArcs[numero]->getArrivee() << std::endl;
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
            std::cout<<"       => Un des trajets qui part du point numero "<< numero+1 <<" est: ";
            std::cout<<m_listeArcs[i]->getNomTrajet()<<std::endl;
            std::cout<<"    Le type du trajet est ";
            std::cout<<m_listeArcs[i]->getType()<< "| Il arrive au sommet : "<< m_listeArcs[i]->getArrivee()<< std::endl;
        }

        if(numero==m_listeArcs[i]->getArrivee())
        {   std::cout<<"       => Un des trajets qui arrive au point numero "<< numero+1 <<" est: ";
            std::cout<<m_listeArcs[i]->getNomTrajet()<<std::endl;
            std::cout<<"    Le type du trajet est ";
            std::cout<<m_listeArcs[i]->getType()<< "| Il part du sommet : "<< m_listeArcs[i]->getDepart()<<std::endl;
        }
    }
    std::cout<<std::endl;
}




auto comparaison = [](std::pair<int,int> Pair1, std::pair<int,int> Pair2)
{
    return Pair2.second < Pair1.second;   //Fonction de comparaison
};

std::vector<std::pair<int,float>> Graphe::dijkstra(int depart)
{
    std::vector<std::pair<int,float>> pred;
    std::pair<int,float> passageA;   //Declaration pair de passage
    std::vector<bool> marquage;
    std::vector<float> distance;
    std::priority_queue<std::pair<int,float>,std::vector<std::pair<int,float>>, decltype(comparaison)> Queueue(comparaison);
    //declaration de la pirority queue qui prend La fonction de comparaison
    for(int i=0;i<m_ordre;i++)   //initialisation
    {
        pred.push_back(std::make_pair(-1,0));
        distance.push_back(1000);   //distance infini
        marquage.push_back(false);  //sommet non d�couvert
    }
    distance[depart]=0;   //Sauf pour le premier sommet choisis en parametre du protoype
    Queueue.push(std::make_pair(depart,distance[depart]));
    while(!Queueue.empty())
    {
        passageA.first = Queueue.top().first;   //Pair de passage
        passageA.second = Queueue.top().second;
        Queueue.pop();    //on pop la queue
        for(auto elem : m_listeSommet[passageA.first]->getVectAdjda()) // boucle des tout les adjacents
        {
            if(marquage[elem.first->getnbr()]== false)   //si le sommet n'est pas marqu�
            {
                marquage[elem.first->getnbr()] = true;   //Marquage du sommet
                if(distance[elem.first->getnbr()] > elem.second->getDuree() + distance[m_listeSommet[passageA.first]->getnbr()])
                {       //si la nouvelle distance est plus petite que la derniere on remplace
                    distance[elem.first->getnbr()] = elem.second->getDuree() + distance[ m_listeSommet[passageA.first]->getnbr()];
                    Queueue.push(std::make_pair(elem.first->getnbr(),distance[elem.first->getnbr()]));   //push dans la queue
                    pred[elem.first->getnbr()].first = passageA.first;
                    pred[elem.first->getnbr()].second = elem.second->getDuree();
                    // vecteur de predesseur qui servira pour l'afichage
                }
            }
        }
    }
    return pred;
}


void Graphe::afficherPred(std::vector<std::pair<int,float>> pred,int depart,int fin)
{
    float numpred;   ///AFFICHAGE GRACE AUX VECTEUR DE PREDESSECEUR
    float poids=m_listeSommet[fin]->getpoids(pred[fin].first);
    std::cout << std::endl;
    std::cout << fin +1;
    numpred=pred[fin].first;
    while(numpred!=-1)   //affichage du chemin  //pour les deux boucles d'affichages on utilise le vecteur de pred
    {
        std::cout << " <-- "<< numpred+1;
        numpred=pred[numpred].first;
    }
    std::cout << std::endl;
    numpred=pred[fin].first;   //affichage des poids
    float numpoids=pred[fin].second;
    bool aff=false;
    float ctp=0;
    while(numpred!=-1)
    {
        if(aff)
        {
        std::cout << " + ";
        }              //affiche chaque distance
        aff = true;
        std::cout << numpoids;
        ctp+=numpoids;
        poids = numpred;
        numpred=pred[numpred].first;
        numpoids=pred[poids].second;
    }
    std::cout << " = ";
    std::cout << ctp;

}
