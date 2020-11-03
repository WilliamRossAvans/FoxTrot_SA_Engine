#pragma once

/// @brief Interface class for Sound facade
class ISoundFacade
{
public:
	virtual bool isMix_PlayingMusic() = 0;
	virtual void SetFiles(unordered_map<string, string> files) = 0;
	virtual void AddFile(const string& identifier, const string& file) = 0;
	virtual void PlayEffect(const string& identifier, const int volume) = 0;
	virtual void LoadEffect(const string& identifier) = 0;
	virtual void UnloadEffect(const string& identifier) = 0;
	virtual void StartLoopedEffect(const string& effect) = 0;
	virtual void StopLoopedEffect(const string& identifier) = 0;
	virtual void LoadMusic(const string& identifier) = 0;

	virtual void PlayMusic(const int volume) = 0;
	virtual void PlayMusic(const string& identifier, const int volume) = 0;

	virtual void ChangeMusic(const string& identifier) = 0;
	virtual void FadeOutMusic(const int fadeTime) = 0;

	virtual void FadeInMusic(const int fadeTime) = 0;
	virtual void FadeInMusic(const string& identifier, const int fadeTime) = 0;

	virtual void RewindMusic() = 0;
	virtual void StopMusic() = 0;
	virtual void PauseMusic() = 0;
	virtual void ResumeMusic() = 0;
	virtual void Flush() = 0;

	virtual bool IdentifierExists(const string& identifier) = 0;
	virtual bool IdentifierIsLoaded(const string& identifier) = 0;

	virtual unordered_map<string, string>& GetSoundPaths() = 0;
	virtual unordered_map<string, int>& GetLoopchannels() = 0;

private:

};
