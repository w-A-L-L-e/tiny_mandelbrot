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

void get_time(int &h, int &m, int &s) {
  // #include <chrono>
  // auto tnow = std::chrono::system_clock::now();
  // std::time_t current_time = std::chrono::system_clock::to_time_t(tnow);

  // shorter way, just use ctime
  std::time_t t = std::time(0); // get time now
  std::tm *now = std::localtime(&t);
  h = now->tm_hour;
  m = now->tm_min;
  s = now->tm_sec;

  // std::cout << h << ":" << m << ":" << s << std::endl;
}

void draw_clock_markers(Screen *scr) {
  int marker_start = 155;
  int marker_end = 170;

  // hour ticks
  for (int hour = 1; hour <= 12; hour++) {
    double hour_angle = (double)hour * M_PI / 6.0; // 12 hours => 2*PI
    scr->line(scr->center_x + marker_start * std::cos(hour_angle - M_PI / 2.0),
              scr->center_y + marker_start * std::sin(hour_angle - M_PI / 2.0),
              scr->center_x + marker_end * std::cos(hour_angle - M_PI / 2.0),
              scr->center_y + marker_end * std::sin(hour_angle - M_PI / 2.0));

    // double thickness
    scr->line(scr->center_x+1 + marker_start * std::cos(hour_angle - M_PI / 2.0),
              scr->center_y + marker_start * std::sin(hour_angle - M_PI / 2.0),
              scr->center_x+1 + marker_end * std::cos(hour_angle - M_PI / 2.0),
              scr->center_y + marker_end * std::sin(hour_angle - M_PI / 2.0));
 
    scr->line(scr->center_x + marker_start * std::cos(hour_angle - M_PI / 2.0),
              scr->center_y+1 + marker_start * std::sin(hour_angle - M_PI / 2.0),
              scr->center_x + marker_end * std::cos(hour_angle - M_PI / 2.0),
              scr->center_y+1 + marker_end * std::sin(hour_angle - M_PI / 2.0));
 
  }

  marker_start = 165;
  marker_end = 170;
  // minute ticks
  for (int min = 0; min < 60; min++) {
    double min_angle = (double)min * M_PI / 30.0; // 60 min => 2*PI
    if(min == 15) continue;
    scr->line(scr->center_x + marker_start * std::cos(min_angle - M_PI / 2.0),
              scr->center_y + marker_start * std::sin(min_angle - M_PI / 2.0),
              scr->center_x + marker_end * std::cos(min_angle - M_PI / 2.0),
              scr->center_y + marker_end * std::sin(min_angle - M_PI / 2.0));
  }
}

void draw_clock_handles(Screen *scr, int hour, int minute, int second) {
  int sec_len = 160;
  int min_len = 130;
  int hour_len = 100;

  double second_angle = (double)second * M_PI / 30.0; // 60 seconds = 2PI
  double minute_angle = (double)minute * M_PI / 30.0; // 60 minutes = 2PI

  if (hour > 12)
    hour -= 12; // 12 hour analogue clock
  double partial_hour = (double)minute / 60.0;
  double hour_angle =
      ((double)hour + partial_hour) * M_PI / 6.0; // 12 hours = 2PI

  scr->setColor(40, 40, 240);
  scr->line(scr->center_x, scr->center_y,
            scr->center_x + hour_len * std::cos(hour_angle - M_PI / 2.0),
            scr->center_y + hour_len * std::sin(hour_angle - M_PI / 2.0));

  scr->setColor(40, 240, 40);
  scr->line(scr->center_x, scr->center_y,
            scr->center_x + min_len * std::cos(minute_angle - M_PI / 2.0),
            scr->center_y + min_len * std::sin(minute_angle - M_PI / 2.0));

  scr->setColor(240, 40, 40);
  scr->line(scr->center_x, scr->center_y,
            scr->center_x + sec_len * std::cos(second_angle - M_PI / 2.0),
            scr->center_y + sec_len * std::sin(second_angle - M_PI / 2.0));
}

int main(int argc, char **argv) {
  Screen screen(640, 400, "analogue clock", false);
  int hour, minute, second;

  SDL_ShowCursor(SDL_DISABLE);

  while (screen.opened()) {
    screen.handle_events();
    //screen.clear(0, 0, 80);
    screen.clear(); //is a little faster

    get_time(hour, minute, second);

    screen.setColor(230, 210, 90);
    draw_clock_markers(&screen);
    draw_clock_handles(&screen, hour, minute, second);

    // SDL_Delay(20); // use this to slow down
    screen.draw();
  }

  return 0;
}
