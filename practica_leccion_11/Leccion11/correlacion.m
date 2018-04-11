#!/usr/bin/octave-cli

pkg load image;

C=imread("~/ltilib-2/img/lenna.png");
G=double(rgb2gray(C))/255;

figure(1,"name","Original");
imshow(G);

## Extraiga una porción de la imagen
F=G(250:350,250:350);
figure(2,"name","Kernel");
imshow(F);

## Correlacione
K=imfilter(G,F,'corr');
figure(3,"name","Correlación");
imshow(K/max(K(:)));

AK=normxcorr2(F,G);
figure(4,"name","Correlación normalizada");
imshow(AK);
