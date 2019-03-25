#pragma once
class Camera
{
public:
	float zoom;
	int offset_x, offset_y;
	Camera();
	Camera(int offsetx, int offsety, float zoom);
	~Camera();
};

