#include <iostream>
#include <SDL3/SDL.h>
#include <glm/glm.hpp>

#include "Renderer.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Scene.h"
#include "Sphere.h"
#include "Material.h"
#include "Random.h"
#include "Plane.h"

int main() {
	constexpr int SCREEN_WIDTH = 1800;
	constexpr int SCREEN_HEIGHT = 900;

	// create renderer
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Ray Tracer", SCREEN_WIDTH, SCREEN_HEIGHT);

	Framebuffer framebuffer(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	float aspectRatio = (float)framebuffer.width / framebuffer.height;
	Camera camera(20.0f, aspectRatio);
	camera.SetView({ 13, 2, 3 }, { 0, 0, 0 });

	Scene scene;

	auto red = std::make_shared<Lambertian>(color3_t{ 1.0f, 0.0f, 0.0f });
	auto green = std::make_shared<Lambertian>(color3_t{ 0.0f, 1.0f, 0.0f });
	auto blue = std::make_shared<Lambertian>(color3_t{ 0.0f, 0.0f, 1.0f });
	auto light = std::make_shared<Emissive>(color3_t{ 1.0f, 1.0f, 1.0f }, 3.0f);
	auto metal = std::make_shared<Metal>(color3_t{ 1.0f, 1.0f, 1.0f }, 0.0f);
	std::vector<std::shared_ptr<Material>> materials = { red, green, blue, light, metal };

	for (int i = 0; i < 15; i++) {
		glm::vec3 position = random::getReal(glm::vec3{ -3.0f }, glm::vec3{ 3.0f });
		float radius = random::getReal(0.1f, 0.7f);
		std::shared_ptr<Material> material = materials[random::getInt(0, static_cast<int>(materials.size()) - 1)];
		std::unique_ptr<Object> sphere = std::make_unique<Sphere>(position, radius, material);
		scene.AddObject(std::move(sphere));
	}

	auto gray = std::make_shared<Lambertian>(color3_t{ 0.2f, 0.2f, 0.2f });
	std::unique_ptr<Plane> plane = std::make_unique<Plane>(gray);
	scene.AddObject(std::move(plane));

	// --- render once before the main loop ---
	const int samples = 150; // 
	scene.Render(framebuffer, camera, samples);
	framebuffer.Update();
	renderer.CopyFramebuffer(framebuffer);
	renderer.Show();
	// --------------------------------------------------------

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
			// optional: press R to re-render (if you want to re-run raytrace)
			if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_R) {
				framebuffer.Clear({ 0, 0, 0, 255 });
				scene.Render(framebuffer, camera, samples);
				framebuffer.Update();
				renderer.CopyFramebuffer(framebuffer);
				renderer.Show();
			}
		}

		// present pre-rendered image (cheap)
		renderer.CopyFramebuffer(framebuffer);
		renderer.Show();

		// small sleep to avoid busy loop; tune as needed
		SDL_Delay(10);
	}
}