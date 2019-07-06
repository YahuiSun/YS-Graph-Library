#pragma once



void boost_graph_print_nw(graph& input_graph) {

	int N = num_vertices(input_graph);

	std::cout << "boost_graph_print_nw:" << std::endl;

	for (int v = 0; v < N; v++) {
		std::cout << "vertex " << v << ": " << get(boost::vertex_name_t(), input_graph, v) << " ";
	}
	std::cout << std::endl;
}