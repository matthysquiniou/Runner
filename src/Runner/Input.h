#pragma once
#include "GCSR.h"

class Input
{
public:

	virtual bool IsKeyPressed(sr::Keyboard::Key key) const;
	virtual bool IsMouseButtonPressed(sr::Mouse::Button button) const;

};

