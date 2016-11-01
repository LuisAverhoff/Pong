#include "Paddle.h"
#include "Ball.h"
#include <cmath>
#include <random>

namespace PaddleRandomNumGenerator
{
	std::random_device randDevice;
	std::default_random_engine randomGenerator(randDevice());
}

Paddle::Paddle(float xPos, float yPos, const int WIDTH, const int HEIGHT) : 
	PADDLE_X_POSITION(xPos), paddleYPosition(yPos),
	PADDLE_WIDTH(WIDTH), PADDLE_HEIGHT(HEIGHT)
{

}

float Paddle::getYPosition() const
{
	return  paddleYPosition; 
}

void Paddle::moveUp(float newYPosition)
{
	if (paddleYPosition > 10) // Height of the top rectangle.
	{
		paddleYPosition -= newYPosition;
	}
}

void Paddle::moveDown(float newYPosition, const int SCREEN_HEIGHT)
{
	if ((paddleYPosition + PADDLE_HEIGHT) < SCREEN_HEIGHT)
	{
		paddleYPosition += newYPosition;
	}
}

void Paddle::AIMove(Ball *ball, float timestep, const int SCREEN_HEIGHT)
{
	float impactDistance, impactTime, targetY;
    
	float ballX = ball->getCenterX();
	float ballY = ball->getCenterY();
	float ballDx = ball->getVelocityX();
	float ballDy = ball->getVelocityY();

	std::uniform_real_distribution<float> speedFactor(0.45f, 0.85f); // A speed factor between 0.65 and 0.85.
	float AISpeedUpFactor = speedFactor(PaddleRandomNumGenerator::randomGenerator);

	impactDistance = PADDLE_X_POSITION - ballX;
	impactTime = impactDistance / (ballDx * AISpeedUpFactor * 1000.0f);
	targetY = ballY + (ballDy * AISpeedUpFactor * 1000.0f) * impactTime;

	if (abs(targetY - (paddleYPosition + (PADDLE_HEIGHT / 2.0f))) < 10.0f)
	{
		return;
	}

	if (targetY > paddleYPosition + (PADDLE_HEIGHT / 2))
	{
		float newYPosition = Y_VELOCITY * AISpeedUpFactor * timestep;
		moveDown(newYPosition, SCREEN_HEIGHT);
	}
	else if (targetY < paddleYPosition + (PADDLE_HEIGHT / 2))
	{
		float newYPosition = Y_VELOCITY * AISpeedUpFactor * timestep;
		moveUp(newYPosition);
	}
}
