#pragma once

bool boost_graph_is_a_tree_ignore_isolated_vertices(graph& input_graph) {

	int N = num_vertices(input_graph); // number of vertices


	std::vector<int> component(N); // vertex i is in component[i]; No.component from 0
	int cpn_num = connected_components(input_graph, &component[0]); // the number of component; decrease component
	int cpn_target;
	for (int i = 0; i < N; i++) {
		if (in_degree(i, input_graph) > 0) {
			cpn_target = component[i];
			break;
		}
	}
	for (int i = 0; i < N; i++) {
		if (in_degree(i, input_graph) > 0 && component[i] != cpn_target) {
			return false;
		}
	}

	if (num_edges(input_graph) == N - cpn_num) { // it is a tree
		return true;
	}
	else {
		return false;
	}

}