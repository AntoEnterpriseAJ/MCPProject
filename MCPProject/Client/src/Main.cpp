#include <iostream>
#include <SFML/Graphics.hpp>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "Player.h"

int main()
{
    cpr::Response greetResponse = cpr::Get(cpr::Url{"http://localhost:18080/greet"});

    auto [statusCode, text] = std::tie(greetResponse.status_code, greetResponse.text);
    if (statusCode == cpr::status::HTTP_OK)
    {
        std::cout << "GET was succesful\n";
        std::cout << text << "\n";
    }
    else
    {
        std::cout << "GET failed, error: " << greetResponse.status_code << "\n";
    }

    sf::Texture playerTexture;
    playerTexture.loadFromFile("res/textures/plane.png");
    sf::Vector2f playerSize{80.0f, 100.0f};

    std::vector<Player> players;
	while(true)
	{
        bool wantToJoin{false};
        std::cout << "Join the game? 1 - Yes  0 - No\n";
        std::cin >> wantToJoin;

        if (wantToJoin)
        {
            std::cout << "Enter your spawn coordinates:\n";
            sf::Vector2f position{};
            std::cin >> position.x >> position.y;

            nlohmann::json data = {
                {"position", {position.x, position.y}}
            };

            cpr::Response joinResponse = cpr::Post(
                cpr::Url{"http://localhost:18080/join"},
                cpr::Header{{"Content-Type", "application/json"}},
                cpr::Body{data.dump()}
            );

            if (joinResponse.status_code == 200)
            {
                players.push_back(Player{position, playerTexture, playerSize});
            }
            else
            {
                std::cout << "There was an error: " << joinResponse.status_code << ", " << joinResponse.error.message << "\n";
                break;
            }

	        sf::RenderWindow window(sf::VideoMode(800, 600), "Networking test");
            while (window.isOpen())
            {
	            sf::Event event;
                while(window.pollEvent(event))
	            {
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    {
                        window.close();
                    }
	            }

                // BAD
                cpr::Response getPlayersResponse = cpr::Get(cpr::Url{"http://localhost:18080/players"});
                if (getPlayersResponse.status_code == 200)
                {
                    players.clear();
                    auto data = nlohmann::json::parse(getPlayersResponse.text);

                    for (const auto& playerData : data)
                    {
                        if (playerData.contains("position") && playerData.at("position").size() == 2)
                        {
                            sf::Vector2f position{playerData.at("position")[0], playerData.at("position")[1]};
                            players.push_back(Player{position, playerTexture, playerSize});
                        }
                        else
                        {
                            std::cout << (playerData.contains("position") ? "Invalid position data\n" : "No position data\n");
                            std::cout << "Player data: " << playerData.dump() << "\n";
                        }
                    }
                }
                else
                {
                    std::cout << "Couldn't retrieve then players data, error: "
                              << getPlayersResponse.status_code << ", "
                              << getPlayersResponse.error.message << "\n";
                }

                for (const auto& player : players)
                {
                    window.draw(player);
                }

	            window.display();
            }
        }

        std::cout << "Are you sure?\n";
    }

    return 0;
}