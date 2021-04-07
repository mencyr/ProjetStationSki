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



void gotoligcol( int lig, int col )
{
// ressources
COORD mycoord;

mycoord.X = col;
mycoord.Y = lig;
SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}


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
            std::cout << i + 1<< " ";  ///temporaire
            x=passage3[i].first;
            y=passage3[i].second;
            std::cout << x + 1<< " " <<  y + 1 << std::endl;  ///temporaire
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


std::vector<bool> Graphe::interface4()
{
        int preferences=-1;
        std::cout<<std::endl;
        std::cout<<"          CHOISIR SES PREFERENCES"<<std::endl;
       // std::cout<<std::endl;
        std::cout<<"                    0.   Pistes Noires"<<std::endl;
       // std::cout<<std::endl;
        std::cout<<"                    1.   Pistes Rouges"<<std::endl;
       // std::cout<<std::endl;
        std::cout<<"                    2.   Pistes Bleues"<<std::endl;
       // std::cout<<std::endl;
        std::cout<<"                    3.   Pistes Vertes"<<std::endl;
     //   std::cout<<std::endl;
        std::cout<<"                    4.   Piste de Kilometre Lance"<<std::endl;
      //  std::cout<<std::endl;
        std::cout<<"                    5.   Domaine reserve au Surf"<<std::endl;
      //  std::cout<<std::endl;
        std::cout<<"                    6.   Telepherique"<<std::endl;
      //  std::cout<<std::endl;
        std::cout<<"                    7.   Telecabine"<<std::endl;
       // std::cout<<std::endl;
        std::cout<<"                    8.   Telesiege debrayable"<<std::endl;
       // std::cout<<std::endl;
        std::cout<<"                    9.   Telesiege"<<std::endl;
       // std::cout<<std::endl;
        std::cout<<"                    10.  Teleski"<<std::endl;
      //  std::cout<<std::endl;
        std::cout<<"                    11.  Navette Bus"<<std::endl;
      //  std::cout<<std::endl;
        std::cout<<"                    12.  J'ai finis"<<std::endl;
        std::cout<<std::endl;
        std::cout<<std::endl;

        std::cout<<"  Entrer le numero des trajets que vous ne souhaitez pas emprunter"<<std::endl;



        std::vector<bool> choix;
        for(int i=0;i<NombreChemin;i++)
        {
            choix.push_back(false);
        }

            while(preferences!=12)
            {
                gotoligcol(10,60);
                std::cout<<"     Votre choix:";
                std::cin>>preferences;


                for(int i=0;i<12;i++)
                {
                    if(preferences==i)
                    {
                    gotoligcol(i+2,3);
                    std::cout<<"X";
                    choix[i]=true;
                    }
                }
            }





 return choix;
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
    for(int i=0;i<m_ordre;i++)
    {
        std::cout << i +1<< " : " << pred[i].first+1 << " " <<  pred[i].second << std::endl;
    }
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


int Graphe::interface0()
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
            interface0();
            break;

        case 2:
            system("CLS");
            afficherVoisins();
            interface0();
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
            interface0();
            break;
    }

    return 0;

}
