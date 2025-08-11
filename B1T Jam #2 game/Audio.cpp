#include "Audio.h"

Audio::Audio() : engine(), sound()
{
}

Audio::~Audio()
{
}

void Audio::InitializeAudio(std::string filePath_, ma_bool32 looping_)
{
	ma_result result;
	result = ma_engine_init(NULL, &engine);

#ifdef _DEBUG
	if (result != MA_SUCCESS)
	{
		printf("Failed to initialize audio engine.");
	}
#endif

	// Load sound
	result = ma_sound_init_from_file(&engine, filePath_.c_str(), 0, NULL, NULL, &sound);

#ifdef _DEBUG
	if (result != MA_SUCCESS)
	{
		printf("Failed to initialize sound.");
	}
#endif

	// Set sound loop
	ma_sound_set_looping(&sound, looping_);
}

void Audio::PlayAudio()
{
	// Play sound
	ma_sound_start(&sound);
}

void Audio::StopAudio()
{
	// Stop sound
	ma_sound_stop(&sound);
}

void Audio::UnloadAudio()
{
	// Unload audio engine and sound
	ma_sound_uninit(&sound);
	ma_engine_uninit(&engine);
}
