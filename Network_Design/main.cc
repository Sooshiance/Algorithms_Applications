#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cstdint>

class Graph
{
public:
    // Adjacency list representation of the graph
    std::unordered_map<std::int32_t, std::vector<std::int32_t>> adjList;

    void addEdge(std::int32_t u, std::int32_t v)
    {
        adjList[u].push_back(v);
    }

    std::vector<std::int32_t> getNodes()
    {
        std::vector<std::int32_t> nodes;
        for (const auto &pair : adjList)
        {
            nodes.push_back(pair.first);
        }
        return nodes;
    }
};

// Function to calculate PageRank
std::unordered_map<std::int32_t, double> pageRank(Graph &graph, std::int32_t maxIterations = 100, double dampingFactor = 0.85)
{
    std::unordered_map<std::int32_t, double> ranks;

    std::vector<std::int32_t> nodes = graph.getNodes();

    std::int32_t numNodes = nodes.size();

    // Initialize ranks
    for (std::int32_t node : nodes)
    {
        // Start with equal rank
        ranks[node] = 1.0 / numNodes;
    }

    // Iterate to update ranks
    for (std::int32_t it = 0; it < maxIterations; ++it)
    {
        std::unordered_map<std::int32_t, double> newRanks;

        for (std::int32_t node : nodes)
        {
            // Base rank
            newRanks[node] = (1 - dampingFactor) / numNodes;

            // Sum contributions from incoming links
            for (const auto &pair : graph.adjList)
            {
                std::int32_t neighbor = pair.first;
                const auto &edges = pair.second;

                if (std::find(edges.begin(), edges.end(), node) != edges.end())
                {
                    newRanks[node] += dampingFactor * (ranks[neighbor] / edges.size());
                }
            }
        }

        // Update ranks for next iteration
        ranks = newRanks;
    }

    return ranks;
}

int main()
{
    Graph graph;

    // Example: Adding edges to the graph
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);
    graph.addEdge(2, 3);
    graph.addEdge(3, 1);

    // Calculate PageRank
    auto ranks = pageRank(graph);

    // Output the results
    std::cout << "PageRank Results:\n";

    for (const auto &pair : ranks)
    {
        std::cout << "Node " << pair.first << ": " << pair.second << "\n";
    }

    std::cout << "\n";

    return 0;
}