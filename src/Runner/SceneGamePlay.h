#pragma once
#include "Scene.h"
#include <GCSR.h>

class TileManager;
class Tile;
class Character;

class SceneGamePlay :
    public Scene
{
public:

    SceneGamePlay();
    ~SceneGamePlay();

    void Init() override;
    void Update(float deltaTime) override;
    void Render() override;
    void AddScore(int scoreToAdd);

    float GetSpeed() const { return m_velocity; }
	int GetMaxSpeed() const { return m_maxSpeed; }
    int GetScore() const { return m_score; }


	SceneGamePlay* GetThis() { return this; }

    void Reset();

    TagScene GetTag() const override { return TagScene::GAMEPLAY; }
    void AddVelocity(float newSpeed);

    void UpdateTimer(float deltaTime);

	void AddTextInArray(sr::Text* text) { Texts.push_back(text); }

    float GetDifficultyMultiplier() { return m_difficultyMultiplier; }
    void SetDifficultyMultiplier(float difficulty) { m_difficultyMultiplier = difficulty; }

private:



    TileManager* m_tileManager;
    Tile* tile;
	Character* m_playerCharacter;

	std::vector<sr::Text*> Texts;

    int m_score = 0;
    float m_velocity = 0.f;
	float m_maxSpeed = 50.0;
    float m_elapsedTime = 0.0f;
    float m_elapsedTimeVelocity = 0.0f;
	float m_timeToAddVelocity = 1.0f;
    float m_difficultyMultiplier = 1.0f;
    int m_maxDifficulty = 10;

    sr::Text* m_timerText;
    sr::Text* m_scoreText;
	sr::Text* m_velocityText;
	sr::Text* m_jetPackText;
	sr::Text* m_difficultyText;

	sr::Text* m_powerUpText;
	sr::Text* m_speedBoostText;
	sr::Text* m_jumpBoostText;
	sr::Text* m_flyingBoostText;
	sr::Text* m_scoreBoostText;
};

