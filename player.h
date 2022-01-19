#include <SFML/Graphics.hpp>
#ifndef PLAYER_H
#define PLAYER_H
static const sf::IntRect dino_frames[] =
    {
        {936, 2, 44, 47},
        {980, 2, 44, 47},
        {848, 2, 44, 47}};
class Player
{
public:
    Player(sf::Texture &texture);
    void draw(sf::RenderTarget &target);
    void animate(float dt);
    void update(float dt);
    void restart();
    void set_player_speed(int speed)
    {
        player_speed = speed;
    }
    float getX() const;
    float getY() const;
    void die();
    bool collides_with(sf::Sprite &);
    bool is_on_ground = true;

private:
    sf::Sprite sp;
    int curr_frame = 0, player_speed;
    float total_dt = 0;
    float x, y, ground, y_speed;
};
#endif