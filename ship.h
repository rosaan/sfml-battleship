#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>

class Ship
{
public:
    Ship(int length = 2, int typeNo = 1, bool isHorizontal = true, float boxSize = 35)
        : length_(length), typeNo_(typeNo),
          isHorizontal_(isHorizontal), boxSize_(boxSize)
    {
        setLength(length);
        rectangle_.setOrigin(0.0f, 0.0f);
        setColor(sf::Color::Green, sf::Color::Black);
    }
    void setLength(int length)
    {
        length_ = length;
        width_ = boxSize_ * length_;
        height_ = boxSize_;
        sf::Vector2f rectangleSize(width_, height_);
        rectangle_.setSize(rectangleSize);
        if (!isHorizontal_)
            changeOrientation();
    }
    int getLength()
    {
        return length_;
    }
    int getTypeNo()
    {
        return typeNo_;
    }
    void setColor(const sf::Color &fillColor,
                  const sf::Color &outlineColor,
                  float outlineThickness = -2.0f)
    {
        fillColor_ = fillColor;
        outlineColor_ = outlineColor;
        outlineThickness_ = outlineThickness;
        rectangle_.setFillColor(fillColor_);
        rectangle_.setOutlineColor(outlineColor_);
        rectangle_.setOutlineThickness(outlineThickness_);
    }
    void changeOrientation()
    {
        isHorizontal_ = !isHorizontal_;
        int temp = width_;
        width_ = height_;
        height_ = temp;
        sf::Vector2f rectangleSize(width_, height_);
        rectangle_.setSize(rectangleSize);
    }
    bool isHorizontal()
    {
        return isHorizontal_;
    }
    void setHorizontal()
    {
        if (isHorizontal_)
            return;
        changeOrientation();
    }
    void setVertical()
    {
        if (!isHorizontal_)
            return;
        changeOrientation();
    }
    void setPosition(int x, int y)
    {
        x_ = x;
        y_ = y;
        rectangle_.setPosition(x, y);
    }

    int getPositionX()
    {
        sf::Vector2f recPos = rectangle_.getPosition();
        return recPos.x;
    }
    int getPositionY()
    {
        sf::Vector2f recPos = rectangle_.getPosition();
        return recPos.y;
    }
    void setOrigin(int x, int y)
    {
        rectangle_.setOrigin(x, y);
    }
    void draw(sf::RenderWindow &window)
    {
        window.draw(rectangle_);
    }
    bool hit(int x, int y)
    {
        if (x > x_ && x < x_ + width_ && y > y_ && y < y_ + height_)
            return true;
        return false;
    }
    int getX()
    {
        return x_;
    }
    int getY()
    {
        return y_;
    }

private:
    int length_, typeNo_, width_, height_;
    int boxSize_;
    int x_, y_;
    bool isHorizontal_;
    sf::Color fillColor_;
    sf::Color outlineColor_;
    float outlineThickness_;
    sf::RectangleShape rectangle_;
};

class Sea
{
public:
    Sea(int OriginX = 450, int OriginY = 120)
        : gridDimX_(10), gridDimY_(10), // no of cells for each dimension of the grid
          cellDimX_(35), cellDimY_(35), // no of pixels for each dimension of the cells
          OriginX_(OriginX), OriginY_(OriginY),
          width_(gridDimX_ * cellDimX_), height_(gridDimY_ * cellDimY_)
    {
        grid.resize(gridDimY_);             // create dimy_ rows
        for (int i = 0; i < gridDimY_; ++i) // for each row
        {
            grid[i].resize(gridDimX_); // create row with dimx_ columns
        }
        for (int i = 0; i < gridDimY_; ++i)
        {
            for (int j = 0; j < gridDimX_; ++j)
            {
                grid[i][j] = 0;
            }
        }
        sf::Vector2f size(cellDimX_, cellDimY_);
        aRectangle_.setSize(size);
        aRectangle_.setFillColor(sf::Color(255, 255, 255, 50));
        aRectangle_.setOutlineColor(sf::Color::Black);
        aRectangle_.setOutlineThickness(-2);
        aRectangle_.setOrigin(0.0f, 0.0f); // origin is at left top corner
    }
    int getOriginX()
    {
        return OriginX_;
    }
    int getOriginY()
    {
        return OriginY_;
    }
    void set(int cellIndexX, int cellIndexY, int type)
    {
        grid[cellIndexY][cellIndexX] = type;
    }

