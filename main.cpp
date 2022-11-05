#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
// #include <windows.h>
#include "network.h"
#include "functions.h"
#include "ship.h"
#include "variable.h"

using namespace std;

int main()
{
    // SetConsoleTitle("The BattleShip Game - Console");
    cout << "\t\t=============================\n";
    cout << "\t\t| A Game By Rosaan Ramasamy |\n";
    cout << "\t\t=============================\n\n";
    cout << "Run as Server (s) or Client (c) ? => ";
    getline(cin, whostr);
    if (whostr == "")
        whostr = "s";
    who = whostr[0];

    MyHost host;

    if (who == 's')
    {
        cout << "Your IP Address : " << sf::IpAddress::getLocalAddress() << endl;
        status = host.initiateAsServer();
        if (status == sf::Socket::Done)
        {
            cout << "Connected to Client!" << endl;
            connected = true;
        }
    }
    else if (who == 'c')
    {
        sf::IpAddress server;
        do
        {
            string serverstr;
            cout << "Address or Name of Server => ";
            getline(cin, serverstr);
            if (serverstr == "")
                serverstr = "localhost";
            server = sf::IpAddress(serverstr);
        } while (server == sf::IpAddress::None);

        do
        {

            status = host.connectToServer(server);
        } while (status != sf::Socket::Done);
        cout << "Connected to Server!" << endl;
        connected = true;
    }
    else
    {
        cout << "Wrong Input !\n";
        system("pause");
        system("cls");
        return main();
    }
    cout << "\n\n                         Chat log starts\n";
    cout << " ------------------------------------------------------------------------------\n\n";
    bool stopall = false;
    do
    {
        Sea sea;
        const int noOfShips = 5;
        int shipLength[noOfShips] = {2, 3, 3, 4, 5};
        Ship ship[noOfShips];

        for (int i = 1; i < noOfShips; i++)
        {
            ship[i].setLength(shipLength[i]);
        }
        ship[0].setPosition(100, 100);
        ship[1].setPosition(100, 150);
        ship[2].setPosition(100, 200);
        ship[3].setPosition(100, 250);
        ship[4].setPosition(100, 300);

        int currentShipNo = -1;

        sf::RenderWindow window(sf::VideoMode(myWorldWidth, myWorldHeight), "Battleship - The Game", sf::Style::Close);
        window.setVerticalSyncEnabled(true);
        window.setFramerateLimit(60);
        window.setIcon(25, 25, icon.getPixelsPtr());
        battle.play();
        while (window.isOpen())
        {

            stringstream hc;
            hc << "Attack left : " << (hits[0]);
            sf::Text hit(hc.str(), font, 40);
            hit.setColor(sf::Color::White);
            hit.setStyle(sf::Text::Bold);
            hit.setPosition(900, 70);
            if (timer)
            {
                donetext.setColor(sf::Color(0, 0, 0, 100));
            }
            else if (!timer)
            {
                donetext.setColor(sf::Color(0, 0, 0, 255));
            }
            // chat receive and all game logic lies here----------------------------------------------------------------
            string msgReceived;
            host.receiveMessage(msgReceived);
            ostringstream attacked_;
            if (msgReceived[0] == '#')
            {
                currentShipNo = -1;
                timer = false;
                istringstream sin(msgReceived.substr(1));
                int i, j;
                sin >> i >> j;
                sentences.clear();
                float q = (450 + (35 * j)) + 2;
                float w = (120 + (35 * i)) + 2;
                if (sea.getGrid(i, j) == sf::Color::Green || sea.getGrid(i, j) == sf::Color(255, 255, 255, 50))
                {
                    for (int a = 0; a < noOfShips; ++a)
                    {
                        if (ship[a].hit(q, w))
                        {
                            currentShipNo = a;
                        }
                    }

                    if (currentShipNo == b1)
                    {
                        display2 = "Your PatrolBoat is attacked\n";
                        attacked_ << ")You have attack a PatrolBoat!\nAt Grid : " << i << " " << j << endl;
                        grid1[i][j].setFillColor(sf::Color::Red);
                        grid1[i][j].setOutlineThickness(-2);
                        patrolBoat1--;
                        if (patrolBoat1 == 0)
                        {
                            attacked_.str("");
                            display2 = "Your PatrolBoat is sinked\n";
                            attacked_ << ")You have destroyed PatrolBoat!\nAt Grid : " << i << " " << j << endl;
                            host.sendMessage(attacked_.str());
                            pointship--;
                            bomb.play();
                            continue;
                        }
                        bomb.play();
                    }
                    else if (currentShipNo == b2)
                    {
                        display2 = "Your Destroyer is attacked\n";
                        attacked_ << ")You have attack a Destroyer!\nAt Grid : " << i << " " << j << endl;
                        grid1[i][j].setFillColor(sf::Color::Red);
                        grid1[i][j].setOutlineThickness(-2);
                        destroyer1--;
                        if (destroyer1 == 0)
                        {
                            attacked_.str("");
                            display2 = "Your Destroyer is sinked\n";
                            attacked_ << ")You have destroyed Destroyer!\nAt Grid : " << i << " " << j << endl;
                            host.sendMessage(attacked_.str());
                            pointship--;
                            bomb.play();
                            continue;
                        }
                        bomb.play();
                    }
                    else if (currentShipNo == b3)
                    {
                        display2 = "Your Submarine is attacked\n";
                        attacked_ << ")You have attack a Submarine!\nAt Grid : " << i << " " << j << endl;
                        grid1[i][j].setFillColor(sf::Color::Red);
                        grid1[i][j].setOutlineThickness(-2);
                        submarine1--;
                        if (submarine1 == 0)
                        {
                            attacked_.str("");
                            display2 = "Your Submarine is sinked\n";
                            attacked_ << ")You have destroyed Submarine!\nAt Grid : " << i << " " << j << endl;
                            host.sendMessage(attacked_.str());
                            pointship--;
                            bomb.play();
                            continue;
                        }
                        bomb.play();
                    }
                    else if (currentShipNo == b4)
                    {
                        display2 = "Your Battleship is attacked\n";
                        attacked_ << ")You have attack a Battleship!\nAt Grid : " << i << " " << j << endl;
                        grid1[i][j].setFillColor(sf::Color::Red);
                        grid1[i][j].setOutlineThickness(-2);
                        battleship1--;
                        if (battleship1 == 0)
                        {
                            attacked_.str("");
                            display2 = "Your Battlehip is sinked\n";
                            attacked_ << ")You have destroyed Battleship!\nAt Grid : " << i << " " << j << endl;
                            host.sendMessage(attacked_.str());
                            pointship--;
                            bomb.play();
                            continue;
                        }
                        bomb.play();
                    }
                    else if (currentShipNo == b5)
                    {
                        display2 = "Your Aircraft Carrier is attacked\n";
                        attacked_ << ")You have attack an \nAircraft Carrier! At Grid : " << i << " " << j << endl;
                        grid1[i][j].setFillColor(sf::Color::Red);
                        grid1[i][j].setOutlineThickness(-2);
                        aircraftCarrier1--;
                        if (aircraftCarrier1 == 0)
                        {
                            attacked_.str("");
                            display2 = "Your Aircraft Carrier is sinked\n";
                            attacked_ << ")You have destroyed Aircraft Carrier!\nAt Grid : " << i << " " << j << endl;
                            host.sendMessage(attacked_.str());
                            pointship--;
                            bomb.play();
                            continue;
                        }
                        bomb.play();
                    }

                    else
                    {
                        display2 = "Missile missed !\n";
                        attacked_ << "&You missed !\n";
                        grid1[i][j].setFillColor(sf::Color::Blue);
                        grid1[i][j].setOutlineThickness(-2);
                        water.play();
                    }
                    host.sendMessage(attacked_.str());
                }
            }

            else if (msgReceived[0] == ')' && msgReceived[msgReceived.length() - 4] != '#')
            {
                display.clear();
                sentences.clear();
                pointship += 2;
                int i, j;
                if (msgReceived[10] == 'd')
                {
                    boatLeft--;
                }

                bomb.play();

                if (msgReceived[msgReceived.length() - 1] == '/')
                {
                    string st;
                    st = msgReceived.substr(0, msgReceived.size() - 1);
                    istringstream ssin(st.substr(st.length() - 4));
                    ssin >> i >> j;
                    display = st.substr(1);
                }
                else
                {
                    istringstream ssin(msgReceived.substr(msgReceived.length() - 4));
                    ssin >> i >> j;
                    display = msgReceived.substr(1);
                }
                grid2[i][j].setFillColor(sf::Color(255, 0, 0, 200));
            }
            else if (msgReceived[0] == '&')
            {
                display.clear();
                sentences.clear();
                display = msgReceived.substr(1);
                water.play();
            }
            else if (msgReceived[0] == '/')
            {
                ostringstream soutwon;
                soutwon << "You Won !\n"
                        << "Total Score : " << (pointship + hits[0] + 10);
                loosetext.setString(soutwon.str());
                timer = true;
                refresh_ = false;
                refreshStop = false;
            }

            else if (!msgReceived.length() == 0 && msgReceived[0] != ')' && msgReceived[0] != '#' && msgReceived[0] != '&' && msgReceived[0] != '/')
            {
                if (msgReceived == "I M READY")
                {
                    chatPing = "*&*";
                }
                cout << " Chat Received : " << msgReceived << endl;
                chatrece = msgReceived;
                sentences.clear();
            }
            else if (patrolBoat1 == 0 && submarine1 == 0 && battleship1 == 0 && aircraftCarrier1 == 0 && destroyer1 == 0)
            {

                ostringstream sout;
                sout << "You Lost !\n"
                     << "Total Score : " << (pointship + hits[0]);
                loosetext.setString(sout.str());
                msgattacksend = "/";
                host.sendMessage(msgattacksend);
                winlo = false;
                timer = true;
                refresh_ = false;
                refreshStop = false;
            }

            sf::Text attacrec("Enemy Respond: " + display, font, 11);
            attacrec.setColor(sf::Color::Black);
            attacrec.setStyle(sf::Text::Bold);
            attacrec.setPosition(100, 350);

            sf::Text attacrec2("Your Stats: " + display2, font, 12);
            attacrec2.setColor(sf::Color::Black);
            attacrec2.setStyle(sf::Text::Bold);
            attacrec2.setPosition(100, 400);

            sf::Text chatreceive("Received Chat: " + chatrece, font, 20);
            chatreceive.setColor(sf::Color::White);
            chatreceive.setStyle(sf::Text::Bold);
            chatreceive.setPosition(450, 500);

            stringstream bl;
            bl << "Enemy Ships Left : " << boatLeft;
            sf::Text boatLeft_(bl.str(), font, 12);
            boatLeft_.setColor(sf::Color(0, 0, 0, 255));
            boatLeft_.setStyle(sf::Text::Bold);
            boatLeft_.setPosition(100, 450);

            if (winlo)
            {

                if (hits[0] == 0)
                {
                    ostringstream south;
                    south << "You are out of move !\n"
                          << "Total Score : " << (pointship + hits[0]);
                    loosetext.setString(south.str());
                    refresh_ = false;
                    refreshStop = false;
                }
            }
            stringstream pp;
            pp << "Points : " << pointship;
            sf::Text point(pp.str(), font, 40);
            point.setColor(sf::Color::White);
            point.setStyle(sf::Text::Bold);
            point.setPosition(450, 70);

            if (reset)
            {
                // showHardwareMouse = true;
                drag = false;
                dra = 0;
                dragOffsetX = dragOffsetY = 0.0f;
                started = true;
                reset = false;
            }
            sf::Event event;
            while (window.pollEvent(event))
            {

                if (started)
                {

                    switch (event.type)
                    {
                    case sf::Event::Closed:
                        stopall = true;
                        window.close();
                        break;
                    case sf::Event::TextEntered:
                        if (event.text.unicode >= 32 && event.text.unicode <= 126)
                            sentences += (char)event.text.unicode;
                        else if (event.text.unicode == 8 && sentences.length() > 0)
                            sentences.erase(sentences.length() - 1, sentences.length());
                        if (sentences.length() > 29)
                            sentences.erase(sentences.length() - 1, sentences.length());
                        text.setString(sentences);
                        break;

                    case sf::Event::KeyPressed:
                        if (event.key.code == sf::Keyboard::Escape)
                        {
                            stopall = true;
                            window.close();
                        }
                        if (event.key.code == sf::Keyboard::Return)
                        {
                            char choice = sentences[0];
                            if (choice != '#' || choice != ')' || choice != '*' || choice != '&' || choice != '/')
                            {
                                string msgToSend = sentences.substr(0);
                                host.sendMessage(msgToSend);
                                sentences.clear();
                                cout << " Chat Send: " << msgToSend << endl;
                            }
                        }
                        break;

                    case sf::Event::MouseButtonPressed:
                    {
                        switch (event.mouseButton.button)
                        {
                        case sf::Mouse::Left:
                        {
                            if (!second1)
                            {

                                float x = event.mouseButton.x;
                                float y = event.mouseButton.y;
                                if (!drag)
                                {
                                    for (int i = 0; i < noOfShips; ++i)
                                    {
                                        if (ship[i].hit(x, y))
                                        {
                                            currentShipNo = i;
                                            break;
                                        }
                                    }
                                    if (currentShipNo != -1)
                                    {
                                        dragOffsetX = x - ship[currentShipNo].getX();
                                        dragOffsetY = y - ship[currentShipNo].getY();
                                        ship[currentShipNo].setOrigin(dragOffsetX, dragOffsetY);
                                        ship[currentShipNo].setPosition(x, y);
                                        drag = true;
                                    }
                                } // if (!drag)
                            }
                            if (!doneStop)
                            {
                                if (!second1)
                                {
                                    if (pressButton(done, event) < 1280)
                                    {
                                        attacklimit = true;
                                        donevi = false;
                                        timer = false;
                                        dra2 = true;
                                        second1 = true;
                                        doneStop = true;
                                        releaseEnemy = true;
                                        host.sendMessage("I M READY");
                                        deployed.play();
                                    }
                                }
                            }

                            if (!refreshStop)
                            {
                                if (pressButton(refresh, event) < 1280)
                                {
                                    refreshStop = true;
                                    window.close();
                                }
                            }

                            break;
                        }
                        case sf::Mouse::Right:
                        {
                            if (!second1)
                            {

                                if (currentShipNo != -1)
                                    ship[currentShipNo].changeOrientation();
                                break;
                            }
                        }
                        }
                        break;
                    }

                    case sf::Event::MouseMoved:
                    {
                        if (!second1)
                        {

                            if (drag)
                            {
                                sf::Vector2i windowPos = sf::Mouse::getPosition(window);
                                ship[currentShipNo].setPosition(windowPos.x, windowPos.y);
                            }
                            break;
                        }
                    }

                    break;

                    case sf::Event::MouseButtonReleased:
                    {
                        switch (event.mouseButton.button)
                        {
                        case sf::Mouse::Left:
                        {
                            if (!second1)
                            {

                                float x = event.mouseButton.x;
                                float y = event.mouseButton.y;
                                if (drag)
                                {
                                    ship[currentShipNo].setOrigin(0.0f, 0.0f);
                                    float newx = x - dragOffsetX;
                                    float newy = y - dragOffsetY;
                                    ship[currentShipNo].setPosition(newx, newy);
                                    sea.dropShip(newx, newy, ship[currentShipNo]);
                                    currentShipNo = -1;
                                    drag = false;
                                    drop.play();
                                }
                                break;
                            }
                        }
                        }
                        break;
                    }
                    }
                }
            }

            window.draw(mainbg);
            window.draw(wallLeft);
            window.draw(wallRight);
            window.draw(wallTop);
            window.draw(wallBottom);
            window.draw(chatbox1);
            window.draw(chatbox2);
            window.draw(boatLeft_);
            if (!refresh_)
            {
                window.draw(refresh);
            }
            if (ship[0].getPositionX() >= 450 && ship[0].getPositionX() <= 800 && ship[0].getPositionY() <= 470 && ship[0].getPositionY() >= 120 &&
                ship[1].getPositionX() >= 450 && ship[1].getPositionX() <= 800 && ship[1].getPositionY() <= 470 && ship[1].getPositionY() >= 120 &&
                ship[2].getPositionX() >= 450 && ship[2].getPositionX() <= 800 && ship[2].getPositionY() <= 470 && ship[2].getPositionY() >= 120 &&
                ship[3].getPositionX() >= 450 && ship[3].getPositionX() <= 800 && ship[3].getPositionY() <= 470 && ship[3].getPositionY() >= 120 &&
                ship[4].getPositionX() >= 450 && ship[4].getPositionX() <= 800 && ship[4].getPositionY() <= 470 && ship[4].getPositionY() >= 120 && donevi)
            {
                doneStop = false;
                window.draw(done);
            }

            window.draw(chatbox3);
            window.draw(text);
            window.draw(point);
            if (releaseEnemy)
            {
                window.draw(hit);
            }
            window.draw(attacrec);
            window.draw(attacrec2);
            window.draw(chatreceive);
            if (releaseEnemy)
            {
                window.draw(donetext);
            }
            window.draw(loosetext);

            sea.draw(window);
            if (second1)
            {
                sea.draw1(window);
            }

            for (int i = 0; i < noOfShips; ++i)
            {
                ship[i].draw(window);
            }
            ship[0].setColor(sf::Color::Green, sf::Color::Black);
            ship[1].setColor(sf::Color::Yellow, sf::Color::Black);
            ship[2].setColor(sf::Color::Magenta, sf::Color::Black);
            ship[3].setColor(sf::Color(255, 89, 0, 255), sf::Color::Black);
            ship[4].setColor(sf::Color(78, 56, 89, 255), sf::Color::Black);

            if (releaseEnemy)
            {
                sf::Vector2i pointerPos = sf::Mouse::getPosition(window);

                for (int i = 0; i < gridSize; i++)
                    for (int j = 0; j < gridSize; j++)
                    {
                        window.draw(grid[i][j]);

                        sf::FloatRect gridBounds = grid[i][j].getGlobalBounds();

                        if (gridBounds.contains((sf::Vector2f)pointerPos))
                        {
                            highlightCell.setPosition(grid[i][j].getPosition());
                            window.draw(highlightCell);

                            if (attacklimit)
                            {
                                if (grid[i][j].getFillColor() != sf::Color::Cyan)
                                {

                                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                                    {
                                        attacked_.str().clear();
                                        if (attacked_.str().size() == 0)
                                        {
                                            if (!timer && chatPing == "*&*")
                                            {
                                                hits[0]--;
                                                stringstream ss;
                                                ss << i << " " << j;
                                                string atta = ss.str();
                                                string msg = atta.substr(0);
                                                istringstream sin(msg);
                                                int i = -1, j = -1;
                                                sin >> i >> j;
                                                ostringstream sout;
                                                sout << "#" << i << " " << j;
                                                if (i != -1 && j != -1)
                                                {
                                                    host.sendMessage(sout.str());
                                                    atta.clear();
                                                }
                                                attacked_.str("");
                                                atta.clear();

                                                grid[i][j].setFillColor(sf::Color::Cyan);
                                                timer = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
            }

            if (second1)
            {

                for (int i = 0; i < gridSize1; i++)
                {

                    for (int j = 0; j < gridSize1; j++)
                    {
                        window.draw(grid1[i][j]);
                    }
                }

                for (int i = 0; i < gridSize2; i++)
                {

                    for (int j = 0; j < gridSize2; j++)
                    {
                        window.draw(grid2[i][j]);
                    }
                }
            }

            if (hits[0] <= 0)
            {
                attacklimit = false;
            }

            window.display();
        }
    } while (!stopall);

    return 0;
}
