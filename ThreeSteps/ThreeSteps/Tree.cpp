#include "Tree.h"

Tree::Tree()
{
    root = 0;
}

Tree::~Tree()
{
    if (root != 0) delete root;
}

void Tree::addNode(int newNodeNumber, int parentNodeNumber)
{
    Node* parentNode = getNodeByNumber(parentNodeNumber, root);
    Node* newNode = new Node(newNodeNumber, parentNode);


    parentNode->addChild(newNode);
}

void Tree::addConnect(int v1, int v2)
{
    Node* node1 = getNodeByNumber(v1, root);
    Node* node2 = getNodeByNumber(v2, root);
    if (node1 && node2)
    {
        node1->addParent(node2);
        node2->addParent(node1);
    }
}

void Tree::setRoot(int number)
{
    root = new Node(number);
}

Tree::Node* Tree::getNodeByNumber(int number, Node* current)
{
    if (current->number == number)
        return current;

    for (int i = 0; i < current->childCount; i++)
    {
        Node* found = getNodeByNumber(number, current->children[i]);
        if (found != 0)
            return found;
    }
    return nullptr;
}

void Tree::print()
{
    printInner(root);
}

void Tree::printInner(Node* current)
{
    std::cout << "N" << current->number << ": ";
    for (int i = 0; i < current->childCount; i++)
    {
        std::cout << current->children[i]->number << ", ";
    }

    std::cout << "\n\n";

    for (int i = 0; i < current->childCount; i++)
    {
        printInner(current->children[i]);
    }
}

void Tree::printThreeSteps(int num)
{
    printThreeStepsInner(getNodeByNumber(num, root));
}

void Tree::printThreeStepsInner(Node* current)
{
    if (!current) return;

    std::cout << "N" << current->number << ": ";

    // Инициализируем массив проверки
    bool check_2[SIZE] = { false };
    check_2[current->number] = true;

    // Первый уровень родителей
    for (int i = 0; i < current->parentsCount; i++)
    {
        Node* parent1 = current->parents[i];

        // можно добавить метки на пройденные, чтоб выводило только те, что непосредственно находятся в 3 шагах (не ближе)

        // Второй уровень родителей
        for (int j = 0; j < parent1->parentsCount; j++)
        {
            Node* parent2 = parent1->parents[j];

            if (parent2->number != current->number)
            {
                // Третий уровень родителей
                for (int k = 0; k < parent2->parentsCount; k++)
                {
                    Node* parent3 = parent2->parents[k];
                    if (!check_2[parent3->number])
                    {
                        std::cout << "Node " << parent3->number << ", ";
                        check_2[parent3->number] = true;
                    }
                }
            }
        }
    }

    std::cout << "\n\n";
}

