#pragma once

#include <boost_graph.h>


void boost_graph_print_all_edges(graph& input_graph) {

	typedef boost::graph_traits<graph>::adjacency_iterator AdjacencyIterator;
	AdjacencyIterator ai, a_end;

	int N = num_vertices(input_graph);

	std::cout << "boost_graph_print_all_edges: " << std::endl;

	for (int i = 0; i < N; i++) {

		boost::tie(ai, a_end) = boost::adjacent_vertices(i, input_graph);
		for (; ai != a_end; ai++) {
			if (i < *ai) {
				std::cout << "ec(" << i << "," << *ai << ")=" <<
					get(boost::edge_weight_t(), input_graph, boost::edge(i, *ai, input_graph).first) << std::endl;
			}
		}

	}

}

