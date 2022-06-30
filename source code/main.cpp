#include "Driver.h"
#include "Config.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

void setupConfig();

int main(void)
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	setupConfig();

	sf::RenderWindow window(sf::VideoMode(
		Config::windowWidth, Config::windowHeight),
		"Gem Drilla Inc",
		sf::Style::Fullscreen);
	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(60);

	const sf::Color clearColor(104, 136, 204);

	Driver driver;

	sf::Clock gameClock;
	float deltaTime = gameClock.restart().asSeconds();

	while (window.isOpen() && !driver.isDone())
	{
		deltaTime = gameClock.restart().asSeconds();

		sf::Event ev;

		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::KeyPressed)
			{
				driver.updateOnKeyPress(ev.key.code);
			}
			else if (ev.type == sf::Event::KeyReleased)
			{
				driver.updateOnKeyRelease(ev.key.code);
			}
			else if (ev.type == sf::Event::MouseButtonPressed)
			{
				driver.updateOnMousePress(ev.mouseButton.x, ev.mouseButton.y, ev.mouseButton.button);
			}
			else if (ev.type == sf::Event::MouseMoved)
			{
				driver.updateOnMouseMove(ev.mouseMove.x, ev.mouseMove.y);
			}
			else if (ev.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		driver.update(deltaTime);

		window.clear(clearColor);
		window.draw(driver);
		window.display();
	}

	return 0;
}

void setupConfig()
{
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();

	Config::windowWidth = mode.width;
	Config::windowHeight = mode.height;

	Config::smallFontSize = static_cast<uint16_t>(std::floorf((Config::windowWidth + Config::windowHeight) * 0.022f / 8.0f) * 8.0f);
	Config::mediumFontSize = static_cast<uint16_t>(std::floorf((Config::windowWidth + Config::windowHeight) * 0.045f / 8.0f) * 8.0f);
	Config::largeFontSize = static_cast<uint16_t>(std::floorf((Config::windowWidth + Config::windowHeight) * 0.09f / 8.0f) * 8.0f);
	Config::globalScale = std::floorf((Config::windowWidth + Config::windowHeight) * 0.004f);
}