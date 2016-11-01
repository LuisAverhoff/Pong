#include "Ball.h"
#include "Paddle.h"
#include "Sound.h"
#include <random>
#include <cmath>

namespace ballRandomNumGenerator
{
	std::random_device randDevice;
	std::default_random_engine randomGenerator(randDevice());
}

static float degree2Rad(float);
static float clamp(float, float, float);
static int sgn(float val);

constexpr float PI_F = 3.14159265358979f;
constexpr float MAX_BOUNCE_ANGLE = PI_F / 4;
constexpr float SPEED_UP_FACTOR = 1.1f;

Ball::Ball(float xCoord, float yCoord, const float RAD) : centerX(xCoord), centerY(yCoord), RADIUS(RAD)
{
	xVelocity = 0.0f;
	yVelocity = 0.0f;
	speed = 640.0f;
	angle = 0.0f;
	ballLaunched = false;
}

void Ball::launchBall()
{
	std::uniform_int_distribution<int> dir(0, 1);
	int dirPivot = dir(ballRandomNumGenerator::randomGenerator);
	int direction = (dirPivot == 0 ? -1 : 1);

	std::uniform_real_distribution<float> degree(-60, 60);
	angle = degree(ballRandomNumGenerator::randomGenerator);

	xVelocity = direction * speed * cos(degree2Rad(angle));
	yVelocity = speed * sin(degree2Rad(angle));

	ballLaunched = true;
}

bool Ball::isBallLaunched()
{
	return ballLaunched;
}

void Ball::move(float newXPosition, float newYPosition)
{
	centerX += newXPosition;
	centerY += newYPosition;
}

void Ball::checkForCollision(float timeStep, Paddle *playerPaddle, Paddle *AIPaddle, Sound &sound, const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
	if (centerX < (SCREEN_WIDTH / 2.0f) && xVelocity < 0.0f)
	{
		if (ballPaddleCollision(playerPaddle))
		{
			deflectBall(playerPaddle);
			float newXPosition = xVelocity * timeStep;
			float newYPosition = yVelocity * timeStep;
			move(newXPosition, newYPosition); // Move early. Do not wait for the next frame to move.
			sound.playSoundEffect(1);
		}
	}
	else if(centerX >= (SCREEN_WIDTH / 2.0f) && xVelocity > 0.0f)
	{
		if (ballPaddleCollision(AIPaddle))
		{
			deflectBall(AIPaddle);
			float newXPosition = xVelocity * timeStep;
			float newYPosition = yVelocity * timeStep;
			move(newXPosition, newYPosition); 
			sound.playSoundEffect(1);
		}
	}

	if (ballWallCollision(SCREEN_HEIGHT))
	{
		yVelocity *= -1.0f; // reverse in the y-axis.
		centerY += (yVelocity * timeStep); // quickly update the position. Do not wait for the next frame to move
		sound.playSoundEffect(2);
	}
}

bool Ball::ballWallCollision(const int SCREEN_HEIGHT)
{
	return (centerY - RADIUS < 10) || (centerY + RADIUS > SCREEN_HEIGHT);
}

bool Ball::ballPaddleCollision(Paddle *paddle)
{
	float deltaX = centerX - clamp(centerX, paddle->PADDLE_X_POSITION, paddle->PADDLE_X_POSITION + paddle->PADDLE_WIDTH);
	float deltaY = centerY - clamp(centerY, paddle->getYPosition(), paddle->getYPosition() + paddle->PADDLE_HEIGHT);;
	return (deltaX * deltaX + deltaY * deltaY) <= (RADIUS * RADIUS);
}

void Ball::deflectBall(Paddle *paddle)
{
	speed = sqrt((xVelocity * xVelocity) + (yVelocity * yVelocity)) * SPEED_UP_FACTOR;
	float pointOfContact = (paddle->getYPosition() + (paddle->PADDLE_HEIGHT / 2)) - centerY;
	float normalizedPointOfContact = (pointOfContact / (paddle->PADDLE_HEIGHT / 2));
	angle = normalizedPointOfContact * MAX_BOUNCE_ANGLE;
	xVelocity = -sgn(xVelocity) * speed * cos(angle); // sgn is to reverse the direction of the xVelocity.
	yVelocity = speed * sin(angle); 
}

void Ball::updateScore(unsigned int *playerScore, unsigned int *AIScore, Sound &sound, const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
	if (centerX + RADIUS < 0)
	{
		sound.playSoundEffect(3);
		(*AIScore)++;
		resetBall(SCREEN_WIDTH, SCREEN_HEIGHT);
	}
	else if(centerX - RADIUS > SCREEN_WIDTH)
	{
		sound.playSoundEffect(3);
		(*playerScore)++;
		resetBall(SCREEN_WIDTH, SCREEN_HEIGHT);
	}
}

void Ball::resetBall(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
	centerX = SCREEN_WIDTH / 2.0f;
	centerY = SCREEN_HEIGHT / 2.0f;
	xVelocity = 0.0f;
	yVelocity = 0.0f;
	speed = 640.0f;
	ballLaunched = false;
}

float Ball::getCenterX() const
{
	return centerX;
}

float Ball::getCenterY() const
{
	return centerY;
}

float Ball::getVelocityX() const
{
	return xVelocity;
}

float Ball::getVelocityY() const
{
	return yVelocity;
}

static float degree2Rad(float degrees)
{
	return degrees * PI_F / 180.0f;
}

static float clamp(float val, float min, float max)
{
	return val < min ? min : val > max ? max : val;
}

static int sgn(float val)
{
	return (val > 0) ? 1 : ((val) < 0 ? -1 : 0);
}
