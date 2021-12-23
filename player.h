#include "constants.h"
class Player
{
public:
    Player(sf::Texture &texture);
    void animate();
    void update(float dt);
    void restart();
    float getX() const;
    sf::Sprite &get_sprite();
    bool collides_with(sf::Sprite &);
    bool is_on_ground = true;
private:
    sf::Sprite sp;
    int curr_frame_anim = 0;
    float x, y, ground, y_speed;
};