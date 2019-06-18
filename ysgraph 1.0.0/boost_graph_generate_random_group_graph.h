#pragma once

#include <boost_graph.h>

graph boost_graph_generate_random_group_graph(int G, int g_size_min, int g_size_max, graph& input_graph) {

	typedef boost::graph_traits<graph>::adjacency_iterator AdjacencyIterator;
	AdjacencyIterator ai, a_end;
	typedef graph::edge_descriptor Edge;

	int V = num_vertices(input_graph);
	int E = num_edges(input_graph);

	graph group_graph(V);


	/*add groups*/
	while (num_vertices(group_graph) < V + G) {

		int group_size = g_size_min + (rand() % (int)(g_size_max - g_size_min + 1)); // generate int random number

		std::vector<int> to_be_added(V);
		std::iota(std::begin(to_be_added), std::end(to_be_added), 0); // Fill with 0, 1, 2, ...

		std::vector<int> group_vertices;
		while (group_vertices.size() < group_size) {

			int randID = rand() % (int)to_be_added.size();
			group_vertices.insert(group_vertices.end(), to_be_added[randID]);
			to_be_added.erase(to_be_added.begin() + randID);

		}


		// add this group
		int new_v = num_vertices(group_graph);
		boost::add_vertex(new_v, group_graph);
		for (int j = 0; j < group_vertices.size(); j++) {
			boost::add_edge(group_vertices[j], new_v, 1, group_graph);
		}


	}

	return group_graph;


}