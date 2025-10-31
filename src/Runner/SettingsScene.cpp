#include "pch.h"
#include "SettingsScene.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "Controller.h"

SettingsScene::SettingsScene() {

	m_settinsText = new sr::Text(L"SETTINGS :");
	m_settinsText->SetPosition({ 900.f, 480.f });

	m_TODOText = new sr::Text(L"TODO::THE SETTINGS AREN'T FINISHED YET !");
	m_TODOText->SetPosition({ 900.f, 520.f });

	m_goBackText = new sr::Text(L"Press B to go back !");
	m_goBackText->SetPosition({ 900.f, 560.f });
}

SettingsScene::~SettingsScene() {
	delete m_settinsText;
	delete m_TODOText;
	delete m_goBackText;
	m_settinsText = nullptr;
	m_TODOText = nullptr;
	m_goBackText = nullptr;
}

void SettingsScene::Render() {
	Scene::Render();
	sr::Window& window = GameManager::GetWindow();
	window.DrawText(*m_settinsText);
	window.DrawText(*m_TODOText);
	window.DrawText(*m_goBackText);
}

void SettingsScene::Update(float deltaTime) {
	Scene::Update(deltaTime);
	//Controller& controller = GameManager::GetInstance()->GetController();

	//if (controller.GetFlag(ControllerFlags::GO_BACK))
	//{

	//}
}

TagScene SettingsScene::GetTag() const {
	return TagScene::SETTINGS;
}