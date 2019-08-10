#pragma once

#include <boost_graph.h>


double boost_graph_sum_of_ec(graph& input_graph) {

	typedef boost::graph_traits<graph>::adjacency_iterator AdjacencyIterator;
	AdjacencyIterator ai, a_end;

	int N = num_vertices(input_graph);

	// total_ec
	double total_ec = 0;
	for (int i = 0; i < N; i++) {
		boost::tie(ai, a_end) = boost::adjacent_vertices(i, input_graph);
		for (; ai != a_end; ai++) {
			if (*ai < i) {
				total_ec = total_ec + get(boost::edge_weight_t(), input_graph, boost::edge(*ai, i, input_graph).first);
			}
		}
	}

	return total_ec;

}