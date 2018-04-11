#!/usr/bin/octave

pkg load image
%pkg load signal

%K=double(imread("isotipo63x63.png"));
K=double(imread("/home/will/Documentos/Imagenes/practica_leccion_11/Leccion11/circle.png"));

K=K/255/4;

figure(1)
imshow(K);

numpts=16;

do
  A=zeros(512,512);

  
  for i=1:numpts
    A(randi(512),randi(512))=rand;
  endfor

  B=conv2(A,K,'same');
  %B=filter2(K,A,'same');
  
  figure(2);
  imshow(A);
  
  figure(3);
  imshow(B);

  printf("Number of points: %i\n",numpts);
  printf("Press ENTER or X key\n");
  fflush(stdout);
  
  key=kbhit();
  numpts=round(numpts*1.25);

  
until(key=='x')
