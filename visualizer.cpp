#include <SFML/Graphics.hpp>
#include "TransportationSystem.h"
#include <iostream>
#include <cmath>

float getDistance(float x1, float y1, float x2, float y2) {
    return std::sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 700), "Transportasi Map");

    TransportationSystem system;
    system.loadFromFile("transportation_data.txt");

    const float SCALE = 10.0f;

    const auto& nodes = system.getGraph().getNodes();
    for (const auto& [name, node] : nodes) {
        std::cout << name << " => (" << node.getX() << ", " << node.getY() << ")\n";
    }

    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cerr << "Gagal memuat font.\n";
        return 1;
    }

    std::string selectedStart = "", selectedEnd = "";
    RouteResult currentRoute;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            float mx = event.mouseButton.x;
            float my = event.mouseButton.y;

            // Klik kanan → tambah lokasi
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                std::string newName;
                std::cout << "Nama lokasi baru: ";
                std::cin >> newName;

                system.addLocation(newName);
                system.setLocationCoordinates(newName, mx / SCALE, my / SCALE);
                std::cout << "Lokasi baru ditambahkan: " << newName << " (" << mx / SCALE << ", " << my / SCALE << ")\n";

                if (!selectedStart.empty() && newName != selectedStart) {
                    system.addRoute(selectedStart, newName, RouteType::BIASA);
                    std::cout << "Rute otomatis dari " << selectedStart << " ke " << newName << " ditambahkan.\n";
                    selectedStart = "";
                } else {
                    selectedStart = newName;
                }

                system.saveToFile("transportation_data.txt");
            }

            // Klik kiri → pilih dua lokasi untuk cari rute terbaik
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                for (const auto& [name, node] : system.getGraph().getNodes()) {
                    float dist = getDistance(mx, my, node.getX() * SCALE, node.getY() * SCALE);
                    if (dist <= 10) {
                        if (selectedStart.empty()) {
                            selectedStart = name;
                            std::cout << "Start: " << name << std::endl;
                        } else if (selectedEnd.empty() && name != selectedStart) {
                            selectedEnd = name;
                            std::cout << "End: " << name << std::endl;

                            system.setUserPreferences();
                            system.findBestRoute(selectedStart, selectedEnd);
                            currentRoute = system.getLastRoute();

                            if (currentRoute.found) {
                                std::cout << "=== RUTE TERBAIK ===\n";
                                for (const auto& kota : currentRoute.path)
                                    std::cout << " - " << kota << '\n';
                                std::cout << "Total Jarak: " << currentRoute.totalDistance << " km\n";
                            } else {
                                std::cout << "Tidak ditemukan rute dari " << selectedStart << " ke " << selectedEnd << '\n';
                            }
                        } else {
                            selectedStart = name;
                            selectedEnd = "";
                        }
                        break;
                    }
                }
            }
        }

        window.clear(sf::Color::White);
        const auto& nodes = system.getGraph().getNodes();

        // Gambar edge (warna sesuai tipe rute)
        for (const auto& [fromName, node] : nodes) {
            for (const auto& edge : node.getEdges()) {
                if (fromName < edge.getDestination()) {
                    const auto& toNode = nodes.at(edge.getDestination());

                    sf::Color edgeColor = sf::Color::Black;
                    switch (edge.getRouteType()) {
                        case RouteType::TOL: edgeColor = sf::Color::Blue; break;
                        case RouteType::RUSAK: edgeColor = sf::Color(139, 69, 19); break;
                        case RouteType::GUNUNG: edgeColor = sf::Color(0, 100, 0); break;
                        default: edgeColor = sf::Color::Black;
                    }

                    sf::Vertex line[] = {
                        sf::Vertex(sf::Vector2f(node.getX() * SCALE, node.getY() * SCALE), edgeColor),
                        sf::Vertex(sf::Vector2f(toNode.getX() * SCALE, toNode.getY() * SCALE), edgeColor)
                    };
                    window.draw(line, 2, sf::Lines);
                }
            }
        }

        // Gambar rute terbaik (merah)
        if (currentRoute.found) {
            for (size_t i = 0; i + 1 < currentRoute.path.size(); ++i) {
                const auto& from = nodes.at(currentRoute.path[i]);
                const auto& to = nodes.at(currentRoute.path[i + 1]);

                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(from.getX() * SCALE, from.getY() * SCALE), sf::Color::Red),
                    sf::Vertex(sf::Vector2f(to.getX() * SCALE, to.getY() * SCALE), sf::Color::Red)
                };
                window.draw(line, 2, sf::Lines);
            }
        }

        // Gambar node dan label
        for (const auto& [name, node] : nodes) {
            sf::CircleShape circle(8);
            circle.setOrigin(8, 8);
            circle.setPosition(node.getX() * SCALE, node.getY() * SCALE);

            if (name == selectedStart)
                circle.setFillColor(sf::Color::Green);
            else if (name == selectedEnd)
                circle.setFillColor(sf::Color::Red);
            else
                circle.setFillColor(sf::Color::Blue);

            window.draw(circle);

            sf::Text label(name, font, 14);
            label.setFillColor(sf::Color::Black);
            label.setPosition((node.getX() + 1) * SCALE, (node.getY() - 1) * SCALE);
            window.draw(label);
        }

        window.display();
    }

    return 0;
}