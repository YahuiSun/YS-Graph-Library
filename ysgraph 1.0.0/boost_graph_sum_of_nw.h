#pragma once

#include <boost_graph.h>


double boost_graph_sum_of_nw(graph& input_graph) {

	int N = num_vertices(input_graph);

	// total_ec
	double total_nw = 0;
	for (int i = 0; i < N; i++) {
		total_nw = total_nw + abs(get(boost::vertex_name_t(), input_graph, i));
	}

	return total_nw;

}