#ifndef FADINGTEXT_H
#define FADINGTEXT_H

#pragma once

#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include "Vector2.h"
#include "Text.h"

class FadingText : public Text
{
public:
	FadingText();
	~FadingText();

	virtual void InitializeText(std::string text_, float fontSize_, Vector2 textPos_, SDL_Color color_ = DARK_GREEN) override;

	virtual void RenderText() override;
	virtual void DestroyText() override;

	int GetAlpha() const { return alpha; }
	void SetAlpha(float alpha_) { alpha = alpha_; }

	bool GetAlphaStateChanged() const { return alphaStateChanged; }
	void SetAlphaStateChanged(bool alphaStateChanged_) { alphaStateChanged = alphaStateChanged_; }

private:
	float alpha;

	bool alphaStateChanged;
};

#endif