#include "Game.h"

Game::Game()
{
	m_window = SDL_CreateWindow("Entity Component Systems", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1500, 900, SDL_WINDOW_OPENGL);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;

	if (IMG_Init(imgFlags) != imgFlags)
	{
		cout << "Error: " << IMG_GetError() << endl;
	}

	client = new Client();
	/*m_dot = new Dot();
	m_dot->Init(m_renderer);

	m_dot->SetPosition(0, 350);
	m_chaser = new Dot(true);

	m_chaser->Init(m_renderer);
	m_chaser->SetPosition(1000, 350);*/
	if (!m_lostText.loadFromFile("lose.png", m_renderer))
	{
		printf("Failed to load dot texture!\n");
	}
	if (!m_winText.loadFromFile("winner.png", m_renderer))
	{
		printf("Failed to load dot texture!\n");
	}
	if (!m_backgroundTexture.loadFromFile("background.png", m_renderer))
	{
		printf("Failed to load dot texture!\n");
	}
	if (client->run())
	{
		client->sendMessage("Join, Hello,");
	}
}

Game::~Game()
{
}

void Game::run()
{
	const Uint32 fps = 60;
	const Uint32 minimumFrameTime = 1000 / fps;

	Uint32 frameTime;
	Uint32 lastFrameTime = 0;
	Uint32 deltaTime = 0;

	while (!exit) {

		processEvents();
		frameTime = SDL_GetTicks();

		deltaTime = frameTime - lastFrameTime;
		lastFrameTime = frameTime;

		update();
		render();

		if ((SDL_GetTicks() - frameTime) < minimumFrameTime)
			SDL_Delay(minimumFrameTime - (SDL_GetTicks() - frameTime));
	}

	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Game::processEvents()
{


	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			exit = true;
			break;
		case SDL_KEYDOWN:
			if (joined == true)
			{
				m_dot->handleEvent(event, *client);
			}

			//m_chaser->handleEvent(event, *client);
			if (event.key.keysym.sym == SDLK_ESCAPE)
				exit = true;
			break;
		}
	}
}

void Game::update()
{

	if (joined == true)
	{
		m_dot->move(800, 1400, *client);
	}
	if (client->join == true)
	{
		m_dotTwo->move(800, 1400, *client);
	}

	
	if (client->number == 2 && !joined)
	{
		m_dot = new Dot(true);
		m_dot->Init(m_renderer);
		joined = true;
	}
	else if (client->number == 3 && !joined)
	{
		m_dot = new Dot(false);
		m_dot->Init(m_renderer);
		joined = true;

		m_dotTwo = new Dot(true);
		m_dotTwo->Init(m_renderer);

		enemyJoined = true;
		client->join = true;
	}

	if (client->join == true && !enemyJoined)
	{
		m_dotTwo = new Dot(false);
		m_dotTwo->Init(m_renderer);
		enemyJoined = true;
	}
	if (joined == true)
	{
		client->sendMessage(m_dot->message);

	}
	//std::cout << client->positionUpdate.size() << std::endl;
	if (client->positionVec.size() > 1)
	{
		//std::cout << client->positionUpdate.at(0) << ", " << client->positionUpdate.at(1) << std::endl;
		m_dotTwo->SetPosition(client->positionVec.at(0), client->positionVec.at(1));
	}
	if (joined == true && enemyJoined == true && m_dotTwo->isChaser) {
		if (m_dotTwo->Checkcollision(m_dot->getPosX(), m_dot->getPosY()))
		{
			//m_dot->Reset();

			client->sendMessage("Game,collide,");
		}
	}
	client->receive();

	if (client->collide == true && m_dotTwo->isChaser)
	{
		gameOver = true;
		m_endText = m_lostText;
	}
	else if (client->collide == true && !m_dotTwo->isChaser)
	{
		gameOver = true;
		m_endText = m_lostText;
	}




}

void Game::render()
{
	if (m_renderer == nullptr)
	{
		SDL_Log("Could not create a renderer: %s", SDL_GetError());
	}

	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
	SDL_RenderClear(m_renderer);
	m_backgroundTexture.render(0, 0, m_renderer);
	if (joined) {
		m_dot->render(m_renderer);
	}
	if (client->join)
	{
		m_dotTwo->render(m_renderer);
	}
	
	if (gameOver)
	{
		m_endText.render(0, 0, m_renderer);
	}
	SDL_RenderPresent(m_renderer);

}





