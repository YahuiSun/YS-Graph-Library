#pragma once


void boost_graph_MST_postprocessing(graph& input_graph, graph& solu_graph) {

	int N = num_vertices(input_graph);

	graph base_graph(N);
	for (int i = 0; i < N; i++) {
		boost::put(boost::vertex_name_t(), base_graph, i, get(boost::vertex_name_t(), input_graph, i)); // input node weight
	}

	graph::out_edge_iterator eit, eend;
	for (int i = 0; i < N; i++) {
		if (in_degree(i, solu_graph) >= 1) { // i is in solu_graph
			tie(eit, eend) = boost::out_edges(i, input_graph); // adjacent_vertices of i in input_graph
			for_each(eit, eend,
				[&input_graph, &i, &base_graph, &solu_graph](graph::edge_descriptor it)
			{
				int j = boost::target(it, input_graph);
				if (i > j && in_degree(j, solu_graph) > 0) { // j is in solu_graph
					boost::add_edge(i, j, get(boost::edge_weight_t(), input_graph, boost::edge(i, j, input_graph).first), base_graph); // input edge 
				}
			});
		}
	}

	solu_graph = boost_graph_find_MST(base_graph);
}