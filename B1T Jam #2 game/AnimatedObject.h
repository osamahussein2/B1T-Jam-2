#ifndef ANIMATEDOBJECT_H
#define ANIMATEDOBJECT_H

#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Vector2.h"

#include <iostream>

class AnimatedObject
{
public:
	AnimatedObject();
	~AnimatedObject();
	
	void InitializeAnimation(std::string filePath_);
	
	void UpdateAnimation(int numberOfFramesX_, int numberOfFramesY_, Vector2 position_, Vector2 scaleMultiplier_, 
		float startAnimationTime_);

	void FreezeAnimation(int numberOfFramesX_, int numberOfFramesY_, Vector2 position_, Vector2 scaleMultiplier_);
	void RenderAnimation();

	int frameY;

	SDL_FRect GetAnimationPosition() const { return destAnimation; }

private:
	SDL_Texture* animatedTexture;
	
	SDL_FRect srcAnimation;
	SDL_FRect destAnimation;
	
	SDL_Surface* animatedSurface;
	
	float animationTimer;
};

#endif