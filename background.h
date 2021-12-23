#include "constants.h"
class Background
{
public:
    Background(sf::FloatRect rect, float speed) : view(rect)
    {
        this->speed = speed;
    }
    void update(float dt)
    {
        view.move(speed * dt, 0);
    }
    bool contains(sf::Sprite &sp)
    {
        return !(sp.getPosition().x + sp.getGlobalBounds().width + 5 - (view.getCenter().x - WIDTH / 2) <= 0);
    }

    sf::View &getView()
    {
        return view;
    }

private:
    float speed;
    sf::View view;
};