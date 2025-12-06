#include <iostream>
#include <SDL3/SDL.h>
#include <glm/glm.hpp>

#include "Renderer.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Scene.h"
#include "Sphere.h"

int main() {
	constexpr int SCREEN_WIDTH = 1800;
	constexpr int SCREEN_HEIGHT = 900;

	// create renderer
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Ray Tracer", SCREEN_WIDTH, SCREEN_HEIGHT);

	Framebuffer framebuffer(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	float aspectRatio = (float)framebuffer.width / framebuffer.height;
	Camera camera(70.0f, aspectRatio);
	camera.SetView({ 0, 0, -5 }, { 0, 0, 0 });

	Scene scene;
	scene.AddObject(std::make_unique<Sphere>(glm::vec3{ -2, .5, 0 }, 1.0f, color3_t{ 1, 0, 0 }));
	scene.AddObject(std::make_unique<Sphere>(glm::vec3{ 2, -.5, 0 }, 1.0f, color3_t{ 1, 0, 1 }));


	SDL_Event event;
	bool quit = false;
	while (!quit) {
		// check for exit events
		while (SDL_PollEvent(&event)) {
			// window (X) quit
			if (event.type == SDL_EVENT_QUIT) {
				quit = true;
			}
			// escape key quit
			if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
				quit = true;
			}
		}

		// draw to frame buffer
		framebuffer.Clear({ 0, 0, 0, 255 });
		scene.Render(framebuffer, camera, 50);
		
		// update frame buffer, copy buffer pixels to texture
		framebuffer.Update();

		// copy frame buffer texture to renderer to display
		renderer.CopyFramebuffer(framebuffer);
		renderer.Show();
	}
}