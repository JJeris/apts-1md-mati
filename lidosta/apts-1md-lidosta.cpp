#include <fstream>
using namespace std;
// Author: Johans Justs Eris, je21033
// AVL tree implementation in C++ from https://www.programiz.com/dsa/avl-tree with some

class Node
// Each node represetns each flight, that is detailed in the input file.
{
public:
    int key; // Take off time
    Node *left;
    Node *right;
    int height; // Height
    int ielidosanasLaiks = -1; // Landing time
    int destinationAirport = -1; // The airport to which the flight is going to
};

int max(int a, int b);

// Calculate height
int height(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

// New node creation
Node *newNode(int key, int landingTime, int destinationAirport)
{
    Node *node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    node->ielidosanasLaiks = landingTime;
    node->destinationAirport = destinationAirport;
    return (node);
}

// Rotate right
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left),
                    height(y->right)) +
                1;
    x->height = max(height(x->left),
                    height(x->right)) +
                1;
    return x;
}

// Rotate left
Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left),
                    height(x->right)) +
                1;
    y->height = max(height(y->left),
                    height(y->right)) +
                1;
    return y;
}

// Get the balance factor of each node
int getBalanceFactor(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) -
           height(N->right);
}

// Insert a node
Node *insertNode(Node *node, int key, int landingTime, int destinationAirport)
{
    // Find the correct postion and insert the node
    if (node == NULL)
        return (newNode(key, landingTime, destinationAirport));
    if (key < node->key)
        node->left = insertNode(node->left, key, landingTime, destinationAirport);
    else if (key > node->key)
        node->right = insertNode(node->right, key, landingTime, destinationAirport);
    else
        return node;

    // Update the balance factor of each node and
    // balance the tree
    node->height = 1 + max(height(node->left),
                           height(node->right));
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1)
    {
        if (key < node->left->key)
        {
            return rightRotate(node);
        }
        else if (key > node->left->key)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    if (balanceFactor < -1)
    {
        if (key > node->right->key)
        {
            return leftRotate(node);
        }
        else if (key < node->right->key)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
    return node;
}

// Node with minimum value
Node *nodeWithMimumValue(Node *node)
{
    Node *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Delete a node
Node *deleteNode(Node *root, int key)
{
    // Find the node and delete it
    if (root == NULL)
        return root;
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else
    {
        if ((root->left == NULL) ||
            (root->right == NULL))
        {
            Node *temp = root->left ? root->left : root->right;
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else
        {
            Node *temp = nodeWithMimumValue(root->right);
            root->key = temp->key;
            root->destinationAirport = temp->destinationAirport;
            root->ielidosanasLaiks = temp->ielidosanasLaiks;
            root->right = deleteNode(root->right,
                                     temp->key);
        }
    }

    if (root == NULL)
        return root;

    // Update the balance factor of each node and
    // balance the tree
    root->height = 1 + max(height(root->left),
                           height(root->right));
    int balanceFactor = getBalanceFactor(root);
    if (balanceFactor > 1)
    {
        if (getBalanceFactor(root->left) >= 0)
        {
            return rightRotate(root);
        }
        else
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if (balanceFactor < -1)
    {
        if (getBalanceFactor(root->right) <= 0)
        {
            return leftRotate(root);
        }
        else
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
}

// Function to find the smallest possible element in an AVL tree
// that is greater than a passed value
Node *findSmallestGreaterThan(Node *root, int izlidosana)
{
    // Initialize the result variable
    Node *result = nullptr;

    // Traverse the tree to find the smallest element greater than the value
    while (root != nullptr)
    {
        if (root->key > izlidosana)
        {
            result = root;
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }

    // Return the result
    return result;
}
// Ja nav neviens lielāks par current time, tad jāskatās uz mazāko nākamo reisu tā, it kā viņš ir notiek nākamajā dienā.

struct resultNode
{
    // An element, that represents a node in a binary tree.
    int from = -1;
    int to = -1;
    int izlidosanasLaiks = -1;
    int ielidosanasLaiks = -1;
};

int main()
{
    // Open the files.
    ifstream input("lidostas.in");
    ofstream output;

    // Create a buffer, to help with the output. Makes the program faster
    // and in turn more effiecient.
    const unsigned int length = 1536;
    char buffer[length];
    output.rdbuf()->pubsetbuf(buffer, length);
    output.open("lidostas.out");

    // cout<<"ok1"<<endl;
    //  Initialize variables.
    int numberOfAirports = 0;
    int startAirport = 0;
    int endAirport = 0;

    int startingTime = 0;

    Node *lidostas[20001];

    int cursor = 0;
    char line[20000];

    // Read in the number of airports.
    input.getline(line, 20000);
    while (line[cursor] != '\0')
    {
        numberOfAirports = numberOfAirports * 10 + line[cursor] - '0';
        cursor++;
    }
    cursor = 0;

    // Read the start airports number
    input.getline(line, 20000);
    while (line[cursor] != ' ')
    {
        startAirport = startAirport * 10 + line[cursor] - '0';
        cursor++;
    }
    cursor++;
    // Read the end airports number
    while (line[cursor] != '\0')
    {
        endAirport = endAirport * 10 + line[cursor] - '0';
        cursor++;
    }

    int hours = 0;
    int minutes = 0;
    cursor = 0;
    input.getline(line, 20000);
    while (line[cursor] != ':')
    {
        hours = hours * 10 + line[cursor] - '0';
        cursor++;
    }
    cursor++;
    while (line[cursor] != '\0')
    {
        minutes = minutes * 10 + line[cursor] - '0';
        cursor++;
    }

    cursor = 0;
    startingTime = (hours * 60) + minutes;
    // cout<<numberOfAirports<<", "<<startAirport<<", "<<endAirport<<", "<<startingTime<<endl;
    // cout<<"ok2"<<endl;
    input.getline(line, 20000);
    while (true)
    {

        if (line[cursor] == '0')
        {
            break;
        }
        // No kura reisa
        int from = 0;
        int to = 0;
        int n = 0;
        while (line[cursor] != ' ')
        {
            from = from * 10 + line[cursor] - '0';
            cursor++;
        }
        cursor++;
        while (line[cursor] != ' ')
        {
            to = to * 10 + line[cursor] - '0';
            cursor++;
        }
        cursor++;
        while (line[cursor] != ' ')
        {
            n = n * 10 + line[cursor] - '0';
            cursor++;
        }
        cursor++;

        int startHour = 0;
        int startMinute = 0;
        int endHour = 0;
        int endMinute = 0;

        // cout<<from<<", "<<to<<", "<<n<<endl;

        for (int i = 0; i < n; i++)
        {
            while (line[cursor] != ':')
            {
                startHour = startHour * 10 + line[cursor] - '0';
                cursor++;
            }
            cursor++;
            while (line[cursor] != '-')
            {
                startMinute = startMinute * 10 + line[cursor] - '0';
                cursor++;
            }
            cursor++;
            while (line[cursor] != ':')
            {
                endHour = endHour * 10 + line[cursor] - '0';
                cursor++;
            }
            cursor++;
            int count = 0;
            while (count != 2)
            {
                endMinute = endMinute * 10 + line[cursor] - '0';
                cursor++;
                count++;
            }
            cursor++;

            int izlidosana = (startHour * 60) + startMinute;
            int ielidosana = (endHour * 60) + endMinute;
            // cout<<"Insert: "<< from << ", " << izlidosana << ", " << ielidosana << ", " << to << endl;
            lidostas[from] = insertNode(lidostas[from], izlidosana, ielidosana, to);

            startHour = 0;
            startMinute = 0;
            endHour = 0;
            endMinute = 0;
            izlidosana = 0;
            ielidosana = 0;
            count = 0;
            // Saglabā reisu
            // Pievienot node
        }
        from = 0;
        to = 0;
        n = 0;
        cursor = 0;
        input.getline(line, 20000);
    }
    // cout<<"M: Before aiziet dirsā!"<<endl;
    resultNode resultArray[20001];
    int resultInterator = 0;
    resultArray[resultInterator].from = startAirport;
    resultArray[resultInterator].izlidosanasLaiks = startingTime;
    resultInterator++;

    // startingTime+=node->key;
    // findSmallestGreater(lidostas[startAirport], startingTime);-
    Node *node = findSmallestGreaterThan(lidostas[startAirport], startingTime);
    if (node == NULL)
    {
        node = findSmallestGreaterThan(lidostas[startAirport], -1);
    }

    while (true)
    {
        int originalStartAirport = startAirport;
        if (node == NULL)
        {
            output << "Impossible";
            break;
        }
        else if (node->destinationAirport == endAirport)
        {
            // izvade
            resultArray[resultInterator].from = startAirport;
            resultArray[resultInterator].to = node->destinationAirport;
            resultArray[resultInterator].izlidosanasLaiks = node->key;
            resultArray[resultInterator].ielidosanasLaiks = node->ielidosanasLaiks;
            for (int k = 0; k <= resultInterator; k++)
            {
                if (k == 0)
                {
                    // timeStart
                    output << resultArray[k].from << " ";
                    if (resultArray[k].izlidosanasLaiks / 60 < 10)
                    {
                        output << "0" << resultArray[k].izlidosanasLaiks / 60 << ":";
                    }
                    else
                    {
                        output << resultArray[k].izlidosanasLaiks / 60 << ":";
                    }
                    if (resultArray[k].izlidosanasLaiks % 60 < 10)
                    {
                        output << "0" << resultArray[k].izlidosanasLaiks % 60 << '\n';
                    }
                    else
                    {
                        output << resultArray[k].izlidosanasLaiks % 60 << '\n';
                    }
                }
                else
                {
                    output << resultArray[k].from << "->" << resultArray[k].to << " ";
                    if (resultArray[k].izlidosanasLaiks / 60 < 10)
                    {
                        output << "0" << resultArray[k].izlidosanasLaiks / 60 << ":";
                    }
                    else
                    {
                        output << resultArray[k].izlidosanasLaiks / 60 << ":";
                    }
                    if (resultArray[k].izlidosanasLaiks % 60 < 10)
                    {
                        output << "0" << resultArray[k].izlidosanasLaiks % 60 << '-';
                    }
                    else
                    {
                        output << resultArray[k].izlidosanasLaiks % 60 << '-';
                    }
                    if (resultArray[k].ielidosanasLaiks / 60 < 10)
                    {
                        output << "0" << resultArray[k].ielidosanasLaiks / 60 << ":";
                    }
                    else
                    {
                        output << resultArray[k].ielidosanasLaiks / 60 << ":";
                    }
                    if (resultArray[k].ielidosanasLaiks % 60 < 10)
                    {
                        output << "0" << resultArray[k].ielidosanasLaiks % 60 << '\n';
                    }
                    else
                    {
                        output << resultArray[k].ielidosanasLaiks % 60 << '\n';
                    }
                }
            }
            break;
        }

        else
        {
            resultArray[resultInterator].from = startAirport;
            resultArray[resultInterator].to = node->destinationAirport;
            resultArray[resultInterator].izlidosanasLaiks = node->key;
            resultArray[resultInterator].ielidosanasLaiks = node->ielidosanasLaiks;
        }
        startingTime = node->ielidosanasLaiks;
        startAirport = resultArray[resultInterator].to;
        resultInterator++;
        lidostas[originalStartAirport] = deleteNode(lidostas[originalStartAirport], node->key);
        node = findSmallestGreaterThan(lidostas[startAirport], startingTime);
        if (node == NULL)
        {
            node = findSmallestGreaterThan(lidostas[startAirport], -1);
        }
    }
    input.close();
    output.close();
}
