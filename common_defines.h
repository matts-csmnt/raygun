#pragma once

//----------
//PI
//----------

#ifndef M_PI
#define M_PI 3.14159265359
#endif // !M_PI

//----------
//Deg to Rad
//----------

float degToRad(float d);

//----------
// MACROS
//----------

#define SAFE_DELETE(x){if(x){delete x; x = nullptr;}}