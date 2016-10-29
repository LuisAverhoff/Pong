#include "Paddle.h"

Paddle::Paddle(float xPos, float yPos, const int WIDTH, const int HEIGHT) : 
	PADDLE_X_POSITION(xPos), paddleYPosition(yPos),
	PADDLE_WIDTH(WIDTH), PADDLE_HEIGHT(HEIGHT)
{

}

float Paddle::getYPosition() const
{
	return  paddleYPosition; 
}

void Paddle::moveUp(float timeStep)
{
	if (paddleYPosition > 10) // Height of the top rectangle.
	{
		paddleYPosition -= (Y_VELOCITY * timeStep);
	}
}

void Paddle::moveDown(float timeStep, const int SCREEN_HEIGHT)
{
	if ((paddleYPosition + PADDLE_HEIGHT) < SCREEN_HEIGHT)
	{
		paddleYPosition += (Y_VELOCITY * timeStep);
	}
}
