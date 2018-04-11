#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string> 
#include <sstream> 


using namespace cv;
using namespace std;

VideoCapture CapturaVideo;
Mat ventanaVideo;
 
int main(int argc, char *argv[]) {
  char key = 0;
  string  valor;
  cout <<"Ingrese la direccion donde se van a guardar las imagenes \n"<< endl;
  cout <<"Ejemplo: /home/Usuario/Documentos/Carpeta1 \n"<< endl;
  cout <<"Nota: en la ultima carpeta no hace falta agregar el: (/), ya se contempla en el codigo \n"<< endl;
  cin >> valor;
  

  int numFoto = 0;
  string direccion = valor +"/0";
 
  cout << "Presione 's' para una foto" << endl;
  cout << "Presione 'Esc' para salir" << endl;
  cout << "Nota: se pueden tomar un maximo de 14 fotos aunque se puede cambiar el parametro" << endl;
 
  CapturaVideo.open(0);
 
  if (!CapturaVideo.isOpened()) {
    cout<<"No se pudo abrir la camara"<<endl;
    return -1;
  }
 
  while (key!=27 && CapturaVideo.grab() && numFoto != 14) {
    CapturaVideo.retrieve(ventanaVideo);
 
    imshow("Video Captura", ventanaVideo);
 
    if (key == 115) {
      imwrite(direccion + ".jpg", ventanaVideo);
      numFoto++;
      direccion = valor + "/"+ static_cast<ostringstream*>(&(ostringstream() << numFoto))->str();
	  }
 
  key=waitKey(20);
  }
}