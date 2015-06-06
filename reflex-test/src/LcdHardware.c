/*
 * LcdHardware.c
 *
 *  Created on: Jun 3, 2015
 *      Author: travis
 */

#include "LcdHardware.h"
#include "display.h"
#include "math.h"

#include <stdio.h>

#define LINE_HEIGHT 10
#define CENTERED_Y    (display_height()/2)
#define CENTERED_X    (display_width()/2)

void LcdHardware_Init() {
  display_init();
  display_fillScreen(DISPLAY_BLACK);
}

void LcdHardware_ShowInfo(double* highScores, int32_t length, double newScore) {
  double epsilon = 0.0000001; // used for checking float equality

  display_fillScreen(DISPLAY_BLACK);
  display_setCursor(0,0);

  char str[255];

  display_setTextSize(2);
  display_println("How to play Reflex Test");
  display_setTextSize(1);
  display_println("");
  display_println("When the game begins, one of the LEDs will flash on.");
  display_println("Press the corresponding button as fast as you can.");

  display_println("");

  display_println("Hold any button to begin.");

  display_println("");
  display_println("");
  display_println("");
  display_println("");
  display_println("");
  display_println("");
  display_setTextSize(2);

  display_println("High Scores");

  display_setTextSize(1);

  int i;
  for (i = 0; i < 5; i++) {
    display_setCursor(0, CENTERED_Y + (LINE_HEIGHT*(i+1)));
    sprintf(str, "%d. %lf", (i+1), highScores[i]);
    // highlight the newest high score.
    if(fabs(highScores[i] - newScore) < epsilon) {
      display_setTextColor(DISPLAY_GREEN);
    }
    else {
      display_setTextColor(DISPLAY_WHITE);
    }
    display_println(str);
  }

  for (i = 5; i < 10; i++) {
    display_setCursor(CENTERED_X, CENTERED_Y + (LINE_HEIGHT*(i-4)));
    sprintf(str, "%d. %lf", (i+1), highScores[i]);
    // highlight the newest high score.
    if(fabs(highScores[i] - newScore) < epsilon) {
      display_setTextColor(DISPLAY_GREEN);
    }
    else {
      display_setTextColor(DISPLAY_WHITE);
    }
    display_println(str);
  }
}

void LcdHardware_BlankScreen(void) {
  display_fillScreen(DISPLAY_BLACK);
}

void LcdHardware_ShowStats(double average, double min, double max) {

  char str[255];
  sprintf(str, "Average Time: %lf", average);
  display_println(str);
  sprintf(str, "Fastest Time: %lf", min);
  display_println(str);
  sprintf(str, "Slowest Time: %lf", max);
  display_println(str);

}
