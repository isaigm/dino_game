#include "player.h"

Player::Player(sf::Texture &texture)
{
    sp.setTexture(texture);
    sp.setTextureRect(dino_frames[curr_frame_anim]);
    x = 20;
    ground = y = 125;
    y_speed = -500;
    sp.setPosition(x, y);
}
void Player::animate()
{
    if (is_on_ground)
    {
        sp.setTextureRect(dino_frames[curr_frame_anim]);
        if (++curr_frame_anim >= 2)
        {
            curr_frame_anim = 0;
        }
    }
    else
    {
        sp.setTextureRect(dino_frames[2]);
        curr_frame_anim = 1;
    }
}
void Player::update(float dt)
{
    x += player_speed * dt;
    if (!is_on_ground)
    {
        y += y_speed * dt;
        y_speed += GRAVITY * dt;
        if (y >= ground)
        {
            y = ground;
            is_on_ground = true;
            y_speed = -500;
        }
    }
    sp.setPosition({x, y});
}
float Player::getX() const
{
    return x;
}
void Player::restart()
{
    is_on_ground = true;
    x = 20;
    y = 125;
    y_speed = -500;
}
sf::Sprite &Player::get_sprite()
{
    return sp;
}
bool Player::collides_with(sf::Sprite &entity)
{
    return sp.getGlobalBounds().intersects(entity.getGlobalBounds());
}