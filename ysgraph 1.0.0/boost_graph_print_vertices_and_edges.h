#pragma once

#include <boost_graph.h>

void boost_graph_print_vertices_and_edges(graph& input_graph) {

	int V = num_vertices(input_graph);
	int E = num_edges(input_graph);

	std::cout << "|V|=" << V << "|E|=" << E << std::endl;

	for (int i = 0; i < V; i++) {
		std::cout << "Vertex: " << i << " Weight: " << get(boost::vertex_name_t(), input_graph, i) << std::endl;
	}
	typedef graph::edge_descriptor Edge;
	for (int i = 0; i < V; i++) {
		for (int j = i; j < V; j++) {
			std::pair<Edge, bool> ed = boost::edge(i, j, input_graph);
			if (ed.second) { // This edge exists!
				std::cout << "Edge: (" << i << "," << j << ") Cost: "
					<< get(boost::edge_weight_t(), input_graph, boost::edge(i, j, input_graph).first) << std::endl;
			}
		}
	}

	std::cout << std::endl;

}