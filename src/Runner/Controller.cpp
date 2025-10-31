#include "Controller.h"
#include "Character.h"
#include "GameManager.h"
#include "Shoot.h"
#include <iostream>
#include <algorithm>

bool Controller::GetFlag(ControllerFlags flag)
{
    auto it = std::find_if(m_flags.begin(), m_flags.end(),
        [flag](ControllerFlags f) {
            return f == flag;
        });
    return it != m_flags.end();
}

void Controller::Update()
{
    ResetFlags();
    UpdateFlags();
}

void Controller::ResetFlags()
{
    m_flags.clear();
}

void Controller::UpdateFlags()
{
	SceneManager* sceneManager = SceneManager::GetInstance();

    if (IsKeyPressed(sr::Keyboard::Q))
    {
        //m_flags.push_back(ControllerFlags::GO_TO_MENU);

        if (sceneManager->IsSceneActiveForUpdate(TagScene::PAUSE))
        {
            sceneManager->AddScene(TagScene::MENU);
            sceneManager->RemoveScene(TagScene::GAMEPLAY);
            sceneManager->RemoveScene(TagScene::PAUSE);
        }

        if (sceneManager->IsSceneActiveForUpdate(TagScene::GAMEOVER))
        {
            sceneManager->AddScene(TagScene::MENU);
            sceneManager->RemoveScene(TagScene::GAMEOVER);
            sceneManager->RemoveScene(TagScene::GAMEPLAY);
        }
    }

    if (IsKeyPressed(sr::Keyboard::S))
    {
        //m_flags.push_back(ControllerFlags::GO_TO_SETTINGS);

        if (sceneManager->IsSceneActiveForUpdate(TagScene::PAUSE))
        {
            sceneManager->AddScene(TagScene::SETTINGS);
            sceneManager->RemoveScene(TagScene::PAUSE);
        }

        if(sceneManager->IsSceneActiveForUpdate(TagScene::MENU))
        {
            sceneManager->AddScene(TagScene::SETTINGS);
            sceneManager->RemoveScene(TagScene::MENU);
		}
    }

    if (IsKeyPressed(sr::Keyboard::SPACE))
    {
        //m_flags.push_back(ControllerFlags::CLOSE_GAME);

        if (sceneManager->IsSceneActiveForUpdate(TagScene::PAUSE) ||
            sceneManager->IsSceneActiveForUpdate(TagScene::MENU) ||
            sceneManager->IsSceneActiveForUpdate(TagScene::GAMEOVER))
        {
            GameManager::GetInstance()->Close();
        }
    }

    if (IsKeyPressed(sr::Keyboard::R))
    {
        //m_flags.push_back(ControllerFlags::RESTART_GAME);

        if (sceneManager->IsSceneActiveForUpdate(TagScene::PAUSE))
        {
            sceneManager->AddScene(TagScene::GAMEPLAY);
            sceneManager->RemoveScene(TagScene::PAUSE);
            sceneManager->ResetGamePlayScene();
        }

        if (sceneManager->IsSceneActiveForUpdate(TagScene::GAMEOVER))
        {
            sceneManager->AddScene(TagScene::GAMEPLAY);
            sceneManager->RemoveScene(TagScene::GAMEOVER);
            sceneManager->ResetGamePlayScene();
        }
    }

    if (IsKeyPressed(sr::Keyboard::C))
    {
        //m_flags.push_back(ControllerFlags::RESUME_GAME);

        if (sceneManager->IsSceneActiveForUpdate(TagScene::PAUSE))
        {
            sceneManager->AddScene(TagScene::GAMEPLAY, false, true);
            sceneManager->RemoveScene(TagScene::PAUSE);
        }
    }

    if (IsKeyPressed(sr::Keyboard::A))
    {
        //m_flags.push_back(ControllerFlags::GO_TO_GAME);

        if (sceneManager->IsSceneActiveForUpdate(TagScene::MENU))
        {
            sceneManager->AddScene(TagScene::GAMEPLAY);
            sceneManager->RemoveScene(TagScene::MENU);
            sceneManager->ResetGamePlayScene();
        }
    }

    if (IsKeyPressed(sr::Keyboard::P))
    {
        //m_flags.push_back(ControllerFlags::GO_TO_PAUSE);
        if (sceneManager->IsSceneActiveForUpdate(TagScene::GAMEPLAY))
        {
            sceneManager->AddScene(TagScene::PAUSE);
            sceneManager->RemoveScene(TagScene::GAMEPLAY, false, true);
        }
    }

    if (IsKeyPressed(sr::Keyboard::B))
    {
        //m_flags.push_back(ControllerFlags::GO_BACK);
        if (sceneManager->IsSceneActiveForUpdate(TagScene::SETTINGS))
        {
            SceneManager* sceneManager = SceneManager::GetInstance();
            sceneManager->AddScene(sceneManager->GetLastRemovedScene());
            sceneManager->RemoveScene(TagScene::SETTINGS);
        }
    }
}

void Controller::ProcessInput(Character* character, float deltaTime)
{
    if (!character) return;

    if (IsKeyPressed(sr::Keyboard::D))
    {
        character->MoveRight(deltaTime);
    }
    else if (IsKeyPressed(sr::Keyboard::Q))
    {
		character->MoveLeft(deltaTime);
    }
    else
    {
        character->m_velocity.x = 0.0f;
        character->LookAhead(deltaTime);
    }

    if (IsKeyPressed(sr::Keyboard::Z))
    {
		character->JetPackUp(deltaTime);
    }
    else if (IsKeyPressed(sr::Keyboard::S))
    {
		character->JetPackDown(deltaTime);
    }

    if (IsKeyPressed(sr::Keyboard::SPACE) && character->m_isGrounded)
    {
		character->Jump();
    }

    if (IsMouseButtonPressed(sr::Mouse::RIGHT))
    {
        if (character->m_camera)
            character->m_camera->MoveCameraToCursor(deltaTime, character);
    }
    else
    {
        if (character->m_camera)
            character->m_camera->Reset();
    }

    if (IsMouseButtonPressed(sr::Mouse::LEFT))
    {
		character->ShootForward();
    }

    character->m_velocity.z = character->m_speed + character->m_acceleration;
}