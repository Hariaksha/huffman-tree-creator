/*
int isInVector(vector<int> search, int start, int end, int value)
{
    for (int i = start; i <= end; i++)
    {
        if (value == search.at(i))
        {
            return i;
        }
    }
    return -1;
}
vector<int> fillVectors2(string fileName)
{
    // Open input file stream
    ifstream stream;
    stream.open(fileName);

    vector<int> result;

    if(!stream.is_open())
    {
        cout << "Could not open file " << fileName << endl;
        return result;
    }

    int tempInt;
    while (stream >> tempInt)
    {
        result.push_back(tempInt);
    }

    return result;
}

Node* buildHuffmanTree(vector<int> inVec, vector<int> levVec, int n)
{
    // If size is 0, then we are finished building and return
    if (n == 0)
    {
        return NULL;
    }

    // Create root and give value
    Node* root = new Node();
    root->value = levVec.at(0);

    // If size is 1 then we have everything
    if (n == 1)
    {
        return root;
    }

    // Find where root value is in inOrderTraversal to divide it
    int rootInInOrder = isInVector(inVec, 0, n-1, root->value);

    // Create two int vectors for left and right trees in inOrder
    vector<int> leftInOrderVec, rightInOrderVec;
    for (int i = 0; i < n; i++)
    {
        if (isInVector(inVec, 0, rootInInOrder-1, levVec.at(i)) != -1)
        {
            leftInOrderVec.push_back(levVec.at(i));
        }
        else if (isInVector(inVec, rootInInOrder+1, n-1, levVec.at(i)) != -1)
        {
            rightInOrderVec.push_back(levVec.at(i));
        }
    }

    // Create two int vectors for left and right trees in levelOrder
    vector<int> leftInLevelVec, rightInLevelVec;
    for (int i = 1; i < n; i++)
    {
        if (isInVector(leftInOrderVec, 0, leftInOrderVec.size()-1, levVec.at(i)) != -1)
        {
            leftInLevelVec.push_back(levVec.at(i));
        }
        else if (isInVector(rightInOrderVec, 0, rightInOrderVec.size()-1, levVec.at(i)) != -1)
        {
            rightInLevelVec.push_back(levVec.at(i));
        }
    }

    root->leftChild = buildHuffmanTree(leftInOrderVec, leftInLevelVec, leftInLevelVec.size());
    root->rightChild = buildHuffmanTree(rightInOrderVec, rightInLevelVec, rightInLevelVec.size());

    return root;
}

void buildTree(const string inOrderFileName, const string levelOrderFileName, Node* root)
{
    // Open input file streams
    ifstream inOrder;
    inOrder.open(inOrderFileName);
    ifstream levelOrder;
    levelOrder.open(levelOrderFileName);

    // Error Check - Do files open?
    if(!inOrder.is_open())
    {
        cout << "Could not open file " << inOrderFileName << endl;
        return;
    }
    if(!levelOrder.is_open())
    {
        cout << "Could not open file " << levelOrderFileName << endl;
        return;
    }

    // Create vectors
    vector<int> levelOrderVector;
    vector<int> inOrderVector;
    vector<int> leftHalf;
    vector<int> rightHalf;

    // Fill up first two vectors
    int tempInt;
    while (levelOrder >> tempInt)
    {
        levelOrderVector.push_back(tempInt);
    }
    while (inOrder >> tempInt)
    {
        inOrderVector.push_back(tempInt);
    }

    // Create variable for root value
    int rootVal = levelOrderVector.at(0);

    // Fill up last two vectors
    int i = 0;
    while (inOrderVector.at(i) != rootVal)
    {
        leftHalf.push_back(inOrderVector.at(i));
        i++;
    }
    i++;
    for (int j = i; j < inOrderVector.size(); j++)
    {
        rightHalf.push_back(inOrderVector.at(j));
    }

    // Build first two levels of tree
    root->setValue(rootVal);
    Node* second = new Node(levelOrderVector.at(1));
    Node* third = new Node(levelOrderVector.at(2));0-
    root->setLeftChild(second);
    root->setRightChild(third);

    // Build left half of tree
    i = 3;
    Node* curr = second;
    for (i = 3; i < levelOrderVector.size(); i++)
    {
        if (isInVector(levelOrderVector.at(i), leftHalf))
        {
            // Give node to leftChild if it is null
            if (curr->leftChild == NULL)
            {
                Node* newNode = new Node(levelOrderVector.at(i));
                curr->setLeftChild(newNode);
                curr = curr->leftChild;
                continue;
            }
            // Give node to rightChild if it is null
            if (curr->rightChild == NULL)
            {
                Node* newNode = new Node(levelOrderVector.at(i));
                curr->setRightChild(newNode);
                curr = curr->rightChild;
                continue;
            }
            // Move to next node

        }
    }

    // Build right half of tree
    i = 3;
    curr = third;
    for (i = 3; i < levelOrderVector.size(); i++)    
    {
        if (isInVector(levelOrderVector.at(i), rightHalf))
        {
            // Give node to leftChild if it is null
            if (curr->leftChild == NULL)
            {
                Node* newNode = new Node(levelOrderVector.at(i));
                curr->setLeftChild(newNode);
                curr = curr->leftChild;
                continue;
            }
            // Give node to rightChild if it is null
            if (curr->rightChild == NULL)
            {
                Node* newNode = new Node(levelOrderVector.at(i));
                curr->setRightChild(newNode);
                curr = curr->rightChild;
                continue;
            }
            // Move to next node

        }
    }

    inOrder.close();  
    levelOrder.close();
}
int fillVectors(string inOrderFileName, string levelOrderFileName, vector<int> inVec, vector<int> levVec)
{
    // Open input file streams
    ifstream inOrder;
    inOrder.open(inOrderFileName);
    ifstream levelOrder;
    levelOrder.open(levelOrderFileName);

    // Make counter variable
    int nodeCount = 0;

    // Error Check - Do files open?
    if(!inOrder.is_open())
    {
        cout << "Could not open file " << inOrderFileName << endl;
        return -1;
    }
    if(!levelOrder.is_open())
    {
        cout << "Could not open file " << levelOrderFileName << endl;
        return -1;
    }

    // Fill up two vectors while counting nodes
    int tempInt;
    while (levelOrder >> tempInt)
    {
        levVec.push_back(tempInt);
        nodeCount++;
    }
    while (inOrder >> tempInt)
    {
        inVec.push_back(tempInt);
    }    

    return nodeCount;
}
*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include <queue>
using namespace std;

class Node
{
    public:
        int value;
        Node* leftChild;
        Node* rightChild;

        void print()
        {
            cout << value << endl;
        };

        Node(int v)
        {
            this->value = v;
            this->leftChild = nullptr;
            this->rightChild = nullptr;
        };

        Node(int v, Node* left, Node* right)
        {
            this->value = v;
            this->leftChild = left;
            this->rightChild = right;
        };

        Node()
        {
            this->value = 0;
            this->leftChild = nullptr;
            this->rightChild = nullptr;
        };
};

Node* createNode(int val)
{
    Node* node = new Node(val);
    return node;
}

string decodeMessage(const string encodedFileName, Node* root)
{
    string result = "";
    Node* node = root;

    ifstream input;
    input.open(encodedFileName);

    // Error Check - Does file open?
    if(!input.is_open())
    {
        return "Could not open file " + encodedFileName + "\n";
    }

    char tempChar;
    while (input >> tempChar)
    {
        if (tempChar == '0')
        {
            node = node->leftChild;
        }
        else if (tempChar == '1')
        {
            node=node->rightChild;
        }
        if (node->leftChild == NULL && node->rightChild == NULL)
        {
            result += char(node->value);
            node = root;
        }
/*
        if ((node->leftChild == NULL) && (node->rightChild == NULL))
        {
            char temp = char(node->value);
            result += (temp);
            node = root;
        }
        else if (tempChar == '0')
        {
            node = node->leftChild;
        }
        else if (tempChar == '1')
        {
            node = node->rightChild;
        }
*/
    }

    // Close file stream and return decoded message
    input.close();
    return result;
}

