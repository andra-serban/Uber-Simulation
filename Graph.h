// Copyright Andra Serban
#ifndef GRAPH_H_
#define GRAPH_H_
#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <algorithm>
#include <string>
template <class T>
class Graph {
 private:
	std::vector<std::vector<T>> neigh;
	int numNodes;
	bool oriented;
	int time;
	std::vector<int> finTime;

 public:
	Graph(int n, bool oriented) {
		this->numNodes = n;
		this->oriented = oriented;
		for (int i = 0; i < numNodes; i++) {
			neigh.push_back(std::vector<T>());
		}
	}

	std::vector<int> get_vecini(T i) {
		return neigh[i];
	}

	void addEdge(T i, T j) {
		neigh[i].push_back(j);
		if (!oriented) {
			neigh[j].push_back(i);
		}
	}

	void removeEdge(T src, T dst) {
		int sz = neigh[src].size();
		int ok = 0;
	    for (auto it = neigh[src].begin(); it != neigh[src].end(); ++it) {
	        if (*it == dst) {
	        	if (neigh[src].end() - 1 == it) {
	        		break;
	        	} else {
	        		neigh[src].erase(it);
	        		ok = 1;
	        	}
	        }
	    }
	    if (ok == 0) {
	    	neigh[src].resize(sz -1);
	    }
	}

	bool isEdge(T i, T j) {
		std::vector<T> v = neigh[i];
		return std::find(v.begin(), v.end(), j) != v.end();
	}

	char bfs(T source, T dest)
	{
	    std::queue<T> q;
	  	std::vector<bool> v(numNodes, false);
	    q.push(source);
	    v[source] = true;
	    while (!q.empty()) {
	        T top = q.front();
	        q.pop();
	        if (dest == top) {
	        	char is_route = 'y';
	        	return is_route;
	        }
	        for (auto i = neigh[top].begin(); i != neigh[top].end(); i++) {
	            if (!v[*i]) {
	                q.push(*i);
	                v[*i] = true;
	            }
	        }
	    }
	    char is_route = 'n';
	    return is_route;
	}

	int minPath(T source, T dest) {
		if (dest == source) return 0;
		std::vector<int> visited(numNodes, 0);
		std::queue<T> q;
		std::vector<int> dist(numNodes, -1);
		std::vector<T> parent(numNodes, -1);
		visited[source] = 1;
		dist[source] = 0;
		q.push(source);
		while (!q.empty()) {
			T v = q.front();
			q.pop();
			for (auto it = neigh[v].begin(); it != neigh[v].end(); it++) {
				if (visited[*it] == 0) {
					visited[*it] = 1;
					parent[*it] = v;
					dist[*it] = dist[v] + 1;
					q.push(*it);
				}
			}
		}
		std::stack<T> path;
		if (parent[dest] == -1) return -1;
		path.push(dest);
		int k = 1;
		while (parent[dest] != source) {
			path.push(parent[dest]);
			dest = parent[dest];
			k++;
		}
		path.push(source);
		return k;
	}
};
#endif  // GRAPH_H_
