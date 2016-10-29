#ifndef SOUND_H
#define SOUND_H

#include <SDL_mixer.h>
#include <memory>

namespace SDL2Sound
{
	struct SDL2Sound_Deleter
	{
		void operator()(Mix_Chunk *ptr) const { Mix_FreeChunk(ptr); }
	};

	using soundPtr = std::unique_ptr<Mix_Chunk, SDL2Sound_Deleter>;
}

class Sound
{
	public:
		Sound();
		void playSoundEffect(int);

	private:
		std::unique_ptr<Mix_Chunk, SDL2Sound::SDL2Sound_Deleter> loadChunk(char const *);
		SDL2Sound::soundPtr paddleBallCollisionEffect;
		SDL2Sound::soundPtr ballWallCollisionEffect;
		SDL2Sound::soundPtr scoreSoundEffect;
};

#endif