void fillArrays(const string inOrderFile, const string levelOrderFile, int inArr[], int levArr[], int s)
{
    ifstream inOrderStream, levelOrderStream;
    inOrderStream.open(inOrderFile);
    levelOrderStream.open(levelOrderFile);

    int temp;

    // Error Check - Do files open?
    if(!inOrderStream.is_open())
    {
        cout << "Could not open file " + inOrderFile + "\n";
        return;
    }
    if(!levelOrderStream.is_open())
    {
        cout << "Could not open file " + levelOrderFile + "\n";
        return;
    }

    // Fill in inOrderArray
    for (int i = 0; i < s; i++)
    {
        inOrderStream >> temp;
        inArr[i] = temp;
    }
    for (int i = 0; i < s; i++)
    {
        levelOrderStream >> temp;
        levArr[i] = temp;
    }
    inOrderStream.close();
    levelOrderStream.close();
}

int findIndexInArray(int arr[], int start, int end, int data)
{
    for (int i = start; i <= end; i++)
    {
        if (arr[i] == data)
        {
            return i;
        }
    }
    return -1;
}

Node* buildHuffmanTree(int inOrder[], int levelOrder[], int n)
{
    // We are finished so return NULL
    if (n == 0)
    {
        return nullptr;
    }

    // Create root with correct value 
    Node* root = createNode(levelOrder[0]);

    // We only need the root
    if (n == 1)
    {
        return root;
    }

    // Find where root value is in the inOrder traversal
    int rootIndexForInOrder = findIndexInArray(inOrder, 0, n-1, root->value);

    // Create two int arrays for left and right half of inOrder
    int leftSubtreeSize = rootIndexForInOrder;
    int rightSubtreeSize = n - rootIndexForInOrder - 1;
    int leftInOrder[leftSubtreeSize], rightInOrder[rightSubtreeSize];
    int li = 0;
    int ri = 0;
    /*
    for (int i = 0; i < n; i++)
    {
        if (findIndexInArray(inOrder, 0, rootIndexForInOrder-1, levelOrder[i]) != -1)
        {
            leftInOrder[li] = levelOrder[i];
            li++;
        }
        else if (findIndexInArray(inOrder, rootIndexForInOrder+1, n-1, levelOrder[i]) != -1)
        {
            rightInOrder[ri] = levelOrder[i];
            ri++;
        }
    }
    */
    for (int i = 0; i < rootIndexForInOrder; i++)
    {
        leftInOrder[li] = inOrder[i];
        li++;
    }
    for (int i = rootIndexForInOrder + 1; i < n; i++)
    {
        rightInOrder[ri] = inOrder[i];
        ri++;
    }

    // Make two int arrays for left and right half of levelOrder as they appear
    int leftLevelOrder[leftSubtreeSize], rightLevelOrder[rightSubtreeSize];
    li = 0;
    ri = 0;
    for (int i = 1; i < n; i++)
    {
        if (findIndexInArray(leftInOrder, 0, leftSubtreeSize-1, levelOrder[i]) != -1)
        {
            leftLevelOrder[li] = levelOrder[i];
            li++;
        }
        else if (findIndexInArray(rightInOrder, 0, rightSubtreeSize-1, levelOrder[i]) != -1)
        {
            rightLevelOrder[ri] = levelOrder[i];
            ri++;
        }
    }

    // Recurse on left and right children
    root->leftChild = buildHuffmanTree(leftInOrder, leftLevelOrder, leftSubtreeSize);
    root->rightChild = buildHuffmanTree(rightInOrder, rightLevelOrder, rightSubtreeSize);

    return root;
}

