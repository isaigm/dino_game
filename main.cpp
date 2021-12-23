#include "player.h"
#include "background.h"
#include "sfx.h"
#include <ctime>
#include <cstdlib>

int get_random_number(int x, int y)
{
    return rand() % (y + 1 - x) + x;
}
void init_clouds(std::vector<sf::Sprite> &clouds, sf::Texture &spritesheet)
{
    float last_coords = WIDTH + 20;
    for (int i = 0; i < N_CLOUDS; i++)
    {
        sf::Sprite cloud(spritesheet);
        cloud.setTextureRect(cloud_frame);
        cloud.setPosition({last_coords, float(get_random_number(0, 20))});
        last_coords += get_random_number(2, 4) * cloud_frame.width;
        clouds.push_back(std::move(cloud));
    }
}
void set_cactus_coords(sf::Sprite &cactus, float x)
{
    cactus.setPosition({x, ground - cactus.getGlobalBounds().height});
}

int main()
{

    sf::Texture spritesheet; // sf::Texture es excelente, ya que te permite recortar y ocupar ese recorte en un sprite, asi no hace falta tener muchos sf::Texture
                             // sino recortar la parte que se necesita

    srand(time(nullptr));
    if (!spritesheet.loadFromFile(SPRITESHEET_FILE))
    {
        std::cerr << "no se pudo cargar el archivo de sprites\n";
        exit(-1);
    }
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "--Google Dino-- por Isaí García Mendoza ");
    Sfx jump("jump.mp3");
    Sfx die("die.mp3");
    std::vector<sf::Sprite> clouds;
    sf::Sprite game_over_screen(spritesheet), cactus(spritesheet);
    Player player(spritesheet);
    Background ground(sf::FloatRect(0, 12, WIDTH, HEIGHT / 2), player_speed);
    Background sky(sf::FloatRect(0, 0, WIDTH, HEIGHT / 2), 25);
    sf::Sprite bg(spritesheet); // fondo principal
    sf::Clock clock;
    float dist_x = player.getX(); // para saber que tanto del fondo actual, que mide 1200 pixeles de ancho, se ha recorrido
    float dt_anim = 0;
    float dt = 0;
    bool main_bg = true;
    bool game_over = false;
    float next_coords = 1200;

    window.setVerticalSyncEnabled(true);
    init_clouds(clouds, spritesheet);
    cactus.setTextureRect(cactus_frames[get_random_number(0, N_CACTUS - 1)]);
    set_cactus_coords(cactus, 500);
    game_over_screen.setTextureRect(game_over_frame);
    game_over_screen.setPosition({float(WIDTH - game_over_frame.width) / 2, 50});
    ground.getView().setViewport(sf::FloatRect(0, 0, 1, 0.5f));
    sky.getView().setViewport(sf::FloatRect(0, 0, 1, 0.5f));
    bg.setTextureRect(sf::IntRect(2, 53, 1200, 15));
    bg.setPosition({0, HEIGHT / 2});
    sf::Sprite next_bg = bg; // fondo auxiliar, aunque igualmente se van a ir intercalando

    while (window.isOpen())
    {
        dt = clock.restart().asSeconds();
        dt_anim += dt;
        sf::Event ev;
        while (window.pollEvent(ev))
        {
            switch (ev.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (ev.key.code == sf::Keyboard::Space && player.is_on_ground)
                {
                    jump.play();
                    player.is_on_ground = false;
                }
                break;
            default:
                break;
            }
        }
        if (game_over && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            bg.setPosition({0, HEIGHT / 2});
            game_over = false;
            dt = 0;
            dt_anim = 0;
            next_coords = 1200;
            main_bg = true;
            dist_x = 20;
            player.restart();
            clouds.erase(clouds.begin(), clouds.end());
            init_clouds(clouds, spritesheet);
            cactus.setTextureRect(cactus_frames[get_random_number(0, N_CACTUS - 1)]);
            sky.getView().setCenter({WIDTH / 2, 80});
            ground.getView().setCenter({WIDTH / 2, 92});
            set_cactus_coords(cactus, 500);
        }
        if (!game_over)
        {
            dist_x += dt * player_speed;
            player.update(dt);
            sky.update(dt);
            ground.update(dt);
            if (player.collides_with(cactus))
            {
                player.get_sprite().setTextureRect(die_frame);
                die.play();
                game_over = true;
                continue;
            }
            if (!ground.contains(cactus))
            {
                cactus.setTextureRect(cactus_frames[get_random_number(0, N_CACTUS - 1)]);
                set_cactus_coords(cactus, ground.getView().getCenter().x + WIDTH / 2 + 30);
            }
            for (auto &cloud : clouds)
            {
                if (!sky.contains(cloud))
                {
                    cloud.setPosition({sky.getView().getCenter().x + WIDTH / 2 + 3 * cloud_frame.width, float(get_random_number(0, 30))});
                }
            }
            if (dist_x >= 1200 - WIDTH) // esto se hace para que antes de recorrer el fondo por completo, se cargue otro en la posicion correcta y asi
            {                           // dar la ilusion de un fondo infinito

                if (main_bg)
                {
                    next_bg.setPosition({next_coords, HEIGHT / 2});
                }
                else
                {
                    bg.setPosition({next_coords, HEIGHT / 2});
                }
                next_coords += 1200;
                main_bg = !main_bg;
                dist_x = -(1200 - dist_x); // en este punto faltan 1200-temp_x pixeles para recorrer todo, igual aqui el segundo fondo ya se ha cargado, pero aun no es visible
                                           // es negativo  porque cuando se recorran los 1200-temp_x pixeles, tiene que valer 0, lo que corresponde con que tanto se ha recorrido
                                           // el segundo fondo
            }
            if (dt_anim >= (1.0f / 10.0f))
            {
                player.animate();
                dt_anim -= (1.0f / 10.0f);
            }
        }
        window.clear(sf::Color::White);
        if (game_over)
        {
            window.setView(window.getDefaultView());
            window.draw(game_over_screen);
        }
        window.setView(sky.getView());
        for (const auto &cloud : clouds)
        {
            window.draw(cloud);
        }
        window.setView(ground.getView());
        window.draw(bg);
        window.draw(player.get_sprite());
        window.draw(next_bg);
        window.draw(cactus);
        window.display();
    }
    return 0;
}