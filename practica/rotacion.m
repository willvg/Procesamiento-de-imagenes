#!/usr/bin/octave-cli

pkg load image;
I=imread("~/Imagnes/practica/lenna.png");

G=rgb2gray(I);
imshow(G);

%% Distancia focal
f=1;

%% Matríz extrínseca
E = [1 0 0 0; 0 1 0 0; 0 0 1 1];

%% Matríz de cámara K
K = [f 0 0; 0 f 0; 0 0 1];

%% Todas las coordenadas de la matriz de entrada
x=1:columns(G);
y=1:rows(G);

%% Creamos ahora el "grid"
[xx,yy]=meshgrid(x,y);

%% Aplanamos todo para tener las nuevas coordenadas
pin = [xx(:)';yy(:)';zeros(1,length(xx(:)));ones(1,length(xx(:)))];

%% Pasemos cada coordenada por su respectiva transformación
pouth = K*E*pin;

%% Pasemos de coordenadas homogeneas a euclídeas
pout = [pouth(1,:)./pouth(3,:);pouth(2,:)./pouth(3,:)];

%% FIX ME!!
Gout(pout(1,:),pout(2,:))=G(pin(1,:),pin(2,:));
