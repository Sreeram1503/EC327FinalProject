#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Sleep.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>

// Window dimensions
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Paddle dimensions
const float PADDLE_WIDTH = 20.0f;
const float PADDLE_HEIGHT = 100.0f;
const float PADDLE_SPEED = 400.0f;

// Ball dimensions and initial velocity
const float BALL_RADIUS = 10.0f;
const float BALL_VELOCITY_X = 300.0f;
const float BALL_VELOCITY_Y = 200.0f;

// Font for displaying text
sf::Font font;

// Function to generate a random math question
std::string generateMathQuestion()
{
    int num1 = rand() % 10;
    int num2 = rand() % 10;
    int operatorIndex = rand() % 4;
    std::string question;

    switch (operatorIndex)
    {
        case 0: // Addition
            question = std::to_string(num1) + " + " + std::to_string(num2);
            break;
        case 1: // Subtraction
            question = std::to_string(num1) + " - " + std::to_string(num2);
            break;
        case 2: // Multiplication
            question = std::to_string(num1) + " * " + std::to_string(num2);
            break;
        case 3: // Division
            question = std::to_string(num1 * num2) + " / " + std::to_string(num2);
            break;
    }

    return question;
}

int main()
{
    // Initialize random seed
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Create the game window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Math Pong Game");

    // Load font
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Failed to load font." << std::endl;
        return 1;
    }

    // Create the paddles
    sf::RectangleShape paddle1(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
    sf::RectangleShape paddle2(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));

    // Set initial paddle positions
    paddle1.setPosition(10.0f, WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2);
    paddle2.setPosition(WINDOW_WIDTH - PADDLE_WIDTH - 10.0f, WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2);

    // Create the ball
    sf::CircleShape ball(BALL_RADIUS);
    ball.setPosition(WINDOW_WIDTH / 2 - BALL_RADIUS, WINDOW_HEIGHT / 2 - BALL_RADIUS);
    sf::Vector2f ballVelocity(BALL_VELOCITY_X, BALL_VELOCITY_Y);

    sf::Clock clock;
    bool questionDisplayed = false;
    std::string currentQuestion;
    sf::Text questionText;
    questionText.setFont(font);
    questionText.setCharacterSize(30);
    questionText.setFillColor(sf::Color::White);

    int player1Score = 0;
    int player2Score = 0;
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::White);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time deltaTime = clock.restart();

        // Move the paddles
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && paddle1.getPosition().y > 0)
            paddle1.move(0, -PADDLE_SPEED * deltaTime.asSeconds());
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && paddle1.getPosition().y + PADDLE_HEIGHT < WINDOW_HEIGHT)
            paddle1.move(0, PADDLE_SPEED * deltaTime.asSeconds());
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && paddle2.getPosition().y > 0)
            paddle2.move(0, -PADDLE_SPEED * deltaTime.asSeconds());
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && paddle2.getPosition().y + PADDLE_HEIGHT < WINDOW_HEIGHT)
            paddle2.move(0, PADDLE_SPEED * deltaTime.asSeconds());

        // Check if the question is displayed and wait for player's input
        if (!questionDisplayed)
        {
            currentQuestion = generateMathQuestion();
            questionText.setString("Question: " + currentQuestion);
            questionText.setPosition(WINDOW_WIDTH / 2 - questionText.getGlobalBounds().width / 2, 10.0f);
            questionDisplayed = true;
        }
        else
        {
            std::string answerString;
            bool answerEntered = false;

            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::TextEntered)
                {
                    if (event.text.unicode == '\b' && answerString.size() > 0)
                        answerString.pop_back();
                    else if (event.text.unicode >= '0' && event.text.unicode <= '9')
                        answerString += static_cast<char>(event.text.unicode);
                    else if (event.text.unicode == '\r' || event.text.unicode == '\n')
                        answerEntered = true;
                }
            }

            if (answerEntered)
            {
                int playerAnswer = std::stoi(answerString);
                int correctAnswer;

                // Calculate the correct answer based on the current question
                std::istringstream questionStream(currentQuestion);
                int num1, num2;
                char op;
                questionStream >> num1 >> op >> num2;
                switch (op)
                {
                    case '+':
                        correctAnswer = num1 + num2;
                        break;
                    case '-':
                        correctAnswer = num1 - num2;
                        break;
                    case '*':
                        correctAnswer = num1 * num2;
                        break;
                    case '/':
                        correctAnswer = num1;
                        break;
                }

                if (playerAnswer == correctAnswer)
                {
                    // Player answered correctly, allow hitting the ball
                    ballVelocity.x = -ballVelocity.x;
                    questionDisplayed = false;
                }
            }
        }

        // Move the ball
        ball.move(ballVelocity.x * deltaTime.asSeconds(), ballVelocity.y * deltaTime.asSeconds());

        // Ball collision with paddles
        if (ball.getPosition().y < 0 || ball.getPosition().y + BALL_RADIUS * 2 > WINDOW_HEIGHT)
            ballVelocity.y = -ballVelocity.y;

        // Check collision with paddles
        if (ball.getGlobalBounds().intersects(paddle1.getGlobalBounds()) ||
            ball.getGlobalBounds().intersects(paddle2.getGlobalBounds()))
        {
            ballVelocity.x = -ballVelocity.x;
        }

        // Ball collision with walls
        if (ball.getPosition().x < 0)
        {
            // Player 2 scores a point
            // Reset ball position and velocity
            ball.setPosition(WINDOW_WIDTH / 2 - BALL_RADIUS, WINDOW_HEIGHT / 2 - BALL_RADIUS);
            ballVelocity.x = BALL_VELOCITY_X;
            ballVelocity.y = BALL_VELOCITY_Y;
            player2Score++;
        }
        else if (ball.getPosition().x + BALL_RADIUS * 2 > WINDOW_WIDTH)
        {
            // Player 1 scores a point
            // Reset ball position and velocity
            ball.setPosition(WINDOW_WIDTH / 2 - BALL_RADIUS, WINDOW_HEIGHT / 2 - BALL_RADIUS);
            ballVelocity.x = -BALL_VELOCITY_X;
            ballVelocity.y = -BALL_VELOCITY_Y;
            player1Score++;
        }

        // Update score text
        std::string scoreString = "Player 1: " + std::to_string(player1Score) + "   Player 2: " + std::to_string(player2Score);
        scoreText.setString(scoreString);
        scoreText.setPosition(WINDOW_WIDTH / 2 - scoreText.getGlobalBounds().width / 2, 40.0f);

        // Clear the window
        window.clear();

        // Draw the paddles, ball, question, and score
        window.draw(paddle1);
        window.draw(paddle2);
        window.draw(ball);
        window.draw(questionText);
        window.draw(scoreText);

        // Display the updated window
        window.display();

        // Add a delay to control the game's speed
        sf::sleep(sf::milliseconds(10));
    }

    return 0;
}
