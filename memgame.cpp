#include<iostream>
#include<string>
#include<SFML/Graphics.hpp>
#include<chrono>
#include<ctime>
#include<thread>

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
    //example for now
    static int question = 0;
    question++;
    string str_ques = to_string(question);
    return str_ques;
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