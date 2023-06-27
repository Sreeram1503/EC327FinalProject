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
    MemoryGame() : window(sf::VideoMode(1200, 875), "SFML Memory Game") {
        //generate random numbers
    int a_rand = rand() % 11;
    int b_rand = rand() % 5;
    int c_rand = rand() % 11;

//question 1: factorial
    int factorial = 1;
    for(int i = 1; i <= a_rand; i++){
        factorial *= i;
    }
    std::string ques_factorial = std::to_string(a_rand) + "!";
    std::string ans_factorial = std::to_string(factorial);

//question 2: derivative x^rand where x=2
    int expo = b_rand;
    int deriv_ans = b_rand * pow(2,b_rand-1);
    //(d/dx)x^rand where x=2
    std::string ques_deriv = "(d/dx) of x^" + std::to_string(expo) + ", x=2";
    std::string ans_deriv = std::to_string(deriv_ans);

//question 3: area of a circle with radius c_rand
    int radius = c_rand;
    float circle_ans = pow(c_rand,2) * 3.14;
    std::string ques_radius = "area of circle with radius " + std::to_string(radius);
    std::string ans_radius = std::to_string(circle_ans);

//question 4: hypotenuse of triangle with sides c_rand and a_rand (rounded)
    int side_one = a_rand;
    int side_two = c_rand;
    float hypot_ans = sqrt((pow(a_rand,2))+(pow(c_rand,2)));
    std::string ques_hypo = " find hypotenuse, sides: " + std::to_string(side_one) + " and " + std::to_string(side_two);
    std::string ans_hypo = std::to_string(hypot_ans);

//question 5: sin^2(c_rand) + cos^2(b_rand)   answer is always 1
    std::string ques_sin = "sin^2(" + std::to_string(b_rand) + ") + cos^2(" + std::to_string(b_rand) + ")";
    std::string ans_sin = "1";

//question 6: (tan(c_rand) + cot(c_rand)) * 3     answer is always 3
    std::string ques_tan = "(tan(" + std::to_string(c_rand) + ") + cot(" + std::to_string(c_rand) + ")) * 3";
    std::string ans_tan = "3";

//question 7: exponent (2^a_rand)
    int exp = a_rand;
    int exp_ans = pow(2,exp);
    std::string ques_exp = "2^" + std::to_string(exp);
    std::string ans_exp = std::to_string(exp_ans);

//question 8: convert b_rand radians to degrees
    int rad = b_rand;
    float rad_ans = rad * (180/3.14);
    std::string ques_deg = "convert " + std::to_string(rad) + " to degrees";
    std::string ans_deg = std::to_string(rad_ans);

        std::vector<Pair> pairs = {
            {ques_factorial, ans_factorial},
            {ques_deriv, ans_deriv},
            {ques_radius, ans_radius},
            {ques_hypo, ans_hypo},
            {ques_sin, ans_sin},
            {ques_tan, ans_tan},
            {ques_exp, ans_exp},
            {ques_deg, ans_deg}
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
            cards[i].rect.setPosition(300.f * (i % SIZE), 200.f * (i / SIZE));
            cards[i].flipButton.setPosition(cards[i].rect.getPosition().x + cards[i].rect.getSize().x / 2.0f - cards[i].flipButton.getSize().x / 2.0f,
                                            cards[i].rect.getPosition().y + cards[i].rect.getSize().y / 2.0f - cards[i].flipButton.getSize().y / 2.0f);
            sf::FloatRect textBounds = cards[i].buttonText.getLocalBounds();
            cards[i].buttonText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                                          textBounds.top + textBounds.height / 2.0f);
            cards[i].buttonText.setPosition(cards[i].flipButton.getPosition().x + cards[i].flipButton.getSize().x / 2.0f,
                                            cards[i].flipButton.getPosition().y + cards[i].flipButton.getSize().y / 2.0f);
        }

        if (!font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf"))
            exit(EXIT_FAILURE);
        lastCard = -1;
        wait = false;
    }


    Card createCard(Pair pair, bool isQuestion) {
        Card card;
        card.rect.setSize(sf::Vector2f(280.f, 180.f));
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
    int countdown_timer(sf::RenderWindow& window,sf::Text countdown,int total_start){
        std::time_t time = std::time(NULL);
        std::tm current_time = *std::localtime(&time);
        int curr_min = current_time.tm_min;
        int curr_sec = current_time.tm_sec;
        int total_curr = (curr_min * 60) + curr_sec;
        int change = total_curr - total_start;
        int time_left = 180 - change;
        int seconds = time_left % 60;
        int minutes = time_left / 60;
        if(seconds < 10){
            countdown.setString(std::to_string(minutes) + ":0" + std::to_string(seconds));
        }
        else{
            countdown.setString(std::to_string(minutes) + ":" + std::to_string(seconds));
        }
            
            window.draw(countdown);
            return time_left;
    }
    
    void Run() {
        std::time_t time = std::time(NULL);
        std::tm start_time = *std::localtime(&time);
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
                    text.setCharacterSize(30);
                    text.setFillColor(sf::Color::Black);
                    sf::FloatRect textRect = text.getLocalBounds();
                    text.setOrigin(textRect.left + textRect.width / 2.0f,
                                   textRect.top + textRect.height / 2.0f);
                    text.setPosition(cards[i].rect.getPosition().x + cards[i].rect.getSize().x / 2.0f,
                                     cards[i].rect.getPosition().y + cards[i].rect.getSize().y / 2.0f);
                    window.draw(text);
                }
            }

            //countdown timer
            sf::Text countdown;
            countdown.setFont(font);
            countdown.setFillColor(sf::Color::White);
            countdown.setPosition(600,820);
            int start_min = start_time.tm_min;
            int start_sec = start_time.tm_sec;
            int total_start = (start_min * 60) + start_sec;
            int time_left = countdown_timer(window,countdown,total_start);

            if(time_left <= 0){
                window.clear();
                sf::Text game_over;
                game_over.setFont(font);
                game_over.setFillColor(sf::Color::White);
                game_over.setPosition(450,420);
                game_over.setCharacterSize(50);
                game_over.setString("Game Over!");
                window.draw(game_over);
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