#ifndef GAME
#define GAME

#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <iostream>
#include "Dot.h"
#include "Client.h"
#include "LTexture.h"

using namespace std;

class Game {

public:
	Game();
	~Game();

	void run();

private:

	void processEvents();
	void update();
	void render();

	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Event event;
	bool exit;

	Dot* m_dot;
	Dot* m_dotTwo;

	Client* client;

	LTexture m_backgroundTexture;
	LTexture m_winText;
	LTexture m_lostText;
	LTexture m_endText;
	bool joined = false;
	bool enemyJoined = false;
	bool collided = false;
	bool gameOver = false;
	bool host = false;
};



#endif // !GAME
