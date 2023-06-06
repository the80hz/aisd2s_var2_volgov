//
// Created by Даниил Вольгов on 06.06.2023.
//

#ifndef AISD2S_VAR2_VOLGOV_GRAPH_H
#define AISD2S_VAR2_VOLGOV_GRAPH_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>

// Реализовать шаблонный класс, моделирющий ориентированный граф
template<typename Vertex, typename Distance = double>
class Graph {
public:
    struct Edge {
        Vertex from;
        Vertex to;
        Distance distance;
    };

    bool has_vertex(const Vertex& v) const;
    void add_vertex(const Vertex& v);
    bool remove_vertex(const Vertex& v);
    std::vector<Vertex> vertices() const;

    void add_edge(const Vertex& from, const Vertex& to, const Distance& d);
    bool remove_edge(const Vertex& from, const Vertex& to);
    bool remove_edge(const Edge& e);
    bool has_edge(const Vertex& from, const Vertex& to) const;
    bool has_edge(const Edge& e);

    std::vector<Edge> edges(const Vertex& vertex);

    size_t order() const;
    size_t degree() const;

    std::vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const;
    std::vector<Vertex> walk(const Vertex& start_vertex) const;

private:
    std::unordered_map<Vertex, std::vector<Edge>> adjacency_list;

    void walkHelper(const Vertex& current, std::unordered_map<Vertex, bool>& visited, std::vector<Vertex>& result) const;
};

// Определение методов


#endif //AISD2S_VAR2_VOLGOV_GRAPH_H
