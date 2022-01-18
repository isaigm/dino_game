#include <SFML/Graphics.hpp>
#ifndef SCORE_H
#define SCORE_H
static sf::IntRect numbers[] = {
    {655, 2, 9, 11},
    {666, 2, 8, 11},
    {672, 2, 9, 11},
    {685, 2, 9, 11},
    {695, 2, 9, 11},
    {705, 2, 9, 11},
    {715, 2, 9, 11},
    {725, 2, 9, 11},
    {735, 2, 9, 11},
    {745, 2, 9, 11}};
class score
{
public:
    score(sf::Texture &texture)
    {
        for(int i = 0; i < 5; i++)
        {
            sdigits[i].setTexture(texture);
            sdigits[i].setTextureRect(numbers[0]);
            
        }
    }
    void draw(sf::RenderTarget &target)
    {

    }
    void update(float dt)
    {

    }
private:
    int score_ = 0;
    int digits[5] = {0};
    sf::Sprite sdigits[5];
};
#endif