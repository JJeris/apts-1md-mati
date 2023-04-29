#include <fstream>
using namespace std;
// Author: Johans Justs Eris, je21033

// AVL tree implementation in C++ from https://www.programiz.com/dsa/avl-tree with some minor improvements.

// Each node represetns each flight, that is detailed in the input file.
class Node
{
public:
    int key; // Take off time
    Node *left;
    Node *right;
    int height; // Height
    int landingTime = -1; // Landing time
    int destinationAirport = -1; // The airport to which the flight is going to
};

int max(int a, int b);

// Returns the height of a node
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
    node->landingTime = landingTime;
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
// We insert a new flight corresponding to its take off airport (node). 
// Key is the time of takeoff, landingTime is landing time and destinationAirport is our destination.
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

// Returns the node with the minimum value.
Node *nodeWithMimumValue(Node *node)
{
    Node *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// After a flight has been flown, we delete it off of its AVL tree.
// This ensures that we don't use a flight again.
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
            root->landingTime = temp->landingTime;
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

// Function to find the smallest possible flight departure time in an AVL tree
// that is greater than the passed currentTime.
Node *findSonnestFlight(Node *indexRoot, int currentTime)
{
    // Initialize the result node
    Node *resultFlight = nullptr;
    // Traverse the tree to find the smallest element greater than the value
    while (indexRoot != nullptr)
    {
        if (indexRoot->key > currentTime)
        {
            resultFlight = indexRoot;
            indexRoot = indexRoot->left;
        }
        else
        {
            indexRoot = indexRoot->right;
        }
    }
    // Return the node with the minimum departure time
    return resultFlight;
}

// A type of node, with wich a static array is created, 
// that stores the resulting output.
struct resultNode
{
    int from = -1;
    int to = -1;
    int takeOffTime = -1;
    int landingTime = -1;
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

    int numberOfAirports = 0;
    int startAirport = 0;
    int endAirport = 0;
    int startingTime = 0;
    // An array of airports.
    Node *airportArr[20001];

    // Used for reading from the input file.
    int cursor = 0;
    char line[20000]; // The char array is 20000 long, so as to be able to read the worse case scenario inputs.

    // Read in the number of airports.
    input.getline(line, 20000);
    while (line[cursor] != '\0')
    {
        numberOfAirports = numberOfAirports * 10 + line[cursor] - '0';
        cursor++;
    }
    cursor = 0;

    // Read in the start airports number
    input.getline(line, 20000);
    while (line[cursor] != ' ')
    {
        startAirport = startAirport * 10 + line[cursor] - '0';
        cursor++;
    }
    cursor++;

    // Read in the end airports number
    while (line[cursor] != '\0')
    {
        endAirport = endAirport * 10 + line[cursor] - '0';
        cursor++;
    }

    int hours = 0;
    int minutes = 0;
    cursor = 0;

    input.getline(line, 20000);

    // Read in the hours
    while (line[cursor] != ':')
    {
        hours = hours * 10 + line[cursor] - '0';
        cursor++;
    }
    cursor++;

    // Read in the minutes
    while (line[cursor] != '\0')
    {
        minutes = minutes * 10 + line[cursor] - '0';
        cursor++;
    }

    cursor = 0;
    startingTime = (hours * 60) + minutes;



    // For the next flight times.
    input.getline(line, 20000);
    while (true)
    {
        if (line[cursor] == '0') // If the file has ended, we break from the while loop.
        {
            break;
        }

        int from = 0; // From which airport
        int to = 0; // To which airport
        int n = 0; // How many such flights exist?
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

        // Time variables, that'll be read in from the remaining length of the read in line.
        int startHour = 0;
        int startMinute = 0;
        int endHour = 0;
        int endMinute = 0;

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

            // We declare a count variable, that helps us exit the next while loop.
            // Without it we wouldn't be able to finish the reading process, unless altering
            // the code in another way. Thiw was a simple and reasonable fix.
            int count = 0;
            while (count != 2)
            {
                endMinute = endMinute * 10 + line[cursor] - '0';
                cursor++;
                count++;
            }
            cursor++;

            // Once we have finishing reading the times from a flight, we input its information
            // into the corresponding index AVL tree.
            // First we convert the time into minutes, so as to make the data useable.
            int izlidosana = (startHour * 60) + startMinute;
            int ielidosana = (endHour * 60) + endMinute;
            airportArr[from] = insertNode(airportArr[from], izlidosana, ielidosana, to);

            // Reset all values
            startHour = 0;
            startMinute = 0;
            endHour = 0;
            endMinute = 0;
            izlidosana = 0;
            ielidosana = 0;
            count = 0;
        }
        
        // Once there are no more flight left, we reset the rest of the values and read in the next line.
        from = 0;
        to = 0;
        n = 0;
        cursor = 0;
        input.getline(line, 20000);
    }
    
    // Once the input files is empty, we move on to finding the path from the starting airport to the end airport.
    resultNode resultArray[20001]; // An array that hold out ouput.
    int resultInterator = 0; // An iterator for our array.

    // Initialize the first element of out array, since it is unique.
    resultArray[resultInterator].from = startAirport;
    resultArray[resultInterator].takeOffTime = startingTime;
    resultInterator++;

    // We find the node (flight) which will be flying the soonest, 
    // depending on out startingTime for the search
    Node *node = findSonnestFlight(airportArr[startAirport], startingTime);
    // If no flight was found, it means that the flight might be leaving the next day.
    // We set the startingTime argument in the function call to -1 or any other negative value.
    if (node == NULL)
    {
        node = findSonnestFlight(airportArr[startAirport], -1);
    }

    while (true)
    {   
        // Make sure to save the startAirport, that we will use
        // when deleting the node.
        int originalStartAirport = startAirport;

        // If we get stuck at an airport, that has no outgoing flights left,
        // we output "Impossible" and break frim the loop. This means, that 
        // findSoonestFlight returned a NULL flight.
        if (node == NULL)
        {
            output << "Impossible";
            break;
        }
        // IF we have arrived at out destination airport, 
        // then we can begin to output our stored results.
        else if (node->destinationAirport == endAirport)
        {
            // We first write in the results from our last node, before outputing
            // the whole array into our output file.
            resultArray[resultInterator].from = startAirport;
            resultArray[resultInterator].to = node->destinationAirport;
            resultArray[resultInterator].takeOffTime = node->key;
            resultArray[resultInterator].landingTime = node->landingTime;
            
            // We iterate for every element in out array.
            for (int k = 0; k <= resultInterator; k++)
            {
                // If k equals 0, we then out the first line of our output file
                // which is rather unique.
                if (k == 0) 
                {
                    // In case the hours or minutes are less than 10 (are not double digit),
                    // we output a "0" to make sure the fomratting stays correct.
                    output << resultArray[k].from << " ";
                    if (resultArray[k].takeOffTime / 60 < 10)
                    {
                        output << "0" << resultArray[k].takeOffTime / 60 << ":";
                    }
                    else
                    {
                        output << resultArray[k].takeOffTime / 60 << ":";
                    }
                    if (resultArray[k].takeOffTime % 60 < 10)
                    {
                        output << "0" << resultArray[k].takeOffTime % 60 << '\n';
                    }
                    else
                    {
                        output << resultArray[k].takeOffTime % 60 << '\n';
                    }
                }
                // When we're passed the first element of out array
                // the rest of the elements are outputed the same way.
                else
                {
                    output << resultArray[k].from << "->" << resultArray[k].to << " ";
                    if (resultArray[k].takeOffTime / 60 < 10)
                    {
                        output << "0" << resultArray[k].takeOffTime / 60 << ":";
                    }
                    else
                    {
                        output << resultArray[k].takeOffTime / 60 << ":";
                    }
                    if (resultArray[k].takeOffTime % 60 < 10)
                    {
                        output << "0" << resultArray[k].takeOffTime % 60 << '-';
                    }
                    else
                    {
                        output << resultArray[k].takeOffTime % 60 << '-';
                    }
                    if (resultArray[k].landingTime / 60 < 10)
                    {
                        output << "0" << resultArray[k].landingTime / 60 << ":";
                    }
                    else
                    {
                        output << resultArray[k].landingTime / 60 << ":";
                    }
                    if (resultArray[k].landingTime % 60 < 10)
                    {
                        output << "0" << resultArray[k].landingTime % 60 << '\n';
                    }
                    else
                    {
                        output << resultArray[k].landingTime % 60 << '\n';
                    }
                }
            }
            break;
        }

        // If we have not reached out destination, we simply update the resultArray 
        // and move on.
        else
        {
            resultArray[resultInterator].from = startAirport;
            resultArray[resultInterator].to = node->destinationAirport;
            resultArray[resultInterator].takeOffTime = node->key;
            resultArray[resultInterator].landingTime = node->landingTime;
        }

        // We update the startingTime to be relavent
        startingTime = node->landingTime;
        // We change our starAirport to the next one that we'll start from
        // in the next iteration.
        startAirport = resultArray[resultInterator].to;
        resultInterator++;

        // We delete the flight we just used
        airportArr[originalStartAirport] = deleteNode(airportArr[originalStartAirport], node->key);
        
        // We find the next soonest flight
        node = findSonnestFlight(airportArr[startAirport], startingTime);
        // Again, If no flight was found, it means that the flight might be leaving the next day.
        // We set the startingTime argument in the function call to -1 or any other negative value.
        if (node == NULL)
        {
            node = findSonnestFlight(airportArr[startAirport], -1);
        }
    }

    // Delete the node
    delete node;

    // Close the files.
    input.close();
    output.close();

}