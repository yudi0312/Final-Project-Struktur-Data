#include <SFML/Graphics.hpp>
#include "TransportationSystem.h"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Transportasi Map");

    TransportationSystem system;
    system.initializeDefaultData();

    const auto& nodes = system.getGraph().getNodes();

    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cerr << "Gagal memuat font.\n";
        return 1;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        // Gambar edge
        for (const auto& [fromName, node] : nodes) {
            for (const auto& edge : node.getEdges()) {
                const auto& toNode = nodes.at(edge.getDestination());

                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(node.getX(), node.getY()), sf::Color::Black),
                    sf::Vertex(sf::Vector2f(toNode.getX(), toNode.getY()), sf::Color::Black)
                };
                window.draw(line, 2, sf::Lines);
            }
        }

        // Gambar node + label
        for (const auto& [name, node] : nodes) {
            sf::CircleShape circle(8);
            circle.setFillColor(sf::Color::Blue);
            circle.setOrigin(8, 8);
            circle.setPosition(node.getX(), node.getY());
            window.draw(circle);

            sf::Text label(name, font, 14);
            label.setFillColor(sf::Color::Black);
            label.setPosition(node.getX() + 10, node.getY() - 10);
            window.draw(label);
        }

        window.display();
    }

    return 0;
}
