#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <ctime>
#include <math.h>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <random>

using std::string;
using std::thread;
using std::to_string;
using std::vector;
std::random_device rd;
std::mt19937 g(rd()); 

class MemoryGame {
public: 
    MemoryGame() { 
        sf::RenderWindow window(sf::VideoMode(1050, 850), "Memory Game"); 

        // generate random numbers for questions 
        
        //generate random numbers
        int a_rand = rand() % 11;
        int b_rand = rand() % 5;
        int c_rand = rand() % 11;

        //question 1: factorial
        int factorial = 1;
        for(int i = 1; i <= a_rand; i++){
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



        srand(time(0)); 

        vector<string> questions = {
            ques_factorial,
            ques_deriv,
            ques_radius,
            ques_hypo,
            ques_sin,
            ques_tan,
            ques_exp,
            ques_deg
        };

        vector<string> answers = {
            ans_factorial,
            ans_deriv,
            ans_radius,
            ans_hypo,
            ans_sin,
            ans_tan,
            ans_exp,
            ans_deg
        };

        std::vector<bool> cardFlipped(8, false);

        sf::Font font;
        if (!font.loadFromFile("/Users/rupalisinha/Desktop/EC327/tuffy.ttf")) {
            std::cerr << "Error loading font." << std::endl;
            return;
        }

        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);

        // creating cards to display 
        sf::RectangleShape one(sf::Vector2f(200,150));
        one.setPosition(50,50);
        one.setFillColor(sf::Color::Blue);

        sf::RectangleShape two(sf::Vector2f(200,150));
        two.setPosition(300,50);
        two.setFillColor(sf::Color::Blue);

        sf::RectangleShape three(sf::Vector2f(200,150));
        three.setPosition(550,50);
        three.setFillColor(sf::Color::Blue);

        sf::RectangleShape four(sf::Vector2f(200,150));
        four.setPosition(800,50);
        four.setFillColor(sf::Color::Blue);

        sf::RectangleShape five(sf::Vector2f(200,150));
        five.setPosition(50,250);
        five.setFillColor(sf::Color::Blue);

        sf::RectangleShape six(sf::Vector2f(200,150));
        six.setPosition(300,250);
        six.setFillColor(sf::Color::Blue);

        sf::RectangleShape seven(sf::Vector2f(200,150));
        seven.setPosition(550,250);
        seven.setFillColor(sf::Color::Blue);

        sf::RectangleShape eight(sf::Vector2f(200,150));
        eight.setPosition(800,250);
        eight.setFillColor(sf::Color::Blue);
    
        sf::RectangleShape nine(sf::Vector2f(200,150));
        nine.setPosition(50,450);
        nine.setFillColor(sf::Color::Blue);

        sf::RectangleShape ten(sf::Vector2f(200,150));
        ten.setPosition(300,450);
        ten.setFillColor(sf::Color::Blue);

        sf::RectangleShape eleven(sf::Vector2f(200,150));
        eleven.setPosition(550,450);
        eleven.setFillColor(sf::Color::Blue);

        sf::RectangleShape twelve(sf::Vector2f(200,150));
        twelve.setPosition(800,450);
        twelve.setFillColor(sf::Color::Blue);

        sf::RectangleShape thirteen(sf::Vector2f(200,150));
        thirteen.setPosition(50,650);
        thirteen.setFillColor(sf::Color::Blue);

        sf::RectangleShape fourteen(sf::Vector2f(200,150));
        fourteen.setPosition(300,650);
        fourteen.setFillColor(sf::Color::Blue);

        sf::RectangleShape fifteen(sf::Vector2f(200,150));
        fifteen.setPosition(550,650);
        fifteen.setFillColor(sf::Color::Blue);

        sf::RectangleShape sixteen(sf::Vector2f(200,150));
        sixteen.setPosition(800,650);
        sixteen.setFillColor(sf::Color::Blue);
    
        window.clear();

        window.draw(one);
        window.draw(two);
        window.draw(three);
        window.draw(four);
        window.draw(five);
        window.draw(six);
        window.draw(seven);
        window.draw(eight);
        window.draw(nine);
        window.draw(ten);
        window.draw(eleven);
        window.draw(twelve);
        window.draw(thirteen);
        window.draw(fourteen);
        window.draw(fifteen);
        window.draw(sixteen);

        vector<sf::RectangleShape> cards = { one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve, thirteen, fourteen, fifteen, sixteen };

        std::shuffle(questions.begin(), questions.end(), g);

        vector<sf::Text> questionsText(8, text);
        vector<sf::Text> answersText(8, text);

        for (int i = 0; i < 8; i++) {
            questionsText[i].setString(questions[i]);
            questionsText[i].setPosition(cards[i].getPosition().x + 20.f, cards[i].getPosition().y + 20.f);
            answersText[i].setString(answers[i]);
            answersText[i].setPosition(cards[i + 8].getPosition().x + 20.f, cards[i + 8].getPosition().y + 20.f);
        }

        bool hasFlippedCard = false; // Flag to track if a card has been flipped
        int flippedCardIndex; // Index of the first flipped card

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                        for (int i = 0; i < 16; i++) {
                            if (cards[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
                                if (i >= 8) {
                                    if (!cardFlipped[i]) {
                                        cardFlipped[i] = true;
                                    }
                                    continue; // Skip processing other events
                                }

                                if (!cardFlipped[i]) {
                                    if (hasFlippedCard) {
                                        // Second card flipped, check for a match
                                        cardFlipped[i] = true;
                                        if (questions[i] == questions[flippedCardIndex]) {
                                            // Match found
                                            // Add your logic here for handling a match
                                        } else {
                                            // No match, implement your logic here
                                        }
                                        hasFlippedCard = false; // Reset the flag
                                    } else {
                                        // First card flipped
                                        cardFlipped[i] = true;
                                        hasFlippedCard = true;
                                        flippedCardIndex = i;
                                    }
                                }
                                break;
                            }
                        }
                    }
                }
            }

            window.clear();

            for (int i = 0; i < 16; i++) {
                window.draw(cards[i]);
             if (cardFlipped[i]) {
                if (i < 8) {
                    window.draw(questionsText[i]);
                } else {
                    window.draw(answersText[i]);
                }
            }
        }


            window.display();
        }
    }
};

int main() {
    MemoryGame game;
    return 0;
}