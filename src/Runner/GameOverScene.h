#pragma once
#include "Scene.h"
#include <GCSR.h>

class GameOverScene : 
    public Scene
{
public:
    GameOverScene();
    ~GameOverScene();
    void Render() override;
    void Update(float deltaTime) override;
    TagScene GetTag() const override;
    
private:
    sr::Text* m_gameOverText;
    sr::Text* m_restartText;
    sr::Text* m_scoreText;
    sr::Text* m_quitMenuText;
    sr::Text* m_quitGameText;
};

