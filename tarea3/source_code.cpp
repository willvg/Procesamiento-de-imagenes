/*
*	Intituto Tecnológico de Costa Rica
*	Authors:
*		Wilberth Varela
*		Jonatan Chaverri
*
*	Procesamiento y analisis de imagenes digitales	
*	I Semester, 2018
*	Assignment 3
*/

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>  
#include <string> 
#include <iostream>

#define PI 3.14159265
using namespace std;

//N is the number of columns.
double linear_letter_S(int N, int j)
{
	double width = (double) N;
	double x = (double) j;
	//cuadratic formula with vertex in x=0
	double a = 180.0/((width-1)*(width-1)-(width-2)*(width-2));
	double c = -90.0-(180.0*(width-2)*(width-2))/((width-1)*(width-1)-(width-2)*(width-2));
	double exp = x*x*a+c;
	return sin (exp*PI/180.0);
}

//M is the number of rows.
double linear_letter_A(int M, int i)
{
	return 127.0*(((double)i)/(((double) M)-1.0));
}

double funtion_escale_S(int N, int j)
{
	double R = (double) N;
	double x = (double) j;
	double K = 0.0001;
	double alpha = (1/(R-1))* log ((R-1)/K);

	return K*(exp(alpha*x));
}

double linear_log_S (int N, int j)
{
	double width = (double) N;
	double x = funtion_escale_S( N, j);
	//cuadratic formula with vertex in x=0
	double a = 180.0/((width-1)*(width-1)-(width-2)*(width-2));
	double c = -90.0-(180.0*(width-2)*(width-2))/((width-1)*(width-1)-(width-2)*(width-2));
	double exp = x*x*a+c;
	return sin (exp*PI/180.0);
}

double funtion_escale_A(int M, int i)
{
	double R = (double) M;
	double x = (double) i;
	double K = 0.0001;
	double alpha = (1/(R-1))*log ((R-1)/K);
	return K*(exp(alpha*x));
}

double linear_log_A (int M, int i)
{
	double a = funtion_escale_A(M, i);
	return 127.0*((a)/(((double) M)-1.0));
}

void create_Image(int N, int M, int fila, string escala){
	int i, j;
	double C;
	cv::Mat image(M,N, CV_8UC3);
	cv::Vec3b color;
	for (i=0; i<M; i++){
		for (j=0; j<N; j++){
			if (escala == "l")
			{
				C = linear_letter_S(N, j)*linear_letter_A(M, i) + 128.0;
			}
			else if (escala == "g")
			{
				C = linear_log_S(N, j)*linear_log_A(M, i) + 128.0;
			}			
			color[0]=C;
			color[1]=C;
			color[2]=C;
			image.at<cv::Vec3b>(cv::Point(j,i))= color;
		}
	}
	
	if (fila!=-1)
	{
		cout << fila << endl;
		for (int i = 0; i < N; ++i)
		{
			//cv::Vec3b pixel = image.at<cv::Vec3b>(fila, i);
			uchar pixel = image.at<uchar>(fila,i);
			cout<< "Fila: "<< fila << " columna: "<< i << " el valor es: " << (int)pixel<< endl;	
		}
	}
	cv::imwrite("image.png", image);
	cv::imshow("image", image);
	cv::waitKey();
}

int main()
{
	//logaritme_img(512, 512);
	int N = 512, M = 512, fila = -1; //N: columnas, M: Filas

	string escala = "g"; // escala l:lineal, g:logaritmo 
	string end = "d";
	string  valor;

	//cout << "Ingrese el numero de Filas, si no ingresa un valor se toma valor como defecto 512"<< endl;
	//cin << valor
	while(end=="d")
	{
		cout << "\nLos valores a aceptar son: \n\n";
		cout << 		"-r: para indicar el valor de las filas, si no ingresa nada el valor por defecto es 512.\n";
		cout << 		"-c: para indicar el valor de las columnas, si no ingresa nada el valor por defecto es 512.\n";
		cout << 		"-l: para indicar si es escala lineal, en caso de querer la logaritmica, no ingrese nada.\n";
		cout << 		"-row: Si se desea saber los valores de esa fila.\n";
		cout << 		"-f: para terminar de ingresar los valores"<< endl;
				;
		cin >> valor;
		if (valor == "-r"){
			valor == "";
			cout<<"Ingrese el tamaño de las filas"<<endl;
			cin >> valor;
			M = atoi(valor.c_str()) ;
		}
		else if(valor == "-c"){
			valor == "";
			cout<<"Ingrese el tamaño de las columnas"<<endl;
			cin >> valor;
			N = atoi(valor.c_str());
		}
		else if(valor == "-l"){
			valor == "";
			cout<<"Ingrese la escala deseada, l:para lineal o g: para logaritmica"<<endl;
			cin >> valor;
			escala = valor;
		}
		else if (valor == "-row"){
			valor == "";
			cout<<"Ingrese la fila que desea"<<endl;
			cin >> valor;

			int temporal = atoi(valor.c_str());
			if (temporal<=M)
			{
				fila = temporal;
			}
			else{
				cout<< "Esta ingresando un valor fuera de rango, por favor ingrese un valor correcto.";
			}
		}
		else if(valor =="-f"){
			end="f";
		}
		else{
			cout<< "El dato ingresado no es el correcto"<<endl;
		}
	}
	create_Image(N,M,fila,escala);
	//cout<< M << "\n" << N << "\n" << fila << "\n" << escala << "\n";
	
	return 0;
}
