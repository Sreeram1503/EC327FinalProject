#include<iostream>
#include<string>
#include<SFML/Graphics.hpp>
#include<chrono>
#include<ctime>
#include<thread>
#include<math.h>
#include<algorithm>
#include<vector>
#include<cstdlib>

using std::string;
using std::thread;
using std::to_string;
using std::vector;
using std::cout;

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

void randomizecards(sf::RenderWindow& window, sf::Text fact, sf::Text fact_answer, sf::Text deriv, sf::Text deriv_answer,
 sf::Text circle, sf::Text circle_answer, sf::Text hypot, sf::Text hypot_answer, sf::Text sin, sf::Text sin_answer,
 sf::Text tan, sf::Text tan_answer, sf::Text degrees, sf::Text degrees_answer, sf::Text exponent, sf::Text exponent_answer,
 int m_pos_X, int m_pos_Y){
    vector<int> Xrand {1,2,3,4};
    std::random_shuffle(Xrand.begin(),Xrand.end());
    vector<int> Yrand {1,2,3,4};
    std::random_shuffle(Yrand.begin(),Yrand.end());
    
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
    int expo = b_rand;
    int deriv_ans = b_rand * pow(2,b_rand-1);
    //(d/dx)x^rand where x=2
    string ques_deriv = "(d/dx) of x ^ " + to_string(expo) + "where x = 2";
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

//set random positions
    fact.setString(ques_factorial); 
    fact.setPosition((Xrand.at(0)*150) + 50 , (Yrand.at(0)*100) + 50);
    int X_ques_factorial = (Xrand.at(0)*150) + 50;
    int Y_ques_factorial = (Yrand.at(0)*100) + 50;
    cout << X_ques_factorial << '\n' << Y_ques_factorial << '\n';

    fact_answer.setString(ans_factorial); 
    fact_answer.setPosition((Xrand.at(0)*150) + 50 , (Yrand.at(1)*100) + 50);
    int X_fact_answer = (Xrand.at(0)*150) + 50;
    int Y_fact_answer = (Yrand.at(1)*100) + 50;

    deriv.setString(ques_deriv); 
    deriv.setPosition((Xrand.at(0)*150) + 50 , (Yrand.at(2)*100) + 50);
    int X_ques_derivative = (Xrand.at(0)*150) + 50;
    int Y_ques_derivative = (Yrand.at(2)*100) + 50;

    deriv_answer.setString(ans_deriv); 
    deriv_answer.setPosition((Xrand.at(0)*150) + 50 , (Yrand.at(3)*100) + 50);
    int X_ans_deriv = (Xrand.at(0)*150) + 50;
    int Y_ans_deriv = (Yrand.at(3)*100) + 50;

    circle.setString(ques_radius); 
    circle.setPosition((Xrand.at(1)*150) + 50 , (Yrand.at(0)*100) + 50);
    int X_ques_radius = (Xrand.at(1)*150) + 50;
    int Y_ques_radius = (Yrand.at(0)*100) + 50;

    circle_answer.setString(ans_radius); 
    circle_answer.setPosition((Xrand.at(1)*150) + 50 , (Yrand.at(1)*100) + 50);
    int X_ans_radius = (Xrand.at(1)*150) + 50;
    int Y_ans_radius = (Yrand.at(1)*100) + 50;

    hypot.setString(ques_hypo); 
    hypot.setPosition((Xrand.at(1)*150) + 50 , (Yrand.at(2)*100) + 50);
    int X_ques_hypo = (Xrand.at(1)*150) + 50;
    int Y_ques_hypo = (Yrand.at(2)*100) + 50;

    hypot_answer.setString(ans_hypo); 
    hypot_answer.setPosition((Xrand.at(1)*150) + 50 , (Yrand.at(3)*100) + 50);
    int X_ans_hypo = (Xrand.at(1)*150) + 50;
    int Y_ans_hypo = (Yrand.at(3)*100) + 50;

    sin.setString(ques_sin); 
    sin.setPosition((Xrand.at(2)*150) + 50 , (Yrand.at(0)*100) + 50);
    int X_ques_sin = (Xrand.at(2)*150) + 50;
    int Y_ques_sin = (Yrand.at(0)*100) + 50;

    sin_answer.setString(ans_sin); 
    sin_answer.setPosition((Xrand.at(2)*150) + 50 , (Yrand.at(1)*100) + 50);


    tan.setString(ques_tan); 
    tan.setPosition((Xrand.at(2)*150) + 50 , (Yrand.at(2)*100) + 50);

    tan_answer.setString(ans_tan); 
    tan_answer.setPosition((Xrand.at(2)*150) + 50 , (Yrand.at(3)*100) + 50);

    degrees.setString(ques_exp); 
    degrees.setPosition((Xrand.at(3)*150) + 50 , (Yrand.at(0)*100) + 50);

    degrees_answer.setString(ans_exp); 
    degrees_answer.setPosition((Xrand.at(3)*150) + 50 , (Yrand.at(1)*100) + 50);

    exponent.setString(ques_deg); 
    exponent.setPosition((Xrand.at(3)*150) + 50 , (Yrand.at(2)*100) + 50);

    exponent_answer.setString(ans_deg); 
    exponent_answer.setPosition((Xrand.at(3)*150) + 50 , (Yrand.at(3)*100) + 50);

    if(X_ques_factorial == m_pos_X and Y_ques_factorial == m_pos_Y){
        window.draw(fact);
        window.display();
    }
    else if(X_fact_answer == m_pos_X and Y_fact_answer == m_pos_Y){
        window.draw(fact_answer);
        window.display();
    }
    else if(X_ques_derivative == m_pos_X and Y_ques_derivative == m_pos_Y){
        window.draw(deriv);
        window.display();
    }
    else if(X_ques_derivative == m_pos_X and Y_ques_derivative == m_pos_Y){
        window.draw(deriv);
        window.display();
    }
    else if(X_ans_deriv == m_pos_X and Y_ans_deriv == m_pos_Y){
        window.draw(deriv_answer);
        window.display();
    }
    else if(X_ques_radius == m_pos_X and Y_ques_radius == m_pos_Y){
        window.draw(circle);
        window.display();
    }
    else if(X_ans_radius == m_pos_X and Y_ans_radius == m_pos_Y){
        window.draw(circle_answer);
        window.display();
    }
}
//function to flip card

