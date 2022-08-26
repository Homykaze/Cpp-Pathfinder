#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

struct queue
{
    string name;
    queue *next;
};

//Add someone to the end of the queue
queue* enqueue(queue* list, string name);
//Remove someone from the beginning of the list
queue* dequeue(queue* list);
//Function check if current node is the target
bool mango_seller(string name);
//Breadth first search algorithm
bool breadth_first_search(queue* list, const unordered_map<string, vector<string>> &graph, queue* done);
//Checks if this person has already been searched
bool in_searched(queue* done, string person);
//Displays the queue
void display(queue* list);

int main()
{
    /*Setting you and your connections into the hash table*/
    //Hash table mapping a string to several strings
    unordered_map<string, vector<string>> graph;
    //Setting you and your connections
    graph["you"];
    unordered_map<string, vector<string>>::iterator itr = graph.find("you");
    itr->second.resize(3);
    itr->second[0] = "alice";
    itr->second[1] = "bob";
    itr->second[2] = "claire";

    //Setting bob, your connection
    graph["bob"];
    itr = graph.find("bob");
    itr->second.resize(2);
    itr->second[0] = "anuj";
    itr->second[1] = "peggy";

    //Setting alice, your connection
    graph["alice"];
    itr = graph.find("alice");
    itr->second.resize(1);
    itr->second[0] = "peggy";

    //Setting claire, your connection
    graph["claire"];
    itr = graph.find("claire");
    itr->second.resize(2);
    itr->second[0] = "thom";
    itr->second[1] = "jonny";

    //Setting anuj, 2nd degree connection
    graph["anuj"];
    itr = graph.find("anuj");
    itr->second.resize(0);

    //Setting peggy, 2nd degree connection
    graph["peggy"];
    itr = graph.find("peggy");
    itr->second.resize(0);

    //Setting thom, 2nd degree connection
    graph["thom"];
    itr = graph.find("thom");
    itr->second.resize(0);

    //Setting jonny, 2nd degree connection
    graph["jonny"];
    itr = graph.find("jonny");
    itr->second.resize(0);
    /*Setting you and your connections into the hash table*/

    //Creation of a queue
    queue* list = NULL;
    queue* done = NULL;
    //Adding all of your connections to the queue
    itr = graph.find("you");
    for (int i = 0; i < itr->second.size(); i++)
        list = enqueue(list, itr->second[i]);
        
    //Breadth first search is here!!!!
    if (breadth_first_search(list, graph, done) == true)
        return 0;
    else
        cout << "Nobody in the network is a mango seller...\n";
}

queue* enqueue(queue* list, string name)
{
    //Base case
    if (list == NULL)
    {
        queue* node = new queue;
        node->name = name;
        node->next = NULL;
        return node;
    }
    //Recursive call
    list->next = enqueue(list->next, name);
    return list;
}

queue* dequeue(queue* list)
{
    if (list == NULL)
        return NULL;
    queue* node = list->next;
    delete list;
    return node;
}

bool mango_seller(string name)
{
    if (name == "anu" /*|| name == "claire"*/)
        return true;
    return false;
}

bool breadth_first_search(queue* list, const unordered_map<string, vector<string>>& graph, queue* done)
{
    unordered_map<string, vector<string>>::const_iterator itr;
    while (list != NULL)
    {
        display(list);
        string person = list->name;
        list = dequeue(list);
        display(list);
        //Same people can be added to the list but they will not be processed
        if (in_searched(done, person) == false)
        {
            if (mango_seller(person) == true)
            {
                cout << person << " is a mango seller!!!\n";
                return true;
            }
            else
            {
                //Adding all of this person's connections to the queue
                itr = graph.find(person);
                for (int i = 0; i < itr->second.size(); i++)
                {
                    list = enqueue(list, itr->second[i]);
                }
                    
                //Adding the person to the list, so we do not use it for search again
                done = enqueue(done, person);
            }
        }
        
    }
    return false;
}

void display(queue* list)
{
    queue* current = list;
    while (current != NULL)
    {
        cout << current->name << " ";
        current = current->next;
    }
    cout << endl;
}

bool in_searched(queue* done, string person)
{
    queue* current = done;
    while (current != NULL)
    {
        if (current->name == person)
            return true;
        current = current->next;
    }
    return false;
}