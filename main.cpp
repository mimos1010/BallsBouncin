#pragma once
#include "main.h"
#include "PBall.h"

//Define a few key functions
float getRand(float min, float max);
bool checkCollision(PBall A, PBall B);
void resolveCollision(PBall A, PBall B);

int main() {
	//important template variables
	int currentradius = 20;
	int currentmass = 5;
	sf::Color color(255, 255, 255, 255);
	std::vector <PBall> balls;

	//define speed for velocity template
	sf::Vector2f the_speed(.1f, .1f);
	
	
#pragma region fontstuff
	// Declare and load a font
	sf::Font font;
	font.loadFromFile("arial.ttf");
	// Create texts
	sf::Text text("Control Panel Window", font);
	text.setCharacterSize(20);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::White);

	sf::Text text2("Control Panel Window", font);
	text2.setCharacterSize(20);
	text2.setStyle(sf::Text::Bold);
	text2.setColor(sf::Color::White);
	text2.setPosition(text2.getPosition().x, 30);

	sf::Text text3("Press R to randomize color", font);
	text3.setCharacterSize(20);
	text3.setStyle(sf::Text::Bold);
	text3.setColor(sf::Color::White);
	text3.setPosition(text3.getPosition().x, 60);

	sf::Text text4("Current Ball:", font);
	text4.setCharacterSize(20);
	text4.setStyle(sf::Text::Bold);
	text4.setColor(sf::Color::White);
	text4.setPosition( 90, 140);

	sf::Text text5("(Main window should be selected)\n Click to Spawn a Ball", font);
	text5.setCharacterSize(14);
	text5.setStyle(sf::Text::Bold);
	text5.setColor(sf::Color::Red);
	text5.setPosition(0, 90);
#pragma endregion font setup and stuff

	//setup for timestepping
	sf::Clock timer;
	double skippedTime = 0;

	//setting up antialias so it looks nice :)
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	//initialize both windows and set up the position on screen
	sf::RenderWindow windowSET(sf::VideoMode(350, 350), "Settings Window");
	sf::RenderWindow window(sf::VideoMode(800, 640), "Physics Balls", sf::Style::Default, settings);

	sf::Vector2i posSET(1, 250);
	sf::Vector2i pos(350, 40);

	windowSET.setPosition(posSET);
	window.setPosition(pos);
	int dontsolve = 0;


	while (window.isOpen() || windowSET.isOpen()) //RUNLOOP--------------------------------------------//
	{
		PBall pballtemplate(currentradius, currentmass);
		pballtemplate.setPosition(120, 180);
		pballtemplate.setFillColor(color);

		std::string radi_string = std::to_string(currentradius);
		std::string mass_string = std::to_string(currentmass);

		text.setString("Mass (change with W or S):   " + mass_string + " kg");
		text2.setString("Radius (change with E or D): " + radi_string);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				windowSET.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::E:
					if (currentradius < 75)
					{
						currentradius++;
					}
					else
					{

					}
					break;
				case sf::Keyboard::D:
					if (currentradius > 5)
					{
						currentradius--;
					}
					else
					{

					}
					break;
				case sf::Keyboard::W:
					if (currentmass < 99)
					{
						currentmass++;
					}
					else
					{

					}
					break;
				case sf::Keyboard::S:
					if (currentmass > 1)
					{
						currentmass--;
					}
					else
					{

					}
					break;
				case sf::Keyboard::R:
					
					color.r = getRand(1, 255);
					color.g = getRand(1, 255);
					color.b = getRand(1, 255);

					break;
				}
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2f mousepos;
				mousepos.x = sf::Mouse::getPosition(window).x;
				mousepos.y = sf::Mouse::getPosition(window).y;
				if (balls.size() < 20)
				{
					pballtemplate.setPosition(mousepos);
					pballtemplate.setSpeed(the_speed);
					float tempvelx = pballtemplate.speed.x * pballtemplate.mass;
					float tempvely = pballtemplate.speed.y * pballtemplate.mass;
					sf::Vector2f tempvel(tempvelx, tempvely);
					pballtemplate.setVelocity(tempvel);
					balls.push_back(pballtemplate);

				}
				else
				{

				}
			}
		}

		//timestepping
		const double elapsedTime = timer.restart().asMicroseconds() / 1000.;
		skippedTime += elapsedTime;

		while (skippedTime > 5) { //Event Handling and Physics

			for (int i = 0; i < balls.size(); i++)
			{
				balls[i].updatePosition();
				balls[i].setupCenter();
				sf::Vector2f vell= balls[i].velocity;
			}
			
			for (int i = 0; i < balls.size(); i++)
			{
				
				balls[i].resolveEdges();
			}

			skippedTime -= 5;
		}
		

		window.clear();
		for (int i = 0; i < balls.size(); i++)
		{
			window.draw(balls[i]);
		}

		window.display();

		windowSET.clear();
		windowSET.draw(text);
		windowSET.draw(text2);
		windowSET.draw(text3);
		windowSET.draw(text4);
		windowSET.draw(text5);
		windowSET.draw(pballtemplate);
		windowSET.display();
		
		
	}

	return 0;
}
#pragma region function definitions
float getRand(float min, float max)
{
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(min, max); // guaranteed unbiased

	auto random_integer = uni(rng);

	return random_integer;
}
bool checkCollision(PBall A, PBall B) {
	if ((A.center.x + A.getRadius() < 400) && (B.center.x - B.getRadius() > 400))
	{
		return false;
	}
	else if ((A.center.y + A.getRadius() < 310) && (B.center.y - B.getRadius() > 310))
	{
		return false;
	}
	else
	{
		float distance = std::sqrtf(((A.center.x - B.center.x)*(A.center.x - B.center.x)) + ((A.center.y - B.center.y)*(A.center.y - B.center.y)));
		if (distance < (A.getRadius() + B.getRadius()))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}


#pragma endregion All the function definitions
