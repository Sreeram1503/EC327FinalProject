#include<iostream>
#include<string>
#include<SFML/Graphics.hpp>
#include<chrono>
#include<ctime>
#include<thread>
#include<math.h>

using std::string;
using std::thread;
using std::to_string;
//function to create the questions 
    //are we creating questions or randomized?
    //create questions but numbers are randomized?
    //place questions on a map

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
    
    window.clear();

    window.draw(one);
    window.draw(two);
    window.draw(three);
    window.draw(four);
    window.display();
}


//function to flip card

void flipcard(sf::RenderWindow& window, int X, int Y){
    
    sf::Text flipcard;
    sf::Font font;
    font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf");
    flipcard.setFont(font);
    
    if(Y > 50 and Y < 150){
        if(X > 50 and X < 250){
            std::cout << "here \n";
            flipcard.setString("1"); //string would be actual question
            flipcard.setFillColor(sf::Color::White);
            flipcard.setOutlineThickness(1);
            flipcard.setPosition(150,100);
            flipcard.setCharacterSize(50);
            window.draw(flipcard);
            window.display();
        }
        if(X > 300 and X < 500){
            flipcard.setString("2"); //string would be actual question
            flipcard.setFillColor(sf::Color::White);
            flipcard.setOutlineThickness(1);
            flipcard.setPosition(400,100);
            flipcard.setCharacterSize(50);
            window.draw(flipcard);
            window.display();
        }
        if(X > 550 and X < 750){

        }
        if(X > 800 and X < 1000){

        }
    }
    else if(Y > 200 and Y < 350){
        //add x coordinates
    }
    
    //will show card for X seconds
    std::this_thread::sleep_for(std::chrono::seconds(5));
}
//function to come up with questions and randomize

string createquestion(){
    //generate random numbers
    a_rand = rand() % 11;
    b_rand = rand() % 5;
    c_rand = rand() % 11;

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
    float circle_ans = pow(c_rand,2) * 3.14
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


void randquestion(sf::RenderWindow& window){
    //will set question to specific coordinates
    
}


int main(){

    sf::RenderWindow window(sf::VideoMode(1050,800),"Memory game");
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
            if(event.type == sf::Event::MouseButtonPressed){
                int m_pos_X = sf::Mouse::getPosition(window).x;
                int m_pos_Y = sf::Mouse::getPosition(window).y;
                flipcard(window, m_pos_X, m_pos_Y);
            }
        }
        window.clear();
        createmap(window);
    }
}