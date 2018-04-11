
/*
*	Intituto Tecnológico de Costa Rica
*	Authors:
*		Wilberth Varela
*
*	Procesamiento y analisis de imagenes digitales	
*	I Semester, 2018
*	Proyect 1
*/


#include "opencv2/core.hpp"
#include <opencv2/core/utility.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string> 
#include <sstream> 
#include <unistd.h>


using namespace cv;
using namespace std;

VideoCapture CapturaVideo;
Mat ventanaVideo;

/*
En este metodo se encargar de tomar las fotos.
 */
int take_Photos(){
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

/*
Calcula los puntos del tablero
 */
static void calcChessboardCorners(Size boardSize, float squareSize, std::vector<cv::Point3f>& corners)
{
	corners.clear();
    for( int i = 0; i < boardSize.height; i++ )
        for( int j = 0; j < boardSize.width; j++ )
            corners.push_back(Point3f(float(j*squareSize),
                                      float(i*squareSize), 0)); 
}

/*
Guarda los datos de calibracion de la camara en un archivo de .yml
 */
static void saveparams(const string& filename, const Mat& cameraMatrix, const Mat& distCoeffs,
					   const vector<Mat>& rvecs,const vector<Mat>& tvecs, const double& RMS)
{
		FileStorage fs( filename, FileStorage::WRITE );
		fs << "Exactitud_Calibracion" << RMS;
		fs << "Matriz_Camara" << cameraMatrix;
		fs << "Coeficientes_Distorcion" << distCoeffs;
		fs << "Vector_Rotacion" << rvecs;
		fs << "Vector_Traslacion" << tvecs;

		if( !rvecs.empty() && !tvecs.empty() ){

			CV_Assert(rvecs[0].type() == tvecs[0].type());
			Mat bigmat((int)rvecs.size(), 6, rvecs[0].type());
			for( int i = 0; i < (int)rvecs.size(); i++ ){
				Mat r = bigmat(Range(i, i+1), Range(0,3));
				Mat t = bigmat(Range(i, i+1), Range(3,6));

				CV_Assert(rvecs[i].rows == 3 && rvecs[i].cols == 1);
				CV_Assert(tvecs[i].rows == 3 && tvecs[i].cols == 1);
      
				r = rvecs[i].t();
				t = tvecs[i].t();
        }
        cvWriteComment( *fs, "Vector Rotacion + Vector Translacion", 0 );
        fs << "Parametros_Extrinsicos" << bigmat;
    }
		fs.release();
}

int calibrate_Display_Result(){
	Size patternsize = Size(9,6);//esquinas interiores del tablero de ajedrez
	vector<Point3f> corners3D;
	vector<Point2f> corners2D;//findChessboardCorners guarda los puntos del tablero aqui
	vector<vector<Point2f> > coord2D;//Ubicacion de las esquinas detectadas en la imagen
	vector<vector<Point3f> > coord3D;//Ubicacion real de los puntos 3D

	string  valor;
  	cout <<"Ingrese la direccion donde se encuentran las imagenes guardadas\n"<< endl;
  	cout <<"Ejemplo: /home/Usuario/Documentos/Carpeta1/ \n"<< endl;
  	cout <<"Nota: La direccion tiene que ser como la direccion anterior\n"<< endl;
  	cin >> valor;
	string direccion = valor; //lee las imagenes
	stringstream imgs;

	calcChessboardCorners(patternsize,25,corners3D); // calcula las esquinas del tablero

	Mat img, imgGray; 
	bool found; 

	for (int  i = 0; i < 14; i++){
		cout << "Valor es: " << i << endl; //carga la imagen
		imgs << direccion << i << ".jpg"; //imprime la direccion de la imagen.
		img = imread(imgs.str().c_str()); //lee la imagen 
		
		if(! img.data )                              // Check for invalid input
    	{
        	cout <<  "No se puede abrir la imagen" << std::endl ;
        	return -1;
    	}
		
		cout << imgs.str().c_str() << endl;
		cvtColor(img, imgGray, COLOR_BGR2GRAY); //pasa la imagen a gris

		imgs.str("");//std::stringstream(); limpia para cargar la otra imagen

		//encuentra la esquinas del tableblero a una bandera de falso o verdadero
		found = findChessboardCorners(imgGray,patternsize,corners2D,CALIB_CB_ADAPTIVE_THRESH + 
			                                                        CALIB_CB_NORMALIZE_IMAGE + 
																	CALIB_CB_FAST_CHECK);

		if( found) {
			
			//marca los puntos de la imagen y la locacion promedio de la distancia entre puntos
			cornerSubPix(imgGray, corners2D, Size(11, 11), Size(-1, -1),TermCriteria( 
				                                                        TermCriteria::EPS + 
																		TermCriteria::COUNT, 30, 0.1 ));
			//dibuja los puntos del tablero
			drawChessboardCorners(img,patternsize,Mat(corners2D),found);
			coord2D.push_back(corners2D);
			coord3D.push_back(corners3D);
		} 
		 namedWindow("image",WINDOW_AUTOSIZE);
		 imshow("image", img);
		 waitKey(500);
	}

	cvDestroyWindow("image");

	//Para calibrar la camara
	Mat cameraMatrix = Mat::eye(3, 3, CV_64F); //matriz de la camara 
	Mat distCoeffs = Mat::zeros(8, 1, CV_64F); // los coeficientes de distorcion
	std::vector<Mat> rvecs; // salida de vector de rotacion
	std::vector<Mat> tvecs; //salida de ventor de traslacion 
   
   //funcion para calibrar la camara
	double rms = calibrateCamera(coord3D, coord2D, img.size(), cameraMatrix,
                  distCoeffs, rvecs, tvecs, 
									CALIB_FIX_PRINCIPAL_POINT +
									CALIB_FIX_ASPECT_RATIO +
									CALIB_ZERO_TANGENT_DIST 
									,TermCriteria(CV_TERMCRIT_ITER + CV_TERMCRIT_EPS, 30, 2.22e-16));

	std::cout << "RMS: " << rms << std::endl;
	std::cout << "Camera matrix: " << cameraMatrix << std::endl;
	std::cout << "Distortion _coefficients: " << distCoeffs << std::endl;

	//Guarda los datos de calibracion
	saveparams(direccion + "DataCam.yml",cameraMatrix,distCoeffs,
				rvecs,tvecs,rms);

	//*****************************************************************************************************
	//Seccion para presentar los vectores.

	// coners1 concer2d
	// objects point coners3d 
	Mat rotation_vector; // rotacion de los vectores
    Mat translation_vector;
	VideoCapture capture(0);
	
	Mat view;
	Mat Img;

	const string x= "X";
	const string y= "Y";
	const string z= "Z";

	vector<Point3d> point3D;
    vector<Point2d> point2D;


    point3D.push_back(Point3d(0,125.0,-100.0)); //-z se representa 10 sea cm o mm depediendo de el tamano 
    point3D.push_back(Point3d(100.0,125.0,0));  //x
	point3D.push_back(Point3d(0,25.0,0));  //y

	while(1)
	{
		capture >> view;	
		if(view.empty()!=1)
		{	
			//encuentra la esquinas del tableblero a una bandera de falso o verdadero
			found=findChessboardCorners(view, patternsize,  corners2D);
		}  

		if(found )

			{
			
			cvtColor(view,Img,CV_BGR2GRAY);
			
			//marca los puntos de la imagen y la locacion promedio de la distancia entre puntos
			cornerSubPix(Img, corners2D, Size(11, 11), Size(-1, -1),
	        TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1)); // 
	      
			
			solvePnP(corners3D, corners2D, cameraMatrix, distCoeffs, rotation_vector, translation_vector);//da el vector de rotacion y de traslacion
	        
			//brinda la funcion que da como point2D del point3D 
	        projectPoints(point3D, rotation_vector, translation_vector, cameraMatrix, distCoeffs, point2D);
			

			//Dibujar los vectores de X, Y y Z
			arrowedLine(view,corners2D[45], point2D[1], Scalar(0,0,255), 3);//z
	        arrowedLine(view,corners2D[45], point2D[0], Scalar(255,0,0), 3);//x
	        arrowedLine(view,corners2D[45], point2D[2], Scalar(0,255,0), 3);//y
		 
			//Dibujar las letras de los ejes
	    	putText(view, z, Point(point2D[0].x-10,point2D[0].y-10),FONT_HERSHEY_COMPLEX_SMALL,1, Scalar(255,0,0),2 );
			putText(view, y, Point(point2D[2].x-10,point2D[2].y-10),FONT_HERSHEY_COMPLEX_SMALL,1, Scalar(0,255,0),2 );
			putText(view, x, Point(point2D[1].x-10,point2D[1].y-10),FONT_HERSHEY_COMPLEX_SMALL,1, Scalar(0,0,255),2 );
	        
	        
	    }

	    cv::imshow("Video", view);
	    cv::waitKey(1);
	}
}

int main(int argc, char *argv[]){

	string end = "f";
	string funcion;
	while(end=="f")
	{
		cout << "\nLos valores a aceptar son: \n\n";
		cout << 		"-t: para inicializar la funcionalidad de tomar las fotos.\n";
		cout << 		"-c: para inicializar la funcionalidad de calibracion y proyeccion de los resultados.\n";
		cout << 		"-e: para terminar el programa."<< endl;
		cin >> funcion;

		if (funcion == "-t")
		{
			take_Photos();
		}
		else if (funcion == "-c")
		{
			calibrate_Display_Result();
		}
		else if (funcion == "-e")
		{
			end = "t";
		}
		else{
			cout << "El valor ingresado es incorrecto" << endl;
		}
	}
	return 0;
}