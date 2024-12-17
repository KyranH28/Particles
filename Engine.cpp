#include "Engine.h"

Engine::Engine()
{
	VideoMode tempVM = VideoMode::getDesktopMode();
	m_Window.create(tempVM, "Particles!");
}

void Engine::run()
{
	Time time;
	Clock clock;

	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;

	while (m_Window.isOpen())
	{
		clock.restart();
		time = clock.getElapsedTime();
		input();
		update(time.asSeconds());
		draw();
	}
}

void Engine::input()
{
	Event event;
	while (m_Window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			m_Window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			m_Window.close();
		}
		if (event.type == Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == Mouse::Left)
			{
				for (int p = 0; p < 5; p++)
				{
					int num = 25 + (rand() % 26);
					Particle P(m_Window, num, Vector2i(event.mouseButton.x, event.mouseButton.y));
					m_particles.push_back(P);
				}
			}
		}
	}
}

void Engine::update(float dtAsSeconds)
{
	for (auto iter = m_particles.begin(); iter != m_particles.end();)
	{
		if (iter->getTTL() > 0.0)
		{
			iter->update(dtAsSeconds);
			++iter;
		}
		else
		{
			iter = m_particles.erase(iter);
		}
	}
}

void Engine::draw()
{
	m_Window.clear();
	for (Particle p : m_particles)
	{
		m_Window.draw(p);
	}
	m_Window.display();
}