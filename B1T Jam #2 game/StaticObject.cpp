#include "StaticObject.h"
#include "Window.h"

StaticObject::StaticObject() : staticTexture(NULL), srcObject(), destObject(), staticSurface(NULL)
{
}

StaticObject::~StaticObject()
{
	SDL_DestroyTexture(staticTexture);

	staticTexture = NULL;
}

void StaticObject::InitializeStaticObject(std::string filePath_, Vector2 position_, Vector2 scaleMultiplier_)
{
	// Load the images from SDL image library
	staticSurface = IMG_Load(filePath_.c_str());

	if (!staticSurface) std::cout << "Can't load " << SDL_GetError();

	// Use the sprite texture to render from the SDL's surface
	staticTexture = SDL_CreateTextureFromSurface(Window::GetRenderer(), staticSurface);

	// Free the surface to release any used memory
	SDL_DestroySurface(staticSurface);

	// Set the source rectangle to match the object dimensions
	srcObject.x = 0.0f;
	srcObject.y = 0.0f;

	srcObject.w = staticTexture->w;
	srcObject.h = staticTexture->h;

	// Draw animated object somewhere on window
	destObject.x = position_.x;
	destObject.y = position_.y;

	destObject.w = (srcObject.w * scaleMultiplier_.x) * (static_cast<float>(Window::GetWindowWidth()) / 800.0f);
	destObject.h = (srcObject.h * scaleMultiplier_.y) * (static_cast<float>(Window::GetWindowHeight()) / 600.0f);
}

void StaticObject::RenderStaticObject()
{
	SDL_RenderTexture(Window::GetRenderer(), staticTexture, &srcObject, &destObject);
}
