#pragma once


#include <boost_graph.h>
#include <subgraph_unordered_map.h>

double subgraph_sum_of_ec(graph& input_graph, subgraph& input_subgraph) {

	int N_subgraph = input_subgraph.size();
	double sum_of_ec = 0;

	for (auto it = input_subgraph.begin(); it != input_subgraph.end(); it++) {
		int v = (*it).first;
		for (auto it2 = (*it).second.begin(); it2 != (*it).second.end(); it2++) {
			int adj_v = *it2;
			if (v < adj_v) { // count an edge only once
				sum_of_ec = sum_of_ec + get(boost::edge_weight_t(), input_graph, 
					boost::edge(v, adj_v, input_graph).first); // plus ec
			}
		}
	}

	return sum_of_ec;


}
