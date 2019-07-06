#pragma once

void boost_graph_transform_ec_nw_back(graph& original_instance, graph& solution_graph) {

	typedef boost::graph_traits<graph>::adjacency_iterator AdjacencyIterator;
	AdjacencyIterator ai, a_end;
	typedef graph::edge_descriptor Edge;

	int N = num_vertices(original_instance);

	// tranform ec and nw back
	for (int i = 0; i < N; i++) {
		double original_nw = get(boost::vertex_name_t(), original_instance, i);
		boost::put(boost::vertex_name_t(), solution_graph, i, original_nw); // put original nw
		boost::tie(ai, a_end) = boost::adjacent_vertices(i, solution_graph);
		for (; ai != a_end; ai++) {
			if (i < *ai) {
				double original_ec = get(boost::edge_weight_t(), original_instance, boost::edge(i, *ai, original_instance).first);
				std::pair<Edge, bool> ed = boost::edge(i, *ai, solution_graph);
				boost::put(boost::edge_weight_t(), solution_graph, ed.first, original_ec); // put original ec
			}
		}
	}

}
