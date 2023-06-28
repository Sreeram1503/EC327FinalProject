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
#include <thread>

using std::string;
using std::thread;
using std::to_string;
using std::vector;
std::random_device rd;
std::mt19937 g(rd()); 

 int get_time(int total_start){
        std::time_t time = std::time(NULL);
        std::tm current_time = *std::localtime(&time);
        int curr_min = current_time.tm_min;
        int curr_sec = current_time.tm_sec;
        int total_curr = (curr_min * 60) + curr_sec;
        int change = total_curr - total_start;
        int time_left = 180 - change;
        return time_left;
 }
 void countdown_timer(sf::RenderWindow& window,sf::Text countdown,int total_start){
        int time_left = get_time(total_start);
        int seconds = time_left % 60;
        int minutes = time_left / 60;
        if(seconds < 10){
            countdown.setString(std::to_string(minutes) + ":0" + std::to_string(seconds));
        }
        else{
            countdown.setString(std::to_string(minutes) + ":" + std::to_string(seconds));
        }
            
            window.draw(countdown);
}

void end_screen(sf::RenderWindow& window){
    window.clear();
    sf::Text won_game;
    sf::Font font;
    font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf");
    won_game.setFont(font);
    won_game.setString("You won!");
    won_game.setFillColor(sf::Color::White);
    won_game.setCharacterSize(50);
    won_game.setPosition(600,400);
}
void temp_cards(sf::RenderWindow& window,sf::Text card_one,sf::Text card_two){

    window.draw(card_one);
    window.draw(card_two);
    
    //pauses for 3 seconds so that user can see card is wrong
    std::this_thread::sleep_for(std::chrono::seconds(3));
} 


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

        vector<string> questions_answers = {
            ques_factorial,
            ques_deriv,
            ques_radius,
            ques_hypo,
            ques_sin,
            ques_tan,
            ques_exp,
            ques_deg,
            ans_factorial,
            ans_deriv,
            ans_radius,
            ans_hypo,
            ans_sin,
            ans_tan,
            ans_exp,
            ans_deg
        };


        std::vector<bool> cardFlipped(16, false);

        sf::Font font;
        if (!font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) {
            std::cerr << "Error loading font." << '\n';
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
    
    //instructions
            sf::Text instructions;
            instructions.setFont(font);
            instructions.setFillColor(sf::Color::White);
            instructions.setCharacterSize(35);
            instructions.setString("Flip over cards, 2 at a time to find a question and answer match");
            instructions.setPosition(50,900);

    //game lost new screen/restart button initializing 
            sf::Text game_over;
                game_over.setFont(font);
                game_over.setFillColor(sf::Color::White);
                game_over.setPosition(450,200);
                game_over.setCharacterSize(50);
                game_over.setString("Game Over!");
            sf::RectangleShape restart_button(sf::Vector2f(250,75));
                restart_button.setFillColor(sf::Color::White);
                restart_button.setPosition(450,375);
                sf::Text restart_words;
                restart_words.setFont(font);
                restart_words.setFillColor(sf::Color::Black);
                restart_words.setPosition(475,390);
                restart_words.setCharacterSize(50);
                restart_words.setString("Restart");

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

        vector<sf::RectangleShape> cards = {one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve, thirteen, fourteen, fifteen, sixteen};

        std::shuffle(questions_answers.begin(), questions_answers.end(), g);

        vector<sf::Text> questions_answers_text(16, text);
        //vector<sf::Text> answersText(8, text);

        for (int i = 0; i < 16; i++) {
            questions_answers_text[i].setString(questions_answers[i]);
            questions_answers_text[i].setPosition(cards[i].getPosition().x + 20.f, cards[i].getPosition().y + 20.f);
        }

        bool hasFlippedCard = false; // track if a card has been flipped

        //obtaining time window was opened for the countdown clock
        std::time_t time = std::time(NULL);
        std::tm start_time = *std::localtime(&time);

        //initializing count to check when the game is finished
        int match_count = 0;

        while (window.isOpen()) {

        //countdown timer
            sf::Text countdown;
            countdown.setFont(font);
            countdown.setFillColor(sf::Color::White);
            countdown.setPosition(600,820);
            int start_min = start_time.tm_min;
            int start_sec = start_time.tm_sec;
            int total_start = (start_min * 60) + start_sec;

             //getting time change to check if time has run out
            int time_left = get_time(total_start);

            //creating shape to restart the game if time runs out 
            sf::RectangleShape restart_button(sf::Vector2f(250,75));

            if(time_left <= 0){
                window.clear();
                sf::Text game_over;
                game_over.setFont(font);
                game_over.setFillColor(sf::Color::White);
                game_over.setPosition(450,200);
                game_over.setCharacterSize(50);
                game_over.setString("Game Over!");

                restart_button.setFillColor(sf::Color::White);
                restart_button.setPosition(450,375);
                sf::Text restart_words;
                restart_words.setFont(font);
                restart_words.setFillColor(sf::Color::Black);
                restart_words.setPosition(475,390);
                restart_words.setCharacterSize(50);
                restart_words.setString("Restart");
                window.draw(game_over);
                window.draw(restart_button);
                window.draw(restart_words);
            }

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
                                    continue; 
                                }

                                if (!cardFlipped[i]) {
                                    if (hasFlippedCard) {
                                        // Second card flipped, check for a match
                                        cardFlipped[i] = true;
                                        for (int i = 0; i < 8; i++) {
                                            if (questions_answers[i] == questions_answers[i+8]) {
                                                window.draw(questions_answers_text[i]); 
                                                window.draw(questions_answers_text[i+8]);
                                                match_count++;
                                                // Add logic here for handling a match
                                            }
                                            else{
                                                temp_cards(window,questions_answers_text.at(i),questions_answers_text.at(i+8));
                                            }
                                        }
                                        for (int i = 0; i < 16; i++) {
                                            window.draw(cards[i]);
                                        if (cardFlipped[i]) {
                                            if (i < 16) {
                                                window.draw(questions_answers_text[i]);
                                            }
                                        }
                                             }

                                            //counting matches to end game
                                            match_count++;
                                            if(match_count == 8){
                                                end_screen(window); // will clear window and display "You won!"
                                            }
                                        } else {
                                            // No match, implement logic here
                                        }
                                        hasFlippedCard = false; // Reset the flag
                                    } else {
                                        // First card flipped
                                        cardFlipped[i] = true;
                                        hasFlippedCard = true;
                                    }
                                }
                                break;
                            }
                        }
                int m_pos_X = sf::Mouse::getPosition(window).x;
                int m_pos_Y = sf::Mouse::getPosition(window).y;
                        if(time_left <= 0 and m_pos_X > 450 and m_pos_X < 700 and m_pos_Y > 375 and m_pos_Y < 450){
                            MemoryGame game;
                        }
                    }
                }
            

            window.clear();

            for (int i = 0; i < 16; i++) {
                window.draw(cards[i]);
             if (cardFlipped[i]) {
                if (i < 16) {
                    window.draw(questions_answers_text[i]);
                //} else {
                    //window.draw(answersText[i]);
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