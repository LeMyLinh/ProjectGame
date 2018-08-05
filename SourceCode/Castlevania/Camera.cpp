#include "Camera.h"
#include "Define.h"

#define ACTIVE_AREA_WIDTH 32
#define ACTIVE_AREA_HEIGHT 32

Camera * Camera::instance = nullptr;

Camera * Camera::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Camera();
		instance->width = GAME_WIDTH;
		instance->height = GAME_HEIGHT;
	}

	return instance;
}

Camera::Camera(int width, int height)
{
	this->width = width;
	this->height = height;
	this->position = D3DXVECTOR3(0, 0, 0);
	this->velocity = D3DXVECTOR2(0, 0);
	this->canFollowHorizontal = true;

	instance = this;
}

Camera::Camera()
{

}

Camera::~Camera()
{
}

void Camera::setPosition(float x, float y)
{
	setPosition(D3DXVECTOR3(x, y, 0));
}

void Camera::setPosition(D3DXVECTOR3 pos)
{
	this->position = pos;
}

void Camera::setPosition(D3DXVECTOR2 pos)
{
	setPosition(pos.x, pos.y);
}

D3DXVECTOR3 Camera::getPosition()
{
	return this->position;
}

RECT Camera::getBound()
{
	RECT bound;

	bound.left = (LONG)(position.x - width * 0.5f);
	bound.right = (LONG)(position.x + width * 0.5f);
	bound.top = (LONG)(position.y - height * 0.5f);
	bound.bottom = (LONG)(position.y + height * 0.5f);

	return bound;
}

int Camera::getWidth()
{
	return this->width;
}

int Camera::getHeight()
{
	return this->height;
}

D3DXVECTOR2 Camera::getVelocity()
{
	return this->velocity;
}

void Camera::setVelocity(D3DXVECTOR2 vec)
{
	this->velocity = vec;
}

RECT Camera::getActiveArea()
{
	RECT area;
	area.left = (LONG)(this->position.x - ACTIVE_AREA_WIDTH * 0.5f);
	area.right = (LONG)(area.left + ACTIVE_AREA_WIDTH);
	area.top = (LONG)(this->position.y - ACTIVE_AREA_HEIGHT * 0.5f);
	area.bottom = (LONG)(area.top + ACTIVE_AREA_HEIGHT);

	return area;
}

void Camera::update(float dt)
{
	this->position = D3DXVECTOR3(this->position.x + this->velocity.x * dt, this->position.y + this->velocity.y * dt, 0);
}

void Camera::setCanFoLLowHorizontal(bool flag)
{
	this->canFollowHorizontal = flag;
}

bool Camera::canFollowHorizon()
{
	return this->canFollowHorizontal;
}