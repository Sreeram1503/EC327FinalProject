#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <ctime>
#include <thread>
#include <math.h>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <thread>
#include <vector>
#include <random>

using std::string;
using std::thread;
using std::to_string;
using std::vector;
std::random_device rd;
std::mt19937 g(rd()); 

struct Pair {
    std::string questions;
    std::string answers;
};


class MemoryGame {
public: 
    MemoryGame() : window(sf::VideoMode(1050,850), "Memory Game") {
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

        // create cards for questions + answers -> make this into a loop to save space 
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
    } 
}; 

//translate map to sfml
void createmap(sf::RenderWindow& window){
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

    window.display();
}

void randomizecards(sf::RenderWindow& window, sf::Text flipcard){
    vector<int> x_rand {1,2,3,4};
    std::shuffle (x_rand.begin(), x_rand.end(), g);

    vector<int> y_rand {1,2,3,4};
    std::shuffle (y_rand.begin(), y_rand.end(), g);

   struct Pair {
        std::string questions;
        std::string answers;
    };

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

    flipcard.setString(ques_factorial); //string would be actual question
    flipcard.setFillColor(sf::Color::White);
    flipcard.setOutlineThickness(1);
    flipcard.setPosition((x_rand.at(0)*150) + 50 , (y_rand.at(0)*100) + 50);
    flipcard.setCharacterSize(50);

    flipcard.setString(ans_factorial); //string would be actual question
    flipcard.setFillColor(sf::Color::White);
    flipcard.setOutlineThickness(1);
    flipcard.setPosition((x_rand.at(0)*150) + 50 , (y_rand.at(1)*100) + 50);
    flipcard.setCharacterSize(50);

    flipcard.setString(ques_deriv); //string would be actual question
    flipcard.setFillColor(sf::Color::White);
    flipcard.setOutlineThickness(1);
    flipcard.setPosition((x_rand.at(0)*150) + 50 , (y_rand.at(2)*100) + 50);
    flipcard.setCharacterSize(50);

    flipcard.setString(ans_deriv); //string would be actual question
    flipcard.setFillColor(sf::Color::White);
    flipcard.setOutlineThickness(1);
    flipcard.setPosition((x_rand.at(0)*150) + 50 , (y_rand.at(3)*100) + 50);
    flipcard.setCharacterSize(50);

    flipcard.setString(ques_radius); //string would be actual question
    flipcard.setFillColor(sf::Color::White);
    flipcard.setOutlineThickness(1);
    flipcard.setPosition((x_rand.at(1)*150) + 50 , (y_rand.at(0)*100) + 50);
    flipcard.setCharacterSize(50);

    flipcard.setString(ans_radius); //string would be actual question
    flipcard.setFillColor(sf::Color::White);
    flipcard.setOutlineThickness(1);
    flipcard.setPosition((x_rand.at(1)*150) + 50 , (y_rand.at(1)*100) + 50);
    flipcard.setCharacterSize(50);

    flipcard.setString(ques_hypo); //string would be actual question
    flipcard.setFillColor(sf::Color::White);
    flipcard.setOutlineThickness(1);
    flipcard.setPosition((x_rand.at(1)*150) + 50 , (y_rand.at(2)*100) + 50);
    flipcard.setCharacterSize(50);

    flipcard.setString(ans_hypo); //string would be actual question
    flipcard.setFillColor(sf::Color::White);
    flipcard.setOutlineThickness(1);
    flipcard.setPosition((x_rand.at(1)*150) + 50 , (y_rand.at(3)*100) + 50);
    flipcard.setCharacterSize(50);

    flipcard.setString(ques_sin); //string would be actual question
    flipcard.setFillColor(sf::Color::White);
    flipcard.setOutlineThickness(1);
    flipcard.setPosition((x_rand.at(2)*150) + 50 , (y_rand.at(0)*100) + 50);
    flipcard.setCharacterSize(50);

    flipcard.setString(ans_sin); //string would be actual question
    flipcard.setFillColor(sf::Color::White);
    flipcard.setOutlineThickness(1);
    flipcard.setPosition((x_rand.at(2)*150) + 50 , (y_rand.at(1)*100) + 50);
    flipcard.setCharacterSize(50);

    flipcard.setString(ques_tan); //string would be actual question
    flipcard.setFillColor(sf::Color::White);
    flipcard.setOutlineThickness(1);
    flipcard.setPosition((x_rand.at(2)*150) + 50 , (y_rand.at(2)*100) + 50);
    flipcard.setCharacterSize(50);

    flipcard.setString(ans_tan); //string would be actual question
    flipcard.setFillColor(sf::Color::White);
    flipcard.setOutlineThickness(1);
    flipcard.setPosition((x_rand.at(2)*150) + 50 , (y_rand.at(3)*100) + 50);
    flipcard.setCharacterSize(50);

    flipcard.setString(ques_exp); //string would be actual question
    flipcard.setFillColor(sf::Color::White);
    flipcard.setOutlineThickness(1);
    flipcard.setPosition((x_rand.at(3)*150) + 50 , (y_rand.at(0)*100) + 50);
    flipcard.setCharacterSize(50);

    flipcard.setString(ans_exp); //string would be actual question
    flipcard.setFillColor(sf::Color::White);
    flipcard.setOutlineThickness(1);
    flipcard.setPosition((x_rand.at(3)*150) + 50 , (y_rand.at(1)*100) + 50);
    flipcard.setCharacterSize(50);

    flipcard.setString(ques_deg); //string would be actual question
    flipcard.setFillColor(sf::Color::White);
    flipcard.setOutlineThickness(1);
    flipcard.setPosition((x_rand.at(3)*150) + 50 , (y_rand.at(2)*100) + 50);
    flipcard.setCharacterSize(50);

    flipcard.setString(ans_deg); //string would be actual question
    flipcard.setFillColor(sf::Color::White);
    flipcard.setOutlineThickness(1);
    flipcard.setPosition((x_rand.at(3)*150) + 50 , (y_rand.at(3)*100) + 50);
    flipcard.setCharacterSize(50);
}

