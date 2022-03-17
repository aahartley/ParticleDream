#include "Sim.h"
#include "Particle.h"
#include "Matrix.h"
#include <iostream>
Sim::Sim() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window = new sf::RenderWindow(sf::VideoMode(800, 800), "Particles", sf::Style::Default, settings);
}

void Sim::path(Matrix& matrix,float dt) {
    float v0 = 0 + 10 * dt;
    float transform[5][1]= {
                             {0},
                             {10.0f * dt},
                             {0},
                             {((v0 +v0)/ 2) * dt},
                             {1}
                           };

    matrix.add(transform,dt);
}
void Sim::draw() {
    window->setFramerateLimit(60);
    Particle p1{ sf::Vector2f{400,200},10.0f };
    Particle p2{ sf::Vector2f{500,190},100.0f };
    sf::CircleShape circle{ 5.0f };
    circle.setPosition(p1.coord);
    p1.circle = circle;
    sf::CircleShape circle2{ 10.0f };
    circle2.setPosition(p2.coord);
    p2.circle = circle2;

    Particle t{ sf::Vector2f{300,200},10.0f };
    sf::CircleShape test{ 5.0f };
    test.setPosition(sf::Vector2f{ 300,200 });
    t.circle = test;

    std::vector<Particle*> buffer;
    buffer.push_back(&p1);
    buffer.push_back(&p2);

    Matrix coords;
    coords.fill(buffer);

    sf::Vertex lines[] =
    {
        sf::Vertex(sf::Vector2f{0,200}),
        sf::Vertex(sf::Vector2f{800,200})
    };

    //ball bottom
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f{0,700}),
        sf::Vertex(sf::Vector2f{800,700})
    };
    //ball top
    sf::Vertex line2[] =
    {
        sf::Vertex(sf::Vector2f{0,100}),
        sf::Vertex(sf::Vector2f{800,100})
    };
    //ball left
    sf::Vertex line3[] =
    {
        sf::Vertex(sf::Vector2f{100,100}),
        sf::Vertex(sf::Vector2f{100,700})
    };
    //ball right
    sf::Vertex line4[] =
    {
        sf::Vertex(sf::Vector2f{700,100}),
        sf::Vertex(sf::Vector2f{700,700})
    };
    sf::Clock clock;
    sf::Time time_per_frame = sf::seconds(1.f / 60.f);
    sf::Time time_since_last_update = sf::Time::Zero;
    sf::Time time_sleep;
    float dt = 1.0f / 60.0f;
    dt = 0.12f;
    bool first = true;
    while (window->isOpen())
    {
        //  time_sleep = sf::Time::Zero;
        dt = clock.restart().asSeconds();
      //  std::cout << dt << '\n';
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                /*#pragma omp parallel for num_threads(2)
                                for (int i = 0; i < buffer.size(); i++) {
                                    buffer[i]->acceleration.y *= -1.0f;
                                }
                                */

            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                /*#pragma omp parallel for num_threads(2)
                                for (int i = 0; i < buffer.size(); i++) {
                                    if (buffer[i]->acceleration.x == 0)
                                        buffer[i]->acceleration.x = 1.0f;
                                    else
                                        buffer[i]->acceleration.x *= -1.0f;
                                }

                            }*/
            }
        }
        if (!first) {
            for (int i = 0; i < buffer.size(); i++) {
                buffer[i]->initialize(dt);
            }
           // first = false;
        }
        else {
            //#pragma omp parallel for num_threads(2) schedule(static)
            for (int i = 0; i < buffer.size(); i++) {
             //   buffer[i]->calculation(dt);
            }
            t.constant(dt);

            path(coords,dt);
        }
        for (int i = 0; i < buffer.size(); i++) {
            for (int j = 0; j < 1; j++) {
                buffer[i]->velocity.x = coords[i][j];
                buffer[i]->velocity.y = coords[i][j + 1];
                buffer[i]->coord.x= coords[i][j + 2];
                buffer[i]->coord.y = coords[i][j + 3];
             //   coords[i][j + 4] 


            }
            buffer[i]->circle.setPosition(buffer[i]->coord);
        }
            window->clear();
            for (int i = 0; i < buffer.size(); i++) {
                window->draw(buffer[i]->circle);
            }
            window->draw(t.circle);
            window->draw(lines, 2, sf::Lines);
            window->draw(line, 2, sf::Lines);
            window->draw(line2, 2, sf::Lines);
            window->draw(line3, 2, sf::Lines);
            window->draw(line4, 2, sf::Lines);
            window->display();
        
    }
}