#pragma once
#include "Scene.h"
#include <GCSR.h>

class SettingsScene :
    public Scene
{
public:
    SettingsScene();
    ~SettingsScene();
    void Render() override;
    void Update(float deltaTime) override;
    TagScene GetTag() const override;

private:
    sr::Text* m_settinsText;
    sr::Text* m_TODOText;
    sr::Text* m_goBackText;
};

