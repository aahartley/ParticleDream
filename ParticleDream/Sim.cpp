#include "Sim.h"
#include "Particle.h"
#include "Matrix.h"
#include <iostream>
float acceleration = 3000;
constexpr float u = 0.5f;
constexpr float e = 0.5f;
int num = 1000;

Sim::Sim() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window = new sf::RenderWindow(sf::VideoMode(800, 800), "Particles", sf::Style::Default, settings);
}
void collision(Matrix& matrix) {
  // #pragma omp parallel for num_threads(2)
    for (int i = 0; i < num; i++) {
        matrix[i][6] = 0;
        /*
        if ((matrix[i][3] >= 250 || matrix[i][3] <= 198)&& matrix[i][2] <= 200) {
            // Vn = (V*N)N
            sf::Vector2f Vn{ matrix[i][0],(matrix[i][1] * 1) * 1 };
            //Vt = V-Vn      
            sf::Vector2f Vt{ matrix[i][0],(matrix[i][1] - Vn.y) };

            //V' = (1-u)Vt-eVn    //u- friction   //e-resilience   0.0-1.0
            matrix[i][1] = (1 - u) * Vt.y - e * Vn.y;
            float S=0;
            if (matrix[i][3] <= 198)S = 198.0;
            if (matrix[i][3] >= 250)S = 250.0f;
            //P'h = Ph - 2[(Ph-S)*N]N
            matrix[i][3] = matrix[i][3] - 2 * ((matrix[i][3] - S) * 1) * 1;
            //P't = Pt - 2[(Pt-S)*N]N
            matrix[i][5] = matrix[i][5] - 2 * ((matrix[i][5] - S) * 1) * 1;
            matrix[i][6] = 1;
        }
        if ((matrix[i][3] >= 450 || matrix[i][3] <= 198) && matrix[i][2] <= 350) {
            // Vn = (V*N)N
            sf::Vector2f Vn{ matrix[i][0],(matrix[i][1] * 1) * 1 };
            //Vt = V-Vn      
            sf::Vector2f Vt{ matrix[i][0],(matrix[i][1] - Vn.y) };

            //V' = (1-u)Vt-eVn    //u- friction   //e-resilience   0.0-1.0
            matrix[i][1] = (1 - u) * Vt.y - e * Vn.y;
            float S = 0;
            if (matrix[i][3] <= 198)S = 198.0f;
            if (matrix[i][3] >= 450)S = 450.0f;
            //P'h = Ph - 2[(Ph-S)*N]N
            matrix[i][3] = matrix[i][3] - 2 * ((matrix[i][3] - S) * 1) * 1;
            //P't = Pt - 2[(Pt-S)*N]N
            matrix[i][5] = matrix[i][5] - 2 * ((matrix[i][5] - S) * 1) * 1;
            matrix[i][6] = 1;

        }*/
        sf::Vector2f point{ matrix[i][2],matrix[i][3] };
        //obstacle  100,500 300,700   

        //std::cout << m * point.x + b << "\n";
        if (point.y>=point.x+400&&point.y<=695&&point.x<=300) {
           // std::cout << "WORKING\n";
            sf::Vector2f N{ (float)std::cos(0),(float)std::sin(0) };
            // Vn = (V*N)N
            sf::Vector2f Vn{ (matrix[i][0] * N.x) * N.x,(matrix[i][1] * N.y) * N.y };
            //Vt = V-Vn      
            sf::Vector2f Vt{ matrix[i][0] - Vn.x,(matrix[i][1] - Vn.y) };

            //V' = (1-u)Vt-eVn    //u- friction   //e-resilience   0.0-1.0
            matrix[i][0] = (1 - u) * Vt.x - e * Vn.x;
            matrix[i][1] = (1 - u) * Vt.y - e * Vn.y;
            float S = point.y;
            //P'h = Ph - 2[(Ph-S)*N]N
            matrix[i][2] = matrix[i][2] - 2 * ((matrix[i][2] - point.x-1) * N.x) * N.x;
            matrix[i][3] = matrix[i][3] - 2 * ((matrix[i][3] - S+2) * N.y) * N.y;
            //P't = Pt - 2[(Pt-S)*N]N
            matrix[i][4] = matrix[i][4] - 2 * ((matrix[i][4] - point.x-1) * 1) * 1;
            matrix[i][5] = matrix[i][5] - 2 * ((matrix[i][5] - S+2) * 1) * 1;
         //   matrix[i][6] = 1;

        }
        
        //floor and top
         if ((matrix[i][3] >= 700 || matrix[i][3] <= 198) ) {
           // Vn = (V*N)N
            sf::Vector2f Vn{ (matrix[i][0]*1)*1,(matrix[i][1] * 1) * 1 };
            //Vt = V-Vn      
            sf::Vector2f Vt{ matrix[i][0]-Vn.x,(matrix[i][1] - Vn.y) };

            //V' = (1-u)Vt-eVn    //u- friction   //e-resilience   0.0-1.0
            matrix[i][0] = (1 - u) * Vt.x - e * Vn.x;
            matrix[i][1] = (1 - u) * Vt.y - e * Vn.y;
            float S = 0;
            if (matrix[i][3] <= 198)S = 198.0f;
            if (matrix[i][3] >= 700)S = 700;
            //P'h = Ph - 2[(Ph-S)*N]N
            matrix[i][2] = matrix[i][2] - 2 * ((matrix[i][2] - point.x-1) * 1) * 1;
            matrix[i][3] = matrix[i][3] - 2 * ((matrix[i][3] - S) * 1) * 1;
            //P't = Pt - 2[(Pt-S)*N]N
            matrix[i][4] = matrix[i][4] - 2 * ((matrix[i][4] - point.x-1) * 1) * 1;
            matrix[i][5] = matrix[i][5] - 2 * ((matrix[i][5] - S) * 1) * 1;
            matrix[i][6] = 1;

        }    
         
         //left and right
        if ((matrix[i][2] >= 698 || matrix[i][2] <= 101) ) {
            // Vn = (V*N)N
            sf::Vector2f Vn{ (matrix[i][0]*1)*1,(matrix[i][1] * 1) * 1 };
            //Vt = V-Vn      
            sf::Vector2f Vt{ matrix[i][0]-Vn.x,(matrix[i][1] - Vn.y) };

            //V' = (1-u)Vt-eVn    //u- friction   //e-resilience   0.0-1.0
            matrix[i][0] = (1 - u) * Vt.x - e * Vn.x;
            matrix[i][1] = (1 - u) * Vt.y - e * Vn.y;
            float S = 0;
            if (matrix[i][2] <= 101)S = 101.0f;
            if (matrix[i][2] >= 698)S = 698.0f;
            //P'h = Ph - 2[(Ph-S)*N]N
            matrix[i][2] = matrix[i][2] - 2 * ((matrix[i][2] - S) * 1) * 1;
            matrix[i][3] = matrix[i][3] - 2 * ((matrix[i][3] - S) * 1) * 1;
            //P't = Pt - 2[(Pt-S)*N]N
            matrix[i][4] = matrix[i][4] - 2 * ((matrix[i][4] - S) * 1) * 1;
            matrix[i][5] = matrix[i][5] - 2 * ((matrix[i][5] - S) * 1) * 1;
            matrix.fill();
        }

        
        

     
        
    }
}
void Sim::path(Matrix& matrix,float dt) {
    float transform[7]= {
                             {0}, //vx
                             {acceleration * dt}, //vy
                             {0},  //x
                             {0}, //y
                             {0}, //cx2
                             {0}, //cy2
                             {0} //rad
                           };
    
    matrix.add(transform,dt);
    collision(matrix);
    /*
    for (int i = 0; i < buffer.size(); i++) {
        for (int j = 0; j < 1; j++) {
            buffer[i]->velocity.x = matrix[i][j];
            buffer[i]->velocity.y = matrix[i][j + 1];
            buffer[i]->coord.x = matrix[i][j + 2];
            buffer[i]->coord.y = matrix[i][j + 3];
            //   coords[i][j + 4] 


        }
        buffer[i]->circle.setPosition(buffer[i]->coord);
    }*/
}
void Sim::draw() {
    window->setFramerateLimit(60);
    /*
    Particle p1{ sf::Vector2f{650,200},10.0f };
    Particle p2{ sf::Vector2f{500,190},100.0f };
    sf::CircleShape circle{ 5.0f };
    circle.setPosition(p1.coord);
    p1.circle = circle;
    p1.coord2 = sf::Vector2f{ p1.coord.x,p1.coord.y - 1 };
    sf::CircleShape tail{ 5.0f };
    tail.setFillColor(sf::Color::Red);
    tail.setPosition(p1.coord2);
    p1.circle2 = tail;

    sf::CircleShape circle2{ 10.0f };
    circle2.setPosition(p2.coord);
    p2.circle = circle2;
    sf::CircleShape tail2{ 10.0f };
    p2.coord2 = sf::Vector2f{ p2.coord.x,p2.coord.y - 10 };
    p2.circle2 = tail2;

    Particle t{ sf::Vector2f{300,200},10.0f };
    sf::CircleShape test{ 5.0f };
    test.setPosition(sf::Vector2f{ 300,200 });
    t.circle = test;S

    std::vector<Particle*> buffer;
    buffer.push_back(&p1);
    buffer.push_back(&p2);
    */
    Matrix particles;
    particles.fill();

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
    sf::Vertex line5[] =
    {
        sf::Vertex(sf::Vector2f{100,500}),
        sf::Vertex(sf::Vector2f{300,700})
    };
    sf::Clock clock;
    sf::Time time_per_frame = sf::seconds(1.f / 60.f);
    sf::Time time_since_last_update = sf::Time::Zero;
    sf::Time time_sleep;
    float dt = 1.0f / 60.0f;
    dt = 0.12f;
    bool first = true;
    float time = 0.0f;
    while (window->isOpen())
    {
        //  time_sleep = sf::Time::Zero;
        dt = clock.restart().asSeconds();
        time += dt;
       // std::cout << time << "\n";
        //if (time > 5)particles.fill(buffer,1000);
        if (time > 5*2)acceleration = 800.0f;
   //     if (time > 5 * 3)acceleration = -800.0f;
        if (time > 5 * 4)acceleration = 800.0f;
     //   if (time > 5 * 5)acceleration = -800.0f;
        if (time > 5 * 6)acceleration = 800.0f;




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
    /*
        //#pragma omp parallel for num_threads(2) schedule(static)
        for (int i = 0; i < buffer.size(); i++) {
                   // buffer[i]->calculation(dt);
        }*/
      //  t.constant(dt);

        path(particles,dt);
        
 
            window->clear();
            /*
            for (int i = 0; i < buffer.size(); i++) {
                window->draw(buffer[i]->circle);
                window->draw(buffer[i]->circle2);

            }*/
            sf::VertexArray points(sf::Points, num*2);

            for (int i = 0; i < num; i++) {
                sf::Vertex point;
                sf::Vertex point2;
                sf::Color color;
                if (particles[i][6] == 0)color=sf::Color::Blue;
                if (particles[i][6] == 1) {
                   // std::cout << "White" << std::endl;
                    color = sf::Color::White;
                }
              //  std::cout << particles[i][6];
              //  circle.setRadius(particles[i][6]);
              //  circle.setPosition(sf::Vector2f{ particles[i][2],particles[i][3] });
                point.position = sf::Vector2f{ particles[i][2],particles[i][3] };
                point.color = color;

              //  sf::CircleShape circle2;
               //circle2.setRadius(particles[i][6]);
              //  circle2.setPosition(sf::Vector2f{ particles[i][4],particles[i][5] });
                point2.position = sf::Vector2f{ particles[i][4],particles[i][5] };
                point2.color = color;

               // circle2.setFillColor(sf::Color::Red);
             //   window->draw(circle);
              //  window->draw(circle2);
                points.append(point);
                points.append(point2);

            }      
            window->draw(points);
           // window->draw(t.circle);
            window->draw(lines, 2, sf::Lines);
          //  window->draw(line, 2, sf::Lines);
            window->draw(line2, 2, sf::Lines);
            window->draw(line3, 2, sf::Lines);
            window->draw(line4, 2, sf::Lines);
            window->draw(line5, 2, sf::Lines);
            window->display();
            
        
    }
}