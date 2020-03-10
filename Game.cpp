#include "Game.h"
#include <math.h>
#include <stdio.h>

Game::Game() {}
Game::~Game(){}

bool Game::Init()
{
	//Initialize SDL with all subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	//Create our window: title, x, y, w, h, flags
	Window = SDL_CreateWindow("Spaceship: arrow keys + space", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (Window == NULL)
	{
		SDL_Log("Unable to create window: %s", SDL_GetError());
		return false;
	}
	//Create a 2D rendering context for a window: window, device index, flags
	Renderer = SDL_CreateRenderer(Window, -1, 0);
	if (Renderer == NULL)
	{
		SDL_Log("Unable to create rendering context: %s", SDL_GetError());
		return false;
	}
	//Initialize keys array
	for (int i = 0; i < MAX_KEYS; ++i)
		keys[i] = KEY_IDLE;

	//Init variables
	Player.Init(375, 850, 104, 82, 5);
	Player2.Init(600, 15, 104, 82, 5);
	idx_shot = 0;
	idx_shot2 = 0;
	p1hp = 3;
	p2hp = 3;

	return true;
}
void Game::Release()
{
	//Clean up all SDL initialized subsystems
	SDL_Quit();
}
bool Game::Input()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)	return false;
	}

	SDL_PumpEvents();
	const Uint8* keyboard = SDL_GetKeyboardState(NULL);
	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keyboard[i])
			keys[i] = (keys[i] == KEY_IDLE) ? KEY_DOWN : KEY_REPEAT;
		else
			keys[i] = (keys[i] == KEY_REPEAT || keys[i] == KEY_DOWN) ? KEY_UP : KEY_IDLE;
	}

	return true;
}
bool Game::Update()
{
	//Read Input
	if (!Input())	return true;
	
	//Process Input Player 1
	int fx = 0, fy = 0;
	if (keys[SDL_SCANCODE_ESCAPE] == KEY_DOWN)	return true;
	if (keys[SDL_SCANCODE_A] == KEY_REPEAT && Player.GetX() >= 0)	fx = -1;
	if (keys[SDL_SCANCODE_D] == KEY_REPEAT && Player.GetX() < 1280-104)	fx = 1;
	if (keys[SDL_SCANCODE_W] == KEY_REPEAT && Player.GetY() >= 0)	fy = -1;
	if (keys[SDL_SCANCODE_S] == KEY_REPEAT && Player.GetY() < 960 - 82)	fy = 1;
	if (keys[SDL_SCANCODE_K] == KEY_DOWN)
	{
		int x, y, w, h;
		Player.GetRect(&x, &y, &w, &h);
		Shotsright[idx_shot].Init(x + w/2-13, y + h / 2 -20, 56, 20, 10);
		idx_shot++;
		idx_shot %= MAX_SHOTS1;
	}
	if (keys[SDL_SCANCODE_J] == KEY_DOWN)
	{
		int x, y, w, h;
		Player.GetRect(&x, &y, &w, &h);
		Shotsbot[idx_shot].Init(x + w/2 - 13, y + h/2 - 20, 20, 56, 10);
		idx_shot++;
		idx_shot %= MAX_SHOTS1;
	}
	if (keys[SDL_SCANCODE_H] == KEY_DOWN)
	{
		int x, y, w, h;
		Player.GetRect(&x, &y, &w, &h);
		Shotsleft[idx_shot].Init(x + w / 2 - 13, y + h / 2 - 20, 56, 20, 10);
		idx_shot++;
		idx_shot %= MAX_SHOTS1;
	}
	if (keys[SDL_SCANCODE_U] == KEY_DOWN)
	{
		int x, y, w, h;
		Player.GetRect(&x, &y, &w, &h);
		Shotstop[idx_shot].Init(x + w / 2 - 13, y + h / 2 -20, 20, 56, 10);
		idx_shot++;
		idx_shot %= MAX_SHOTS1;
	}

	//Process imput player 2
	int fx2 = 0, fy2 = 0;
	if (keys[SDL_SCANCODE_ESCAPE] == KEY_DOWN)	return true;
	if (keys[SDL_SCANCODE_LEFT] == KEY_REPEAT && Player2.GetX() >= 0)	fx2 = -1;
	if (keys[SDL_SCANCODE_RIGHT] == KEY_REPEAT && Player2.GetX() < 1280 - 104)	fx2 = 1;
	if (keys[SDL_SCANCODE_UP] == KEY_REPEAT && Player2.GetY() >= 0)	fy2 = -1;
	if (keys[SDL_SCANCODE_DOWN] == KEY_REPEAT && Player2.GetY() < 960 - 82)	fy2 = 1;
	if (keys[SDL_SCANCODE_KP_6] == KEY_DOWN)
	{
		int x, y, w, h;
		Player2.GetRect(&x, &y, &w, &h);
		Shotsright2[idx_shot2].Init(x + w / 2 - 13, y + h / 2 - 20, 56, 20, 10);
		idx_shot2++;
		idx_shot2 %= MAX_SHOTS2;
	}
	if (keys[SDL_SCANCODE_KP_5] == KEY_DOWN)
	{
		int x, y, w, h;
		Player2.GetRect(&x, &y, &w, &h);
		Shotsbot2[idx_shot2].Init(x + w / 2 - 13, y + h / 2 - 20, 20, 56, 10);
		idx_shot2++;
		idx_shot2 %= MAX_SHOTS2;
	}
	if (keys[SDL_SCANCODE_KP_4] == KEY_DOWN)
	{
		int x, y, w, h;
		Player2.GetRect(&x, &y, &w, &h);
		Shotsleft2[idx_shot2].Init(x + w / 2, y + h / 2 - 20, 56, 20, 10);
		idx_shot2++;
		idx_shot2 %= MAX_SHOTS2;
	}
	if (keys[SDL_SCANCODE_KP_8] == KEY_DOWN)
	{
		int x, y, w, h;
		Player2.GetRect(&x, &y, &w, &h);
		Shotstop2[idx_shot2].Init(x + w / 2 - 13, y + h / 2 - 20, 20, 56, 10);
		idx_shot2++;
		idx_shot2 %= MAX_SHOTS2;
	}

	//Logic
	//Player update
	
	Player.Move(fx, fy);
	Player2.Move(fx2, fy2);

	//Shots update
	//Player One shots update
	
	for (int i = 0; i < MAX_SHOTS1; ++i)
	{
		if (Shotstop[i].IsAlive())
		{
		Shotstop[i].Move(0, -1);
		if (Shotstop[i].GetX() > WINDOW_WIDTH)	Shotstop[i].ShutDown();
		if (Shotstop[i].GetX() <= Player2.GetX() + 104 && Shotstop[i].GetX() >= Player2.GetX() && Shotstop[i].GetY() <= Player2.GetY() + 82 && Shotstop[i].GetY() >= Player2.GetY())
		{
			//SDL_Quit();
			Shotstop[i].ShutDown();
			p2hp--;
		}
		}
	}
	for (int i = 0; i < MAX_SHOTS1; ++i)
	{
		if (Shotsbot[i].IsAlive())
		{
			Shotsbot[i].Move(0, 1);
			if (Shotsbot[i].GetX() > WINDOW_WIDTH)	Shotsbot[i].ShutDown();
			if (Shotsbot[i].GetX() <= Player2.GetX() + 104 && Shotsbot[i].GetX() >= Player2.GetX() && Shotsbot[i].GetY() <= Player2.GetY() + 82 && Shotsbot[i].GetY() >= Player2.GetY())
			{
				//SDL_Quit();
				Shotsbot[i].ShutDown();
				p2hp--;
			}

		}
	}
	for (int i = 0; i < MAX_SHOTS1; ++i)
	{
		if (Shotsleft[i].IsAlive())
		{
			Shotsleft[i].Move(-1, 0);
			if (Shotsleft[i].GetX() > WINDOW_WIDTH)	Shotsleft[i].ShutDown();
			if (Shotsleft[i].GetX() <= Player2.GetX() + 104 && Shotsleft[i].GetX() >= Player2.GetX() && Shotsleft[i].GetY() <= Player2.GetY() + 82 && Shotsleft[i].GetY() >= Player2.GetY())
			{
				//SDL_Quit();
				Shotsleft[i].ShutDown();
				p2hp--;
			}
		}
	}
	for (int i = 0; i < MAX_SHOTS1; ++i)
	{
		if (Shotsright[i].IsAlive())
		{
			Shotsright[i].Move(1, 0);
			if (Shotsright[i].GetX() > WINDOW_WIDTH)	Shotsright[i].ShutDown();
			if (Shotsright[i].GetX() <= Player2.GetX() + 104 && Shotsright[i].GetX() >= Player2.GetX() && Shotsright[i].GetY() <= Player2.GetY() + 82 && Shotsright[i].GetY() >= Player2.GetY())
			{
				//SDL_Quit();
				Shotsright[i].ShutDown();
				p2hp--;
			}
		}
	}
	//Player 2 shots update
	for (int i = 0; i < MAX_SHOTS2; ++i)
	{
		if (Shotstop2[i].IsAlive())
		{
			Shotstop2[i].Move(0, -1);
			if (Shotstop2[i].GetX() > WINDOW_WIDTH)	Shotstop2[i].ShutDown();
			if (Shotstop2[i].GetX() <= Player.GetX() + 104 && Shotstop2[i].GetX() >= Player.GetX() && Shotstop2[i].GetY() <= Player.GetY() + 82 && Shotstop2[i].GetY() >= Player.GetY())
			{
				//SDL_Quit();
				Shotstop2[i].ShutDown();
				p1hp--;
			}
		}
		
	}
	for (int i = 0; i < MAX_SHOTS2; ++i)
	{
		if (Shotsbot2[i].IsAlive())
		{
			Shotsbot2[i].Move(0, 1);
			if (Shotsbot2[i].GetX() > WINDOW_WIDTH)	Shotsbot2[i].ShutDown();
			if (Shotsbot2[i].GetX() <= Player.GetX() + 104 && Shotsbot2[i].GetX() >= Player.GetX() && Shotsbot2[i].GetY() <= Player.GetY() + 82 && Shotsbot2[i].GetY() >= Player.GetY())
			{
				//SDL_Quit();
				Shotsbot2[i].ShutDown();
				p1hp--;
			}
		}
	}
	for (int i = 0; i < MAX_SHOTS2; ++i)
	{
		if (Shotsleft2[i].IsAlive())
		{
			Shotsleft2[i].Move(-1, 0);
			if (Shotsleft2[i].GetX() > WINDOW_WIDTH)	Shotsleft2[i].ShutDown();
			if (Shotsleft2[i].GetX() <= Player.GetX() + 104 && Shotsleft2[i].GetX() >= Player.GetX() && Shotsleft2[i].GetY() <= Player.GetY() + 82 && Shotsleft2[i].GetY() >= Player.GetY())
			{
				//SDL_Quit();
				Shotsleft2[i].ShutDown();
				p1hp--;
			}
		}
	}
	for (int i = 0; i < MAX_SHOTS2; ++i)
	{
		if (Shotsright2[i].IsAlive())
		{
			Shotsright2[i].Move(1, 0);
			if (Shotsright2[i].GetX() > WINDOW_WIDTH)	Shotsright2[i].ShutDown();
			if (Shotsright2[i].GetX() <= Player.GetX() + 104 && Shotsright2[i].GetX() >= Player.GetX() && Shotsright2[i].GetY() <= Player.GetY() + 82 && Shotsright2[i].GetY() >= Player.GetY())
			{
				//SDL_Quit();
				Shotsright2[i].ShutDown();
				p1hp--;
				
			}
		}
	}

	if (p1hp == 0) {
		SDL_Quit();
	}
	if (p2hp == 0) {
		SDL_Quit();
	}
		
	
	return false;
}
void Game::Draw()
{
	//Set the color used for drawing operations
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	//Clear rendering target
	SDL_RenderClear(Renderer);

	//Draw player
	SDL_Rect rc;
	Player.GetRect(&rc.x, &rc.y, &rc.w, &rc.h);
	SDL_SetRenderDrawColor(Renderer, 0, 192, 0, 255);
	SDL_RenderFillRect(Renderer, &rc);

	//Draw Player 2
	SDL_Rect rc2;
	Player2.GetRect(&rc2.x, &rc2.y, &rc2.w, &rc2.h);
	SDL_SetRenderDrawColor(Renderer, 110, 192, 110, 255);
	SDL_RenderFillRect(Renderer, &rc2);

	//Draw shots
	SDL_SetRenderDrawColor(Renderer, 192, 0, 0, 255);
	for (int i = 0; i < MAX_SHOTS1; ++i)
	{
		if (Shotstop[i].IsAlive())
		{
			Shotstop[i].GetRect(&rc.x, &rc.y, &rc.w, &rc.h);
			SDL_RenderFillRect(Renderer, &rc);
		}
	}
	for (int i = 0; i < MAX_SHOTS1; ++i)
	{
		if (Shotsbot[i].IsAlive())
		{
			Shotsbot[i].GetRect(&rc.x, &rc.y, &rc.w, &rc.h);
			SDL_RenderFillRect(Renderer, &rc);
		}
	}
	for (int i = 0; i < MAX_SHOTS1; ++i)
	{
		if (Shotsleft[i].IsAlive())
		{
			Shotsleft[i].GetRect(&rc.x, &rc.y, &rc.w, &rc.h);
			SDL_RenderFillRect(Renderer, &rc);
		}
	}
	for (int i = 0; i < MAX_SHOTS1; ++i)
	{
		if (Shotsright[i].IsAlive())
		{
			Shotsright[i].GetRect(&rc.x, &rc.y, &rc.w, &rc.h);
			SDL_RenderFillRect(Renderer, &rc);
		}
	}
	//Player 2 Shots
	SDL_SetRenderDrawColor(Renderer, 100, 0, 100, 0);
	for (int i = 0; i < MAX_SHOTS2; ++i)
	{
		if (Shotstop2[i].IsAlive())
		{
			Shotstop2[i].GetRect(&rc.x, &rc.y, &rc.w, &rc.h);
			SDL_RenderFillRect(Renderer, &rc);
		}
	}
	for (int i = 0; i < MAX_SHOTS2; ++i)
	{
		if (Shotsbot2[i].IsAlive())
		{
			Shotsbot2[i].GetRect(&rc.x, &rc.y, &rc.w, &rc.h);
			SDL_RenderFillRect(Renderer, &rc);
		}
	}
	for (int i = 0; i < MAX_SHOTS2; ++i)
	{
		if (Shotsleft2[i].IsAlive())
		{
			Shotsleft2[i].GetRect(&rc.x, &rc.y, &rc.w, &rc.h);
			SDL_RenderFillRect(Renderer, &rc);
		}
	}
	for (int i = 0; i < MAX_SHOTS2; ++i)
	{
		if (Shotsright2[i].IsAlive())
		{
			Shotsright2[i].GetRect(&rc.x, &rc.y, &rc.w, &rc.h);
			SDL_RenderFillRect(Renderer, &rc);
		}
	}

	//Update screen
	SDL_RenderPresent(Renderer);

	SDL_Delay(10);	// 1000/10 = 100 fps max
}

