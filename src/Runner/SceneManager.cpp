#include "pch.h"
#include "SceneManager.h"
#include <SceneGamePlay.h>
#include <GameOverScene.h>
#include <MenuScene.h>
#include <SettingsScene.h>
#include <PauseScene.h>
#include <algorithm>
#include "GameManager.h"
#include "Camera.h"

Camera* SceneManager::m_camera = nullptr;

SceneManager* SceneManager::m_instance = nullptr;

SceneManager* SceneManager::GetInstance()
{
    if (m_instance == nullptr)
        m_instance = new SceneManager();
    return m_instance;
}  

Camera* SceneManager::GetCamera()
{
    return m_camera;
}

SceneManager::SceneManager() 
{
    m_camera = new Camera(
        { 0.f, 0.f, 0.f },
        { 0.0f, 0.0f, 0.0f },
        gce::PI / 2.0f,
        500.0f,
        0.001f,
        { -1.f, 6.5f, -5.f }
    );
}

TagScene SceneManager::GetLastRemovedScene() const {
    return m_lastRemovedScene;
}


void SceneManager::AddScene(TagScene tagScene, bool render, bool update) {
    if (render)
    {
        m_activesRenderScenes.insert(tagScene);
    }

    if (update)
    {
        m_activesUpdateScenes.insert(tagScene);
    }
}

void SceneManager::AddScene(TagScene tagScene) {
    m_activesRenderScenes.insert(tagScene);
    m_activesUpdateScenes.insert(tagScene);
}

bool SceneManager::IsSceneActiveForRender(TagScene tagScene) const
{
    if (m_activesRenderScenes.find(tagScene) != m_activesRenderScenes.end())
    {
        return true;
    }
    return false;
}

bool SceneManager::IsSceneActiveForUpdate(TagScene tagScene) const
{
    if (m_activesUpdateScenes.find(tagScene) != m_activesUpdateScenes.end())
    {
        return true;
	}
    return false;
}

void SceneManager::RemoveScene(TagScene tagScene, bool render, bool update) {
    m_lastRemovedScene = tagScene;
    if (render)
    {
        m_activesRenderScenes.erase(tagScene);
    }
    if (update)
    {
        m_activesUpdateScenes.erase(tagScene);
    }
}

void SceneManager::RemoveScene(TagScene tagScene) {
    m_lastRemovedScene = tagScene;
    m_activesRenderScenes.erase(tagScene);
    m_activesUpdateScenes.erase(tagScene);
}

Scene* SceneManager::GetScene(TagScene tagScene) const {
    auto it = std::find_if(m_scenes.begin(), m_scenes.end(),
        [tagScene](Scene* scene) {
            return scene->GetTag() == tagScene;
        });
    return it != m_scenes.end() ? *it : nullptr;
}

void SceneManager::ResetGamePlayScene() {
    for (Scene* scene : m_scenes) {
        if (scene->GetTag() == TagScene::GAMEPLAY) {
            static_cast<SceneGamePlay*>(scene)->Reset();
        }
    }
}


void SceneManager::Init()
{
    SceneGamePlay* sceneGamePlay = new SceneGamePlay();
    m_scenes.push_back(sceneGamePlay);

    GameOverScene* gameOverScene = new GameOverScene();
    m_scenes.push_back(gameOverScene);

    MenuScene* menuScene = new MenuScene();
    m_scenes.push_back(menuScene);

    PauseScene* pauseScene = new PauseScene();
    m_scenes.push_back(pauseScene);

    SettingsScene* settingsScene = new SettingsScene();
    m_scenes.push_back(settingsScene);

    AddScene(TagScene::MENU);

    for (Scene* scene : m_scenes) {
        if (scene) {
            scene->Init();
        }
    }
}

void SceneManager::Update(float deltaTime)
{
    m_timeElapsed += deltaTime;
    auto activesUpdateScene = m_activesUpdateScenes;
    for (Scene* scene : m_scenes) {
        if (activesUpdateScene.contains(scene->GetTag()))
            scene->Update(deltaTime);
        
    }
}

void SceneManager::Render() {
    sr::Window& window = GameManager::GetWindow();
    window.Begin(m_camera->GetCamera());  
    auto activesRenderScene = m_activesRenderScenes;
    for (Scene* scene : m_scenes) {
        if (activesRenderScene.contains(scene->GetTag()))
            scene->Render();
    }
}


void SceneManager::EmptyEntityBuffer()
{
    for (Scene* scene : m_scenes)
		scene->EmptyEntityBuffer();
}

void SceneManager::SetTimeElapsed(float time)
{
    m_timeElapsed = time;
}

float SceneManager::GetTimeElapsed()
{
    return m_timeElapsed;
}

SceneManager::~SceneManager() {
    for (Scene* scene : m_scenes)
        delete scene;

    delete m_camera;
    m_camera = nullptr;
}