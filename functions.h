#include <SFML/Audio.hpp>

sf::Texture loadTexture(const string &imageFilename)
{
    sf::Texture myTexture;
    if (!myTexture.loadFromFile(imageFilename))
    {
        cout << "Can not load image from " << imageFilename << endl;
        system("pause");
    }
    return myTexture;
}

sf::RectangleShape createRectangle(float width = 1.0f, float height = 1.0f, sf::Vector2f position = sf::Vector2f(0, 0),
                                   const sf::Color &myFillColor = sf::Color::White,
                                   const sf::Color &myOutlineColor = sf::Color::Black,
                                   float myOutlineThickness = -2)
{
    sf::RectangleShape myRectangle;
    sf::Vector2f myRectangleSize(width, height);
    myRectangle.setSize(myRectangleSize);
    myRectangle.setPosition(position);
    myRectangle.setFillColor(sf::Color(255, 255, 255, 50));
    myRectangle.setOutlineColor(myOutlineColor);
    myRectangle.setOutlineThickness(myOutlineThickness);
    return myRectangle;
}

sf::RectangleShape createRectangle1(float width = 1.0f, float height = 1.0f, sf::Vector2f position = sf::Vector2f(0, 0),
                                    const sf::Color &myFillColor = sf::Color::White,
                                    const sf::Color &myOutlineColor = sf::Color::Black,
                                    float myOutlineThickness = 0)
{
    sf::RectangleShape myRectangle;
    sf::Vector2f myRectangleSize(width, height);
    myRectangle.setSize(myRectangleSize);
    myRectangle.setPosition(position);
    myRectangle.setFillColor(sf::Color(0, 0, 0, 0));
    myRectangle.setOutlineColor(myOutlineColor);
    myRectangle.setOutlineThickness(myOutlineThickness);
    return myRectangle;
}

sf::RectangleShape createRectangle2(float width = 1.0f, float height = 1.0f, sf::Vector2f position = sf::Vector2f(0, 0),
                                    const sf::Color &myFillColor = sf::Color::White,
                                    const sf::Color &myOutlineColor = sf::Color::Black,
                                    float myOutlineThickness = -2)
{
    sf::RectangleShape myRectangle;
    sf::Vector2f myRectangleSize(width, height);
    myRectangle.setSize(myRectangleSize);
    myRectangle.setPosition(position);
    myRectangle.setFillColor(sf::Color(0, 0, 0, 0));
    myRectangle.setOutlineColor(myOutlineColor);
    myRectangle.setOutlineThickness(myOutlineThickness);
    return myRectangle;
}

sf::Font loadFont(const string &fontFilename = "resources/sansation.ttf")
{
    sf::Font myFont;
    if (!myFont.loadFromFile(fontFilename))
    {
        cout << "Can not load font from " << fontFilename << endl;
        exit(1);
    }
    return myFont;
}

float pressButton(sf::Sprite &sprite, sf::Event &event)
{
    float mouseX = event.mouseButton.x;
    float mouseY = event.mouseButton.y;
    float circleX = sprite.getPosition().x;
    float circleY = sprite.getPosition().y;
    float dx = mouseX - circleX;
    float dy = mouseY - circleY;

    return (dx * dx + dy * dy);
}

sf::SoundBuffer loadSoundBuffer(const string &waveFilename)
{
    sf::SoundBuffer mySoundBuffer;
    if (!mySoundBuffer.loadFromFile(waveFilename))
    {
        cout << "Can not load sound from " << waveFilename << endl;
        exit(1);
    }
    return mySoundBuffer;
}

sf::Sound createSound(const sf::SoundBuffer &mySoundBuffer)
{
    sf::Sound mySound(mySoundBuffer);
    return mySound;
}

enum ShipID
{
    patrolBoat = 0,
    destroyer,
    submarine,
    battleship,
    aircraftCarrier
};