void flipit(sf::RenderWindow& window, sf::Text fact, sf::Text fact_answer, sf::Text deriv, sf::Text deriv_answer,
 sf::Text circle, sf::Text circle_answer, sf::Text hypot, sf::Text hypot_answer, sf::Text sin, sf::Text sin_answer,
 sf::Text tan, sf::Text tan_answer, sf::Text degrees, sf::Text degrees_answer, sf::Text exponent, 
 sf::Text exponent_answer,int X, int Y){
   // randomizecards(window,fact,fact_answer,deriv,deriv_answer,circle,
      //          circle_answer,hypot,hypot_answer,sin,sin_answer,tan,
      //          tan_answer,degrees,degrees_answer,exponent,exponent_answer,m_pos_X,m_pos_Y);
    
    
    if(Y > 50 and Y < 150){
        if(X > 50 and X < 250){
            std::cout << "here \n";
            window.display();
        }
        if(X > 300 and X < 500){
            window.display();
        }
        if(X > 550 and X < 750){
            window.display();
        }
        if(X > 800 and X < 1000){
            window.display();
        }
    }
    else if(Y > 200 and Y < 350){
        if(X > 50 and X < 250){
            std::cout << "here \n";
            window.display();
        }
        if(X > 300 and X < 500){
            window.display();
        }
        if(X > 550 and X < 750){
            window.display();
        }
        if(X > 800 and X < 1000){
            window.display();
        }
    }
    else if(Y > 400 and Y < 550){
        if(X > 50 and X < 250){
            std::cout << "here \n";
            window.display();
        }
        if(X > 300 and X < 500){
            window.display();
        }
        if(X > 550 and X < 750){
            window.display();
        }
        if(X > 800 and X < 1000){
            window.display();
        }
    }
    else if(Y > 600 and Y < 750){
        if(X > 50 and X < 250){
            std::cout << "here \n";
            window.display();
        }
        if(X > 300 and X < 500){
            window.display();
        }
        if(X > 550 and X < 750){
            window.display();
        }
        if(X > 800 and X < 1000){
            window.display();
        }
    }
    
    //will show card for X seconds
    std::this_thread::sleep_for(std::chrono::seconds(5));
}
//function to come up with questions and randomize

