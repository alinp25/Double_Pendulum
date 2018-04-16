#include <SFML/Graphics.hpp>
#include <cmath>

const int WIDTH = 1000;
const int HEIGHT = 1000;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Double Pendulum!");
    window.setFramerateLimit(60);
    float x0 = WIDTH / 2, y0 = HEIGHT / 2 - 200;
    float length1 = 400, length2 = 300;
    float x1 = x0, y1 = y0 + length1;
    float x2 = x1, y2 = y1 + length2;
    float angle1 = M_PI / 8, angle2 = M_PI / 4;
    float m1 = 10, m2 = 20;
    float angle1_v = 0, angle2_v = 0;
    const float g = 1;

    sf::CircleShape ball1, ball2;
    ball1.setRadius(m1);
    ball2.setRadius(m2);
    ball1.setPosition(x1 - m1, y1 - m1);
    ball2.setPosition(x2 - m2, y2 - m2);
    sf::Vertex line1[] = {
        sf::Vertex(sf::Vector2f(x0, y0)),
        sf::Vertex(sf::Vector2f(x1, y1))
    };
    sf::Vertex line2[] = {
        sf::Vertex(sf::Vector2f(x1, y1)),
        sf::Vertex(sf::Vector2f(x2, y2))
    };
    sf::VertexArray path;
    path.append(sf::Vertex(sf::Vector2f(x0 + x2, x0 + y2)));
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float top1 = -g * (2 * m1 + m2) * sin(angle1);
        float top2 = -m2 * g * sin(angle1 - 2 * angle2);
        float top3 = -2 * sin(angle1 - angle2) * m2;
        float top4 = angle2_v * angle2_v * length2 + angle1_v * angle1_v * length1 * cos(angle1 - angle2);
        float down = length1 * (2 * m1 + m2 - m2 * cos(2 * angle1 - 2 * angle2));
        float angle1_a = (top1 + top2 + top3 * top4) / down;

        top1 = 2 * sin(angle1 - angle2);
        top2 = angle1_v * angle1_v * length1 * (m1 + m2);
        top3 = g * (m1 + m2) * cos(angle1);
        top4 = angle2_v * angle2_v * length2 * m2 * cos(angle1 - angle2);
        down = length2 * (2 * m1 + m2 - m2 * cos(2 * angle1 - 2 * angle2));
        float angle2_a = top1 * (top2 + top3 + top4) / down;

        x1 = length1 * sin(angle1);
        y1 = length1 * cos(angle1);
        x2 = x1 + length2 * sin(angle2);
        y2 = y1 + length2 * cos(angle2);
        ball1.setPosition(x0 + x1 - m1, y0 + y1 - m1);
        ball2.setPosition(x0 + x2 - m2, y0 + y2 - m2);
        line1[0] = sf::Vector2f(x0, y0);
        line1[1] = sf::Vector2f(x0 + x1, y0 + y1);
        line2[0] = sf::Vector2f(x0 + x1, y0 + y1);
        line2[1] = sf::Vector2f(x0 + x2, y0 + y2);
        path.append(line2[1]);

        window.clear();
        window.draw(line1, 2, sf::Lines);
        window.draw(line2, 2, sf::Lines);
        window.draw(ball1);
        window.draw(ball2);
        window.draw(path);
        window.display();
        
        angle1 += angle1_v;
        angle2 += angle2_v;
        angle1_v += angle1_a;
        angle2_v += angle2_a;
    }
    return 0;
}

