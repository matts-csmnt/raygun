#pragma once
#include "rayg_surface.h"

namespace ray_g {

	//-------------
	// Default Scenes
	//-------------
	
	//-------------
	// Random Scenes
	//-------------

	SurfaceList RandomScene();

	//-------------
	// Test Scenes
	//-------------

	SurfaceList TwoPerlinSpheres();
	SurfaceList CornellBox();
}