#include <iostream>
#include <string>

using namespace std;


//This function displays the contents of the matrix 'map'
void display(int x, int y);

//This function lets user create the starting and the finishing points on the grid
void destinations(int x, int y);

//This function lets user create obstacles on the map
void get_obstacles(int x, int y);

//Pathfinding algorithm
void find_path(int x, int y);

//Make found path visible
void get_path(int x, int y, int cur_x, int cur_y, int cur_value);

//Global variable, dynamically created matrix
string** map;
int** map_copy;
//Global starting and finishing points of the path
int xs = 0, ys = 0;
int xf = 0, yf = 0;

//Structure of nodes containing coordinates of a certain tile with the counter value of how many steps it takes to get there from finish
struct node
{
    int x1;
    int y1;
    int counter;
    node* p_next;
};

//Global list (main list)
node *list = NULL;

//Important function that allows us to add new nodes to the list
node* get_new(int x, int y, int val)
{
    node* cell = new node;
    cell->x1 = x;
    cell->y1 = y;
    cell->counter = val;
    cell->p_next = list;
    list = cell;
    return cell;
}

//Append a new node to the end of the list
void append_new(int x, int y, int val)
{

    node* cell = new node;
    node* last = list;

    cell->counter = val;
    cell->x1 = x;
    cell->y1 = y;
    cell->p_next = NULL;   

    if (list == NULL)
    {
        list = cell;
        return;
    }

    while (last->p_next != NULL)
        last = last->p_next;

    last->p_next = cell;
    return;
}

//This function chekcs whether there are elements with the same coordinates in the list already
bool check_same(int x, int y)
{
    node* temp = list;
    while (temp != NULL)
    {
        //cout << "checking...\n";
        if (temp->x1 == x && temp->y1 == y)
            return true;
        temp = temp->p_next;
    }
    return false;
}

//This function creates a sublist of max 4 nodes based on the current tile's coordinates
void expand_list(int width, int height, int x, int y, int val)
{
    //Check for the upper cell if we can go there
    if (y - 1 > 0)
    {
        //cout << "trying to go up\n";
        if (map[x][y - 1] == "_" || map[x][y - 1] == "S")
        {
            //cout << "going up\n";
            map_copy[x][y - 1] = val + 1;
            map[x][y - 1] = "p";
            //Check for presence of the same coordinate in the list
            if (check_same(x, y - 1) == false)
                append_new(x, y - 1, val + 1);
        }
    }

    //Check for the right cell if we can go there
    if (x + 1 < width - 1)
    {
        //cout << "trying to go right\n";
        if (map[x + 1][y] == "_" || map[x + 1][y] == "S")
        {
            //cout << "going right\n";
            map_copy[x + 1][y] = val + 1;
            map[x + 1][y] = "p";
            //Check for presence of the same coordinate in the list
            if (check_same(x + 1, y) == false)
                append_new(x + 1, y, val + 1);
        }
    } 

    //Check for the lower cell if we can go there
    if (y + 1 < height - 1)
    {
        //cout << "trying to go down\n";
        if (map[x][y + 1] == "_" || map[x][y + 1] == "S")
        {
            //cout << "going down\n";
            map_copy[x][y + 1] = val + 1;
            map[x][y + 1] = "p";
            //Check for presence of the same coordinate in the list
            if (check_same(x, y + 1) == false)
                append_new(x, y + 1, val + 1);
        }
    }

    //Check for the left cell if we can go there
    if (x - 1 > 0)
    {
        //cout << "trying to go left\n";
        if (map[x - 1][y] == "_" || map[x - 1][y] == "S")
        {
            //cout << "going left\n";
            map_copy[x - 1][y] = val + 1;
            map[x - 1][y] = "p";
            //Check for presence of the same coordinate in the list
            if (check_same(x - 1, y) == false)
                append_new(x - 1, y, val + 1);
        }
    }
    return;
}

//This function displays elements of the linked list
void display_list()
{
    node* temp = list;
    while (temp != NULL)
    {
        cout << "(" << temp->x1 << ", " << temp->y1 << ", " << temp->counter << ") ";
        temp = temp->p_next;
    }
    cout << endl;
}

