//
// Created by Даниил Вольгов on 06.06.2023.
//

#include "Graph.h"


template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::has_vertex(const Vertex& v) const {
    return adjacency_list.count(v) > 0;
}

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::add_vertex(const Vertex& v) {
    if (!has_vertex(v)) {
        adjacency_list[v] = std::vector<Edge>();
    }
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::remove_vertex(const Vertex& v) {
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

template<typename Vertex, typename Distance>
std::vector<Vertex> Graph<Vertex, Distance>::vertices() const {
    std::vector<Vertex> result;
    result.reserve(adjacency_list.size());

    for (const auto& pair : adjacency_list) {
        result.push_back(pair.first);
    }

    return result;
}

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::add_edge(const Vertex& from, const Vertex& to, const Distance& d) {
    add_vertex(from);
    add_vertex(to);

    adjacency_list[from].push_back({from, to, d});
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::remove_edge(const Vertex& from, const Vertex& to) {
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

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::remove_edge(const Edge& e) {
    return remove_edge(e.from, e.to);
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::has_edge(const Vertex& from, const Vertex& to) const {
    if (has_vertex(from) && has_vertex(to)) {
        const auto& edges = adjacency_list.at(from);
        return std::any_of(edges.begin(), edges.end(), [&](const Edge& edge) {
            return edge.to == to;
        });
    }

    return false;
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::has_edge(const Edge& e) {
    return has_edge(e.from, e.to);
}

template<typename Vertex, typename Distance>
std::vector<typename Graph<Vertex, Distance>::Edge> Graph<Vertex, Distance>::edges(const Vertex& vertex) {
    std::vector<Edge> result;

    if (has_vertex(vertex)) {
        result = adjacency_list[vertex];
    }

    return result;
}

template<typename Vertex, typename Distance>
size_t Graph<Vertex, Distance>::order() const {
    return adjacency_list.size();
}

template<typename Vertex, typename Distance>
size_t Graph<Vertex, Distance>::degree() const {
    size_t max_degree = 0;

    for (const auto& pair : adjacency_list) {
        max_degree = std::max(max_degree, pair.second.size());
    }

    return max_degree;
}

template<typename Vertex, typename Distance>
std::vector<typename Graph<Vertex, Distance>::Edge> Graph<Vertex, Distance>::shortest_path(const Vertex& from, const Vertex& to) const {
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

template<typename Vertex, typename Distance>
std::vector<Vertex> Graph<Vertex, Distance>::walk(const Vertex& start_vertex) const {
    std::vector<Vertex> result;
    std::unordered_map<Vertex, bool> visited;

    for (const auto& pair : adjacency_list) {
        visited[pair.first] = false;
    }

    walkHelper(start_vertex, visited, result);

    return result;
}

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::walkHelper(const Vertex& current, std::unordered_map<Vertex, bool>& visited, std::vector<Vertex>& result) const {
    visited[current] = true;
    result.push_back(current);

    if (adjacency_list.count(current) > 0) {
        for (const auto& edge : adjacency_list.at(current)) {
            if (!visited[edge.to]) {
                walkHelper(edge.to, visited, result);
            }
        }
    }
}