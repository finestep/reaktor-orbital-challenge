#pragma once

//graphs and pathfinding

#include <set>
#include <vector>
#include <stack>
#include <map>

#include "geo.h"
#include "los.h"

using namespace std;

struct node {
	const int id;
	set<int> neighbour; //list of node id's - could be pointers as well
	vec3 pos;
	node(int i, const vec3 &p): id(i), pos(p) {}
};

void connect(node &a, node &b) {
	a.neighbour.insert(b.id);
	b.neighbour.insert(a.id);
}

/*

Turns the list of satellite geodesic positions into a graph

graph
	node
		neighbours
			node_index
			node_index
			...
	node
		neighbours
			...
	...
	
*/

vector<node>* makeGraph(vector<geo> sats, geo start, geo end) {

	vector<node>* graph = new vector<node>();

	for (int i = 0; i < sats.size(); i++) {
		graph->push_back(node(i, geoToVec(sats[i])));
	}
	graph->push_back(node(graph->size(), geoToVec(start)));
	graph->push_back(node(graph->size(), geoToVec(end)));

	//check all the satellite pairs
	for (int i = 0; i < graph->size(); i++) {
		for (int j = i+1; j < graph->size(); j++) {

			if ( isClear(graph->at(i).pos, graph->at(j).pos ) ) connect(graph->at(i), graph->at(j));

		}
	}

	return graph;
}

vector<int>* BFS(vector<node>* graph, int from, int goal) {
	vector<int>* ret = new vector<int>();
	stack<int> toVisit;
	vector<int> parents(graph->size(),-1);

	int current;

	toVisit.push(from);

	while (toVisit.size() > 0) {

		current = toVisit.top();
		toVisit.pop();

		if (current == goal) {
			break;
		}

		//add children to toVisit and marking their parent
		for (auto i = graph->at(current).neighbour.begin();
				i != graph->at(current).neighbour.end(); i++) {
			int child = *i;
			if (parents[child] == -1) {
				toVisit.push(child);
				parents[child] = current;
			}
		}
		
	}

	//trace back the route
	current = goal;
	while (current != from) {

		//reverse the order, stl container style
		ret->insert(ret->begin(), current);

		current = parents[current];

		if (current == -1) {
			delete ret;
			return NULL; //abort mission
		}

	}

	ret->insert(ret->begin(), current );

	return ret;
}