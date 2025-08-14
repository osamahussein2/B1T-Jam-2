#ifndef AUDIO_H
#define AUDIO_H

#pragma once

#include <miniaudio.h>

#include <iostream>

class Audio
{
public:
	Audio();
	~Audio();

	void InitializeAudio(std::string filePath_, ma_bool32 looping_ = MA_FALSE);

	void PlayAudio();
	void StopAudio();

	void UnloadAudio();

private:
	ma_engine engine;
	ma_sound sound;
};

#endif