int main()
{
    int width;
    int height;

    //Input of dimensions of the grid
    do
    {
        cout << "Enter width and height of the grid: ";
        cin >> width >> height;
    } while (width < 10 || height < 10);

    //Matrix creation, memory allocation
    width += 2;
    height += 2;
    map = new string * [width];
    for (int i = 0; i < width; i++)
        map[i] = new string[height];
    //Copy creation, memory allocation
    map_copy = new int* [width];
    for (int i = 0; i < width; i++)
        map_copy[i] = new int[height];

    //Matrix initialization
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (i == 0 || i == width - 1 || j == 0 || j == height - 1)
                map[i][j] = "X";
            else
                map[i][j] = "_";
        }
    }

    //Copy initialization
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            map_copy[i][j] = -1;
        }
    }
    
    //Input of starting and finishing points
    display(width, height);
    destinations(width, height);
    display(width, height);
    //Creation of obstacles if any
    get_obstacles(width, height);
    //Call for pathfinding algorithm
    find_path(width, height);
    get_path(width, height, xs, ys, width*height);
    map[xs][ys] = "S";
    display(width, height);

    //Deallocation of memory (deletion of the matrix)
    for (int i = 0; i < width; i++)
        delete[] map[i];
    delete[] map;
}


//This function displays the contents of the matrix 'map'
void display(int x, int y)
{
    for (int i = 0; i < 5; i++)
        cout << "\n";

    for (int j = 0; j < y; j++)
    {
        cout << "\t\t";
        for (int i = 0; i < x; i++)
            cout << map[i][j] << " ";
        cout << "\n";
    }

    for (int i = 0; i < 5; i++)
        cout << "\n";
}

//This function lets user create the starting and the finishing points on the grid
void destinations(int x, int y)
{
    do
    {
        cout << "Enter starting point of the path (x0, y0): ";
        cin >> xs >> ys;
    } while (xs > (x - 2) || xs < 1 || ys > (y - 2) || ys < 1);
    do
    {
        cout << "Enter finishing point of the path (x0, y0): ";
        cin >> xf >> yf;
    } while (xf > (x - 2) || xf < 1 || yf > (y - 2) || yf < 1 || (xf == xs && yf == ys));
    map[xs][ys] = "S";
    map[xf][yf] = "F";
}

//This function lets user create obstacles on the map
void get_obstacles(int x, int y)
{
    int xo, yo;
    cout << "Enter '-1 -1' to exit.\n";
    do
    {
        do
        {
            cout << "Enter coordinates of an obstacle (x, y): ";
            cin >> xo >> yo;
            if (xo == -1 && yo == -1)
                break;
        } while (map[xo][yo] != "_" || xo < 1 || xo > (x - 2) || yo < 1 || yo > (y - 2));
        if (xo == -1 && yo == -1)
            break;
        map[xo][yo] = "X";
        display(x, y);
    } while (1);
}

//Dijkstra's pathfinding algorithm
void find_path(int x, int y)
{
    list = get_new(xf, yf, 0);
    while (list != NULL && (list->x1 != xs || list->y1 != ys))
    {
        expand_list(x, y, list->x1, list->y1, list->counter);
        list = list->p_next;
    }
}

//Makes found path visible
void get_path(int x, int y, int cur_x, int cur_y, int cur_value)
{
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            if (map[i][j] == "p")
                map[i][j] = "_";
        }
    }

    while (cur_value > 1)
    {
        bool up = false, right = false, down = false, left = false;
        if (cur_y - 1 > 0)
        {
            if (map_copy[cur_x][cur_y - 1] < cur_value && map_copy[cur_x][cur_y - 1] != -1)
            {
                cur_value = map_copy[cur_x][cur_y - 1];
                up = true;
            }
        }
        if (cur_x + 1 < x - 1)
        {
            if (map_copy[cur_x + 1][cur_y] < cur_value && map_copy[cur_x + 1][cur_y] != -1)
            {
                cur_value = map_copy[cur_x + 1][cur_y];
                up = false;
                right = true;
                down = false;
                left = false;
            }
        }
        if (cur_y + 1 < y - 1)
        {
            if (map_copy[cur_x][cur_y + 1] < cur_value && map_copy[cur_x][cur_y + 1] != -1)
            {
                cur_value = map_copy[cur_x][cur_y + 1];
                up = false;
                right = false;
                down = true;
                left = false;
            }
        }
        if (cur_x - 1 > 0)
        {
            if (map_copy[cur_x - 1][cur_y] < cur_value && map_copy[cur_x - 1][cur_y] != -1)
            {
                cur_value = map_copy[cur_x - 1][cur_y];
                up = false;
                right = false;
                down = false;
                left = true;
            }
        }
        if (up == true)
            cur_y--;
        else if (right == true)
            cur_x++;
        else if (down == true)
            cur_y++;
        else if (left == true)
            cur_x--;
        map[cur_x][cur_y] = "P";
    }
}