int findNumNodes(const string file)
{
    ifstream input;
    input.open(file);

    int answer = 0;
    int temp;

    // Error Check - Does file open?
    if(!input.is_open())
    {
        cout << "Could not open file " + file + "\n";
        return -1;
    }

    while (input >> temp)
    {
        answer++;
    }
    input.close();
    return answer;
}

void preorderTraversal(Node* root) 
{
    if (root == NULL) 
    {
        return;
    }
    cout << root->value << " ";
    preorderTraversal(root->leftChild);
    preorderTraversal(root->rightChild);
}
void postorderTraversal(Node* root)
{
    if (root == NULL) 
    {
        return;
    }
    postorderTraversal(root->leftChild);
    postorderTraversal(root->rightChild);
    cout << root->value << " ";
}
void inorderTraversal(Node* root)
{
    if (root == NULL) 
    {
        return;
    }
    inorderTraversal(root->leftChild);
    cout << root->value << " ";
    inorderTraversal(root->rightChild);
}

int main(int argc, char* argv[]) 
{
    // Error Check
    if (argc != 4) 
    {
        cout << endl << "Needs 3 command line arguments" << endl;
        return 1;   // 1 indicates error
    }

    // Create variables for command line arguments
    string inOrderText = argv[1];
    string levelOrderText = argv[2];
    string encodedText = argv[3];

    // Fill in arrays
    int size = findNumNodes(levelOrderText);
    int levelOrderArray[size];
    int inOrderArray[size];
    fillArrays(inOrderText, levelOrderText, inOrderArray, levelOrderArray, size);

/*
    for (int i = 0; i < size; i++)
    {
        cout << levelOrderArray[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < size; i++)
    {
        cout << inOrderArray[i] << " ";
    }
*/

    // Part One: Create the Tree
    Node* first = buildHuffmanTree(inOrderArray, levelOrderArray, size);

/*
    cout << "before traversals" << endl;
    // See if tree was successfully created
    preorderTraversal(first);
    cout << endl;
    postorderTraversal(first);
    cout << endl;
    inorderTraversal(first);
    cout << endl;
    cout << "after traversals" << endl;
*/

    // Part Two: Decode the message
    cout << decodeMessage(encodedText, first);

    return 0;
}