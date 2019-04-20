#pragma once

//PI
#ifndef M_PI
#define M_PI 3.14159265359
#endif // !M_PI

//HELPERS
float degToRad(float d) {
	return d * (M_PI / 180);
}