#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <SFML/Network.hpp>

#define DEBUG false

using namespace std;

bool connected = false;
sf::Socket::Status status;

string whostr;
char who;

class MyHost
{
public:
    MyHost(unsigned short port = 50001)
        : myPort(port)
    {
        mySocket.setBlocking(false);
    }
    sf::Socket::Status initiateAsServer();
    sf::Socket::Status connectToServer(sf::IpAddress server);
    sf::Socket::Status sendMessage(string outMsg);
    sf::Socket::Status receiveMessage(string &inMsg);

private:
    unsigned short myPort;
    sf::TcpSocket mySocket;
};

sf::Socket::Status MyHost::initiateAsServer()
{
    // Create a server socket to accept new connections
    sf::TcpListener listener;
    sf::Socket::Status status;

    // Listen to the given port for incoming connections
    status = listener.listen(myPort);
    if (status != sf::Socket::Done)
    {
        if (DEBUG)
            cout << "initiateAsServer(): Listen Failed!" << endl;
        if (DEBUG)
            cout << status << endl;
        return status;
    }
    if (DEBUG)
        cout << "Server is listening to port " << myPort << ", waiting for connections... " << endl;

    // Wait for a connection
    status = listener.accept(mySocket);
    if (status != sf::Socket::Done)
    {
        if (DEBUG)
            cout << "initiateAsServer(): Accept Failed!" << endl;
        if (DEBUG)
            cout << status << endl;
        return status;
    }
    if (DEBUG)
        cout << "Client connected: " << mySocket.getRemoteAddress() << endl;
    if (DEBUG)
        cout << status << endl;
    return status;
}

sf::Socket::Status MyHost::connectToServer(sf::IpAddress server)
{
    sf::Socket::Status status;

    // Connect to the server
    status = mySocket.connect(server, myPort);
    if (status != sf::Socket::Done)
    {
        if (DEBUG)
            cout << "connectToServer(): Connect Failed!" << endl;
        if (DEBUG)
            cout << status << endl;
        return status;
    }
    if (DEBUG)
        cout << "Connected to server " << server << endl;
    if (DEBUG)
        cout << status << endl;
    return status;
}

sf::Socket::Status MyHost::sendMessage(string outMsg)
{
    sf::Socket::Status status;

    // Send a message to the connected client
    status = mySocket.send(outMsg.c_str(), outMsg.length());
    if (status != sf::Socket::Done)
    {
        if (DEBUG)
            cout << "sendMessage(): Send Failed!" << endl;
        if (DEBUG)
            cout << status << endl;
        return status;
    }
    // cout << "Message [" << outMsg << "] sent." << endl;
    if (DEBUG)
        cout << status << endl;
    return status;
}

sf::Socket::Status MyHost::receiveMessage(string &inMsg)
{
    sf::Socket::Status status;

    // Receive a message back from the client
    char in[128];
    size_t sizeReceived;
    status = mySocket.receive(in, sizeof(in), sizeReceived);
    if (status != sf::Socket::Done)
    {
        if (DEBUG)
            cout << "receiveMessage(): Receive Failed!" << endl;
        if (DEBUG)
            cout << status << endl;
        return status;
    }
    inMsg = in;
    inMsg = inMsg.substr(0, sizeReceived);
    // cout << "Message [" << inMsg << "] received." << endl;
    if (DEBUG)
        cout << status << endl;
    return status;
}
