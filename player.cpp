#include "player.h"
#include "collision.h"
#include "iostream"
static const float GRAVITY = 900.0f;
static const sf::IntRect die_frame = {1024, 2, 44, 47};
Player::Player(sf::Texture &texture)
{
    sp.setTexture(texture);
    sp.setTextureRect(dino_frames[curr_frame]);
    x = 20;
    ground = y = 125;
    y_speed = -500;
    player_speed = 130;
    sp.setPosition(x, y);
}
void Player::die()
{
    sp.setTextureRect(die_frame);
}
void Player::animate(float dt)
{
    total_dt += dt;
    if (total_dt >= (1 / 10.f))
    {
        if (is_on_ground)
        {
            sp.setTextureRect(dino_frames[curr_frame]);
            if (++curr_frame >= 2)
            {
                curr_frame = 0;
            }
        }
        else
        {
            sp.setTextureRect(dino_frames[2]);
            curr_frame = 1;
        }
        total_dt = 0;
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
float Player::getY() const
{
    return y;
}
void Player::restart()
{
    is_on_ground = true;
    x = 20;
    y = 125;
    y_speed = -500;
    player_speed = 130;
}

void Player::draw(sf::RenderTarget &target)
{
    target.draw(sp);
}
bool Player::collides_with(sf::Sprite &entity)
{
    return Collision::PixelPerfectTest(sp, entity);
}