//////////////////////////////////
//				//
//    Programme d'amelioration	//
//    de Contraste d'une Image	//		
//  Auteur: OUSSSEINI HAMZA	//
//		Abdoul-Djalil	//
//  Promotion 22		//
//			       	//
//////////////////////////////////


#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
//using namespace std;
using namespace cv;

class fonctionPrincipale:public Mat
{
private:
  int color; //0 rouge, 1 vert, 2 blue
public:
/*declaration des differentes fonctions*/
  fonctionPrincipale();
  fonctionPrincipale(Mat image, int c);
  fonctionPrincipale(fonctionPrincipale& fonctionprincipale);
  fonctionPrincipale& operator=(const fonctionPrincipale& fonctionprincipale);
/*Fonction pour le tracer du profil */
  void drawProfil(Mat image, Point start, Point end);
  void drawProfil_simple(Mat image, Point start, Point end);
/*Fonction pour le tracer d'histogramme */
  void drawHist(Mat hist, int color);
  friend Scalar getScalar(fonctionPrincipale);
  friend void initHistData(int data[], int N);
  void setHistData(int data[], int N);
  friend int getMax(int data[], int N);
  friend int getMin(int data[], int N);
  /*Fonction pour le contraste des differentes methodes */
 
  Mat contrastLinaireSaturation(int s_min, int s_max);

  Mat contrastLinaireMorceaux(float r1, float s1, float r2, float s2); 
  Mat contrastGama(float gama);
  friend int calcGama(int gama);
  void normalisationHist(float hn[], int h[], int N);
  friend void densite(float c[], float hn[], int N);
 
  
  int getColor();
  virtual ~fonctionPrincipale();
};














