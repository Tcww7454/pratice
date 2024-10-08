#include "Graph.h"

Graph::Graph(int vertices) : vertices(vertices) {
    adjList.resize(vertices);
}

void Graph::addEdge(int src, int dest, int weight) {
    adjList[src].emplace_back(dest, weight);
    adjList[dest].emplace_back(src, weight);
}

const std::vector<std::list<std::pair<int, int>>>& Graph::getAdjList() const {
    return adjList;
}

std::vector<Edge> Graph::getEdges() const {
    std::vector<Edge> edges;
    for (int i = 0; i < vertices; ++i) {
        for (const auto& neighbor : adjList[i]) {
            if (i < neighbor.first) {
                edges.push_back({ i, neighbor.first, neighbor.second });
            }
        }
    }
    return edges;
}

int Graph::getVerticesCount() const {
    return vertices;
}

void Graph::dfsUtil(int vertex, std::vector<bool>& visited) {
    visited[vertex] = true;
    std::cout << vertex << " ";
    for (const auto& neighbor : adjList[vertex]) {
        if (!visited[neighbor.first]) {
            dfsUtil(neighbor.first, visited);
        }
    }
}

void Graph::dfs(int start) {
    std::vector<bool> visited(vertices, false);
    dfsUtil(start, visited);
    std::cout << std::endl;
}

void Graph::bfs(int start) {
    std::vector<bool> visited(vertices, false);
    std::queue<int> q;
    visited[start] = true;
    q.push(start);
    while (!q.empty()) {
        int vertex = q.front();
        q.pop();
        std::cout << vertex << " ";
        for (const auto& neighbor : adjList[vertex]) {
            if (!visited[neighbor.first]) {
                visited[neighbor.first] = true;
                q.push(neighbor.first);
            }
        }
    }
    std::cout << std::endl;
}

vector<Edge> Graph::primMST(int start) {
    vector<Edge>res;
    vector<bool> inMST(vertices, false);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    vector<int> minEdge(vertices, INT_MAX);

    minEdge[start] = INT_MAX;
    pq.push({ 0, start });
    while (!pq.empty()){
        int u = pq.top().second;
        pq.pop();
        
        if (inMST[u])continue;
        inMST[u] = true;

        int finalV = -1;
        int finalWeight = INT_MAX;
        for (const auto& ver : adjList[u]) {
            int v = ver.first;
            if (inMST[v])
                continue;
            int weight = ver.second;
            if (!inMST[v] && weight < minEdge[u]) {
                minEdge[u] = weight;
                finalV = v;
                finalWeight = weight;
            }
        }
        if (finalV == -1)
            continue;
        pq.push({ finalWeight,finalV });
        res.push_back({ u,finalV,finalWeight });
    }
    return res;
}

int Graph::shortestPath(int start, int end) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq; // 第一个 int 指代的是节点到start的距离 第二个是权重
    vector<int> dist(vertices, INT_MAX); // 记录目前每个节点到start节点的最小距离
    vector<int> predecessor(vertices, -1); // 记录前驱节点

    dist[start] = 0;
    pq.push({ 0, start });

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (u == end) {
            return dist[end];
        }

        for (const auto& neighbor : adjList[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                predecessor[v] = u;
                pq.push({ dist[v], v });
            }
        }
    }

    return -1; // 终点不可达
}




