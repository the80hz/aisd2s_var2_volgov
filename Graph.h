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

template<typename Vertex, typename Distance = double>
class Graph {
public:
    struct Edge {
        Vertex from;
        Vertex to;
        Distance distance;
    };

    bool has_vertex(const Vertex& v) const {
        return adjacency_list.count(v) > 0;
    }

    void add_vertex(const Vertex& v) {
        if (!has_vertex(v)) {
            adjacency_list[v] = std::vector<Edge>();
        }
    }

    bool remove_vertex(const Vertex& v) {
        if (has_vertex(v)) {
            adjacency_list.erase(v);

            for (auto& pair : adjacency_list) {
                auto& edges = pair.second;
                edges.erase(std::remove_if(edges.begin(), edges.end(), [&](const Edge& edge) {
                    return edge.from == v || edge.to == v;
                }), edges.end());
            }

            return true;
        }

        return false;
    }

    std::vector<Vertex> vertices() const {
        std::vector<Vertex> result;
        result.reserve(adjacency_list.size());

        for (const auto& pair : adjacency_list) {
            result.push_back(pair.first);
        }

        return result;
    }

    void add_edge(const Vertex& from, const Vertex& to, const Distance& d) {
        add_vertex(from);
        add_vertex(to);

        adjacency_list[from].push_back({from, to, d});
    }

    bool remove_edge(const Vertex& from, const Vertex& to) {
        if (has_vertex(from) && has_vertex(to)) {
            auto& edges = adjacency_list[from];
            auto it = std::find_if(edges.begin(), edges.end(), [&](const Edge& edge) {
                return edge.to == to;
            });

            if (it != edges.end()) {
                edges.erase(it);
                return true;
            }
        }

        return false;
    }

    // c учетом расстояния
    bool remove_edge(const Edge& e) {
        if (has_vertex(e.from) && has_vertex(e.to)) {
            auto& edges = adjacency_list[e.from];
            auto it = std::find_if(edges.begin(), edges.end(), [&e](const Edge& edge) {
                return edge.to == e.to && edge.distance == e.distance;
            });

            if (it != edges.end()) {
                edges.erase(it);
                return true;
            }
        }

        return false;
    }

    bool has_edge(const Vertex& from, const Vertex& to) const {
        if (has_vertex(from) && has_vertex(to)) {
            const auto& edges = adjacency_list[from];
            return std::find_if(edges.begin(), edges.end(), [&](const Edge& edge) {
                return edge.to == to;
            }) != edges.end();
        }
        return false;
    }

    // c учетом distance в Edge
    bool has_edge(const Edge& e) const {
        if (has_vertex(e.from) && has_vertex(e.to)) {
            const auto& edges = adjacency_list[e.from];
            return std::find_if(edges.begin(), edges.end(), [&e](const Edge& edge) {
                return edge.to == e.to && edge.distance == e.distance;
            }) != edges.end();
        }
        return false;
    }

    std::vector<Edge> edges(const Vertex& vertex) {
        std::vector<Edge> result;

        if (has_vertex(vertex)) {
            result = adjacency_list[vertex];
        }

        return result;
    }

    [[nodiscard]] size_t order() const {
        return adjacency_list.size();
    }

    [[nodiscard]] size_t degree() const {
        size_t max_degree = 0;

        for (const auto& pair : adjacency_list) {
            max_degree = std::max(max_degree, pair.second.size());
        }

        return max_degree;
    }

    std::vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const {
        std::unordered_map<Vertex, Distance> distances;
        std::unordered_map<Vertex, Vertex> parents;

        for (const auto& pair : adjacency_list) {
            distances[pair.first] = std::numeric_limits<Distance>::max();
        }

        distances[from] = Distance();

        for (size_t i = 0; i < adjacency_list.size() - 1; ++i) {
            for (const auto& pair : adjacency_list) {
                const auto& vertex = pair.first;
                const auto& edges = pair.second;

                for (const auto& edge : edges) {
                    const auto& from_vertex = edge.from;
                    const auto& to_vertex = edge.to;
                    const auto& distance = edge.distance;

                    if (distances[from_vertex] + distance < distances[to_vertex]) {
                        distances[to_vertex] = distances[from_vertex] + distance;
                        parents[to_vertex] = from_vertex;
                    }
                }
            }
        }

        std::vector<Edge> path;

        if (parents.count(to) > 0) {
            Vertex current = to;

            while (current != from) {
                const Vertex parent = parents[current];
                const Distance distance = distances[current] - distances[parent];

                path.push_back({parent, current, distance});

                current = parent;
            }

            std::reverse(path.begin(), path.end());
        }

        return path;
    }

    void walk(const Vertex& start_vertex, std::function<void(const Vertex&)> action) const {
        std::unordered_map<Vertex, bool> visited;
        walkHelper(start_vertex, visited, action);
    }

    const std::vector<Vertex>& vertices(std::vector<Vertex>& result) const {
        result.clear();
        result.reserve(adjacency_list.size());

        for (const auto& pair : adjacency_list) {
            result.push_back(pair.first);
        }

        return result;
    }

    const std::vector<Edge>& edges(const Vertex& vertex, std::vector<Edge>& result) const {
        result.clear();

        if (has_vertex(vertex)) {
            result = adjacency_list[vertex];
        }

        return result;
    }

    // get adjacency_list
    const std::unordered_map<Vertex, std::vector<Edge>>& get_adjacency_list() const {
        return adjacency_list;
    }

private:
    std::unordered_map<Vertex, std::vector<Edge>> adjacency_list;

    void walkHelper(const Vertex& current, std::unordered_map<Vertex, bool>& visited, std::function<void(const Vertex&)> action) const {
        visited[current] = true;
        action(current);

        if (adjacency_list.count(current) > 0) {
            for (const auto& edge : adjacency_list.at(current)) {
                if (!visited[edge.to]) {
                    walkHelper(edge.to, visited, action);
                }
            }
        }
    }
};


#endif //AISD2S_VAR2_VOLGOV_GRAPH_H
