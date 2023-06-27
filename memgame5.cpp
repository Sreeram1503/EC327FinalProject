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

using std::string;
using std::to_string;
using std::thread;
using std::vector;
using std::shuffle;
using std::chrono::seconds;
using std::chrono::duration_cast;
using std::chrono::system_clock;

#define SIZE 4

struct Card {
    sf::RectangleShape rect;
    sf::RectangleShape flipButton;
    sf::Text buttonText;
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
    MemoryGame() : window(sf::VideoMode(1000, 900), "SFML Memory Game") {
        if (!font.loadFromFile("/Users/rupalisinha/Desktop/EC327/tuffy.ttf"))
            exit(EXIT_FAILURE);
        lastCard = -1;
        wait = false;

        // Generate random numbers
        int a_rand = rand() % 11;
        int b_rand = rand() % 5;
        int c_rand = rand() % 11;

        // Question 1: factorial
        int factorial = 1;
        for (int i = 1; i <= a_rand; i++) {
            factorial *= i;
        }
        string ques_factorial = to_string(a_rand) + "!";
        string ans_factorial = to_string(factorial);

        // Question 2: derivative x^rand where x=2
        int exponent = b_rand;
        int deriv_ans = b_rand * pow(2, b_rand - 1);
        string ques_deriv = "(d/dx) of x ^ " + to_string(exponent) + " where x = 2";
        string ans_deriv = to_string(deriv_ans);

        // Question 3: area of a circle with radius c_rand
        int radius = c_rand;
        float circle_ans = pow(c_rand, 2) * 3.14;
        string ques_radius = "area of circle with radius " + to_string(radius);
        string ans_radius = to_string(circle_ans);

        // Question 4: hypotenuse of triangle with sides c_rand and a_rand (rounded)
        int side_one = a_rand;
        int side_two = c_rand;
        float hypot_ans = sqrt((pow(a_rand, 2)) + (pow(c_rand, 2)));
        string ques_hypo = " find hypotenuse, sides: " + to_string(side_one) + " and " + to_string(side_two);
        string ans_hypo = to_string(hypot_ans);

        // Question 5: sin^2(c_rand) + cos^2(b_rand)   answer is always 1
        string ques_sin = "sin^2(" + to_string(b_rand) + ") + cos^2(" + to_string(b_rand) + ")";
        string ans_sin = "1";

        // Question 6: (tan(c_rand) + cot(c_rand)) * 3     answer is always 3
        string ques_tan = "(tan(" + to_string(c_rand) + ") + cot(" + to_string(c_rand) + ")) * 3";
        string ans_tan = "3";

        // Question 7: exponentiation
        int base = a_rand;
        int exponentiation = rand() % 6;
        int result = pow(base, exponentiation);
        string ques_exponent = to_string(base) + "^" + to_string(exponentiation);
        string ans_exponent = to_string(result);

        // Create cards
        for (int i = 0; i < SIZE * SIZE / 2; i++) {
            Card card;
            card.rect.setSize(sf::Vector2f(150, 150));
            card.rect.setFillColor(sf::Color::White);
            card.rect.setOutlineThickness(2);
            card.rect.setOutlineColor(sf::Color::Black);
            card.rect.setPosition(sf::Vector2f(200 + (i % SIZE) * 200, 200 + (i / SIZE) * 200));
            card.revealed = false;
            card.matched = false;
            card.isQuestion = false;

            card.flipButton.setSize(sf::Vector2f(140, 40));
            card.flipButton.setFillColor(sf::Color::Blue);
            card.flipButton.setPosition(sf::Vector2f(card.rect.getPosition().x + 5, card.rect.getPosition().y + 155));

            card.buttonText.setFont(font);
            card.buttonText.setString("Click to Flip");
            card.buttonText.setCharacterSize(14);
            card.buttonText.setFillColor(sf::Color::White);

        // Shuffle cards
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

        // Run the game loop
        void Run() {
            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window.close();
                    else if (event.type == sf::Event::MouseButtonPressed) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            int x = event.mouseButton.x;
                            int y = event.mouseButton.y;

                    for (int i = 0; i < cards.size(); i++) {
                        if (cards[i].flipButton.getGlobalBounds().contains(x, y) && !cards[i].matched && !cards[i].revealed) {
                            cards[i].revealed = true;

                        if (lastCard == -1) {
                            lastCard = i;
                        } else {
                            if (cards[lastCard].text == cards[i].text) {
                                cards[lastCard].matched = true;
                                cards[i].matched = true;
                            } else {
                                wait = true;
                            }
                            lastCard = -1;
                            }
                        }
                    }; 
                }
            }
        }
    }

            window.clear(sf::Color::White);

            // Draw cards
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

            window.display();
        }
    };

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    MemoryGame game;
    game.Run();
    return EXIT_SUCCESS;
}
