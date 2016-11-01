#ifndef PADDLE_H
#define PADDLE_H

class Ball;

class Paddle
{
	public:
		Paddle(const float, float, const int, const int);
		float getYPosition() const;
		void moveUp(float);
		void moveDown(float, const int);
		void AIMove(Ball *, float, const int);

	private:
		float paddleYPosition;

	public:
		const int PADDLE_WIDTH;
		const int PADDLE_HEIGHT;
		const float PADDLE_X_POSITION;
		const float Y_VELOCITY = 640.0f;
};

#en
