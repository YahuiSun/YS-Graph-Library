#pragma once


#include <boost_graph.h>
#include <subgraph_unordered_map.h>

double subgraph_sum_of_nw(graph& input_graph, subgraph& input_subgraph) {

	int N_subgraph = input_subgraph.size();
	double sum_of_nw = 0;

	for (auto it = input_subgraph.begin(); it != input_subgraph.end(); it++) {
		int v = (*it).first;
		sum_of_nw = sum_of_nw + get(boost::vertex_name_t(), input_graph, v); // plus nw
	}

	return sum_of_nw;


}
