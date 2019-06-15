#pragma once


#include <boost_graph.h>
#include <subgraph_vector.h>


#pragma region
double subgraph_sum_of_nw_and_ec(graph& input_graph, subgraph& input_subgraph) {

	int N_subgraph = input_subgraph.size();
	double sum_of_nw_and_ec = 0;

	for (int i = 0; i < N_subgraph; i++) {
		int v = input_subgraph[i].first;
		sum_of_nw_and_ec = sum_of_nw_and_ec + get(boost::vertex_name_t(), input_graph, v); // plus nw
		for (int j = 0; j < input_subgraph[i].second.size(); j++) {
			int adj_v = input_subgraph[i].second[j];
			if (i < adj_v) { // count an edge only once
				sum_of_nw_and_ec = sum_of_nw_and_ec + get(boost::edge_weight_t(), input_graph, boost::edge(v, adj_v, input_graph).first); // plus ec
			}
		}
	}

	return sum_of_nw_and_ec;


}
#pragma endregion subgraph_sum_of_nw_and_ec
