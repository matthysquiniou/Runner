#include "pch.h"
#include "PauseScene.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "Controller.h"

PauseScene::PauseScene() {

	m_pausedText = new sr::Text(L"PAUSED :");
	m_pausedText->SetPosition({ 900.f, 480.f });

	m_restartText = new sr::Text(L"Press R to restart !");
	m_restartText->SetPosition({ 900.f, 520.f });

	m_resumeText = new sr::Text(L"Press C to resume !");
	m_resumeText->SetPosition({ 900.f, 560.f });

	m_settingsText = new sr::Text(L"Press S to open the settings !");
	m_settingsText->SetPosition({ 900.f, 600.f });

	m_quitMenuText = new sr::Text(L"Press Q to go quit to the menu !");
	m_quitMenuText->SetPosition({ 900.f, 640.f });

	m_quitGameText = new sr::Text(L"Press Escape to go quit the game !");
	m_quitGameText->SetPosition({ 900.f, 680.f });
}

PauseScene::~PauseScene() {
	delete m_pausedText;
	delete m_restartText;
	delete m_resumeText;
	delete m_settingsText;
	delete m_quitMenuText;
	delete m_quitGameText;
	m_pausedText = nullptr;
	m_restartText = nullptr;
	m_resumeText = nullptr;
	m_settingsText = nullptr;
	m_quitMenuText = nullptr;
	m_quitGameText = nullptr;
}

void PauseScene::Render() {
	Scene::Render();
	sr::Window& window = GameManager::GetWindow();
	window.DrawText(*m_pausedText);
	window.DrawText(*m_restartText);
	window.DrawText(*m_resumeText);
	window.DrawText(*m_settingsText);
	window.DrawText(*m_quitMenuText);
	window.DrawText(*m_quitGameText);
}

void PauseScene::Update(float deltaTime) {
	Scene::Update(deltaTime);
	SceneManager* sceneManager = SceneManager::GetInstance();
	//Controller& controller = GameManager::GetInstance()->GetController();


	//if (controller.GetFlag(ControllerFlags::RESTART_GAME))
	//{

	//}
	//else if (controller.GetFlag(ControllerFlags::GO_TO_SETTINGS))
	//{

	//}
	//else if (controller.GetFlag(ControllerFlags::RESUME_GAME))
	//{

	//}
	//else if (controller.GetFlag(ControllerFlags::GO_TO_MENU))
	//{

	//}
	//else if (controller.GetFlag(ControllerFlags::CLOSE_GAME))
	//{
	//}
}

TagScene PauseScene::GetTag() const {
	return TagScene::PAUSE;
}