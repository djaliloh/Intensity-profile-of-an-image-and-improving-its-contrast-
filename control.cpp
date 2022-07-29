#include <iostream>
#include <stdio.h>
#include <vector>
#include "fonctionprincipale.h"
#include "control.h"

using namespace std;
using namespace cv;

Control::Control()
{
}

Control::Control(Mat img)
{
  image = img;
}

Control::Control(Mat img, Point start, Point end)
{
  image = img;
  line_profil_start = start;
  line_profil_end = end;
}

Mat Control::getImage()
{
  return image;
}
/*lecture de l'image entrer par l'utilisateur*/
void Control::input(string file_name)
{
  image = imread(file_name, 1);
}

bool Control::output(string file_name)
{
  bool res = imwrite(file_name, image);
  return res;
}
/*Structure de la fonction permettant de Tracer la ligne*/
void Control::drawLine()
{
    line(image, line_profil_start,
	 line_profil_end, Scalar( 255, 0, 0), 1, 8, 0);
}
/*Definition des pointeurs qui vont permettre de pointer les pixels de debut et de fin*/
void Control::setStartPoint(Point point)
{
  line_profil_start = point;
}

void Control::setEndPoint(Point point)
{
  line_profil_end = point;
}

/*Fonction permettant le tracage du profil*/

void Control::drawProfil(int option, string image_name,
			 int x1, int y1, int x2, int y2)
{
	/*Initialisation des variables et creation des images Mat*/
  Mat image;
  this->input(image_name);
  image = this->getImage();
  Point start(x1, y1);
  Point end(x2, y2);
  this->setStartPoint(start);
  this->setEndPoint(end);
  float lengh = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
  Mat profil_img(260, lengh + 10, CV_8UC3, Scalar(255, 255, 255));
  Mat hist(600, 256, CV_8UC3, Scalar(255, 255, 255));
 
/* Tracage du profil d'une image a niveau de gris */
 
 if (option == 0)
    {
      cvtColor(image, image, CV_RGB2GRAY);
      fonctionPrincipale fonctionprincipale(image, 0);
      fonctionprincipale.drawProfil(profil_img, start, end);
      fonctionprincipale.drawHist(hist, 1);
    }

/* Tracage du profil d'une image en couleur */

  if (option == 1)
    {
      vector<Mat> rgb_planes;
      fonctionPrincipale fonctionprincipale;
      split(image, rgb_planes );	/*cette fonction permet la separation des differents canal i.e R,G,B donc pour les representes on les 						recuperent par la boucles for et ont les passent a la fonction fonctionprincipale qui les representent  						lors du tracage du profile ou de l'histogramme*/
      for (int i = 0; i < 3; i++)
	{
	  fonctionPrincipale fonctionprincipale(rgb_planes[i], i);
	  fonctionprincipale.drawProfil(profil_img, start, end);
	  fonctionprincipale.drawHist(hist, i+1);
	}
    }
/*Enregistrement des resultats*/
  this->drawLine();
  this->output("image/image_out.tif");
  imwrite("image/profil.tif", profil_img);
  imwrite("image/hist.tif", hist);
}



/*Fonction permettant de modifier le contraste*/
void Control::calcContrast(int option, string image_name,
			   int function)
{
  Mat image;
  this->input(image_name);
  image = this->getImage();
  Mat image_contrast = image.clone();			/*creation de l'objet image resultant*/
  Mat hist(600, 256, CV_8UC3, Scalar(255, 255, 255));	/*creation de l'objet histogramme de l'image originale*/
  Mat hist_contrast(600, 256, CV_8UC3, Scalar(255, 255, 255));	/*creation de l'objet histogramme de l'image contrastee*/
  int s_min, s_max;
  int r1, s1, r2, s2;
  float gama;
  
  if (function == 1)				/*Test du choix operer par l'utilisateur, si 1 le choix a porter le choix sur la methode de 							contraste lineaire par morceau, il est alors invites a saisir les deux point necessaire*/
    {
      cout<<"Entrez 2 points: r1 s1 r2 s2\n";
      cin>>r1 >>s1 >>r2 >>s2;
    }
  if (function == 2)			/*Test du choix operer par l'utilisateur, si 2 le choix a porter le choix sur la methode de 							correction par gama, il est alors invites a saisir un indice compris entre 1-3*/
    {
      cout<<"Entrez gama: gama\n";
      cin>>gama;
    }
    if (function == 3)			/*Test du choix operer par l'utilisateur, si 1 le choix a porter le choix sur la methode de 							contraste lineaire par saturation, il est alors invites a saisir S_min & S_max necessaire*/
    {
      cout<<"Entrez: Smin Smax\n";
      cin>>s_min >>s_max;
    }
  if (option == 0)			/*Test de choix des option 0 pour image a niveau de gris 1 pour couleur*/
    {
      cvtColor(image, image, CV_RGB2GRAY);
      fonctionPrincipale fonctionprincipale(image, 0);
      fonctionprincipale.drawHist(hist, 1);
      switch(function)		/*Test sur la fonction choisie 1 pour Linaire par morceaux, 2 correction gama, 3 lineaire par saturation*/
	{

	case 1:
	  image_contrast = fonctionprincipale.contrastLinaireMorceaux((float)r1, (float)s1, (float)r2, (float)s2);
	  break;

	case 2:
	  image_contrast = fonctionprincipale.contrastGama(gama);
	  break;
    case 3:
	  image_contrast = fonctionprincipale.contrastLinaireSaturation(s_min, s_max);
	  break;
	}
      fonctionPrincipale fonctionprincipale_contrast(image_contrast, 0);	/*Tracage de l'histogramme du contraste*/
      fonctionprincipale.drawHist(hist_contrast, 1);
    }
  if (option == 1)			/*Meme processus que ci-dessous juste qu'ici le choix est porte sur une image en couleur donc les meme 						operations vont s'effectuees mais avec la prise en compte qu'ici c'est trois canal R,G,B*/
    {
      vector<Mat> rgb_planes;
      split(image, rgb_planes);
      for (int i = 0; i < 3; i++)
	{
	  fonctionPrincipale fonctionprincipale(rgb_planes.at(i), i);
	  fonctionprincipale.drawHist(hist, i+1);
	  switch(function)
	    {
	    case 1:
	      image_contrast = fonctionprincipale.contrastLinaireMorceaux((float)r1, (float)s1, (float)r2, (float)s2);
	      break;
	    case 2:
	      image_contrast = fonctionprincipale.contrastGama(gama);
	      break;
	   case 3:
	      image_contrast = fonctionprincipale.contrastLinaireSaturation(s_min, s_max);
	      break;
	    }
	  fonctionPrincipale fonctionprincipale_contrast(rgb_planes.at(i), i);		
	  fonctionprincipale.drawHist(hist_contrast, i+1);
	}
      merge(rgb_planes, image_contrast);	/*'merge'cette fonction permet joindre les differents canaux canaux separer ci-haut*/
    }
  
  imwrite("image/hist.tif", hist);		/*Enregistrement de l'histogramme de l'image originale dans le dossier image*/
  imwrite("image/contrast.tif", image_contrast); /*Enregistrement de l'image contrastee dans le dossier image*/
  imwrite("image/hist_contrast.tif", hist_contrast); /*Enregistrement de l'histogramme de l'image contrastee dans le dossier image*/
				
}












