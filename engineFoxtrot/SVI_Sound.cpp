#include "SVI.h"

// Functions in this cpp file may only call functions in this file. And global SDL2 definitions

/// @brief
/// Replaces the identifier,filepath map
/// @param files
void SVI::SetFiles(map<string, string> files)
{
	this->soundPaths = files;
}

/// @brief 
/// Adds a file to the files map
/// @param identifier 
/// The identifier to link the file to
/// @param file
/// The file path to the music/effect
void SVI::AddFile(const string& identifier, const string& file) {
	this->soundPaths[identifier] = file;
}

/// @brief 
/// Flushes the audio buffers
void SVI::Flush()
{
	for (auto it = loadedSoundEffects.begin(); it != loadedSoundEffects.end(); /* don't increment here*/) {
		it = loadedSoundEffects.erase(it);  /// update here
	}
	for (auto it = loopChannels.begin(); it != loopChannels.end(); /* don't increment here*/) {
		it = loopChannels.erase(it);  /// update here
	}
}

/// @brief 
/// Plays the effect that belongs to the given identifier at max volume
/// @param identifier 
/// The sound identifier saved when the file has been added
void SVI::PlayEffect(const string& identifier) {
	///Play sound (first parameter is the channel, the last one the amount of loops)
	if (soundPaths.find(identifier) != soundPaths.end() && loadedSoundEffects.find(identifier) == loadedSoundEffects.end()) {
		LoadEffect(identifier);
	}
	if (loadedSoundEffects.find(identifier) != loadedSoundEffects.end()) {
		int channel = Mix_PlayChannel(FIRST_AVAILABLE_CHANNEL, loadedSoundEffects[identifier], DONT_LOOP);
		Mix_Volume(channel, MIX_MAX_VOLUME);
	}
}

/// @brief 
/// Plays the effect that belongs to the given identifier at the given volume
/// @param identifier 
/// The sound identifier saved when the file has been added
/// @param volume
/// The volume to play the effect at. Ranges from 1 to 128
void SVI::PlayEffect(const string& identifier, int volume) {
	///Play sound (first parameter is the channel, the last one the amount of loops)
	if (soundPaths.find(identifier) != soundPaths.end() && loadedSoundEffects.find(identifier) == loadedSoundEffects.end()) {
		LoadEffect(identifier);
	}
	if (loadedSoundEffects.find(identifier) != loadedSoundEffects.end()) {
		int channel = Mix_PlayChannel(FIRST_AVAILABLE_CHANNEL, loadedSoundEffects[identifier], DONT_LOOP);
		Mix_Volume(channel, volume);
	}
}

/// @brief 
/// Loads the effect that belongs to the given identifier into the buffer
/// @param identifier 
/// The sound identifier saved when the file has been added
bool SVI::LoadEffect(const string& identifier) {
	if (loadedSoundEffects.find(identifier) == loadedSoundEffects.end()) {
		loadedSoundEffects[identifier] = Mix_LoadWAV(soundPaths.at(identifier).c_str());
		if (!loadedSoundEffects[identifier]) {
			std::cerr << "Mix_LoadWAV Error: " << Mix_GetError() << std::endl;
			return false;
		}
		return true;
	}
	return false;
}

/// @brief 
/// Unloads the effect that belongs to the given identifier from the buffer
/// @param identifier 
/// The sound identifier saved when the file has been added
void SVI::UnloadEffect(const string& identifier) {
	if (loadedSoundEffects.find(identifier) == loadedSoundEffects.end()) {
		return;
	}
	StopLoopedEffect(identifier);
	loadedSoundEffects.erase(identifier);
	loopChannels.erase(identifier);
}

/// @brief 
/// Indefinitely plays a loaded effect that belongs to the given identifier
/// @param identifier 
/// The sound identifier saved when the file has been added
void SVI::StartLoopedEffect(const string& identifier) {
	///Play sound forever and save it in the loopChannels map
	if (loadedSoundEffects.find(identifier) != loadedSoundEffects.end()) {
		int channel = Mix_PlayChannel(FIRST_AVAILABLE_CHANNEL, loadedSoundEffects[identifier], LOOP_INDEFINITELY);
		loopChannels.insert(pair<string, int>(identifier, channel));
	}
}

