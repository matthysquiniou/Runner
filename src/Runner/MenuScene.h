#pragma once
#include "Scene.h"
#include <GCSR.h>

class MenuScene :
    public Scene
{
public:
    MenuScene();
    ~MenuScene();
    void Render() override;
    void Update(float deltaTime) override;
    TagScene GetTag() const override; 

private:
    sr::Text* m_startText;
    sr::Text* m_exitText;
    sr::Text* m_settingsText;
    sr::Text* m_titleText;
};

