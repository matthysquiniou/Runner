#pragma once

#include "GCSR.h"
#include "SceneManager.h"
#include "Pool.h"

class Camera;

class SceneGamePlay;

class Controller;

class GameManager
{
public:

    static GameManager* GetInstance();

    void Run();
    void Loop();

    GameManager();
    ~GameManager();

    inline static sr::Window& GetWindow() { return *m_window; }
    inline static Controller& GetController() { return *m_controller; }
    inline static Pool<sr::Geometry>& GetGeometryPool() { return *m_geometryPool; }
    inline static Pool<sr::Geometry>& GetOrcPool() { return *m_orcPool; }
    void Close();

private:

    bool m_close = false;

    SceneManager* m_sceneManager = nullptr;

    static Pool<sr::Geometry>* m_geometryPool;
    static Pool<sr::Geometry>* m_orcPool;
    static GameManager* m_instance;
    static sr::Window* m_window;
    static Controller* m_controller;

};