int main(){

    sf::RenderWindow window(sf::VideoMode(1050,850),"Memory game");
    while (window.isOpen()){
        sf::Text fact;
        sf::Font font;
        font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf");
        fact.setFont(font); 
        fact.setFillColor(sf::Color::White);
        fact.setOutlineThickness(1);
        fact.setCharacterSize(50);
        //window.draw(fact);

        sf::Text fact_answer;
        fact_answer.setFont(font); 
        fact_answer.setFillColor(sf::Color::White);
        fact_answer.setOutlineThickness(1);
        fact_answer.setCharacterSize(50);
        window.draw(fact_answer);

        sf::Text deriv;
        deriv.setFont(font); 
        deriv.setFillColor(sf::Color::White);
        deriv.setOutlineThickness(1);
        deriv.setCharacterSize(50);
        window.draw(deriv);

        sf::Text deriv_answer;
        deriv_answer.setFont(font); 
        deriv_answer.setFillColor(sf::Color::White);
        deriv_answer.setOutlineThickness(1);
        deriv_answer.setCharacterSize(50);
        window.draw(deriv_answer);

        sf::Text circle;
        circle.setFont(font); 
        circle.setFillColor(sf::Color::White);
        circle.setOutlineThickness(1);
        circle.setCharacterSize(50);
        window.draw(circle);

        sf::Text circle_answer;
        circle_answer.setFont(font); 
        circle_answer.setFillColor(sf::Color::White);
        circle_answer.setOutlineThickness(1);
        circle_answer.setCharacterSize(50);
        window.draw(circle_answer);

        sf::Text hypot;
        hypot.setFont(font); 
        hypot.setFillColor(sf::Color::White);
        hypot.setOutlineThickness(1);
        hypot.setCharacterSize(50);
        window.draw(hypot);

        sf::Text hypot_answer;
        hypot_answer.setFont(font); 
        hypot_answer.setFillColor(sf::Color::White);
        hypot_answer.setOutlineThickness(1);
        hypot_answer.setCharacterSize(50);
        window.draw(hypot_answer);

        sf::Text sin;
        sin.setFont(font); 
        sin.setFillColor(sf::Color::White);
        sin.setOutlineThickness(1);
        sin.setCharacterSize(50);
        window.draw(sin);

        sf::Text sin_answer;
        sin_answer.setFont(font); 
        sin_answer.setFillColor(sf::Color::White);
        sin_answer.setOutlineThickness(1);
        sin_answer.setCharacterSize(50);
        window.draw(sin_answer);

        sf::Text tan;
        tan.setFont(font); 
        tan.setFillColor(sf::Color::White);
        tan.setOutlineThickness(1);
        tan.setCharacterSize(50);
        window.draw(tan);

        sf::Text tan_answer;
        tan_answer.setFont(font); 
        tan_answer.setFillColor(sf::Color::White);
        tan_answer.setOutlineThickness(1);
        tan_answer.setCharacterSize(50);
        window.draw(tan_answer);

        sf::Text degrees;
        degrees.setFont(font); 
        degrees.setFillColor(sf::Color::White);
        degrees.setOutlineThickness(1);
        degrees.setCharacterSize(50);
        window.draw(degrees);

        sf::Text degrees_answer;
        degrees_answer.setFont(font); 
        degrees_answer.setFillColor(sf::Color::White);
        degrees_answer.setOutlineThickness(1);
        degrees_answer.setCharacterSize(50);
        window.draw(degrees_answer);

        sf::Text exponent;
        exponent.setFont(font); 
        exponent.setFillColor(sf::Color::White);
        exponent.setOutlineThickness(1);
        exponent.setCharacterSize(50);
        window.draw(exponent);

        sf::Text exponent_answer;
        exponent_answer.setFont(font); 
        exponent_answer.setFillColor(sf::Color::White);
        exponent_answer.setOutlineThickness(1);
        exponent_answer.setCharacterSize(50);
        window.draw(exponent_answer);

        sf::Event event;
        while (window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
            if(event.type == sf::Event::MouseButtonPressed){
                int m_pos_X = sf::Mouse::getPosition(window).x;
                int m_pos_Y = sf::Mouse::getPosition(window).y;
                randomizecards(window,fact,fact_answer,deriv,deriv_answer,circle,
                circle_answer,hypot,hypot_answer,sin,sin_answer,tan,
                tan_answer,degrees,degrees_answer,exponent,exponent_answer,m_pos_X, m_pos_Y);
            }
        }
        window.clear();
        createmap(window);
    }
}