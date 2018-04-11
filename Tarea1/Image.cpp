#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    if( argc != 2)
    {
     cout <<" Tarea: Usa una imagen la carga y la despliega" << endl;
     return -1;
    }

    //Realiza la lectura del valor de entrada
    Mat imagen = imread(argv[1], CV_LOAD_IMAGE_COLOR);

    // Valida si la imagen es correcta y se puede cargar. 
    if(!imagen.data)
    {
        cout <<  "Error: No se puede mostrar la imagen" <<endl ;
        return -1;
    }

    //Crea la ventana.
    namedWindow( "Ventana", WINDOW_AUTOSIZE );
    //Muestra la imagen
    imshow( "Ventana", imagen );

    waitKey(0);
    return 0;
}