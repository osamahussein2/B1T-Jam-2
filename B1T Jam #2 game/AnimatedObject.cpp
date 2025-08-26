#include "AnimatedObject.h"
#include "Window.h"

AnimatedObject::AnimatedObject() : animatedTexture(NULL), srcAnimation(), destAnimation(), animatedSurface(NULL), 
animationTimer(0.0f), frameY(0)
{
}

AnimatedObject::~AnimatedObject()
{
	SDL_DestroyTexture(animatedTexture);

	animatedTexture = NULL;
}

void AnimatedObject::InitializeAnimation(std::string filePath_)
{
	// Load the images from SDL image library
	animatedSurface = IMG_Load(filePath_.c_str());

	if (!animatedSurface) std::cout << "Can't load " << SDL_GetError();

	// Use the sprite texture to render from the SDL's surface
	animatedTexture = SDL_CreateTextureFromSurface(Window::GetRenderer(), animatedSurface);

	// Free the surface to release any used memory
	SDL_DestroySurface(animatedSurface);
}

void AnimatedObject::UpdateAnimation(int numberOfFramesX_, int numberOfFramesY_, Vector2 position_, 
	Vector2 scaleMultiplier_, float startAnimationTime_)
{
	// Prevents from going to whichever frame the programmer chooses if the frame is meant to be a static one
	if (animationTimer <= startAnimationTime_) animationTimer = startAnimationTime_;

	// Prevents the x frame animation from animating too fast
	animationTimer += Window::GetDeltaTime() * 10.0f;

	// Set the source rectangle to match the sprite dimensions for animation
	srcAnimation.x = (animatedTexture->w / static_cast<float>(numberOfFramesX_)) * 
		(static_cast<int>(animationTimer) % numberOfFramesX_);

	srcAnimation.y = (animatedTexture->h / static_cast<float>(numberOfFramesY_)) * (frameY % numberOfFramesY_);

	srcAnimation.w = animatedTexture->w / static_cast<float>(numberOfFramesX_);
	srcAnimation.h = animatedTexture->h / static_cast<float>(numberOfFramesY_);

	// Draw animated object somewhere on window
	destAnimation.x = position_.x;
	destAnimation.y = position_.y;

	destAnimation.w = (srcAnimation.w * scaleMultiplier_.x) * (static_cast<float>(Window::GetWindowWidth()) / 800.0f);
	destAnimation.h = (srcAnimation.h * scaleMultiplier_.y) * (static_cast<float>(Window::GetWindowHeight()) / 600.0f);
}

void AnimatedObject::FreezeAnimation(int numberOfFramesX_, int numberOfFramesY_, Vector2 position_, 
	Vector2 scaleMultiplier_)
{
	// Set the source rectangle to match the sprite dimensions for freezing at frame
	srcAnimation.x = (animatedTexture->w / static_cast<float>(numberOfFramesX_));

	srcAnimation.y = (animatedTexture->h / static_cast<float>(numberOfFramesY_)) * (frameY % numberOfFramesY_);

	srcAnimation.w = animatedTexture->w / static_cast<float>(numberOfFramesX_);
	srcAnimation.h = animatedTexture->h / static_cast<float>(numberOfFramesY_);

	// Draw freezed object somewhere on window
	destAnimation.x = position_.x;
	destAnimation.y = position_.y;

	destAnimation.w = (srcAnimation.w * scaleMultiplier_.x) * (static_cast<float>(Window::GetWindowWidth()) / 800.0f);
	destAnimation.h = (srcAnimation.h * scaleMultiplier_.y) * (static_cast<float>(Window::GetWindowHeight()) / 600.0f);
}

void AnimatedObject::RenderAnimation(bool halfTransparent_)
{
	SDL_RenderTexture(Window::GetRenderer(), animatedTexture, &srcAnimation, &destAnimation);

	if (halfTransparent_)
	{
		SDL_SetTextureAlphaMod(animatedTexture, 50);
	}

	else
	{
		SDL_SetTextureAlphaMod(animatedTexture, 255);
	}
}