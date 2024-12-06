// FlatternBinaryTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <queue>
#include <vector>

class Node
{
public:
    Node* left;
    Node* right;
    int data;

    Node(int d)
        : data(d)
        , left(nullptr)
        , right(nullptr)
    {}
};

Node* ArrayToTree(const std::vector<int>& v)
{
    if (v.size() == 0)
        return nullptr;
    Node* root = new Node(v[0]);
    std::queue<Node*> q;
    q.push(root);
    bool l = true;
    for (size_t i = 1; i < v.size(); ++i, l = !l)
    {
        Node* pNode = q.front();
        if (!l)
            q.pop();
        if (v[i] != -1)
        {
            if (l)
            {
                pNode->left = new Node(v[i]);
                q.push(pNode->left);
            }
            else
            {
                pNode->right = new Node(v[i]);
                q.push(pNode->right);
            }
        }
    }

    return root;
}

void FreeTree(Node* pNode)
{
    if (pNode == nullptr)
        return;

    FreeTree(pNode->left);
    FreeTree(pNode->right);

    delete pNode;
}

void Flatten(Node* pNode, Node** ppTail)
{
    if (pNode == nullptr)
        return;

    // Store right, and relink left to its right
    Node* pRight = pNode->right;
    pNode->right = pNode->left;
    if (pNode->left != nullptr)
        (*ppTail) = pNode->left;

    // Flatten the left node then make the left null
    Flatten(pNode->left, ppTail);
    pNode->left = nullptr;

    // Link the right to the tail of the link
    if (pRight != nullptr)
    {
        (*ppTail)->right = pRight;
        (*ppTail) = pRight;
    }

    // Flatten the right node
    Flatten(pRight, ppTail);
}

void Flatten(Node* root)
{
    Node* pTail = root;
    Flatten(root, &pTail);
}

int main()
{
    while (true)
    {
        std::cout << "Number of nodes in the tree: ";
        int count = 0;
        std::cin >> count;
        if (count == 0)
            break;

        std::cout << "Values of the tree nodes: ";
        std::vector<int> v(count, 0);
        for (int i = 0; i < count; ++i)
            std::cin >> v[i];

        Node* root = ArrayToTree(v);

        Flatten(root);
        Node* pNode = root;
        std::cout << root->data;
        pNode = pNode->right;

        while (pNode)
        {
            std::cout << ", " << pNode->data;
            pNode = pNode->right;
        }
        std::cout << std::endl << std::endl;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
