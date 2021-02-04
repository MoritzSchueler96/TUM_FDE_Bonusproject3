#ifndef FDE20_BONUSPROJECT_3_KNN_HPP
#define FDE20_BONUSPROJECT_3_KNN_HPP

#include "Matrix.hpp"
#include <set>
#include <iterator>
#include <map>
#include <gtest/gtest.h>

using namespace std;
#define INF 0x3f3f3f3f

//---------------------------------------------------------------------------
/// Find the top k neighbors for the node start. The directed graph is stored in
/// matrix m and you can use getNeighbors(node) to get all neighbors of a node.
/// A more detailed description is provided in Matrix.hpp.
/// The function should return the k nearest neighbors in sorted order as vector
/// of Matrix::Entry, where Entry->column is the neighbor node and Entry->weight
/// is the cost to reach the node from the start node.
std::vector<Matrix::Entry> getKNN(const Matrix &m, unsigned start, unsigned k)
{

    using Entry = Matrix::Entry;
    std::vector<Entry> result;
    result.reserve(k);

    // ToDo implement your solution here
    /*
    Basic Djikstra implementation taken from: https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-set-in-stl/
    */

    // Create Waiting List & Init list of weights with INF
    set<pair<double, unsigned>> waitinglist;
    vector<double> weights(m.width + 1, INF);

    // Create list which contains the nearest neighbours with their weights
    set<pair<double, unsigned>> NN;

    // Insert Start Node and set weight to 0
    waitinglist.insert(make_pair(0, start));
    weights[start] = 0.0;

    // Iterate as long as waitinglist is not empty
    while (!waitinglist.empty())
    {
        // pop first node from waitinglist
        pair<double, int> tmp = *(waitinglist.begin());
        waitinglist.erase(waitinglist.begin());
        int u = tmp.second;

        // get all neighbours
        for (auto &e : m.getNeighbors(u))
        {
            // extract node and weight
            int v = e.column;
            double weight = e.weight;

            // check if current path is shortest for this node
            if (weights[v] > weights[u] + weight)
            {
                // Update waiting and NN list to exclude worse path
                if (weights[v] != INF)
                {
                    waitinglist.erase(waitinglist.find(make_pair(weights[v], v)));
                    NN.erase(NN.find(make_pair(weights[v], v)));
                }

                // update weights for node and put new best path into waiting and NN list
                weights[v] = weights[u] + weight;
                waitinglist.insert(make_pair(weights[v], v));
                NN.insert(make_pair(weights[v], v));
            }
        }
    }

    // Check if number of NN is smaller than requested by k
    if (NN.size() < k)
    {
        // put all found NN into result
        for (auto it = NN.begin(); it != NN.end(); it++)
        {
            if (it->first == INF)
                break;
            result.push_back({it->second, it->first});
        }
    }
    else
    {
        // put only top k NN into result
        auto itend = NN.begin();
        std::advance(itend, k);
        for (auto it = NN.begin(); it != itend; it++)
        {
            if (it->first == INF)
                break;
            result.push_back({it->second, it->first});
        }
    }
    return result;
}

//---------------------------------------------------------------------------

#endif // FDE20_BONUSPROJECT_3_KNN_HPP
