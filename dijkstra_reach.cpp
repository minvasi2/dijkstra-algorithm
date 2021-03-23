#include <bits/stdc++.h>

using namespace std;

struct Comparator {
    constexpr bool operator()(pair<int, int> const& a, pair<int, int> const& b) const noexcept
    {
        return a.second > b.second;
    }
};

vector<int> shortestReach(int n, vector<vector<int>> edges, int s)
{
    vector<vector<pair<int, int>>> adjacencyList(n, vector<pair<int, int>> {});

    for (int i = 0; i < edges.size(); i++)
    {
        adjacencyList[edges.at(i).at(0) - 1].push_back(make_pair(edges.at(i).at(1) - 1, edges.at(i).at(2)));
        adjacencyList[edges.at(i).at(1) - 1].push_back(make_pair(edges.at(i).at(0) - 1, edges.at(i).at(2)));
    }

    vector<int> distance(n);

    bool* visited = new bool[n];

    for (int i = 0; i < n; i++)
    {
        distance[i] = INT_MAX;
        visited[i] = false;
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, Comparator> pq;

    pq.push(make_pair(s - 1, 0));

    distance[s - 1] = 0;

    while (!pq.empty())
    {
        pair<int, int> node = pq.top();

        pq.pop();

        visited[node.first] = true;

        if (distance.at(node.first) < node.second) continue;

        vector<pair<int, int>> list = adjacencyList.at(node.first);

        for (int i = 0; i < list.size(); i++)
        {
            if (!visited[list.at(i).first] && distance.at(node.first) + list.at(i).second < distance.at(list.at(i).first))
            {
                distance[list.at(i).first] = distance.at(node.first) + list.at(i).second;

                pq.push(make_pair(list.at(i).first, distance.at(list.at(i).first)));
            }
        }
    }

    delete[] visited;

    distance.erase(distance.begin() + s - 1);

    for (int i = 0; i < n - 1; i++)
    {
        if (distance.at(i) == INT_MAX)
        {
            distance[i] = -1;
        }
    }

    return distance;
}

vector<string> split_string(string);

int main()
{
    ios::sync_with_stdio(false);

    ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string nm_temp;
        getline(cin, nm_temp);

        vector<string> nm = split_string(nm_temp);

        int n = stoi(nm[0]);

        int m = stoi(nm[1]);

        vector<vector<int>> edges(m);
        for (int i = 0; i < m; i++) {
            edges[i].resize(3);

            for (int j = 0; j < 3; j++) {
                cin >> edges[i][j];
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        int s;
        cin >> s;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        vector<int> result = shortestReach(n, edges, s);

        for (int i = 0; i < result.size(); i++) {
            fout << result[i];

            if (i != result.size() - 1) {
                fout << " ";
            }
        }

        fout << "\n";
    }

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [](const char& x, const char& y) {
        return x == y and x == ' ';
        });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}