/// @brief 
/// Stops a looped effect
/// @param identifier 
/// The sound identifier saved when the file has been added
void SVI::StopLoopedEffect(const string& identifier) {
	///Stop the channel the looped effect is playing on
	if (loopChannels.find(identifier) != loopChannels.end()) {
		Mix_HaltChannel(loopChannels[identifier]);
		loopChannels.erase(identifier);
	}
}

/// @brief 
/// Loads the music that belongs to the given identifier into the buffer
/// @param identifier 
/// The sound identifier saved when the file has been added
bool SVI::LoadMusic(const string& identifier) {
	///If old music is loaded (!= NULL), free it
	if (music) {
		Mix_FreeMusic(music);
	}

	/// TODO add fade between music
	if (soundPaths.find(identifier) != soundPaths.end())
	{
		///Load new music and play it infinitely
		music = Mix_LoadMUS(soundPaths[identifier].c_str());
		if (!music) {
			std::cerr << "Mix_LoadMUS Error: " << Mix_GetError() << std::endl;
			return false;
		}
		return true;
	}
	return false;
}


/// @brief 
/// Plays the currently loaded music
void SVI::PlayMusic() {
	Mix_VolumeMusic(MIX_MAX_VOLUME);
	Mix_PlayMusic(music, LOOP_INDEFINITELY);
}

/// @brief 
/// Plays the currently loaded music at the given volume
/// @param volume 
/// The volume to play the music at. Ranges from 0 to 128
void SVI::PlayMusic(int volume) {
	Mix_VolumeMusic(volume);
	Mix_PlayMusic(music, LOOP_INDEFINITELY);
}

/// @brief 
/// Loads and plays music that belongs to the given identifier
/// @param identifier 
/// The sound identifier saved when the file has been added
void SVI::PlayMusic(const string& identifier) {
	if (soundPaths.find(identifier) != soundPaths.end()) {
		if (LoadMusic(identifier)) {
			Mix_VolumeMusic(MIX_MAX_VOLUME);
			Mix_PlayMusic(music, LOOP_INDEFINITELY);
		}
	}
}

/// @brief 
/// Loads and plays music that belongs to the given identifier at the given volume
/// @param identifier 
/// The sound identifier saved when the file has been added
/// @param volume
/// The volume to play the music at. Ranges from 0 to 128
void SVI::PlayMusic(const string& identifier, int volume) {
	if (soundPaths.find(identifier) != soundPaths.end()) {
		if (LoadMusic(identifier)) {
			Mix_VolumeMusic(volume);
			Mix_PlayMusic(music, LOOP_INDEFINITELY);
		}
	}
}

/// @brief 
/// Stops the currently playing music and swaps it with the music that belongs to the given identifier
/// @param identifier 
/// The sound identifier saved when the file has been added
void SVI::ChangeMusic(const string& identifier) {
	StopMusic();
	if (LoadMusic(identifier)) {
		PlayMusic();
	}
}

/// @brief 
/// Fades out the currently playing music over the given time
/// @param fadeTime 
/// The amount of time it takes for the music to fade in ms
void SVI::FadeOutMusic(int fadeTime) {
	Mix_FadeOutMusic(fadeTime);
}

/// @brief 
/// Fades in the currently playing music over the given time
/// @param fadeTime 
/// The amount of time it takes for the music to fade in ms
void SVI::FadeInMusic(int fadeTime) {
	RewindMusic();
	Mix_FadeInMusic(music, LOOP_INDEFINITELY, fadeTime);
}

/// @brief 
/// Fades in the music that belongs to the given identifier over [fadeTime]ms
/// @param identifier
/// The sound identifier saved when the file has been added
/// @param fadeTime 
/// The amount of time it takes for the music to fade in ms
void SVI::FadeInMusic(const string& identifier, int fadeTime) {
	StopMusic();
	if (LoadMusic(identifier)) {
		Mix_FadeInMusic(music, LOOP_INDEFINITELY, fadeTime);
	}
}

/// @brief 
/// Rewinds the currently playing music
void SVI::RewindMusic() {
	Mix_RewindMusic();
}

/// @brief 
/// Stops the currently playing music
void SVI::StopMusic() {
	Mix_PauseMusic();
}

/// @brief 
/// Pauses the currently playing music
void SVI::PauseMusic() {
	Mix_PauseMusic();
}

/// @brief 
/// Resumes the currently playing music
void SVI::ResumeMusic() {
	Mix_ResumeMusic();
}