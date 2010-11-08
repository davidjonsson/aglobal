#include "Kdtree.h"

void Kdtree::setSize(int size)
{
    root->pointsetSize = size;
}

void Kdtree::generateKdtreeAtRoot(Photon* photons[])
{
    if(root->pointsetSize == 0)
    {
    }
    else
    {

        int leftSize = root->pointsetSize / 2;
        int rightSize = root->pointsetSize - leftSize - 1;

        int median = root->pointsetSize / 2;

        Photon* leftSet[leftSize];
        Photon* rightSet[rightSize];

        for(int i = 0; i < leftSize; i++)
            leftSet[i] = photons[i];

        for(int i = 0; i < rightSize; i++)
            rightSet[i] = photons[leftSize + i];

//        std::cout << "atROOT: leftSize(" << leftSize << ") rightSize(" << rightSize << ")" << std::endl;

        root->p = photons[median];
        root->left = generateKdtree(leftSet, (root->depth + 1), leftSize);
        root->right = generateKdtree(rightSet, (root->depth + 1), rightSize);
    }
}

Node* Kdtree::generateKdtree(Photon* photons[], int depth, int size)
{
    if(size == 0)
    {
        return 0;
    }
    else
    {
        int axis = depth % 3;

        shellSort(photons, size, axis);

        int median = size/2; // Räkna ut detta genom att ta photons[node->pointsetSize/2].axis

        Node* currentNode = new Node(depth);
        currentNode->pointsetSize = size;
        currentNode->p = photons[median];

        int leftSize = currentNode->pointsetSize / 2;
        int rightSize = currentNode->pointsetSize - leftSize - 1;

        Photon* leftSet[leftSize];
        Photon* rightSet[rightSize];

        for(int i = 0; i < leftSize; i++)
            leftSet[i] = photons[i];

        for(int i = 0; i < rightSize; i++)
            rightSet[i] = photons[(leftSize + 1) + i];

        currentNode->left = generateKdtree(leftSet, (currentNode->depth + 1), leftSize);
        currentNode->right = generateKdtree(rightSet, (currentNode->depth + 1), rightSize);

        return currentNode;
    }
}

void Kdtree::shellSort(Photon* photons[], int size, int axis)
{
    int inc;
    bool swapOccured;
    inc = size;

   /* std::cout << "Unsorted: {";
    for(int i = 0; i < size; i++)
    {
        switch(axis)
        {
            case 0:
                std::cout << " z(" << photons[i]->position.z << ") ";
                break;
            case 1:
                std::cout << " x(" << photons[i]->position.x << ") ";
                break;
            case 2:
                std::cout << " y(" << photons[i]->position.y << ") ";
                break;
            default:
                break;
        }
    }
    std::cout << "}" << std::endl;*/

    while(swapOccured || inc > 1)
    {
        swapOccured = false;
        inc = inc/2.2;
        for(int i = 0; i < (size - inc); i++)
        {
            switch(axis)
            {
                case 0:
                    if(photons[i+inc]->position.z < photons[i]->position.z)
                    {
                        Photon* temp = photons[i+inc];
                        photons[i+inc] = photons[i];
                        photons[i] = temp;
                        swapOccured = true;
                    }
                    break;
                case 1:
                    if(photons[i+inc]->position.x < photons[i]->position.x)
                    {
                        Photon* temp = photons[i+inc];
                        photons[i+inc] = photons[i];
                        photons[i] = temp;
                        swapOccured = true;
                    }
                    break;
                case 2:
                    if(photons[i+inc]->position.y < photons[i]->position.y)
                    {
                        Photon* temp = photons[i+inc];
                        photons[i+inc] = photons[i];
                        photons[i] = temp;
                        swapOccured = true;
                    }
                    break;
                default:
                    break;
            }
        }
    }
/*
    std::cout << "Sorted: {";
    for(int i = 0; i < size; i++)
    {
        switch(axis)
        {
            case 0:
                std::cout << " z(" << photons[i]->position.z << ") ";
                break;
            case 1:
                std::cout << " x(" << photons[i]->position.x << ") ";
                break;
            case 2:
                std::cout << " y(" << photons[i]->position.y << ") ";
                break;
            default:
                break;
        }
    }
    std::cout << "}" << std::endl;*/
}
