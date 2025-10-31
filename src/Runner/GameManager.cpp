#include "GameManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "SceneGamePlay.h"
#include "Controller.h"

GameManager* GameManager::m_instance = nullptr;
sr::Window* GameManager::m_window = nullptr;
Controller* GameManager::m_controller = nullptr;

Pool<sr::Geometry>* GameManager::m_geometryPool = new Pool<sr::Geometry>();
Pool<sr::Geometry>* GameManager::m_orcPool = new Pool<sr::Geometry>();

GameManager* GameManager::GetInstance()
{
    if (m_instance == nullptr)
    {
        m_instance = new GameManager();
    }
    return m_instance;
}

GameManager::GameManager() {
    m_window = new sr::Window(L"Test", 1920, 1080, sr::Window::FLAG_ENABLE_SHADOWPASS | sr::Window::FLAG_MSAA_X4);
    m_controller = new Controller();
}

GameManager::~GameManager()
{
    delete m_window;
    m_window = nullptr;
    delete m_geometryPool;
    m_geometryPool = nullptr;
}

void GameManager::Run()
{

    m_sceneManager = SceneManager::GetInstance();
    if (m_sceneManager) {
        m_sceneManager->Init();
    }

    Loop();
}

void GameManager::Loop()
{
    if (!m_window) return;

    while (m_window->IsOpen())
    {
        m_controller->Update();
        if (m_sceneManager) {
            float dt = m_window->GetDeltaTime();
            m_sceneManager->Update(dt);
            m_sceneManager->Render();
			m_sceneManager->EmptyEntityBuffer();
        }

        m_window->End();
        m_window->Display();
        if (m_close) break;
    }
    delete m_instance;
}

void GameManager::Close() {
    m_close = true;
}