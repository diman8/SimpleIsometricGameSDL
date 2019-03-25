#include "Camera.h"



Camera::Camera()
{
	this->offset_x = 0;
	this->offset_y = 0;
	this->zoom = 1;
}

Camera::Camera(int offsetx, int offsety, float zoom)
{
	this->offset_x = offsetx;
	this->offset_y = offsety;
	this->zoom = zoom;
}


Camera::~Camera()
{
}