//function to flip card
void flipit(sf::RenderWindow& window, sf::Text flipcard, int X, int Y){
    randomizecards(window,flipcard);
    if(Y > 50 and Y < 150){
        if(X > 50 and X < 250){
            std::cout << "here \n";
            window.draw(flipcard);
            window.display();
        }
        if(X > 300 and X < 500){
            window.draw(flipcard);
            window.display();
        }
        if(X > 550 and X < 750){
            window.draw(flipcard);
            window.display();
        }
        if(X > 800 and X < 1000){
            window.draw(flipcard);
            window.display();
        }
    }
    else if(Y > 200 and Y < 350){
        if(X > 50 and X < 250){
            std::cout << "here \n";
            window.draw(flipcard);
            window.display();
        }
        if(X > 300 and X < 500){
            window.draw(flipcard);
            window.display();
        }
        if(X > 550 and X < 750){
            window.draw(flipcard);
            window.display();
        }
        if(X > 800 and X < 1000){
            window.draw(flipcard);
            window.display();
        }
    }
    else if(Y > 400 and Y < 550){
        if(X > 50 and X < 250){
            std::cout << "here \n";
            window.draw(flipcard);
            window.display();
        }
        if(X > 300 and X < 500){
            window.draw(flipcard);
            window.display();
        }
        if(X > 550 and X < 750){
            window.draw(flipcard);
            window.display();
        }
        if(X > 800 and X < 1000){
            window.draw(flipcard);
            window.display();
        }
    }
    else if(Y > 600 and Y < 750){
        if(X > 50 and X < 250){
            std::cout << "here \n";
            window.draw(flipcard);
            window.display();
        }
        if(X > 300 and X < 500){
            window.draw(flipcard);
            window.display();
        }
        if(X > 550 and X < 750){
            window.draw(flipcard);
            window.display();
        }
        if(X > 800 and X < 1000){
            window.draw(flipcard);
            window.display();
        }
    }
    
    //will show card for X seconds
    std::this_thread::sleep_for(std::chrono::seconds(5));
}

//function to come up with questions and randomize

void createquestion(){
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
}


int main(){

    sf::RenderWindow window(sf::VideoMode(1050,850),"Memory game");
    while (window.isOpen()){
        sf::Text flipcard;
        sf::Font font;
        font.loadFromFile("/Users/rupalisinha/Desktop/EC327/tuffy.ttf");
        flipcard.setFont(font); 
        flipcard.setFillColor(sf::Color::White);
        flipcard.setOutlineThickness(1);
        flipcard.setCharacterSize(50);
        sf::Event event;
        while (window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
            if(event.type == sf::Event::MouseButtonPressed){
                int m_pos_X = sf::Mouse::getPosition(window).x;
                int m_pos_Y = sf::Mouse::getPosition(window).y;
                flipit(window, flipcard, m_pos_X, m_pos_Y);
            }
        }
        window.clear();
        createmap(window);
    }
}