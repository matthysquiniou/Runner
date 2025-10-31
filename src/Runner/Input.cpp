#include "pch.h"
#include "Input.h"

bool Input::IsKeyPressed(sr::Keyboard::Key key) const
{
    return sr::GetKey(key);
}

bool Input::IsMouseButtonPressed(sr::Mouse::Button button) const
{
    return sr::GetButton(static_cast<sr::Mouse::Button>(button));
}