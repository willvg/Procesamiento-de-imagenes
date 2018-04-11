/*
*	Intituto Tecnológico de Costa Rica
*	Authors:
*		Wilberth Varela
*
*	Procesamiento y analisis de imagenes digitales	
*	I Semester, 2018
*	Proyect 1
*/


Links de referencia

Para las flechas: https://docs.opencv.org/3.0-beta/modules/imgproc/doc/drawing_functions.html

Para los vectores: http://www.cplusplus.com/reference/vector/vector/push_back/

Para formar los vectores en el tablero en vivo: https://docs.opencv.org/3.3.0/d7/d53/tutorial_py_pose.html
												https://docs.opencv.org/3.3.1/d9/d0c/group__calib3d.html

Para la calibracion de la camara: https://docs.opencv.org/2.4/modules/calib3d/doc/camera_calibration_and_3d_reconstruction.html

Para los puntos 3d: https://docs.opencv.org/java/2.4.9/org/opencv/core/Point3.html

Para generar los archivos: https://docs.opencv.org/2.4/modules/core/doc/xml_yaml_persistence.html

Referencia de calibracion: http://tecnicasdevision.blogspot.com.es/2014/05/calibrar-una-camara-con-opencv.html


***********************************************************************************************************************
***********************************************************************************************************************
***********************************************************************************************************************
Rutas para la posible ejecucion del programa.

Ruta utilizada para tomar las fotos: /home/USUARIO/proyecto1/Imagenes
Ruta utilizada leer la fotos: /home/USUARIO/proyecto1/Imagenes


La parabra USUARIO se cambia por el usuario de la computadora.


***********************************************************************************************************************
***********************************************************************************************************************
***********************************************************************************************************************
Para la ejecucion de programa.

	1. Se dercargar el .tar
	2. se descomprime el .tar en la root de sistema, posible direccion: "/home/USUARIO/"
		
		Nota: donde el USUARIO se cambia. por el usuario del computador.
	
	3. Entra a la carpeta "/proyecto1/build/"
	
	4. Dentro de este punto, abre una ventana de terminal.
	
	5. Ejecuta el comando:
		cmake ../ -DCMAKE_INSTALL_PREFIX:PATH=/home/USUARIO/proyecto1/build/usr

			Nota: Donde USUARIO debe reemplazar el usuario del sistema.
	6. Construccion de programa: Para la construccion del programa (modo usuario) unicamente se debe ejecutar el comando
		$ make
	
	7. Instalacion: Para la instalacion del programa se ejecuta
		$ make install
		
			Nota: El comando anterior instala el binario en el directorio usr/bin.
	
	8. Verificacion: Para verificar el programa se requiere la ejecucion del mismo.
		$ cd usr/bin && ./proyecto1




