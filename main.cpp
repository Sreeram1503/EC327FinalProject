#include <SFML/Graphics.hpp>
#include <iostream>
#include "FirstScreen.h" 

class Level1Screen
{
public:
    Level1Screen(sf::RenderWindow& window, int& activeScreen)
        : window(window), activeScreen(activeScreen)
    {
        // Load font for question and answer text
        if (!font.loadFromFile("myfnt.ttf")) {
            std::cout << "Error: Failed to load font\n";
        }

        // Create question rectangles
        createQuestionRectangles();

        // Set up answer texts
        setupAnswerTexts();

        // Set up correct answers
        setupCorrectAnswers();
    }

    void handleEvent(const sf::Event& event)
    {
        if (event.type == sf::Event::MouseButtonReleased)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                // Check if mouse click is inside any of the answer rectangles
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                for (size_t i = 0; i < answerRectangles.size(); ++i)
                {
                    if (answerRectangles[i].getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
                    {
                        // Check if the clicked answer is correct
                        if (i < correctAnswers.size() && correctAnswers[i])
                        {
                            // Mark the answer as correct and change its color to green
                            answerTexts[i].setFillColor(sf::Color::Green);
                            // Move to the next question if all answers are correct
                            if (checkAllAnswersCorrect())
                            {
                                activeScreen = 3; // Transition to the blank screen (activeScreen set to 3)
                            }
                        }
                        else
                        {
                            // Mark the answer as incorrect and change its color to red
                            answerTexts[i].setFillColor(sf::Color::Red);
                        }
                    }
                }
            }
        }
    }

    void update()
    {
        // Add any necessary update logic for the level 1 screen here
    }

    void render()
    {
        // Draw the question rectangles
        for (size_t i = 0; i < questionRectangles.size(); ++i)
        {
            window.draw(questionRectangles[i]);
        }

        // Draw the question texts
        for (size_t i = 0; i < questionTexts.size(); ++i)
        {
            window.draw(questionTexts[i]);
        }

        // Draw the answer rectangles
        for (size_t i = 0; i < answerRectangles.size(); ++i)
        {
            window.draw(answerRectangles[i]);
        }

        // Draw the answer texts
        for (size_t i = 0; i < answerTexts.size(); ++i)
        {
            window.draw(answerTexts[i]);
        }
    }

private:
    sf::RenderWindow& window;
    int& activeScreen;
    sf::Font font;

    std::vector<sf::RectangleShape> questionRectangles;
    std::vector<sf::Text> questionTexts;

    std::vector<sf::RectangleShape> answerRectangles;
    std::vector<sf::Text> answerTexts;

    std::vector<bool> correctAnswers;

    void createQuestionRectangles()
    {
        // Define the position and size of the question rectangles
        sf::Vector2f rectSize(500, 50);
        sf::Vector2f rectPosition(window.getSize().x / 2 - rectSize.x / 2, 100);

        // Create the question rectangles
        for (size_t i = 0; i < 5; ++i)
        {
            sf::RectangleShape rect(rectSize);
            rect.setPosition(rectPosition.x, rectPosition.y + (i * 100));
            rect.setFillColor(sf::Color::White);
            rect.setOutlineThickness(2);
            rect.setOutlineColor(sf::Color::Black);
            questionRectangles.push_back(rect);
        }
    }

    void setupAnswerTexts()
    {
        // Define the font size for the answer texts
        unsigned int fontSize = 30;

        // Create the answer texts
        for (size_t i = 0; i < 5; ++i)
        {
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(fontSize);
            text.setFillColor(sf::Color::Black);
            text.setPosition(questionRectangles[i].getPosition().x + 10, questionRectangles[i].getPosition().y + 10);
            answerTexts.push_back(text);
        }

        // Set the question texts for the level 1 problems
        questionTexts.push_back(createQuestionText("Solve for x: 2x + 5 = 15"));
        questionTexts.push_back(createQuestionText("Solve for d: 6d + 9 = 45"));
        questionTexts.push_back(createQuestionText("Solve for y: 4y + 2 = 18"));
        questionTexts.push_back(createQuestionText("Solve for p: 3p + 7 = 22"));
        questionTexts.push_back(createQuestionText("Solve for r: 5r - 3 = 27"));
    }

    void setupCorrectAnswers()
    {
        // Set the correct answers for the level 1 problems
        correctAnswers.push_back(true);
        correctAnswers.push_back(false);
        correctAnswers.push_back(true);
        correctAnswers.push_back(true);
        correctAnswers.push_back(false);
    }

    bool checkAllAnswersCorrect()
    {
        for (size_t i = 0; i < correctAnswers.size(); ++i)
        {
            if (!correctAnswers[i])
            {
                return false;
            }
        }
        return true;
    }

    sf::Text createQuestionText(const std::string& question)
    {
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(30);
        text.setString(question);
        text.setFillColor(sf::Color::Black);
        text.setPosition(window.getSize().x / 2 - text.getLocalBounds().width / 2, 125 + questionTexts.size() * 100);
        return text;
    }
};

class BlankScreen
{
public:
    BlankScreen(sf::RenderWindow& window, int& activeScreen)
        : window(window), activeScreen(activeScreen)
    {
    }

    void handleEvent(const sf::Event& event)
    {
    }

    void update()
    {
    }

    void render()
    {
    }

private:
    sf::RenderWindow& window;
    int& activeScreen;
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1500, 1000), "MathQuest");

    int activeScreen = 1; // First screen is active by default

    FirstScreen firstScreen(window, activeScreen);
    Level1Screen level1Screen(window, activeScreen);
    BlankScreen blankScreen(window, activeScreen);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (activeScreen == 1)
            {
                firstScreen.handleEvent(event);
            }
            else if (activeScreen == 2)
            {
                level1Screen.handleEvent(event);
            }
            else if (activeScreen == 3)
            {
                blankScreen.handleEvent(event);
            }
        }

        if (activeScreen == 1)
        {
            firstScreen.update();
        }
        else if (activeScreen == 2)
        {
            level1Screen.update();
        }
        else if (activeScreen == 3)
        {
            blankScreen.update();
        }

        window.clear();

        if (activeScreen == 1)
        {
            firstScreen.render();
        }
        else if (activeScreen == 2)
        {
            level1Screen.render();
        }
        else if (activeScreen == 3)
        {
            blankScreen.render();
        }

        window.display();
    }

    return 0;
}