    void dropShip(int x, int y, Ship &ship)
    {
        int length = ship.getLength();
        int isHorizontal = ship.isHorizontal();
        int type = ship.getTypeNo();
        // note: x and y are pixel coords relative to window
        if (x < OriginX_ || x > OriginX_ + width_ || y < OriginY_ || y > OriginY_ + height_)
            return;
        int cellIndexX = (x - OriginX_) / cellDimX_;
        int cellIndexY = (y - OriginY_) / cellDimY_;
        int newx = cellIndexX * cellDimX_ + OriginX_;
        int newy = cellIndexY * cellDimY_ + OriginY_;
        if (isHorizontal && cellIndexX + length <= gridDimX_)
        {
            bool empty = true;
            for (int j = cellIndexX; j < cellIndexX + length; ++j)
            {
                if (grid[cellIndexY][j] != 0)
                {
                    empty = false;
                    break;
                }
            }
            if (empty)
            {
                for (int j = cellIndexX; j < cellIndexX + length; ++j)
                    grid[cellIndexY][j] = type;
                ship.setPosition(newx, newy);
            }
        }
        if (!isHorizontal && cellIndexY + length <= gridDimY_)
        {
            bool empty = true;
            for (int i = cellIndexY; i < cellIndexY + length; ++i)
            {
                if (grid[i][cellIndexX] != 0)
                {
                    empty = false;
                    break;
                }
            }
            if (empty)
            {
                for (int i = cellIndexY; i < cellIndexY + length; ++i)
                    grid[i][cellIndexX] = type;
                ship.setPosition(newx, newy);
            }
        }
    }

    void draw(sf::RenderWindow &window)
    {
        for (int i = 0, y = OriginY_; i < gridDimY_; ++i, y += cellDimY_)
        {
            for (int j = 0, x = OriginX_; j < gridDimX_; ++j, x += cellDimX_)
            {
                aRectangle_.setPosition(x, y);
                if (grid[i][j] == 0)
                {
                    aRectangle_.setFillColor(sf::Color(255, 255, 255, 50));
                }
                window.draw(aRectangle_);
            }
        }
    }

    void draw1(sf::RenderWindow &window)
    {
        for (int i = 0, y = OriginY_; i < gridDimY_; ++i, y += cellDimY_)
        {
            for (int j = 0, x = OriginX_; j < gridDimX_; ++j, x += cellDimX_)
            {
                aRectangle_.setPosition(x, y);
                if (grid[i][j] == 0)
                {
                    aRectangle_.setFillColor(sf::Color(255, 255, 255, 50));
                }
                else if (grid[i][j] == 1)
                {
                    aRectangle_.setFillColor(sf::Color(255, 255, 255, 50));
                }
                window.draw(aRectangle_);
            }
        }
    }

    sf::Color getGrid(int i, int j)
    {
        for (int i = 0, y = OriginY_; i < gridDimY_; ++i, y += cellDimY_)
        {
            for (int j = 0, x = OriginX_; j < gridDimX_; ++j, x += cellDimX_)
            {
                aRectangle_.setPosition(x, y);
                if (grid[i][j] == 0)
                {
                    return sf::Color(255, 255, 255, 50);
                }
                else if (grid[i][j] == 1)
                {
                    return sf::Color::Green;
                }
            }
        }
    }

private:
    const int gridDimX_, gridDimY_;
    vector<vector<int>> grid; // 2D array of int
    const int cellDimX_, cellDimY_;
    int OriginX_, OriginY_, width_, height_;
    sf::RectangleShape aRectangle_;
};
