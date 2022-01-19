#include <SFML/Graphics.hpp>
#include <fstream>
#include <array>
#ifndef SCORE_H
#define SCORE_H
static sf::IntRect numbers[] = {
    {655, 2, 9, 11},
    {666, 2, 9, 11},
    {675, 2, 9, 11},
    {685, 2, 9, 11},
    {695, 2, 9, 11},
    {705, 2, 9, 11},
    {715, 2, 9, 11},
    {725, 2, 9, 11},
    {735, 2, 9, 11},
    {745, 2, 9, 11}};
static sf::IntRect hi_frame = {755, 2, 19, 11};
class Score
{
public:
    Score(sf::Texture &texture)
    {
        hi.setTexture(texture);
        hi.setTextureRect(hi_frame);
        hi.setPosition(430, 10);
        for (int i = 0; i < 5; i++)
        {
            score_digits[i].setTexture(texture);
            max_score_digits[i].setTexture(texture);
            score_digits[i].setTextureRect(numbers[0]);
            score_digits[i].setPosition(530 + 11 * i, 10);
            max_score_digits[i].setPosition(455 + 11 * i, 10);
        }
        std::ifstream ifs("max_score.txt");
        if(!ifs.is_open())
        {
            std::ofstream ofs("max_score.txt");
            ofs << 0;
            ofs.close();
        }else
        {
            ifs >> max_score;
            ifs.close();
        }
        set_digits(max_score, max_score_digits);
    }
    int get_score()
    {
        return score;
    }
    void draw(sf::RenderTarget &target)
    {
        target.draw(hi);
        for(auto &mdigit: max_score_digits)
        {
            target.draw(mdigit);
        }
        if (!visible)
            return;
        for (auto &sdigit : score_digits)
        {
            target.draw(sdigit);
        }
    }
    void restart()
    {
        _100more = false;
        score = 0;
        visible = true;
        std::ofstream ofs("max_score.txt");
        ofs << max_score;
        set_digits(max_score, max_score_digits);
        ofs.close();
    }
    bool has_updated(){
        if(_100more)
        {
            _100more = false;
            return true;
        }
        return false;
    }
    void update(float dt)
    {
        if (score % 100 == 0 && score > 0)
        {
            set_digits(score, score_digits);
            blink(dt);
            total_time = 0;
            return;
        }
        total_time += dt;
        if (total_time >= 0.1f)
        {
            set_digits(score, score_digits);
            max_score = std::max(max_score, score);
            score++;
            _100more = score % 100 == 0;
            total_time = 0;
        }
    }

private:
    void set_digits(int n, std::array<sf::Sprite, 5> &digits)
    {
        for (int i = 0; i < 5; i++)
        {
            int digit = n % 10;
            n /= 10;
            digits[4 - i].setTextureRect(numbers[digit]);
        }
    }
    void blink(float dt)
    {
        if (cnt >= 8)
        {
            score++;
            cnt = 0;
            blink_time = 0;
            return;
        }
        blink_time += dt;
        if (blink_time >= 0.2f) //cada 0.2 s es visible y no visible, por lo tanto este if se cumple dos veces para conseguir un parpadeo
        {                       //queremos 4 parpadeos, por lo tanto son 8 veces que debe pasar por este if                    
            visible = !visible;
            cnt++;
            blink_time = 0;
        }
    }
    int cnt = 0;
    int score = 0;
    int max_score = 0;
    bool visible = true;
    bool _100more = false;
    float total_time = 0;
    float blink_time = 0;
    std::array<sf::Sprite, 5> score_digits;
    std::array<sf::Sprite, 5> max_score_digits;
    sf::Sprite hi;
};
#endif