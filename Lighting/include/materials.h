#ifndef MATERIALS_H
#define MATERIALS_H

float *goldAmbient(void)  { static float a[] = { 0.2473f, 0.1995f, 0.0745f, 1.0f }; return a; }
float *goldDiffuse(void)  { static float a[] = { 0.7516f, 0.6065f, 0.2265f, 1.0f }; return a; };
float *goldSpecular(void) { static float a[] = { 0.6283f, 0.5558f, 0.3661f, 1.0f }; return a; };
float goldShininess(void) { return 51.2f; }

float *pearlAmbient(void)  { static float a[] = { 0.2500f, 0.2073f, 0.2073f, 0.922f }; return a; }
float *pearlDiffuse(void)  { static float a[] = { 1.0000f, 0.8290f, 0.8290f, 0.922f }; return a; };
float *pearlSpecular(void) { static float a[] = { 0.2966f, 0.2966f, 0.2966f, 0.922f }; return a; };
float pearlShininess(void) { return 11.264f; }

#endif // !MATERIALS_H
