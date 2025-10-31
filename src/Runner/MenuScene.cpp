#include "pch.h"
#include "MenuScene.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "Controller.h"

MenuScene::MenuScene() {

	m_titleText = new sr::Text(L"Welcome to ORC RUNNER !!!");
	m_titleText->SetPosition({ 900.f, 480.f });

	m_startText = new sr::Text(L"Press A to start !");
	m_startText->SetPosition({ 900.f, 520.f });

	m_settingsText = new sr::Text(L"Press S to open the settings !");
	m_settingsText->SetPosition({ 900.f, 560.f });

	m_exitText = new sr::Text(L"Press Escape to close the game !");
	m_exitText->SetPosition({ 900.f, 600.f });
}

MenuScene::~MenuScene() {
	delete m_titleText;
	delete m_startText;
	delete m_settingsText;
	delete m_exitText;
	m_titleText = nullptr;
	m_startText = nullptr;
	m_settingsText = nullptr;
	m_exitText = nullptr;
}

void MenuScene::Render() {
	Scene::Render();
	sr::Window& window = GameManager::GetWindow();
	window.DrawText(*m_titleText);
	window.DrawText(*m_startText);
	window.DrawText(*m_settingsText);
	window.DrawText(*m_exitText);
}

void MenuScene::Update(float deltaTime) 
{
	Scene::Update(deltaTime);

	SceneManager* sceneManager = SceneManager::GetInstance();
	//Controller& controller = GameManager::GetInstance()->GetController();

	//if (controller.GetFlag(ControllerFlags::GO_TO_GAME))
	//{

	//}
	//else if (controller.GetFlag(ControllerFlags::GO_TO_SETTINGS))
	//{

	//}
	//else if (controller.GetFlag(ControllerFlags::CLOSE_GAME))
	//{
	//}
}

TagScene MenuScene::GetTag() const {
	return TagScene::MENU; 
}