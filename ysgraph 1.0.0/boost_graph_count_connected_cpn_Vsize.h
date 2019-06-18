#pragma once


int boost_graph_count_connected_cpn_Vsize(graph& input_graph, int StartVertex) {

	typedef boost::graph_traits<graph>::adjacency_iterator AdjacencyIterator;
	AdjacencyIterator ai, a_end;

	int V = num_vertices(input_graph);
	int cpn_size = 0;
	std::vector<int> touched(V);
	std::vector<int> added_to_be_touched(V); // it is necessary when input_graph is not a tree, otherwise to_be_touched may contain vertex repetitively
	std::vector<int> to_be_touched;

	touched[StartVertex] = 1;
	cpn_size++;

	boost::tie(ai, a_end) = boost::adjacent_vertices(StartVertex, input_graph);
	for (; ai != a_end; ai++) {
		added_to_be_touched[*ai] = 1;
		to_be_touched.insert(to_be_touched.end(), *ai);
	}

	while (to_be_touched.size() > 0) {
		touched[to_be_touched[0]] = 1;

		cpn_size++;
		boost::tie(ai, a_end) = boost::adjacent_vertices(to_be_touched[0], input_graph);
		for (; ai != a_end; ai++) {
			if (touched[*ai] == 0 && added_to_be_touched[*ai] == 0) {
				added_to_be_touched[*ai] = 1;
				to_be_touched.insert(to_be_touched.end(), *ai);
				//cout << "to_be_touched.insert " << *ai << endl;
			}
		}
		to_be_touched.erase(to_be_touched.begin());
	}

	return cpn_size;

}
