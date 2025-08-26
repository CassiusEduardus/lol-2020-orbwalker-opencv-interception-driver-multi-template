#include "Estruturas.h"

InterceptionMouseStroke MOUSE_STROKE_ENPOS;
InterceptionMouseStroke MOUSE_STROKE_MYPOS;

MSE_Context_STRUCT MOUSE_CONTEXT_G;

KBD_Context_STRUCT KBD_Context = {};

int SPACE_STATE_G = 0;

int SLEEP_CAST_G = 1000;
int SLEEP_WALK_G = 1000;

int X_POS_ATUAL = 0;
int Y_POS_ATUAL = 0;

unsigned int screenWidth;
unsigned int screenHeight;

int myChampID = 0;

float ATSP_G = 0.48;