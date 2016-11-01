#ifndef BALL_H
#define BALL_H

class Paddle;
class Sound;

class Ball
{
	public:
		Ball(float, float, const float);
		void launchBall();
		bool isBallLaunched();
		void move(float, float);
		void checkForCollision(float, Paddle *, Paddle *, Sound &, const int, const int);
		bool ballWallCollision(const int);
		bool ballPaddleCollision(Paddle *);
		void deflectBall(Paddle *);
		void updateScore(unsigned int *, unsigned int *, Sound &, const int, const int);
		void resetBall(const int, const int);
		float getCenterX() const;
		float getCenterY() const;
		float getVelocityX() const;
		float getVelocityY() const;

	private:
		float centerX, centerY;
		float xVelocity, yVelocity, speed;
		float angle;
		bool ballLaunched;
	
	public:
		const float RADIUS;
};

#endif 
