#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
#include <random>
#include <chrono>
#include <thread>

#define SIZE 4

struct Pair {
    std::string question;
    std::string answer;
};

struct Card {
    sf::RectangleShape rect;
    sf::RectangleShape flipButton;
    sf::Text buttonText;
    Pair pair;
    std::string text;
    bool revealed;
    bool matched;
    bool isQuestion;
};

class MemoryGame {
private:
    sf::RenderWindow window;
    std::vector<Card> cards;
    sf::Font font;
    int lastCard;
    bool wait;
    sf::Clock clock;

public:
    MemoryGame() : window(sf::VideoMode(800, 800), "SFML Memory Game") {
        std::vector<Pair> pairs = {
            {"1+1", "2"},
            {"2+2", "4"},
            {"3+3", "6"},
            {"4+4", "8"},
            {"5+5", "10"},
            {"6+6", "12"},
            {"7+7", "14"},
            {"8+8", "16"}
        };

        // Create question cards
        for (int i = 0; i < SIZE * SIZE / 2; ++i) {
            cards.push_back(createCard(pairs[i], true));
        }

        // Create answer cards
        for (int i = 0; i < SIZE * SIZE / 2; ++i) {
            cards.push_back(createCard(pairs[i], false));
        }

        // Shuffle after all cards have been created
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(cards.begin(), cards.end(), g);

        // Update positions of cards after shuffle
        for (int i = 0; i < SIZE * SIZE; ++i) {
            cards[i].rect.setPosition(200.f * (i % SIZE), 200.f * (i / SIZE));
            cards[i].flipButton.setPosition(cards[i].rect.getPosition().x + cards[i].rect.getSize().x / 2.0f - cards[i].flipButton.getSize().x / 2.0f,
                                            cards[i].rect.getPosition().y + cards[i].rect.getSize().y / 2.0f - cards[i].flipButton.getSize().y / 2.0f);
            sf::FloatRect textBounds = cards[i].buttonText.getLocalBounds();
            cards[i].buttonText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                                          textBounds.top + textBounds.height / 2.0f);
            cards[i].buttonText.setPosition(cards[i].flipButton.getPosition().x + cards[i].flipButton.getSize().x / 2.0f,
                                            cards[i].flipButton.getPosition().y + cards[i].flipButton.getSize().y / 2.0f);
        }

        if (!font.loadFromFile("myfnt.ttf"))
            exit(EXIT_FAILURE);
        lastCard = -1;
        wait = false;
    }


    Card createCard(Pair pair, bool isQuestion) {
        Card card;
        card.rect.setSize(sf::Vector2f(180.f, 180.f));
        card.rect.setPosition(200.f * (cards.size() % SIZE), 200.f * (cards.size() / SIZE));
        card.rect.setFillColor(sf::Color::White);

        card.flipButton.setSize(sf::Vector2f(120.f, 60.f));
        card.flipButton.setPosition(card.rect.getPosition().x + card.rect.getSize().x / 2.0f - card.flipButton.getSize().x / 2.0f,
                                    card.rect.getPosition().y + card.rect.getSize().y / 2.0f - card.flipButton.getSize().y / 2.0f);
        card.flipButton.setFillColor(sf::Color::Green);

        card.pair = pair;
        card.text = isQuestion ? pair.question : pair.answer;
        card.revealed = false;
        card.matched = false;
        card.isQuestion = isQuestion;

        card.buttonText.setFont(font);
        card.buttonText.setString("Flip");
        card.buttonText.setCharacterSize(36);
        card.buttonText.setFillColor(sf::Color::Black);
        card.buttonText.setStyle(sf::Text::Bold);

        sf::FloatRect textBounds = card.buttonText.getLocalBounds();
        card.buttonText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                                  textBounds.top + textBounds.height / 2.0f);
        card.buttonText.setPosition(card.flipButton.getPosition().x + card.flipButton.getSize().x / 2.0f,
                                    card.flipButton.getPosition().y + card.flipButton.getSize().y / 2.0f);

        return card;
    }

    void Run() {
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonPressed && !wait)
                {
                    sf::Vector2i pos = sf::Mouse::getPosition(window);
                    for (int i = 0; i < SIZE * SIZE; ++i) {
                        if (cards[i].flipButton.getGlobalBounds().contains(pos.x, pos.y) && !cards[i].matched && !cards[i].revealed) {
                            cards[i].revealed = true;
                            if (lastCard != -1) {
                                if (cards[lastCard].pair.answer == cards[i].pair.answer) {
                                    cards[lastCard].matched = true;
                                    cards[i].matched = true;
                                    lastCard = -1;
                                }
                                else {
                                    wait = true;
                                    clock.restart();
                                }
                            }
                            else {
                                lastCard = i;
                            }
                            break;
                        }
                    }
                }
            }

            if (wait && clock.getElapsedTime() > sf::seconds(2.f)) {
                for (Card& card : cards) {
                    if (!card.matched) {
                        card.revealed = false;
                    }
                }
                lastCard = -1;
                wait = false;
            }

            window.clear();
            for (int i = 0; i < SIZE * SIZE; ++i) {
                window.draw(cards[i].rect);
                window.draw(cards[i].flipButton);
                window.draw(cards[i].buttonText);
                if (cards[i].revealed || cards[i].matched) {
                    sf::Text text(cards[i].text, font);
                    text.setCharacterSize(60);
                    sf::FloatRect textRect = text.getLocalBounds();
                    text.setOrigin(textRect.left + textRect.width / 2.0f,
                                   textRect.top + textRect.height / 2.0f);
                    text.setPosition(cards[i].rect.getPosition().x + cards[i].rect.getSize().x / 2.0f,
                                     cards[i].rect.getPosition().y + cards[i].rect.getSize().y / 2.0f);
                    window.draw(text);
                }
            }
            window.display();
        }
    }
};

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    MemoryGame game;
    game.Run();
    return EXIT_SUCCESS;
}
