#include <iostream>
#include <vector>
#include <functional>
#include "Graph.h"

// Функция для печати вершин, встреченных при обходе
template<typename Vertex>
void printVertices(const std::vector<Vertex>& vertices) {
    std::cout << "Visited vertices: ";
    for (const auto& vertex : vertices) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;
}

// Функция для поиска оптимальной точки склада
template<typename Vertex, typename Distance>
Vertex findOptimalWarehouse(const Graph<Vertex, Distance>& graph) {
    Vertex optimalWarehouse;
    Distance minMaxDistance = std::numeric_limits<Distance>::max();

    for (const auto& vertex : graph.vertices()) {
        Distance maxDistance = 0;
        auto shortestPaths = graph.shortest_path(vertex, vertex);

        for (const auto& path : shortestPaths) {
            if (path.distance > maxDistance) {
                maxDistance = path.distance;
            }
        }

        if (maxDistance < minMaxDistance) {
            minMaxDistance = maxDistance;
            optimalWarehouse = vertex;
        }
    }

    return optimalWarehouse;
}

// Функция для печати меню и обработки выбора пользователя
void printMenu() {
    std::cout << "-------- Menu --------" << std::endl;
    std::cout << "1. Add vertex" << std::endl;
    std::cout << "2. Add edge" << std::endl;
    std::cout << "3. Print all vertices" << std::endl;
    std::cout << "4. Print all edges of a vertex" << std::endl;
    std::cout << "5. Perform graph traversal" << std::endl;
    std::cout << "6. Find shortest path between vertices" << std::endl;
    std::cout << "7. Find optimal warehouse" << std::endl;
    std::cout << "8. Exit" << std::endl;
    std::cout << "-----------------------" << std::endl;
    std::cout << "Enter your choice: ";
}

int main() {
    Graph<int, double> graph;

    int choice;
    do {
        printMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int vertex;
                std::cout << "Enter vertex value: ";
                std::cin >> vertex;
                graph.add_vertex(vertex);
                break;
            }
            case 2: {
                int from, to;
                double distance;
                std::cout << "Enter source vertex: ";
                std::cin >> from;
                std::cout << "Enter destination vertex: ";
                std::cin >> to;
                std::cout << "Enter distance: ";
                std::cin >> distance;
                graph.add_edge(from, to, distance);
                break;
            }
            case 3: {
                std::vector<int> vertices = graph.vertices();
                std::cout << "Vertices: ";
                for (const auto& vertex : vertices) {
                    std::cout << vertex << " ";
                }
                std::cout << std::endl;
                break;
            }
            case 4: {
                int vertex;
                std::cout << "Enter vertex: ";
                std::cin >> vertex;
                std::vector<typename Graph<int, double>::Edge> edges = graph.edges(vertex);
                std::cout << "Edges of vertex " << vertex << ": ";
                for (const auto& edge : edges) {
                    std::cout << "(" << edge.from << "->" << edge.to << ") ";
                }
                std::cout << std::endl;
                break;
            }
            case 5: {
                int startVertex;
                std::cout << "Enter start vertex: ";
                std::cin >> startVertex;
                std::vector<int> visitedVertices;
                graph.walk(startVertex, [&](const int& vertex) {
                    visitedVertices.push_back(vertex);
                });
                printVertices(visitedVertices);
                break;
            }
            case 6: {
                int from, to;
                std::cout << "Enter source vertex: ";
                std::cin >> from;
                std::cout << "Enter destination vertex: ";
                std::cin >> to;
                std::vector<typename Graph<int, double>::Edge> shortestPath = graph.shortest_path(from, to);
                std::cout << "Shortest path from " << from << " to " << to << ": ";
                for (const auto& edge : shortestPath) {
                    std::cout << edge.from << "->" << edge.to << " ";
                }
                std::cout << std::endl;
                break;
            }
            case 7: {
                int optimalWarehouse = findOptimalWarehouse(graph);
                std::cout << "Optimal warehouse: " << optimalWarehouse << std::endl;
                break;
            }
            case 8: {
                std::cout << "Exiting the program..." << std::endl;
                break;
            }
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
        std::cout << std::endl;

    } while (choice != 8);

    return 0;
}
