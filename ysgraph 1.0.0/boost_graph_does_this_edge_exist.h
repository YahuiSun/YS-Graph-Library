#pragma once

#include <boost_graph.h>

bool boost_graph_does_this_edge_exist(int v1, int v2, graph& initial_graph) {

	typedef graph::edge_descriptor Edge;

	std::pair<Edge, bool> ed = boost::edge(v1, v2, initial_graph);
	if (!ed.second) { // cout << "This edge does not exist!" << endl;
		return false;
	}

	return true;

}
