#pragma once

#include <boost_graph.h>


#pragma region
double total_ec_and_nw_calculation(graph& input_graph, int N) {

	typedef boost::graph_traits<graph>::adjacency_iterator AdjacencyIterator;
	AdjacencyIterator ai, a_end;

	// total_ec
	double total_ec_and_nw = 0;
	for (int i = 0; i < N; i++) {
		total_ec_and_nw = total_ec_and_nw + abs(get(boost::vertex_name_t(), input_graph, i));
		boost::tie(ai, a_end) = boost::adjacent_vertices(i, input_graph);
		for (; ai != a_end; ai++) {
			if (*ai < i) {
				total_ec_and_nw = total_ec_and_nw + get(boost::edge_weight_t(), input_graph, boost::edge(*ai, i, input_graph).first);
			}
		}
	}

	return total_ec_and_nw;

}
#pragma endregion total_ec_and_nw_calculation 2018_10_30_22:45:59