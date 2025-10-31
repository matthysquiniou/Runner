#pragma once
#include "Scene.h"
#include <GCSR.h>

class PauseScene :
    public Scene
{
public:
    PauseScene();
    ~PauseScene();
    void Render() override;
    void Update(float deltaTime) override;
    TagScene GetTag() const override;

private:
    sr::Text* m_pausedText;
    sr::Text* m_resumeText;
    sr::Text* m_settingsText;
    sr::Text* m_restartText;
    sr::Text* m_quitMenuText;
    sr::Text* m_quitGameText;
};

