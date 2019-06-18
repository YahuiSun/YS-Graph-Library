#pragma once


void boost_graph_save_graph_NWGSTP(std::string instance_name, graph& result_graph, graph& group_graph) {

	std::string save_name = instance_name; // save_name
	std::ofstream outputFile;
	outputFile.precision(6);
	outputFile.setf(std::ios::fixed);
	outputFile.setf(std::ios::showpoint);
	outputFile.open(save_name); // stp file
	outputFile << "boost_graph_save_graph_NWGSTP" << std::endl;
	outputFile << std::endl;

	// comments
	outputFile << "SECTION Comments" << std::endl;
	outputFile << "Name \"" << save_name << "\"" << std::endl;
	outputFile << "Creator \"boost_graph_save_graph_NWGSTP\"" << std::endl;
	outputFile << "END" << std::endl;
	outputFile << std::endl;

	// edges
	outputFile << "SECTION Graph" << std::endl;
	outputFile << "Nodes " << num_vertices(result_graph) << std::endl;
	outputFile << "Edges " << num_edges(result_graph) << std::endl;
	graph::out_edge_iterator eit, eend;
	for (int i = 0; i < num_vertices(result_graph); i++) {
		tie(eit, eend) = boost::out_edges(i, result_graph); // adjacent_vertices
		for_each(eit, eend,
			[&result_graph, &i, &outputFile](graph::edge_descriptor it)
		{
			int j = boost::target(it, result_graph);
			if (i < j) {
				outputFile << "E " << i << " " << j << " " << 
					get(boost::edge_weight_t(), result_graph, boost::edge(i, j, result_graph).first) << std::endl;
			}
		});
	}
	outputFile << "END" << std::endl;
	outputFile << std::endl;

	// nodes
	outputFile << "SECTION Node Weights" << std::endl;
	for (int i = 0; i < num_vertices(result_graph); i++) {
		outputFile << "V " << i << " " << get(boost::vertex_name_t(), result_graph, i) << std::endl;
	}
	outputFile << "END" << std::endl;
	outputFile << std::endl;

	// Groups
	outputFile << "SECTION Group Vertices" << std::endl;
	int N = num_vertices(result_graph);
	int N_group = num_vertices(group_graph) - N;
	typedef boost::graph_traits<graph>::adjacency_iterator AdjacencyIterator;
	AdjacencyIterator ai, a_end;
	for (int i = 0; i < N_group; i++) {
		outputFile << "G";
		boost::tie(ai, a_end) = boost::adjacent_vertices(i + N, group_graph);
		for (; ai != a_end; ai++) {
			int j = *ai;
			outputFile << " " << j;
		}
		outputFile << std::endl;
	}
	outputFile << "END" << std::endl;
	outputFile << std::endl;


	outputFile << "EOF" << std::endl;

}
