#pragma once

#include "SDL_Image/include/SDL_image.h"
#include "SDL/include/SDL.h"
#include "SDL2_mixer-2.0.4/include/SDL_mixer.h"

#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )
#pragma comment(lib, "SDL_Image/libx86/SDL2_image.lib")
#pragma comment( lib, "SDL2_mixer-2.0.4/lib/x86/SDL2_mixer.lib")
#pragma comment( lib, "SDL_TTF/lib/x86/SDL2_ttf.lib")
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
	bool LoadImages();
	void Release();
	
	bool Input();
	bool Update();
	void Draw();

private:
	SDL_Window *Window;
	SDL_Renderer *Renderer;

	Entity Player, Shotstop[MAX_SHOTS1], Shotsbot[MAX_SHOTS1], Shotsleft[MAX_SHOTS1], Shotsright[MAX_SHOTS1], Player2, Shotstop2[MAX_SHOTS2], Shotsbot2[MAX_SHOTS1], Shotsleft2[MAX_SHOTS2], Shotsright2[MAX_SHOTS2];
	Entity P1hp1, P1hp2, P1hp3, P2hp1, P2hp2, P2hp3;
	SDL_Texture* player1, * player2, * heart, * emptyheart;

	Mix_Music* music = NULL;

	bool hit1 = true;
	bool hit2 = true; 
	bool hit3 = true;
	bool hit4 = true;
	bool hit5 = true;
	bool hit6 = true;

	int idx_shot;
	int idx_shot2;
	int p1hp, p2hp;

	int counter1 = 0;
	int counter2 = 0;

	//Winscreen titles
	const char *titles[2] = { "Player 1 Wins!","Player 2 Wins!" };

	enum KEY_STATE { KEY_IDLE, KEY_DOWN, KEY_REPEAT, KEY_UP	};
	KEY_STATE keys[MAX_KEYS]; 
};
