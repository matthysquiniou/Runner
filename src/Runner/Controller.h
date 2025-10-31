#pragma once
#include "ControllerFlags.h"
#include "Input.h"
#include <vector>

class Character;

class Controller : public Input
{
public:
    bool GetFlag(ControllerFlags flag);
    void Update();

    // traite le mouvement / actions du player (appele depuis Character::Update)
    void ProcessInput(Character* character, float deltaTime);

private:
    void ResetFlags();
    void UpdateFlags();
private:
    std::vector<ControllerFlags> m_flags;
};

