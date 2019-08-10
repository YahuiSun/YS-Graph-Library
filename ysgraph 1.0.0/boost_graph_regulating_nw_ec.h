#pragma once


#include <boost_graph.h>


void boost_graph_regulating_nw_ec(graph& input_graph, double lambda) {

	/*change G(V,E,w,c) to G(V,E,(1 - lambda)*w,lambda*c)*/

	typedef boost::graph_traits<graph>::adjacency_iterator AdjacencyIterator;
	AdjacencyIterator ai, a_end, bi, b_end;
	typedef graph::edge_descriptor Edge;

	if (lambda < 0 || lambda > 1) {
		std::cout << "lambda in boost_graph_regulating_nw_ec is non-sense!" << std::endl;
		getchar();
		exit(1);
	}


	int N = num_vertices(input_graph); // number of vertices


	for (int i = 0; i < N; i++) {

		double w_i = get(boost::vertex_name_t(), input_graph, i);
		boost::put(boost::vertex_name_t(), input_graph, i, (1 - lambda)*w_i);

		boost::tie(ai, a_end) = boost::adjacent_vertices(i, input_graph);
		for (; ai != a_end; ai++) {
			int j = *ai;
			if (i < j) { // edge (i,j)

				std::pair<Edge, bool> ed = boost::edge(i, j, input_graph);
				double c_ij = get(boost::edge_weight_t(), input_graph, ed.first);
				boost::put(boost::edge_weight_t(), input_graph, ed.first, lambda*c_ij);

			}
		}

	}


}