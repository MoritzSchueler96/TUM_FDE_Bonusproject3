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
    set<pair<double, unsigned>> setds;
    vector<double> dist(m.width+1, INF);

    set<pair<double, unsigned>> NN;

    setds.insert(make_pair(0, start));
    dist[start] = 0.0;

    while (!setds.empty()) {
        pair<double, int> tmp = *(setds.begin());
        setds.erase(setds.begin());
        int u = tmp.second;
        for (auto &e : m.getNeighbors(u)) {
            int v = e.column;
            double weight = e.weight;
            if (dist[v] > dist[u] + weight) {
                if (dist[v] != INF) {
                    setds.erase(setds.find(make_pair(dist[v], v)));
                    NN.erase(NN.find(make_pair(dist[v], v)));
                }
                dist[v] = dist[u] + weight;
                setds.insert(make_pair(dist[v], v));
                NN.insert(make_pair(dist[v], v));
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
