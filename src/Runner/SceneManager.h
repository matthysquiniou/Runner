#pragma once

#include "Scene.h"
#include <vector>
#include <set>

class Camera;
class SceneManager {
public:

    SceneManager();

    ~SceneManager();

    static SceneManager* GetInstance();
    static Camera* GetCamera();

	void Init();
	void Update(float deltaTime);
	void Render();

    void ResetGamePlayScene();

	void EmptyEntityBuffer();

    void SetTimeElapsed(float time);
    float GetTimeElapsed();

    Scene* GetScene(TagScene tagScene) const;

    void AddScene(TagScene tagScene, bool render, bool update);
    void AddScene(TagScene tagScene);

    bool IsSceneActiveForRender(TagScene tagScene) const;
    bool IsSceneActiveForUpdate(TagScene tagScene) const;

    void RemoveScene(TagScene tagScene, bool render, bool update);
    void RemoveScene(TagScene tagScene);
    TagScene GetLastRemovedScene() const;

private:
    std::vector<Scene*> m_scenes;
    std::set<TagScene> m_activesRenderScenes;
    std::set<TagScene> m_activesUpdateScenes;
    TagScene m_lastRemovedScene;
    float m_timeElapsed = 0;


    static SceneManager* m_instance;
    static Camera* m_camera;
};
