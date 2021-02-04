#ifndef FDE20_BONUSPROJECT_3_KNN_HPP
#define FDE20_BONUSPROJECT_3_KNN_HPP

#include "Matrix.hpp"
#include <set>
#include <iterator>
#include <map>
#include <gtest/gtest.h>

using namespace std;
# define INF 0x3f3f3f3f

//---------------------------------------------------------------------------
/// Find the top k neighbors for the node start. The directed graph is stored in
/// matrix m and you can use getNeighbors(node) to get all neighbors of a node.
/// A more detailed description is provided in Matrix.hpp.
/// The function should return the k nearest neighbors in sorted order as vector
/// of Matrix::Entry, where Entry->column is the neighbor node and Entry->weight
/// is the cost to reach the node from the start node.
std::vector<Matrix::Entry> getKNN(const Matrix &m, unsigned start, unsigned k) {

    using Entry = Matrix::Entry;
    std::vector<Entry> result;
    result.reserve(k);

    // ToDo implement your solution here
    set<pair<double, unsigned>> waitinglist;
    vector<double> weights(m.width+1, INF);

    set<pair<double, unsigned>> NN;

    waitinglist.insert(make_pair(0, start));
    weights[start] = 0.0;

    while (!waitinglist.empty()) {
        pair<double, int> tmp = *(waitinglist.begin());
        waitinglist.erase(waitinglist.begin());
        int u = tmp.second;
        for (auto &e : m.getNeighbors(u)) {
            int v = e.column;
            double weight = e.weight;
            if (weights[v] > weights[u] + weight) {
                if (weights[v] != INF) {
                    waitinglist.erase(waitinglist.find(make_pair(weights[v], v)));
                    NN.erase(NN.find(make_pair(weights[v], v)));
                }
                weights[v] = weights[u] + weight;
                waitinglist.insert(make_pair(weights[v], v));
                NN.insert(make_pair(weights[v], v));
            }
        }
    }


    if(NN.size()<k) {
        for (auto it = NN.begin(); it != NN.end(); it++) {
            if (it->first == INF) break;
            result.push_back({it->second, it->first});
        }
    }else{
        auto itend = NN.begin();
        std::advance(itend, k);
        for (auto it = NN.begin(); it != itend; it++) {
            if (it->first == INF) break;
            result.push_back({it->second, it->first});
        }
    }
    return result;
}

//---------------------------------------------------------------------------

#endif // FDE20_BONUSPROJECT_3_KNN_HPP
