#include <iostream>
#include <fstream>
#include <vector>

#include "geo.h"
#include "path.h"

using namespace std;

int main(int argc, char** argv) {
	if (argc != 2) {
		cout << "Usage: sat.exe file\n";
		return -2;
	}
	fstream f(argv[1]);

	if (f.fail()) {
		cout << "File not found\n";
		return -1;
	}

	/*

	//points on planet's surface
	int num = 16;
	for (int i = 0; i < num/2; i++) {
		for (int j = 0; j < num; j++) {
			vec3 t = geoToVec(geo(i * degToRad(180 / num * 2)-PI/2, j * degToRad(360 / num)-PI, RADIUS));
			printf("%.2f,%.2f,%.2f,\n", t.x, t.y, t.z);
		}
	}
	*/

	char ID[8];

	double lon,lat,rad;

	vector<geo> sats;
	geo start;
	geo end;

	//input reading

	while ( f.good() ) {
		if (f.peek() == '#') {
			f.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		f.get(ID, 8, ',');
		if (!strncmp(ID, "SAT", 3)) {
			f.ignore();

			f >> lat;
			f.ignore();

			f >> lon;
			f.ignore();

			f >> rad;
			f.ignore();

			sats.push_back( geo( degToRad(lat), degToRad(lon), rad + RADIUS) );

		} else if( !strcmp(ID, "ROUTE") ) {
			f.ignore();

			f >> lat;
			f.ignore();

			f >> lon;
			f.ignore();

			start = geo(degToRad(lat), degToRad(lon), RADIUS + 0.01);

			f >> lat;
			f.ignore();

			f >> lon;
			f.ignore();

			end = geo(degToRad(lat), degToRad(lon), RADIUS + 0.01);
		}
	}

	f.close();

	//prints a bunch of data for visualization purposes - I used Mathbox.js

	int n = 0;
	for (auto i = sats.begin(); i != sats.end(); i++) {
		printf("SAT%d: %f,%f,%f\n", n, i->lon, i->lat, i->rad);
		n++;
	}

	//construct a graph from the satellite positions
	vector<node>* graph = makeGraph(sats, start, end);

	printf("points:\n");
	for (auto i = graph->begin(); i != graph->end(); i++) {
		printf("%f,%f,%f,\n", i->pos.x,i->pos.y,i->pos.z);
	}

	//print the lines on the graph
	set<pair<int, int> > lines;
	printf("graph:\n");
	for (auto i = graph->begin(); i != graph->end(); i++) {
		for (auto j = i->neighbour.begin(); j != i->neighbour.end(); j++) {
			if (lines.count( pair<int,int>(i->id, *j) ) == 0) {
				node &neigh = graph->at(*j);
				printf("%f,%f,%f,\t%f,%f,%f,\n", i->pos.x, i->pos.y, i->pos.z,
												neigh.pos.x,neigh.pos.y,neigh.pos.z);
				lines.insert(pair<int, int>(i->id, *j));
				lines.insert(pair<int, int>(*j,i->id ));
			}
		}
		
	}

	//breadth-first search for a path - start and end are the two last nodes in the graph, respectively
	vector<int>* path = BFS(graph, graph->size() - 2, graph->size() - 1);
	if (path != NULL) {
		printf("PATH: ");
		for (auto i = path->begin(); i != path->end(); i++) {
			if (*i == graph->size() - 2) printf("START, ");
			else if(*i == graph->size() - 1) printf("END, ");
			else printf("SAT%i, ", *i);
		}
		delete path;
	} else printf("No path\n");

	delete graph;
	return 0;
}