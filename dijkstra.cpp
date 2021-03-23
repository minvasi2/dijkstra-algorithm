#include <iostream>
#include <utility>
#include <vector>
#include <float.h>
#include <queue>

using namespace std;

int minimumDistanceIndex(vector<pair<int, double>> &nodes)
{
    pair<int, double> minNode = nodes.front();

    int minIndex = 0;

    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes.at(i).second < minNode.second)
        {
            minNode = nodes.at(i);
            minIndex = i;
        }
    }

    return minIndex;
}

// Naivi realizacija, sudetingumas O(E*V)
pair<int*, double*> dijkstra_naive(int start, vector<vector<pair<int, double>>> &adjacencyList)
{
    bool* visited = new bool[adjacencyList.size()];

    double* distance = new double[adjacencyList.size()];

    int* previous = new int[adjacencyList.size()];

    for (int i = 0; i < adjacencyList.size(); i++)
    {
        visited[i] = false;
        distance[i] = DBL_MAX;
        previous[i] = -1;
    }

    vector<pair<int, double>> queue;

    distance[start] = 0.0;

    queue.push_back(make_pair(start, 0.0));

    while (!queue.empty())
    {
        int index = minimumDistanceIndex(queue);

        pair<int, double> node = queue[index];

        queue.erase(queue.begin() + index);

        visited[node.first] = true;

        if (distance[node.first] < node.second) continue;

        vector<pair<int, double>> list = adjacencyList.at(node.first);

        for (int i = 0; i < list.size(); i++)
        {
            if (!visited[list.at(i).first] && distance[node.first] + list.at(i).second < distance[list.at(i).first])
            {
                distance[list.at(i).first] = distance[node.first] + list.at(i).second;
                previous[list.at(i).first] = node.first;
                queue.push_back(make_pair(list.at(i).first, distance[list.at(i).first]));
            }
        }
    }

    delete[] visited;

    return make_pair(previous, distance);
}

struct Comparator {
    constexpr bool operator()(pair<int, double> const& a, pair<int, double> const& b) const noexcept
    {
        return a.second > b.second;
    }
};

// Standartine realizacija, sudetingumas O(E*log(V))
pair<int*, double*> dijkstra(int start, vector<vector<pair<int, double>>>& adjacencyList)
{
    bool* visited = new bool[adjacencyList.size()];

    double* distance = new double[adjacencyList.size()];

    int* previous = new int[adjacencyList.size()];

    for (int i = 0; i < adjacencyList.size(); i++)
    {
        visited[i] = false;
        distance[i] = DBL_MAX;
        previous[i] = -1;
    }

    priority_queue<pair<int, double>, vector<pair<int, double>>, Comparator> queue;

    distance[start] = 0.0;

    queue.push(make_pair(start, 0.0));

    while (!queue.empty())
    {
        pair<int, double> node = queue.top();

        queue.pop();

        visited[node.first] = true;

        if (distance[node.first] < node.second) continue;

        vector<pair<int, double>> list = adjacencyList.at(node.first);

        for (int i = 0; i < list.size(); i++)
        {
            if (!visited[list.at(i).first] && distance[node.first] + list.at(i).second < distance[list.at(i).first])
            {
                distance[list.at(i).first] = distance[node.first] + list.at(i).second;
                previous[list.at(i).first] = node.first;
                queue.push(make_pair(list.at(i).first, distance[list.at(i).first]));
            }
        }
    }

    delete[] visited;

    return make_pair(previous, distance);
}

void print_result(pair<int*, double*> result, int n, char *nodes_map)
{
    int* previous = result.first;
    double* dist = result.second;

    for (int i = 0; i < n; i++)
    {
        cout << nodes_map[i] << " - " << dist[i] << " sequence: ";

        for (int j = i; j != -1; j = previous[j])
        {
            cout << nodes_map[j] << " ";
        }

        cout << endl;
    }

    cout << endl;

    delete[] previous;
    delete[] dist;
}

int main()
{
    char nodes[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};

    vector<vector<pair<int, double>>> adjacency_list;

    adjacency_list.push_back(vector<pair<int, double>>{make_pair(2, 1.0), make_pair(5, 10.0)});
    adjacency_list.push_back(vector<pair<int, double>>{make_pair(2, 3.0), make_pair(4, 1.0)});
    adjacency_list.push_back(vector<pair<int, double>>{make_pair(0, 1.0), make_pair(1, 3.0), make_pair(3, 2.0), make_pair(4, 5.0)});
    adjacency_list.push_back(vector<pair<int, double>>{make_pair(2, 2.0), make_pair(5, 4.0)});
    adjacency_list.push_back(vector<pair<int, double>>{make_pair(1, 1.0), make_pair(2, 5.0), make_pair(5, 8.0)});
    adjacency_list.push_back(vector<pair<int, double>>{make_pair(0, 10.0), make_pair(3, 4.0), make_pair(4, 8.0), make_pair(6, 2.0)});
    adjacency_list.push_back(vector<pair<int, double>>{make_pair(5, 2.0)});

    for (int i = 0; i < adjacency_list.size(); i++)
    {
        cout << nodes[i] << " -> ";

        for (int j = 0; j < adjacency_list.at(i).size(); j++)
        {
            cout << "(" << nodes[adjacency_list.at(i).at(j).first] << ", " << adjacency_list.at(i).at(j).second << ")" << " ";
        }

        cout << endl;
    }

    pair<int*, double*> result;

    result = dijkstra_naive(0, adjacency_list);

    print_result(result, adjacency_list.size(), nodes);

    result = dijkstra(0, adjacency_list);

    print_result(result, adjacency_list.size(), nodes);
}
