#include "Sound.h"

Sound::Sound()
{
	paddleBallCollisionEffect = loadChunk("PongPaddleHit.wav");
	ballWallCollisionEffect = loadChunk("PongWallHit.wav");
	scoreSoundEffect = loadChunk("PongScoreSound.wav");
}

void Sound::playSoundEffect(int soundID)
{
	switch (soundID)
	{
		case 1:
			Mix_PlayChannel(-1, paddleBallCollisionEffect.get(), 0);
			break;
		case 2:
			Mix_PlayChannel(-1, ballWallCollisionEffect.get(), 0);
			break;
		case 3:
			Mix_PlayChannel(-1, scoreSoundEffect.get(), 0);
			break;
		default:
			break;
	}
}

std::unique_ptr<Mix_Chunk, SDL2Sound::SDL2Sound_Deleter>
Sound::loadChunk(char const *title)
{
	return std::unique_ptr<Mix_Chunk, SDL2Sound::SDL2Sound_Deleter>(Mix_LoadWAV(title), SDL2Sound::SDL2Sound_Deleter());
}
