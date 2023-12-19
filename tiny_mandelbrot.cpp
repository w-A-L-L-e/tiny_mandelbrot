/*=============================================================================
author        : Walter Schreppers
filename      : clock.cpp
created       : 16/5/2022 at 22:50:23
modified      : 16/5/2022
version       :
copyright     : Walter Schreppers
description   : Simple analogue clock
=============================================================================*/

#include "screen.h"
#include <ctime>
#include <iostream>
#include <numeric>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

int mandelbrot(double real, double imag) {
	int limit = 100;
	double zReal = real;
	double zImag = imag;

	for (int i = 0; i < limit; ++i) {
		double r2 = zReal * zReal;
		double i2 = zImag * zImag;
		
		if (r2 + i2 > 4.0) return i;

		zImag = 2.0 * zReal * zImag + imag;
		zReal = r2 - i2 + real;
	}

	return limit;
}

int main(int argc, char **argv) {
  int width = 640;
  int height = 400;

  Screen screen(width, height, "Mandelbrot set", false);
  SDL_ShowCursor(SDL_DISABLE);

  double x_start = -2.0;
	double x_fin = 1.0;
	double y_start = -1.0;
	double y_fin = 1.0;
	
	double dx = (x_fin - x_start)/(width - 1);
	double dy = (y_fin - y_start)/(height - 1);

  double animate = 1.0;

  while (screen.opened()) {
    screen.handle_events();
    screen.clear();

    // little hack to cycle the colors
    animate += 0.1;
    if (animate > 3.5) animate = 0.8;

    // TODO: make start pos and end pos changeable with keyboard
    // double x_start = -0.25;
	  // double x_fin = 0.05;
	  // double y_start = -0.95;
	  // double y_fin = -0.75;
	
	  // double x_start = -0.13;
	  // double x_fin = -0.085;
	  // double y_start = -0.91;
	  // double y_fin = -0.88;

    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        
        double x = x_start + j*dx; // current real value
        double y = y_fin - i*dy; // current imaginary value
        
        int value = mandelbrot(x,y) * animate;
        
        if (value == 100)    { screen.pixel(j,i,0,0,0); }      // black
        else if (value > 90) { screen.pixel(j,i,50,0,0); }     // dark red
        else if (value > 70) { screen.pixel(j,i,255,20,20); }  // light red
        else if (value > 50) { screen.pixel(j,i,200,100,10); } // orange
        else if (value > 30) { screen.pixel(j,i,240,236,0); }  // yellow
        else if (value > 20) { screen.pixel(j,i,57,240,6); }   // light green
        else if (value > 10) { screen.pixel(j,i,10,140,10); }  // green
        else if (value > 5)  { screen.pixel(j,i,8,230,230); }  // light cyan
        else if (value > 4)  { screen.pixel(j,i,0,120,120); }  // cyan
        else if (value > 3)  { screen.pixel(j,i,8,140,250); }  // light blue
        else if (value > 2)  { screen.pixel(j,i,10,10,250); }  // blue
        else if (value > 1)  { screen.pixel(j,i,120,4,140); }  // magenta
        else                 { screen.pixel(j,i,195,8,227); }  // light magenta
      }
    }

    // sleep a little
    SDL_Delay(20);
    screen.draw();
  }

  return 0;
}
