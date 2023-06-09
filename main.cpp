#include <iostream>
#include <vector>
#include <functional>
#include "Graph.h"

#include <iostream>
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
    // Генерация случайного графа
    Graph<int, double> graph = generateRandomGraph(6, 10);

    // Печать графа в консоль
    std::cout << "Graph:" << std::endl;
    printGraph(graph);
    std::cout << std::endl;

    // Поиск кратчайшего пути
    int start_vertex = 1;
    int end_vertex = 6;
    std::vector<Graph<int, double>::Edge> shortest_path = graph.shortest_path(start_vertex, end_vertex);

    std::cout << "Shortest path from " << start_vertex << " to " << end_vertex << ":" << std::endl;
    for (const auto& edge : shortest_path) {
        std::cout << edge.from << " -> " << edge.to << " (distance: " << edge.distance << ")" << std::endl;
    }
    std::cout << std::endl;

    // Обход графа
    std::cout << "Graph walk:" << std::endl;
    graph.walk(start_vertex, [](const int& vertex) {
        std::cout << vertex << " ";
    });
    std::cout << std::endl;

    // Решение задачи поиска оптимальной точки для размещения склада
    double max_cost = std::numeric_limits<double>::max();
    int optimal_point = 0;

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

    return 0;
}
