#include "Graphe.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <utility>
#include <limits>
#include <windows.h>
#include <cmath>

#define NombreChemin 12
#define infini 100000

void gotoligcol( int lig, int col )
{
// ressources
COORD mycoord;

mycoord.X = col;
mycoord.Y = lig;
SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}

Graphe::Graphe(std::string nom,std::vector<bool> choix)                           ///CONSTRUCTEUR DU GRAPHE AVEC OUVERTURE DU FICHIER
{
    int w,x,y,z,h,ctp;
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
            fichier >> x >> passage >> passage2 >> y >> z >> h;
            passage3.push_back(std::make_pair(y-1,z-1));
            m_listeArcs.push_back(new Arcs(i,passage,passage2,y-1,z-1,m_listeSommet[y-1]->GetAlt(),m_listeSommet[z-1]->GetAlt(),h));
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

Graphe::~Graphe()                                                                 ///DESTRUCTEUR DU GRAPHE
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

void Graphe::afficherTrajet()                                                     ///AFFICHAGE DES BORNES DE L'ARC
{

    int numero;

    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<< "    Choisir un numero de trajet pour savoir son point d'arrivee et son point de depart"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"     Mon choix :  ";
    std::cin>> numero;
    if( 1<=numero && 95>=numero)
    {
        numero=numero-1;
    std::cout<<"        Le sommet de depart du trajet est : ";
    std::cout<< m_listeArcs[numero]->getDepart() << std::endl;
    std::cout<<"        Le sommet d'arrivee du trajet est : ";
    std::cout<< m_listeArcs[numero]->getArrivee() << std::endl;
    std::cout<<std::endl;
    } else
        {
            std::cout<<std::endl;
            std::cout<< "  veuillez entrer un nombre valide"<<std::endl;
            //afficherTrajet();
        }

}

void Graphe::afficherVoisins()                                                    ///AFFICHAGE DES ARCS ENTRANTS ET SORTANTS D'UN SOMMET
{
    int numero;
    std::cout<<"Choisir un point pour connaitre les trajets qui y partent et qui y arrivent"<<std::endl;
    std::cout<<"Mon choix :  ";
    std::cin>>numero;
    if( 1<=numero && 37>=numero)
    {

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
    }   else
        {
        std::cout<<std::endl;
        std::cout<< "  veuillez entrer un nombre valide"<<std::endl;
        }
}

std::vector<std::pair<Sommet*,Arcs *>> Graphe::getSuccesseur(int i)               ///SUCCESSEUR DU SOMMET I
{
    std::vector<std::pair<Sommet*,Arcs *>> successeurtacaptemonreuf;
    for(int j=0;j<m_ordre;j++)
    {
        for(auto elem : m_listeSommet[j]->getVectAdjda())
        {
            if(elem.first->getnbr()==i)
            {
                successeurtacaptemonreuf.push_back(elem);
            }
        }
    }
    return successeurtacaptemonreuf;
}

auto comparaison = [](std::pair<int,int> Pair1, std::pair<int,int> Pair2)         ///FONCTION DE COMPARAISON DES POIDS POUR LE PRIORITY QUEUE
{
    return Pair2.second < Pair1.second;   //Fonction de comparaison
};

std::vector<std::pair<int,float>> Graphe::dijkstra(int depart)                    ///ALGORITHME DE DIJKSTRA
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

void Graphe::afficherPredDijkstraAll(std::vector<std::pair<int,float>> pred)      ///AFFICHAGE DE TOUT LES PLUS COURT CHEMIN AVEC DIJKSTRA
{
    float numpred,numpoids,poids;
    bool aff=false;
    float ctp=0;
    std::cout << std::endl << std::endl;
    std::cout << std::endl << std::endl;
    std::cout << "Voici tout les chemins plus courts (en minutes) pour rejoindre les autres sommets :" << std::endl << std::endl;
    for(int i=0;i<m_ordre;i++)  //pour tout les sommets
    {
        std::cout << i +1;
        numpred=pred[i].first;
        while(numpred!=-1)   //affichage du chemin  //pour les deux boucles d'affichages on utilise le vecteur de pred
        {
            std::cout << " <-- "<< numpred+1;
            numpred=pred[numpred].first;
        }
        std::cout << std::endl;
        numpred=pred[i].first;   //affichage des poids
        numpoids=pred[i].second;
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
        std::cout << ctp << std::endl;
        ctp=0;
        aff=false;
    }
    std::cout << std::endl;
}

void Graphe::afficherPredDijkstra(std::vector<std::pair<int,float>> pred,int fin) ///AFFICHAGE D'UN SEUL PLUS COURT CHEMIN AVEC DIJKSTRA
{
    float numpred;
    int ctp2=0;   ///AFFICHAGE GRACE AUX VECTEUR DE PREDESSECEUR
    float poids=m_listeSommet[fin]->getpoids(pred[fin].first);
    std::cout << std::endl << std::endl;
    std::cout << std::endl << std::endl;
    std::cout << fin +1;
    numpred=pred[fin].first;
    while(numpred!=-1)   //affichage du chemin  //pour les deux boucles d'affichages on utilise le vecteur de pred
    {
        ctp2++;
        numpred=pred[numpred].first;
    }
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
    std::cout << std::endl;
}

std::vector<int> Graphe::BFS(int depart)                                          ///ALGORITHME DU PLUS COURT CHEMIN, BFS
{
    std::vector<int> pred;       //predecesseur
    int num;
    std::vector<Sommet*> succ; //successeur
    std::vector<std::pair<Sommet*,Arcs*>> succ2;
    std::vector<bool> marquage; //notera false si il a déjà été trouvé true sinon
    std::queue<int> file;       //file indispensabe pour le programme
    for(int i=0;i<m_ordre;i++)   //initialisation
    {
        pred.push_back(-1);
        marquage.push_back(false);
    }
    file.push(depart);          /// au rang 0
    marquage[depart]=true;       //le sommet est decouvert il devient "noir"
    do                          ///au rang n
    {
        num = file.front(); //transfert du haut de la pile dans la variable num
        file.pop();
        succ2=m_listeSommet[num]->getVectAdjda();   //succ prend les successeur
        for(auto elem :succ2)
        {
            succ.push_back(elem.first);
        }
        for(int i=0;i<succ.size();i++)
        {
            if(marquage[succ[i]->getnbr()]==0)
            {
                marquage[succ[i]->getnbr()]=true;     //le sommet est decouvert il devient "noir"
                file.push(succ[i]->getnbr());          //num devient le nouveau predecesseur de i
                pred[succ[i]->getnbr()] = num;
            }
        }
    }while(!file.empty());
    return pred;
}

void Graphe::afficherPredBFSAll(std::vector<int> pred)                            ///AFFICHAGE DE TOUT LES PLUS COURT CHEMIN AVEC BFS
{
    int numpred;
    std::cout << std::endl << std::endl;
    std::cout << std::endl << std::endl;
    std::cout << "Voici tout les chemins plus courts (en nombre de trajets) pour rejoindre les autres sommets :" << std::endl << std::endl;
    for(int i=0;i<m_ordre;i++)  //pour tout les sommets
    {
        std::cout << i +1;
        numpred=pred[i];
        while(numpred!=-1)   //refaire le chemin fait dans la fonction de recherche BFS
        {
            std::cout << " <-- "<< numpred+1;
            numpred=pred[numpred];
        }
        std::cout << std::endl;
    }

}

void Graphe::afficherPredBFS(std::vector<int> pred,int fin)                       ///AFFICHAGE D'UN SEUL PLUS COURT CHEMIN AVEC BFS
{
    int numpred,ctp =0;
    std::cout << std::endl << std::endl;
    std::cout << std::endl << std::endl;
    std::cout << fin +1;
    numpred=pred[fin];
    while(numpred!=-1)   //refaire le chemin fait dans la fonction de recherche BFS
    {
        ctp++;
        numpred=pred[numpred];
    }
    numpred=pred[fin];
    while(numpred!=-1)   //refaire le chemin fait dans la fonction de recherche BFS
    {
        std::cout << " <-- "<< numpred+1;
        numpred=pred[numpred];
    }
    std::cout << std::endl;
}

void Graphe::reseau()                                                             ///TRANSFORMER LE GRAPHE EN UN RESEAU
{
    int ctp1=0,ctp2=0;
    int depart, fin;
    std::vector<bool> choix {false,false,false};
    system("CLS");
    std::cout<<std::endl;
    std::cout<<"         Dans quel village vous vous situez ?"<<std::endl<<std::endl;
    std::cout<<"                    0.   Arcs 1600"<<std::endl;
    std::cout<<"                    1.   Arcs 1800"<<std::endl;
    std::cout<<"                    2.   Arcs 2000"<<std::endl;
    std::cout<<"                    3.   Confirmez votre choix"<<std::endl;
    while(depart!=3)
        {
            gotoligcol(4,60);
            std::cout<<"     Votre choix:";
            std::cin>>depart;
            gotoligcol(4,60);
            std::cout<<"                    ";
            for(int i=0;i<3;i++)
            {
                if(depart==i)
                {
                    for(int i=0;i<3;i++)
                    {
                        gotoligcol(i+3,17);
                        std::cout<<" ";
                        choix[i]=false;
                    }
                    if(!choix[i])
                    {
                        gotoligcol(i+3,17);
                        std::cout<<"X";
                        choix[i]=true;
                    }
                }
            }
        }
    if(depart==0)
        depart=29;
    if(depart==1)
        depart=35;
    if(depart==2)
        depart=6;
    system("CLS");
    for(int i=0;i<3;i++)
    {
        if(choix[i])
        {
            ctp1++;
        }
    }
    if(ctp1==0)
        reseau();
    std::vector<bool> choix2 {false,false,false};
    std::cout<<std::endl;
    std::cout<<"         Ou est ce que vous voulez aller ?"<<std::endl<<std::endl;
    std::cout<<"                    0.   Aiguille-rouge"<<std::endl;
    std::cout<<"                    1.   Arpette"<<std::endl;
    std::cout<<"                    2.   col-de-la-chal"<<std::endl;
    std::cout<<"                    3.   Confirmez votre choix"<<std::endl;
    while(fin!=3)
        {
            gotoligcol(4,60);
            std::cout<<"     Votre choix:";
            std::cin>>fin;
            gotoligcol(4,60);
            std::cout<<"                    ";
            for(int i=0;i<3;i++)
            {
                if(fin==i)
                {
                    for(int i=0;i<3;i++)
                    {
                        gotoligcol(i+3,17);
                        std::cout<<" ";
                        choix2[i]=false;
                    }
                    if(!choix2[i])
                    {
                        gotoligcol(i+3,17);
                        std::cout<<"X";
                        choix2[i]=true;
                    }
                }
            }
        }
    if(fin==0)
        fin=4;
    if(fin==1)
        fin=14;
    if(fin==2)
        fin=25;
    system("CLS");
    for(int i=0;i<3;i++)
    {
        if(choix2[i])
        {
            ctp2++;
        }
    }
    if(ctp2==0)
        reseau();
    m_SourcePuit.first=m_listeSommet[depart];
    m_SourcePuit.second=m_listeSommet[fin];
    for(int i=0;i< m_taille;i++)
    {
        if(depart==m_listeArcs[i]->getArrivee())
            m_listeSommet[m_listeArcs[i]->getDepart()]->removeAdjacence(depart);
    }
    m_listeSommet[fin]->resetAdjacence();
}

std::vector<std::pair<Sommet *,std::pair<int,int>>> Graphe::FordFulkersonMarque() ///ALGORITHME DE  MARQUAGE DE FORD ET FULKERSON
{
    Sommet delta(38,"delta",10);
    std::vector<std::pair<Sommet *,std::pair<int,int>>> marquage;
    std::vector<bool> examen;
    bool finExamen = false;
    int alpha,beta;
    for(int i=0;i<m_ordre;i++)
    {
        examen.push_back(false);
        marquage.push_back(std::make_pair(nullptr,std::make_pair(0,0)));
    }
    marquage[m_SourcePuit.first->getnbr()] = std::make_pair(&delta,std::make_pair(0,infini));
    while(marquage[m_SourcePuit.second->getnbr()].first==nullptr && (!finExamen))
    {
        finExamen = true;
        for(int i=0;i<m_ordre;i++)
        {
            if(!(marquage[i].first!=nullptr && (!examen[i])))
            {
                finExamen = false;
            }
        }
        for(int i=0;i<m_ordre;i++)
        {
            if(marquage[i].first != nullptr && (!examen[i]))
            {
                alpha = abs(marquage[i].second.second);
                for(auto elem : m_listeSommet[i]->getVectAdjda())
                {
                    if(marquage[elem.first->getnbr()].first==nullptr)
                    {
                        if(elem.second->getCapacite() > elem.second->getFlot())
                        {
                            beta = std::min(alpha,elem.second->getCapacite() - elem.second->getFlot());
                            marquage[elem.first->getnbr()]=std::make_pair(m_listeSommet[i],std::make_pair(1,beta));
                        }
                    }
                }
                for(auto elem : getSuccesseur(i))
                {
                    if(marquage[elem.second->getDepart()].first==nullptr)
                    {
                        if(elem.second->getFlot()>0)
                        {
                            beta = std::min(alpha,elem.second->getFlot());
                            marquage[elem.second->getDepart()] = std::make_pair(m_listeSommet[elem.second->getArrivee()],std::make_pair(-1,beta));
                        }
                    }
                }
                examen[i]=true;
            }
        }
    }
    return marquage;
}

void Graphe::FordFulkerson()
{
    int flot =0;
    std::vector<std::pair<Sommet *,std::pair<int,int>>> marquage;
    do
    {
        marquage=FordFulkersonMarque();
        if(marquage[m_SourcePuit.second->getnbr()].first!=nullptr)
        {

        }

    }while(marquage[m_SourcePuit.second->getnbr()].first != nullptr);
}
