#include "GameManager.h"

int main() {
    GameManager* gameManager = GameManager::GetInstance();
    gameManager->Run();

    
    return 0;
}