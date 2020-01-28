#pragma once

class TouchXPT2046 : public Touch
{
	XPT2046_Touchscreen  *_touch;
	int16_t _x0;
	int16_t _y0;
	int16_t _x1;
	int16_t _y1;
	int16_t _x;
	int16_t _y;
	
public:
	TouchXPT2046(XPT2046_Touchscreen *touch) : Touch(), _touch(touch), _x0(0), _y0(0), _x1(320), _y1(200) { }

	void scale(int16_t x0, int16_t y0, int16_t x1, int16_t y1)
	{
		_x0 = x0;
		_y0 = y0;
		_x1 = x1;
		_y1 = y1;
	}

	bool dataAvailable()
	{
		return _touch->touched();
	}
	
	int16_t getX()
	{
		return _x;
	};

	int16_t getY()
	{
		return _y;
	}

	void read()
	{
		uint16_t x, y;
		uint8_t z;
		_touch->readData(&x, &y, &z);
		_x = ((int32_t)x) * (_x1 - _x0) / 4096 + _x0;
		_y = ((int32_t)y) * (_y1 - _y0) / 4096 + _y0;
	}
};
