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