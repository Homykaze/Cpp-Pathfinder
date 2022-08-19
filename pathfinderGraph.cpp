#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#define INF 2147483647

using namespace std;

//Structure for a weighted graph
struct node {
    string name;
    int weight = INF;
};

//Setting the graph with the costs hash table, and the parents too!
void setGraph(unordered_map<string, vector<node>> &graph, unordered_map<string, int> &costs, unordered_map<string, string> &parents);
//Finds a node from its connections with the lowest value
string find_lowest_cost_node(const unordered_map<string, int>& costs, const vector<string> &processed);
//Check if node is processed, returns true if node has not been processed yet
bool node_is_not_processed(string node, const vector<string> &processed);
//This function tracks all parents from the final node back to the start and displays this path
void getPath(unordered_map<string, string> &parents);


int main()
{
    //Name of node to its neighboring nodes
    unordered_map<string, vector<node>> graph;
    //Name of node to how much it takes to get to it
    unordered_map<string, int> costs;
    //Name of node to name of its parent
    unordered_map<string, string> parents;
    //Stores nodes that have already been processed
    vector<string> processed(0);
    
    setGraph(graph, costs, parents);

    //Dijkstra's algorithm right here!
    string nod = find_lowest_cost_node(costs, processed);
    while (nod != "")
    {
        int cost = costs[nod];
        vector<node> neighbors = graph[nod];
        for (int i = 0; i < neighbors.size(); i++)
        {
            string n = neighbors[i].name;
            int new_cost = cost + neighbors[i].weight;
            if (costs[n] > new_cost)
            {
                costs[n] = new_cost;
                parents[n] = nod;
            }
        }
        processed.push_back(nod);
        nod = find_lowest_cost_node(costs, processed);
    }
    cout << "Shortest path takes " << costs["Finish"] << " units of weight\n";

    getPath(parents);
    return 0;
}

void setGraph(unordered_map<string, vector<node>>& graph, unordered_map<string, int>& costs, unordered_map<string, string>& parents)
{
    cout << "Enter the number of nodes: ";
    int input;
    cin >> input;
    for (int i = 0; i < input; i++)
    {
        string name;
        if (i == 0)
            name = "Start";
        else if (i == input - 1)
            name = "Finish";
        else
        {
            cout << "Enter the name of the node: ";
            cin.ignore();
            getline(cin, name, '\n');
        }
        graph[name];

        int connections;  
        cout << "Enter the number of connections " << name << " has: ";
        cin >> connections;
        unordered_map<string, vector<node>>::iterator itr = graph.find(name);
        itr->second.resize(connections);
        for (int j = 0; j < connections; j++)
        {
            node connection;
            cout << "Enter name of connection of " << name << ": ";
            cin.ignore();
            getline(cin, connection.name, '\n');
            cout << "Its weight: ";
            cin >> connection.weight;
            itr->second[j] = connection;

            //Setting the parents table
            if (i == 0)
                parents[connection.name] = name;
            else
                parents[connection.name] = "";
            //Setting the costs table here
            if (i == 0)
                costs[connection.name] = connection.weight;
            else
                costs[connection.name] = INF;
        }
        cout << endl;
    }
}

string find_lowest_cost_node(const unordered_map<string, int>& costs, const vector<string>& processed)
{
    int lowest_cost = INF;
    string lowest_cost_node = "";
    unordered_map<string, int>::const_iterator itr = costs.begin();
    unordered_map<string, int>::const_iterator end = costs.end();
    for (itr; itr != end; ++itr)
    {
        int cost = itr->second;
        if (cost < lowest_cost && node_is_not_processed(itr->first, processed))
        {
            lowest_cost = cost;
            lowest_cost_node = itr->first;
        }
    }
    return lowest_cost_node;
}

bool node_is_not_processed(string node, const vector<string>& processed)
{
    int size = processed.size();
    for (int i = 0; i < size; i++)
    {
        if (node == processed[i])
            return false;
    }
    return true;
}

void getPath(unordered_map<string, string>& parents)
{
    string step = "Finish";
    vector<string> path(0);
    path.push_back(step);

    while (step != "Start")
    {
        step = parents[step];
        path.push_back(step);
    }

    int size = path.size();
    for (int i = size - 1; i > 0; i++)
        cout << " -> " << path[i];
    cout << endl;
}