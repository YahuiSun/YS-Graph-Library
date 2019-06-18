#pragma once


#include <subgraph_adjacency_list_is_tree.h>


bool subgraph_adjacency_list_feasible_NWGSTP(subgraph& input_subgraph, graph& input_graph, graph& group_graph) {

	typedef boost::graph_traits<graph>::adjacency_iterator AdjacencyIterator;
	AdjacencyIterator ai, a_end;

	int N_original = num_vertices(input_graph);
	int N_group_graph = num_vertices(group_graph);
	int N_group = N_group_graph - N_original;

	if (subgraph_adjacency_list_is_tree(input_subgraph) == false) {
		std::cout << "Error: This subgraph is not a tree!" << std::endl;
		return false;
	}

	for (int i = 0; i < N_group; i++) {
		bool group_covered = false;
		boost::tie(ai, a_end) = boost::adjacent_vertices(N_original + i, group_graph);
		for (; ai != a_end; ai++) { // *ai is aa vertex in this group
			if (subgraph_contain_vertex(input_subgraph, *ai)) {
				group_covered = true;
				break;
			}
		}
		if (group_covered == false) {
			std::cout << "Error: This subgraph does not cover a group!" << std::endl;
			return false;
		}
	}

	return true;

}
