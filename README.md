# 3D Runner Project – Learning the Fundamentals of 3D Gameplay

## Installation and Solution Generation

1. Go to the `bin/` folder.  
2. Run `make.bat`.  
3. The script will generate an `ide/` folder containing `[SOLUTION_NAME].sln`.  
4. Open the Visual Studio solution.  

School project developed using a **simplified version of GCE (Gaming Campus Game Engine)**.  
Main objective: **continue improving 3D development skills** with a strong focus on the **3Cs**:

- **Camera**
- **Controller**
- **Character**

The game is a **3D runner**, centered on character movement, camera management, and real-time interactions.

---

### 1. Character
- Lateral movement management  
- Jump and grounded states  
- Controlled vertical movement (jetpack)  
- Shooting system  
- Velocity handling  

### 2. Controller
- Keyboard and mouse input handling  
- Direct link between inputs and character actions  
- Logical separation between:
  - **gameplay controls**
  - **menu / scene controls**

### 3. Camera
- Camera attached to the character  
- Dynamic movement toward the cursor  
- Automatic return to default position  

---

## Game Concept

The player controls a character in a **3D runner-style** environment.  
The objective is to progress while avoiding obstacles using:

- lateral movement  
- jumping  
- jetpack movement  
- shooting  

The gameplay strongly relies on control responsiveness and camera readability.

---

## 🎮 Controls – Gameplay (In Game)

| Key / Mouse | Action |
|-------------|--------|
| **Q** | Move left |
| **D** | Move right |
| *(no lateral key pressed)* | Character looks forward |
| **SPACE** | Jump (only when grounded) |
| **Z** | Jetpack up |
| **S** | Jetpack down |
| **Left Click** | Shoot forward |
| **Right Click (hold)** | Move camera toward cursor |
| *(release right click)* | Camera reset |

---

## Controls – Menus & Scene Management

The game uses a **SceneManager** to handle states:

- MENU  
- GAMEPLAY  
- PAUSE  
- SETTINGS  
- GAMEOVER  

| Key | Function |
|-----|----------|
| **A** | Start the game from the menu |
| **P** | Pause the game (from gameplay) |
| **C** | Resume the game (from pause) |
| **R** | Restart the game (from pause or game over) |
| **S** | Go to settings (from menu or pause) |
| **B** | Return to previous scene (from settings) |
| **Q** | Return to menu (from pause or game over) |
| **SPACE** | Quit the game (from menu, pause, or game over) |

---

Project focused on **technical learning**, not a final production.
