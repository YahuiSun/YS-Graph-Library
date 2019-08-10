#pragma once


#include <boost_graph.h>


void boost_graph_nw_ec_normalization(graph& input_graph) {

	/*this is "min-max normalization" for bringing all node weights to [0,1];
	https://en.wikipedia.org/wiki/Normalization_(statistics)*/

	typedef boost::graph_traits<graph>::adjacency_iterator AdjacencyIterator;
	AdjacencyIterator ai, a_end;
	typedef graph::edge_descriptor Edge;


	int N = num_vertices(input_graph); // number of vertices

	double min_nw = 1e100, max_nw = -1e100;
	double min_ec = 1e100, max_ec = -1e100;

	for (int i = 0; i < N; i++) {
		double w_i = get(boost::vertex_name_t(), input_graph, i);
		if (w_i < min_nw) {
			min_nw = w_i;
		}
		if (w_i > max_nw) {
			max_nw = w_i;
		}

		boost::tie(ai, a_end) = boost::adjacent_vertices(i, input_graph);
		for (; ai != a_end; ai++) {
			int j = *ai;
			if (i < j) { // edge (i,j)

				std::pair<Edge, bool> ed = boost::edge(i, j, input_graph);
				double c_ij = get(boost::edge_weight_t(), input_graph, ed.first);

				if (c_ij < min_ec) {
					min_ec = c_ij;
				}
				if (c_ij > max_ec) {
					max_ec = c_ij;
				}

			}
		}

	}

	for (int i = 0; i < N; i++) {

		double w_i = get(boost::vertex_name_t(), input_graph, i);
		double new_w_i = (w_i - min_nw) / (max_nw - min_nw);
		boost::put(boost::vertex_name_t(), input_graph, i, new_w_i);

		boost::tie(ai, a_end) = boost::adjacent_vertices(i, input_graph);
		for (; ai != a_end; ai++) {
			int j = *ai;
			if (i < j) { // edge (i,j)

				std::pair<Edge, bool> ed = boost::edge(i, j, input_graph);
				double c_ij = get(boost::edge_weight_t(), input_graph, ed.first);
				double new_c_ij = (c_ij - min_ec) / (max_ec - min_ec);
				boost::put(boost::edge_weight_t(), input_graph, ed.first, new_c_ij);

			}
		}


	}


}