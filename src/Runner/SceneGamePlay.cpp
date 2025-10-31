#include "SceneGamePlay.h"
#include "Mesh.h"
#include "Character.h"
#include "GCSR.h"
#include "Entity.h"
#include "EntityManager.h"
#include "TileManager.h"
#include "GameManager.h"
#include "Controller.h"

SceneGamePlay::SceneGamePlay() : Scene()
{
	GameManager* gameManager = GameManager::GetInstance();
	float width = gameManager->GetWindow().GetWidth();
	float height = gameManager->GetWindow().GetHeight();

    m_scoreText = new sr::Text(L"Score : " + std::to_wstring(m_score));
    m_scoreText->SetPosition({ 20.f, 20.f });

    m_velocityText = new sr::Text(L"velocity : " + std::to_wstring((int)m_velocity));
    m_velocityText->SetPosition({ 20.f, 60.f });

    m_timerText = new sr::Text(L"Time : " + std::to_wstring(m_elapsedTime));
    m_timerText->SetPosition({ 20.f, 100.f });

    m_difficultyText = new sr::Text(L"Difficulty :");
    m_difficultyText->SetPosition({ 20, width * 0.5f});

    int initialJet = 0;
	bool power = false;
    if (m_playerCharacter)
    {
        initialJet = m_playerCharacter->GetJetPackFuel();
		power = m_playerCharacter->GetPowerUpIsActive();
    }
    m_jetPackText = new sr::Text(std::wstring(L"JetPack : ") + std::to_wstring(initialJet) + L" %");
    m_jetPackText->SetPosition({ 20.f, 140.f });

    m_powerUpText = new sr::Text(std::wstring(L"Power Up : "));

    m_speedBoostText = new sr::Text(std::wstring(L"SpeedBoost : ") + std::to_wstring(power));
    m_speedBoostText->SetPosition({ 20.f, 180.f });

	m_jumpBoostText = new sr::Text(std::wstring(L"JumpBoost : ") + std::to_wstring(power));
	m_jumpBoostText->SetPosition({ 20.f, 220.f });

	m_flyingBoostText = new sr::Text(std::wstring(L"FlyingBoost : ") + std::to_wstring(power));
	m_flyingBoostText->SetPosition({ 20.f, 260.f });

	m_scoreBoostText = new sr::Text(std::wstring(L"ScoreBoost : ") + std::to_wstring(power));
	m_scoreBoostText->SetPosition({ 20.f, 300.f });

	AddTextInArray(m_difficultyText);
	AddTextInArray(m_scoreText);
	AddTextInArray(m_velocityText);
	AddTextInArray(m_timerText);
	AddTextInArray(m_jetPackText);
}

SceneGamePlay::~SceneGamePlay() {
	Texts.clear();
	delete m_speedBoostText;
	m_speedBoostText = nullptr;
	delete m_jumpBoostText;
	m_jumpBoostText = nullptr;
	delete m_flyingBoostText;
	m_flyingBoostText = nullptr;
	delete m_scoreBoostText;
	m_scoreBoostText = nullptr;
}

void SceneGamePlay::Init()
{
	Scene::Init();

    Mesh* playerMesh = new Mesh();

    m_playerCharacter = new Character(playerMesh, 10, m_entityManager, SceneManager::GetCamera());

    m_tileManager = new TileManager(this, m_entityManager);
    m_tileManager->InitTileManager();
}

