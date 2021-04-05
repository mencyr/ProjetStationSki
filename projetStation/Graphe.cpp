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
            m_listeArcs.push_back(new Arcs(i,passage,passage2,y,z));
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

}


void Graphe::afficherVoisins()
{

}


auto comparaison = [](std::pair<int,int> Pair1, std::pair<int,int> Pair2)
{
    return Pair2.second < Pair1.second;   //Fonction de comparaison
};

std::vector<int> Graphe::dijkstra(int depart)
{
    std::vector<int> pred;
    std::pair<int,int> passageA;   //Declaration pair de passage
    std::vector<bool> marquage;
    std::vector<float> distance;
    std::priority_queue<std::pair<int,float>,std::vector<std::pair<int,float>>, decltype(comparaison)> Queueue(comparaison);
    //declaration de la pirority queue qui prend La fonction de comparaison
    for(int i=0;i<m_ordre;i++)   //initialisation
    {
        pred.push_back(-1);
        distance.push_back(1000);   //distance infini
        marquage.push_back(false);  //sommet non découvert
    }
    distance[depart]=0;   //Sauf pour le premier sommet choisis en parametre du protoype
    marquage[depart]=true;
    Queueue.push(std::make_pair(depart,distance[depart]));
    while(!Queueue.empty())
    {
        passageA.first = Queueue.top().first;   //Pair de passage
        passageA.second = Queueue.top().second;
        Queueue.pop();    //on pop la queue
        if(marquage[passageA.first])   //si le soumet dans la paire de passage est marqué
        {
            marquage[passageA.first] = true;
        for(auto elem : m_listeSommet[passageA.first]->getVectAdjda()) // boucle des tout les adjacents
        {
            if(marquage[elem.first->getnbr()]== false)   //si le sommet n'est pas marqué
            {
                marquage[elem.first->getnbr()] = true;   //Marquage du sommet
                if(distance[elem.first->getnbr()] < elem.second->getDuree() + distance[m_listeSommet[passageA.first]->getnbr()])
                {       //si la nouvelle distance est plus petite que la derniere on remplace
                distance[elem.first->getnbr()] = elem.second->getDuree() + distance[ m_listeSommet[passageA.first]->getnbr()];
                }
                Queueue.push(std::make_pair(elem.first->getnbr(),distance[elem.first->getnbr()]));   //push dans la queue
                pred[elem.first->getnbr()] = m_listeSommet[passageA.first]->getnbr();
                // vecteur de predesseur qui servira pour l'afichage
            }
        }
        }
    }
    return pred;
}


void Graphe::afficherPred(std::vector<int> pred,int depart,int fin)
{
    float numpred;   ///AFFICHAGE GRACE AUX VECTEUR DE PREDESSECEUR
    float poids=m_listeSommet[fin]->getpoids(pred[fin]);
    std::cout << std::endl;
    std::cout << fin ;
    numpred=pred[fin];
    while(numpred!=-1)   //affichage du chemin  //pour les deux boucles d'affichages on utilise le vecteur de pred
    {
        std::cout << " <-- "<< numpred;
        numpred=pred[numpred];
    }
    std::cout << std::endl;
    numpred=fin;   //affichage des poids
    float ctp=0;    //affiche la distance totale
    bool aff=false;
    while(numpred!=depart)
    {
        if(aff)
        {
        std::cout << " + ";
        }              //affiche chaque distance
        aff = true;
        std::cout << m_listeSommet[numpred]->getpoids(pred[numpred]);
        ctp+= m_listeSommet[numpred]->getpoids(pred[numpred]);
        numpred = pred[numpred];
    }
    std::cout << " = ";
    std::cout << ctp;

}
