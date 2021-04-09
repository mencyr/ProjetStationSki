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

void interfaceBfsDijkstra(std::pair<int,int> DebutFin,Graphe Station);
void interface0();
std::vector<bool> interface4();
std::pair<int,int> interface34();


int main()
{
    interface0();
    return 0;
}

void interface0()
{
    int menu;
    std::vector<bool> choix;
    std::pair<int,int> DF;
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
    std::cout<<"    5.    Connaitre le chemin de remonte ideal : "<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<"   Saisir votre choix"<<std::endl;
    std::cin>>menu;

    switch(menu)
    {
        case 1:
            system("CLS");
            for(int i=0;i<NombreChemin;i++)
                choix.push_back(false);
            break;
        case 2:
            system("CLS");
            for(int i=0;i<NombreChemin;i++)
                choix.push_back(false);
            break;

        case 3:
            system("CLS");
            for(int i=0;i<NombreChemin;i++)
                choix.push_back(false);
            DF=interface34();
            break;

        case 4:
            system("CLS");
            choix=interface4();
            DF=interface34();
            break;
        case 5:
            system("CLS");
            for(int i=0;i<NombreChemin;i++)
                choix.push_back(false);
            break;

        default:
            system("CLS");
            interface0();
            break;
    }
    Graphe Station("Graphe.txt",choix);
    switch(menu)
    {
        case 1:
            Station.afficherTrajet();
            interface0();
            break;
        case 2:
            Station.afficherVoisins();
            interface0();
            break;

        case 3:
            std::cout << std::endl << std::endl;
            interfaceBfsDijkstra(DF,Station);
            system("CLS");
            interface0();
            break;

        case 4:
            std::cout << std::endl << std::endl;
            interfaceBfsDijkstra(DF,Station);
            system("CLS");
            interface0();
            break;
        case 5:
            Station.reseau();
            interface0();
        default:
            system("CLS");

            break;
    }
}

std::vector<bool> interface4()
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
            gotoligcol(10,60);
            std::cout<<"                    ";
            for(int i=0;i<12;i++)
            {
                if(preferences==i)
                {
                    if(!choix[i])
                    {
                        gotoligcol(i+2,17);
                        std::cout<<"X";
                        choix[i]=true;
                    }
                    else
                    {
                        gotoligcol(i+2,17);
                        std::cout<<" ";
                        choix[i]=false;
                    }
                }
            }
        }
 return choix;
}

std::pair<int,int> interface34()
{
    std::pair<int,int> DebutFin;
    system("CLS");
    std::cout << "Veuillez renseignez le numero de votre sommet actuel :" << std::endl;
    std::cin >> DebutFin.first;
    system("CLS");
    std::cout << "Veuillez renseignez le numero du sommet final : " << std::endl;
    std::cin >> DebutFin.second;
    DebutFin.first--;
    DebutFin.second--;
    system("CLS");
    return DebutFin;
}

void interfaceBfsDijkstra(std::pair<int,int> DebutFin,Graphe Station)
{
    int type;
    std::vector<bool> choix {false,false,false};
    std::cout << "Faire votre choix : " << std::endl << std::endl;
    std::cout<<"                    0.   Afficher les plus courts chemins depuis le sommet de depart : "<<std::endl;
    std::cout<<"                    1.   Afficher le plus court chemin entre les deux sommets : "<<std::endl;
    std::cout<<"                    2.   Revenir au menu : "<<std::endl;
    gotoligcol(10,20);
    std::cout<<"     Votre choix:";
    std::cin>>type;
    gotoligcol(10,20);
    std::cout<<"                    ";
    for(int i=0;i<3;i++)
    {
        if(type==i)
        {
            for(int i=0;i<3;i++)
            {
                gotoligcol(i+3,17);
                std::cout<<" ";
                choix[i]=false;
            }
        }
    }
    if(type == 0)
    {
        Station.afficherPredBFSAll(Station.BFS(DebutFin.first));
        Station.afficherPredDijkstraAll(Station.dijkstra(DebutFin.first));
        std::cout << std::endl << "Entrer n'importe quel chiffre pour revenir au choix d'affichage : ";
        std::cin >> type;
        system("CLS");
        interfaceBfsDijkstra(DebutFin,Station);
    }
    if(type == 1)
    {
        Station.afficherPredBFS(Station.BFS(DebutFin.first),DebutFin.second);
        Station.afficherPredDijkstra(Station.dijkstra(DebutFin.first),DebutFin.second);
        std::cout << std::endl << "Entrer n'importe quel chiffre pour revenir au choix d'affichage : ";
        std::cin >> type;
        system("CLS");
        interfaceBfsDijkstra(DebutFin,Station);
    }
}
