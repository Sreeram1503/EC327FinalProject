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

        //generate random numbers
    int a_rand = rand() % 11;
    int b_rand = rand() % 5;
    int c_rand = rand() % 11;

//question 1: factorial
    int factorial = 1;
    for (int i = 1; i <= a_rand; i++) {
        factorial *= i;
    }
    string ques_factorial = to_string(a_rand) + "!";
    string ans_factorial = to_string(factorial);

//question 2: derivative x^rand where x=2
    int exponent = b_rand;
    int deriv_ans = b_rand * pow(2,b_rand-1);
    //(d/dx)x^rand where x=2
    string ques_deriv = "(d/dx) of x ^ " + to_string(exponent) + "where x = 2";
    string ans_deriv = to_string(deriv_ans);

//question 3: area of a circle with radius c_rand
    int radius = c_rand;
    float circle_ans = pow(c_rand,2) * 3.14;
    string ques_radius = "area of circle with radius " + to_string(radius);
    string ans_radius = to_string(circle_ans);

//question 4: hypotenuse of triangle with sides c_rand and a_rand (rounded)
    int side_one = a_rand;
    int side_two = c_rand;
    float hypot_ans = sqrt((pow(a_rand,2))+(pow(c_rand,2)));
    string ques_hypo = " find hypotenuse, sides: " + to_string(side_one) + " and " + to_string(side_two);
    string ans_hypo = to_string(hypot_ans);

//question 5: sin^2(c_rand) + cos^2(b_rand)   answer is always 1
    string ques_sin = "sin^2(" + to_string(b_rand) + ") + cos^2(" + to_string(b_rand) + ")";
    string ans_sin = "1";

//question 6: (tan(c_rand) + cot(c_rand)) * 3     answer is always 3
    string ques_tan = "(tan(" + to_string(c_rand) + ") + cot(" + to_string(c_rand) + ")) * 3";
    string ans_tan = "3";

//question 7: exponent (2^a_rand)
    int exp = a_rand;
    int exp_ans = pow(2,exp);
    string ques_exp = "2^" + to_string(exp);
    string ans_exp = to_string(exp_ans);

//question 8: convert b_rand radians to degrees
    int rad = b_rand;
    float rad_ans = rad * (180/3.14);
    string ques_deg = "convert " + to_string(rad) + " to degrees";
    string ans_deg = to_string(rad_ans);

    struct Pair {
        std::string questions;
        std::string answers;
    };

    questions.push_back(ques_factorial); 
    questions.push_back(ques_deriv);
    questions.push_back(ques_radius);
    questions.push_back(ques_hypo);
    questions.push_back(ques_sin);
    questions.push_back(ques_tan); 
    questions.push_back(ques_exp);
    questions.push_back(ques_deg); 

    answers.push_back(ans_factorial);
    answers.push_back(ans_deriv);
    answers.push_back(ans_radius);
    answers.push_back(ans_hypo);
    answers.push_back(ans_sin);
    answers.push_back(ans_tan);
    answers.push_back(ans_exp);
    answers.push_back(ans_deg);

public:
    MemoryGame() : window(sf::VideoMode(800, 800), "SFML Memory Game") {
        std::vector<Pair> pairs = {
            {questions[0], answers[0]},
            {questions[1], answers[1]},
            {questions[2], answers[2]},
            {questions[3], answers[3]},
            {questions[4], answers[4]},
            {questions[5], answers[5]},
            {questions[6], answers[6]},
            {questions[7], answers[7]}
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

        if (!font.loadFromFile("/Users/rupalisinha/Desktop/EC327/tuffy.ttf"))
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

        card.text = isQuestion ? pair.questions : pair.answers;
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
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonPressed && !wait) {
                    sf::Vector2i pos = sf::Mouse::getPosition(window);
                    for (int i = 0; i < SIZE * SIZE; ++i) {
                        if (cards[i].flipButton.getGlobalBounds().contains(pos.x, pos.y) && !cards[i].matched && !cards[i].revealed) {
                            cards[i].revealed = true;
                            if (lastCard != -1) {
                                if (cards[lastCard].text == cards[i].text) {
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
