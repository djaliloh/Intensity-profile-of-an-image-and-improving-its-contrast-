//////////////////////////////////
//				//
//    Programme d'amelioration	//
//    de Contraste d'une Image	//		
//  Auteur: OUSSEINI HAMZA	//
//		Abdoul-Djalil	//
//  Promotion 22		//
//			       	//
//////////////////////////////////



#include "control.h"
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

void displayWelcome()		//displayWelcome
{
  cout<<"Bienvenue sur le Programme d'amelioration du contraste\n";
  cout<<"======================================\n";
}

void displayMenu()	//displayMenu
{
  cout<<"Taper:\n";
  cout<<"intensite [option] image x1 y1 x2 y2 - pour afficher le profil\n";
  cout<<"contraste [option] image function - pour caculer le contraste\n";
  cout<<"\toption: 0 pour image gray : 1 pour image de coleur\n";
  cout<<"\tfunction: 1, 2 ou 3\n";
  cout<<"\t\t1: Linaire par morceaux\n";
  cout<<"\t\t2: Correction gama\n";
  cout<<"\t\t3: Linaire avec saturation\n";
  cout<<"======================================\n";
}

int main(int argc, char* argv[])
{
  Control control;	//On fait appel a notre fonction Controle
  int x1, y1, x2, y2;	//on demande a l'utilisateur d'entrer les deux points
  string cmd("");
  int option = 0;
  string image("image.jpg");
  int function = 1;
  string exit = "no";

  displayWelcome();	//displayWelcome
  do
    {
      displayMenu();
      cin>>cmd >>option >>image;	/*on demande a l'utilisateur d'entrer son choix et puis on test s'il choisi l'intensite on lui demande 						d'entrer les deux points*/
      if(cmd.compare("intensite") == 0)
	{
	  cin>>x1 >>y1 >>x2 >>y2;
	  control.drawProfil(option, image, x1, y1, x2, y2);
	}
      else if(cmd.compare("contraste") == 0)
	{						/*de ici on fait la comparaison s'il choisit la contraste on lui demande de complete les 								parametre option, son image, et la fonction qu */
	  cin>>function;
	  control.calcContrast(option, image, function);
	}
      else{
	cout<<"Aucune commande trouvée\n";
	continue;
      }
      cout<<"les resultats de vos operations sont dans le dossier image/\n";
      cout<<"Tapez yes - pour quitter: \n";
      cout<<"Tapez no - pour continuer: \n";
      cin>>exit;
    } while (exit.compare("yes") != 0);
  return 0;
}
