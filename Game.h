#pragma once

#include "SDL_Image/include/SDL_image.h"
#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )
#pragma comment(lib, "SDL_Image/libx86/SDL2_image.lib")

#include "Entity.h"

#define WINDOW_WIDTH	1280
#define WINDOW_HEIGHT	960
#define MAX_KEYS		256
#define MAX_SHOTS1		3
#define MAX_SHOTS2		3

class Game
{
public:
	Game();
	~Game();

	bool Init();
	void Release();
	
	bool Input();
	bool Update();
	void Draw();

private:
	SDL_Window *Window;
	SDL_Renderer *Renderer;

	Entity Player, Shotstop[MAX_SHOTS1], Shotsbot[MAX_SHOTS1], Shotsleft[MAX_SHOTS1], Shotsright[MAX_SHOTS1], Player2, Shotstop2[MAX_SHOTS2], Shotsbot2[MAX_SHOTS1], Shotsleft2[MAX_SHOTS2], Shotsright2[MAX_SHOTS2];
	Entity P1hp1, P1hp2, P1hp3, P2hp1, P2hp2, P2hp3;
	int idx_shot;
	int idx_shot2;
	int p1hp, p2hp;

	enum KEY_STATE { KEY_IDLE, KEY_DOWN, KEY_REPEAT, KEY_UP	};
	KEY_STATE keys[MAX_KEYS]; 
};
