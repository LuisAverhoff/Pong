#ifndef BALL_H
#define BALL_H

#include "Sound.h"
#include "Paddle.h"

class Ball
{
	public:
		Ball(float, float, const float);
		void launchBall();
		bool isBallLaunched();
		void move(float);
		void checkForCollision(float, Paddle *, Paddle *, Sound &, const int, const int);
		bool ballWallCollision(const int);
		bool ballPaddleCollision(Paddle *);
		void deflectBall(Paddle *);
		void updateScore(unsigned int *, unsigned int *, Sound &, const int, const int);
		void resetBall(const int, const int);
		float getCenterX() const;
		float getCenterY() const;

	private:
		float centerX, centerY;
		float xVelocity, yVelocity, speed;
		float angle;
		bool ballLaunched;
	
	public:
		const float RADIUS;
};

#endif 

