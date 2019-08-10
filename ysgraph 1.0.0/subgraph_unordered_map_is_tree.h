#pragma once


#include <subgraph_unordered_map_count_connected_cpn_Vsize.h>


bool subgraph_unordered_map_is_tree(subgraph& input_graph) {

	int StartVertex = input_graph.begin()->first;

	int V = input_graph.size();

	int E = subgraph_num_edges(input_graph);

	if (V != E + 1) { // this is not a tree
		return false;
	}

	int cpn = subgraph_unordered_map_count_connected_cpn_Vsize(input_graph, StartVertex);

	if (cpn == V) { // input_graph is connected and V == E + 1
		return true;
	}
	else {
		return false;
	}

}
