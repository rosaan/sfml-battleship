#include <sstream>
#include <SFML/Audio.hpp>

const int myWorldWidth = 1280;
const int myWorldHeight = 600;
const int myWallThickness = 40;
const int gridSize = 10;
int gridCellSize = 35;
int gridX = 850;
int gridY = 120;
const int gridSize1 = 10;
int gridCellSize1 = 35;
int gridX1 = 450;
int gridY1 = 120;
const int gridSize2 = 10;
int gridCellSize2 = 35;
int gridX2 = 850;
int gridY2 = 120;
sf::RectangleShape wallLeft, wallRight, wallTop, wallBottom, mainbg, chatbox1, chatbox2, chatbox3;
wallLeft.setFillColor(sf::Color(255, 255, 200));
wallLeft.setOutlineThickness(0.0f);
wallLeft.setSize(sf::Vector2f(myWallThickness, myWorldHeight));
wallLeft.setPosition(0, 0);
wallRight = wallLeft;
wallRight.setPosition(myWorldWidth - myWallThickness, 0);
wallTop = wallLeft;
wallTop.setSize(sf::Vector2f(myWorldWidth, myWallThickness));
wallTop.setPosition(0, 0);
wallBottom = wallTop;
wallBottom.setPosition(0, myWorldHeight - myWallThickness);
sf::Texture myWallTexture = loadTexture("resources/wall.jpg");
myWallTexture.setSmooth(true);
myWallTexture.setRepeated(true);
wallLeft.setTextureRect(sf::IntRect(0, 0, myWallThickness, myWorldHeight));
wallRight.setTextureRect(sf::IntRect(0, 0, myWallThickness, myWorldHeight));
wallTop.setTextureRect(sf::IntRect(0, 0, myWorldWidth, myWallThickness));
wallBottom.setTextureRect(sf::IntRect(0, 0, myWorldWidth, myWallThickness));
wallLeft.setTexture(&myWallTexture);
wallRight.setTexture(&myWallTexture);
wallTop.setTexture(&myWallTexture);
wallBottom.setTexture(&myWallTexture);
sf::Texture background = loadTexture("resources/background.jpg");
mainbg.setSize(sf::Vector2f(myWorldWidth, myWorldHeight));
mainbg.setPosition(0, 0);
mainbg.setTexture(&background);
chatbox1.setSize(sf::Vector2f(350, 450));
chatbox1.setPosition(75, 75);
chatbox1.setFillColor(sf::Color(255, 255, 255, 200));
chatbox1.setOutlineThickness(2);
chatbox1.setOutlineColor(sf::Color::Black);
chatbox2.setSize(sf::Vector2f(350, 20));
chatbox2.setPosition(75, 505);
chatbox2.setFillColor(sf::Color(255, 255, 255, 200));
chatbox2.setOutlineThickness(2);
chatbox2.setOutlineColor(sf::Color::Black);
chatbox3.setSize(sf::Vector2f(600, 24));
chatbox3.setPosition(445, 500);
chatbox3.setFillColor(sf::Color::Black);
chatbox3.setOutlineThickness(1);
chatbox3.setOutlineColor(sf::Color::White);
sf::RectangleShape grid[gridSize][gridSize];
sf::RectangleShape grid1[gridSize][gridSize];
sf::RectangleShape grid2[gridSize][gridSize];
sf::RectangleShape highlightCell = createRectangle(gridCellSize, gridCellSize);
highlightCell.setFillColor(sf::Color(0, 255, 0, 128));
highlightCell.setOutlineColor(sf::Color(0, 102, 0));

sf::Font font;
if (!font.loadFromFile("resources/sansation.ttf"))
    cout << "Font not found !\n";

sf::Texture refre, rese, don;
if (!refre.loadFromFile("resources/refresh.png") || !don.loadFromFile("resources/done.png"))
{
    cout << "Image not found !";
}
refre.setSmooth(true);
sf::Sprite refresh, resetb, done;
refresh.setTexture(refre);
refresh.setPosition(sf::Vector2f(280, 460));
done.setTexture(don);
done.setPosition(sf::Vector2f(380, 460));

sf::Image icon;
icon.loadFromFile("resources/icon.png");

string sentences, receive, pointsys, chatrece, loosetex = "";
int pointship = 0;
sf::Text text(sentences, font, 20);
text.setColor(sf::Color::Black);
text.setStyle(sf::Text::Bold);
text.setPosition(75, 502);

sf::Text donetext("Your Turn", font, 20);
donetext.setColor(sf::Color(0, 0, 0, 255));
donetext.setStyle(sf::Text::Bold);
donetext.setPosition(980, 470);

sf::Text loosetext(loosetex, font, 20);
loosetext.setColor(sf::Color(0, 0, 0, 255));
loosetext.setStyle(sf::Text::Bold);
loosetext.setPosition(80, 80);

for (int i = 0; i < gridSize; i++)
{
    for (int j = 0; j < gridSize; j++)
    {
        grid[i][j] = createRectangle(gridCellSize, gridCellSize, sf::Vector2f(gridX, gridY));
        gridX += gridCellSize;
    }

    gridY += gridCellSize;
    gridX = 850;
}

for (int i = 0; i < gridSize1; i++)
{
    for (int j = 0; j < gridSize1; j++)
    {
        grid1[i][j] = createRectangle1(gridCellSize1, gridCellSize1, sf::Vector2f(gridX1, gridY1));

        gridX1 += gridCellSize1;
    }

    gridY1 += gridCellSize1;
    gridX1 = 450;
}

for (int i = 0; i < gridSize2; i++)
{
    for (int j = 0; j < gridSize2; j++)
    {
        grid2[i][j] = createRectangle2(gridCellSize2, gridCellSize2, sf::Vector2f(gridX2, gridY2));

        gridX2 += gridCellSize2;
    }

    gridY2 += gridCellSize2;
    gridX2 = 850;
}

bool showHardwareMouse;
bool started;
bool drag;
int dra;
float dragOffsetX, dragOffsetY;
bool LeftMouseButtonDown = false;
bool reset = true;
int hits[1] = {50};

int patrolBoat1 = 2;
int destroyer1 = 3;
int submarine1 = 3;
int battleship1 = 4;
int aircraftCarrier1 = 5;

bool attacklimit = false;
bool donevi = true;
bool dra2 = false;
bool timer = true;
sf::String msgattacksend, secondb;
bool second1 = false;
bool winlo = true;
bool attacklimit2 = false;
string display, display2, chatstart, chatPing;
int geti, getj;
bool receiveb = false;
bool refresh_ = true;
bool doneStop = true;
bool refreshStop = true;
bool releaseEnemy = false;
int boatLeft = 5;

ShipID b1, b2, b3, b4, b5;
b1 = patrolBoat;
b2 = destroyer;
b3 = submarine;
b4 = battleship;
b5 = aircraftCarrier;

sf::SoundBuffer deployedBuffer = loadSoundBuffer("resources/deployed.ogg");
sf::Sound deployed = createSound(deployedBuffer);
sf::SoundBuffer bombBuffer = loadSoundBuffer("resources/bomb.ogg");
sf::Sound bomb = createSound(bombBuffer);
sf::SoundBuffer waterBuffer = loadSoundBuffer("resources/water.ogg");
sf::Sound water = createSound(waterBuffer);
sf::SoundBuffer battleBuffer = loadSoundBuffer("resources/battle.ogg");
sf::Sound battle = createSound(battleBuffer);
battle.setLoop(true);
sf::SoundBuffer dropBuffer = loadSoundBuffer("resources/drop.ogg");
sf::Sound drop = createSound(dropBuffer);
