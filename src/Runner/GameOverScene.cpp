#include "pch.h"
#include "GameOverScene.h"
#include "GameManager.h"
#include "SceneGamePlay.h"
#include "Controller.h"

GameOverScene::GameOverScene() {
	m_gameOverText = new sr::Text(L"Game Over :(");
	m_gameOverText->SetPosition({ 900.f, 480.f });

	m_restartText = new sr::Text(L"Press R to start !");
	m_restartText->SetPosition({ 900.f, 520.f });

	m_scoreText = new sr::Text(L"");
	m_scoreText->SetPosition({ 900.f, 560.f });

	m_quitMenuText = new sr::Text(L"Press Q to quit to the menu !");
	m_quitMenuText->SetPosition({ 900.f, 600.f });

	m_quitGameText = new sr::Text(L"Press Escape to close the game !");
	m_quitGameText->SetPosition({ 900.f, 640.f });
}

GameOverScene::~GameOverScene() {
	delete m_gameOverText;
	delete m_restartText;
	delete m_quitMenuText;
	delete m_scoreText;
	delete m_quitGameText;
	m_gameOverText = nullptr;
	m_restartText = nullptr;
	m_quitMenuText = nullptr;
	m_quitGameText = nullptr;
	m_scoreText = nullptr;
}

void GameOverScene::Render() {
	Scene::Render();
	sr::Window& window = GameManager::GetWindow();
	window.DrawText(*m_gameOverText);
	window.DrawText(*m_restartText);
	window.DrawText(*m_scoreText);
	window.DrawText(*m_quitGameText);
	window.DrawText(*m_quitGameText);
}

void GameOverScene::Update(float deltaTime) {
	Scene::Update(deltaTime);
	SceneManager* sceneManager = SceneManager::GetInstance();
	SceneGamePlay* gameplayScene = static_cast<SceneGamePlay*>(sceneManager->GetScene(TagScene::GAMEPLAY));
	m_scoreText->SetText(L"Score : " + std::to_wstring(gameplayScene->GetScore()));
	//Controller& controller = GameManager::GetInstance()->GetController();

	//if (controller.GetFlag(ControllerFlags::RESTART_GAME))
	//{

	//}
	//else if (controller.GetFlag(ControllerFlags::GO_TO_MENU))
	//{

	//}
	//else if (controller.GetFlag(ControllerFlags::CLOSE_GAME))
	//{

	//}
}

TagScene GameOverScene::GetTag() const {
	return TagScene::GAMEOVER;
}