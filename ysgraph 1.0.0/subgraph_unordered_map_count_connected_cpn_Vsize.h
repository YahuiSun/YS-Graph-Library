#pragma once


int subgraph_unordered_map_count_connected_cpn_Vsize(subgraph& input_graph, int StartVertex) {

	typedef boost::graph_traits<graph>::adjacency_iterator AdjacencyIterator;
	AdjacencyIterator ai, a_end;

	int V = input_graph.size();
	int cpn_size = 0;
	std::vector<int> touched(V, 0);
	std::vector<int> added_to_be_touched(V, 0); // it is necessary when input_graph is not a tree, otherwise to_be_touched may contain vertex repetitively
	std::vector<int> to_be_touched;

	touched[subgraph_vertex_list_ID(input_graph, StartVertex)] = 1;
	cpn_size++;

	std::list<int> adj_list = subgraph_adjacent_vertices(input_graph, StartVertex);
	for (std::list<int>::iterator it = adj_list.begin(); it != adj_list.end(); it++) {
		added_to_be_touched[subgraph_vertex_list_ID(input_graph, *it)] = 1;
		to_be_touched.insert(to_be_touched.end(), *it); // to_be_touched contains original V_IDs
	}


	while (to_be_touched.size() > 0) {

		touched[subgraph_vertex_list_ID(input_graph, to_be_touched[0])] = 1;
		cpn_size++;

		std::list<int> adj_list2 = subgraph_adjacent_vertices(input_graph, to_be_touched[0]); // to_be_touched contains original V_IDs
		for (std::list<int>::iterator it = adj_list2.begin(); it != adj_list2.end(); it++) {
			if (touched[subgraph_vertex_list_ID(input_graph, *it)] == 0
				&& added_to_be_touched[subgraph_vertex_list_ID(input_graph, *it)] == 0) {
				added_to_be_touched[subgraph_vertex_list_ID(input_graph, *it)] = 1;
				to_be_touched.insert(to_be_touched.end(), *it); // to_be_touched contains original V_IDs
				//cout << "to_be_touched.insert " << *it << endl;
			}
		}

		to_be_touched.erase(to_be_touched.begin());
	}

	return cpn_size;

}
