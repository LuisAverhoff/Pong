#ifndef PADDLE_H
#define PADDLE_H

class Paddle
{
	public:
		Paddle(const float, float, const int, const int);
		void moveUp(float);
		void moveDown(float, const int);
		float getYPosition() const;

	private:
		float paddleYPosition;

	public:
		const int PADDLE_WIDTH;
		const int PADDLE_HEIGHT;
		const float PADDLE_X_POSITION;
		const float Y_VELOCITY = 640.0f;
};

#endif
