#include <iostream>
#include <vector>
#include <functional>
#include "Graph.h"

#include <iostream>
#include <string>
#include "Graph.h"

// Функция для генерации случайного графа с n вершинами и m ребрами
Graph<int, double> generateRandomGraph(int n, int m) {
    Graph<int, double> graph;

    // Генерация случайных вершин
    for (int i = 1; i <= n; ++i) {
        graph.add_vertex(i);
    }

    // Генерация случайных ребер
    for (int i = 0; i < m; ++i) {
        int from = rand() % n + 1;
        int to = rand() % n + 1;
        double distance = static_cast<double>(rand() % 100) + 1; // случайное расстояние от 1 до 100
        graph.add_edge(from, to, distance);
    }

    return graph;
}

// Функция для печати графа в консоль
void printGraph(const Graph<int, double>& graph) {
    std::cout << "Vertices: ";
    for (const auto& vertex : graph.vertices()) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    std::cout << "Edges:" << std::endl;
    for (const auto& pair : graph.get_adjacency_list()) {
        int from = pair.first;
        const auto& edges = pair.second;
        for (const auto& edge : edges) {
            int to = edge.to;
            double distance = edge.distance;
            std::cout << from << " -> " << to << " (distance: " << distance << ")" << std::endl;
        }
    }
}

int main() {
    Graph<int, double> graph;
    int choice;

    do {
        std::cout << "----- Menu -----" << std::endl;
        std::cout << "1. Generate random graph" << std::endl;
        std::cout << "2. Add vertex" << std::endl;
        std::cout << "3. Add edge" << std::endl;
        std::cout << "4. Print graph" << std::endl;
        std::cout << "5. Find shortest path" << std::endl;
        std::cout << "6. Graph walk" << std::endl;
        std::cout << "7. Find optimal warehouse location" << std::endl;
        std::cout << "8. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int n, m;
                std::cout << "Enter the number of vertices: ";
                std::cin >> n;
                std::cout << "Enter the number of edges: ";
                std::cin >> m;
                graph = generateRandomGraph(n, m);
                std::cout << "Random graph generated." << std::endl;
                break;
            }
            case 2: {
                int vertex;
                std::cout << "Enter the vertex to add: ";
                std::cin >> vertex;
                graph.add_vertex(vertex);
                std::cout << "Vertex added." << std::endl;
                break;
            }
            case 3: {
                int from, to;
                double distance;
                std::cout << "Enter the source vertex: ";
                std::cin >> from;
                std::cout << "Enter the destination vertex: ";
                std::cin >> to;
                std::cout << "Enter the distance: ";
                std::cin >> distance;
                graph.add_edge(from, to, distance);
                std::cout << "Edge added." << std::endl;
                break;
            }
            case 4: {
                printGraph(graph);
                break;
            }
            case 5: {
                int start, end;
                std::cout << "Enter the start vertex: ";
                std::cin >> start;
                std::cout << "Enter the end vertex: ";
                std::cin >> end;
                auto shortest_path = graph.shortest_path(start, end);
                std::cout << "Shortest path: ";
                for (const auto& edge : shortest_path) {
                    std::cout << edge.from << " -> " << edge.to << " ";
                }
                std::cout << std::endl;
                break;
            }
            case 6: {
                int start_vertex;
                std::cout << "Enter the start vertex for graph walk: ";
                std::cin >> start_vertex;
                std::cout << "Graph walk: ";
                graph.walk(start_vertex, [](const int& vertex) {
                    std::cout << vertex << " ";
                });
                std::cout << std::endl;
                break;
            }
            case 7: {
                int end_vertex;
                double max_cost = std::numeric_limits<double>::max();
                int optimal_point = 0;

                std::cout << "Enter the end vertex for warehouse location: ";
                std::cin >> end_vertex;

                for (const auto& vertex : graph.vertices()) {
                    auto path = graph.shortest_path(vertex, end_vertex);
                    double max_distance = 0.0;

                    for (const auto& edge : path) {
                        max_distance = std::max(max_distance, edge.distance);
                    }

                    if (max_distance < max_cost) {
                        max_cost = max_distance;
                        optimal_point = vertex;
                    }
                }

                std::cout << "Optimal point for warehouse placement: " << optimal_point << std::endl;
                break;
            }
            case 8: {
                std::cout << "Exiting..." << std::endl;
                break;
            }
            default: {
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
            }
        }

        std::cout << std::endl;

    } while (choice != 8);

    return 0;
}