void SceneGamePlay::Update(float deltaTime) 
{
	UpdateTimer(deltaTime);
    SceneManager* sceneManager = SceneManager::GetInstance();

    Controller& controller = GameManager::GetInstance()->GetController();
    controller.ProcessInput(m_playerCharacter, deltaTime);

	m_elapsedTimeVelocity += deltaTime;

    if (m_difficultyMultiplier > m_maxDifficulty)
        m_difficultyMultiplier = m_maxDifficulty;
    else
        m_difficultyMultiplier += deltaTime * 0.02f;

    

	//velocity increase over time
    if (m_elapsedTimeVelocity > m_timeToAddVelocity && m_playerCharacter->GetAcceleration() < m_playerCharacter->GetMaxAcceleration()) {
        AddVelocity(0.2f);
        m_elapsedTimeVelocity = 0;
    }

    if (GetDifficultyMultiplier() <= 3) {
        m_difficultyText->SetText(L"Difficulty : EASY");
		m_difficultyText->SetColor(gce::Color::Green);
    }
    else if (GetDifficultyMultiplier() <= 5) {
        m_difficultyText->SetText(L"Difficulty : MEDIUM");
        m_difficultyText->SetColor(gce::Color::Yellow);
    }
    else {
        m_difficultyText->SetText(L"Difficulty : HARD");
        m_difficultyText->SetColor(gce::Color::Red);
	}

    if (m_jetPackText && m_playerCharacter)
    {
        if (m_playerCharacter->GetJetPackFuel() <= 25.0f)
            m_jetPackText->SetColor(gce::Color::Red);
        else if (m_playerCharacter->GetJetPackFuel() <= 50.0f)
            m_jetPackText->SetColor(gce::Color::Yellow);
        else if (m_playerCharacter->GetJetPackFuel() <= 100.0f)
			m_jetPackText->SetColor(gce::Color::White);
        else
            m_jetPackText->SetColor(gce::Color::Cyan);

        m_jetPackText->SetText(std::wstring(L"JetPack : ") + std::to_wstring((int)m_playerCharacter->GetJetPackFuel()) + L" %");
    }

    if (m_velocityText && m_playerCharacter)
    {
        if(m_playerCharacter->GetAcceleration() >= m_playerCharacter->GetMaxAcceleration())
            m_velocityText->SetColor(gce::Color::Blue);
        else
			m_velocityText->SetColor(gce::Color::White);

        m_velocityText->SetText(L"velocity : " + std::to_wstring((int)m_playerCharacter->GetAcceleration()));

        switch (m_playerCharacter->GetPowerUpIsActive()) {
        case true:
            m_powerUpText->SetColor(gce::Color::Green);
            m_powerUpText->SetText(L"Power Up : ACTIVE");
            break;
        case false:
            m_powerUpText->SetColor(gce::Color::Red);
            m_powerUpText->SetText(L"Power Up : INACTIVE");
            break;
        }
    }

    if (m_playerCharacter->GetSpeedBoostIsActive()) {
		m_speedBoostText->SetColor(gce::Color::Green);
        m_speedBoostText->SetText(std::wstring(L"SpeedBoost : ACTIVE"));
    }

    if (m_playerCharacter->GetJumpBoostIsActive()) {
        m_jumpBoostText->SetColor(gce::Color::Green);
		m_jumpBoostText->SetText(std::wstring(L"JumpBoost : ACTIVE"));
    }

    if (m_playerCharacter->GetFlyingBoostIsActive()) {
		m_flyingBoostText->SetColor(gce::Color::Green);
		m_flyingBoostText->SetText(std::wstring(L"FlyingBoost : ACTIVE"));
    }

    if (m_playerCharacter->GetScoreBoostIsActive()){
		m_scoreBoostText->SetColor(gce::Color::Green);
		m_scoreBoostText->SetText(std::wstring(L"ScoreBoost : ACTIVE"));
	}

    m_entityManager->Collide();
    m_tileManager->regenerateTiles();

    Scene::Update(deltaTime);

}


void SceneGamePlay::Render() {
    Scene::Render();
    sr::Window& window = GameManager::GetWindow();
    for (auto& text : Texts) 
        window.DrawText(*text);

    if (m_playerCharacter->GetSpeedBoostIsActive())
		window.DrawText(*m_speedBoostText);

	if (m_playerCharacter->GetJumpBoostIsActive())
		window.DrawText(*m_jumpBoostText);

	if (m_playerCharacter->GetFlyingBoostIsActive())
		window.DrawText(*m_flyingBoostText);

	if (m_playerCharacter->GetScoreBoostIsActive())
		window.DrawText(*m_scoreBoostText);
    
}

void SceneGamePlay::AddScore(int scoreToAdd) {
    int multiplier = 1;
    if (m_playerCharacter) {
        multiplier = m_playerCharacter->GetPowerUpScoreMultiplier();
    }
    m_score += scoreToAdd * multiplier;
    m_scoreText->SetText(L"Score : " + std::to_wstring(m_score));
}
void SceneGamePlay::AddVelocity(float newVelocity) {
    m_velocity += newVelocity;
    if (m_playerCharacter) {
        if(m_playerCharacter->GetAcceleration() == 0)
            m_playerCharacter->SetAcceleration(m_velocity);
		else
        m_playerCharacter->AddAcceleration(newVelocity);

    }

    if (m_velocityText && m_playerCharacter)
        m_velocityText->SetText(L"velocity : " + std::to_wstring((int)m_playerCharacter->GetAcceleration()));
}

void SceneGamePlay::UpdateTimer(float deltaTime) {
    m_elapsedTime += deltaTime;
    m_timerText->SetText(L"Time : " + std::to_wstring((int)m_elapsedTime));
}

void SceneGamePlay::Reset() {

    delete m_tileManager;
    m_tileManager = nullptr;

    delete m_entityManager;
    m_entityManager = nullptr;

    m_playerCharacter = nullptr;

	m_difficultyMultiplier = 1.0f;

    m_score = 0;
    m_velocity = 0.f;
    m_maxSpeed = 50.0;
    m_elapsedTime = 0.0f;

    m_timerText->SetText(L"Time : " + std::to_wstring((int)m_elapsedTime));
    m_velocityText->SetText(L"velocity : " + std::to_wstring((int)m_velocity));
    m_scoreText->SetText(L"Score : " + std::to_wstring(m_score));
	m_jetPackText->SetText(std::wstring(L"JetPack : ") + std::to_wstring(100) + L" %");

    Init();
}