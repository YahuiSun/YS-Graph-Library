#pragma once


graph boost_graph_find_MST(graph& input_graph) {

	/*input_graph may be disconnected*/

	typedef boost::graph_traits<graph>::adjacency_iterator AdjacencyIterator;
	AdjacencyIterator ai, a_end;

	int N = num_vertices(input_graph); // number of vertices
	graph output_graph(N);
	for (int i = 0; i < N; i++) {
		boost::put(boost::vertex_name_t(), output_graph, i, get(boost::vertex_name_t(), input_graph, i)); // put inside the node weight
	}

	/*add dummy vertices and edges for disconnected input_graph*/
	double M = 1e20; // we assume that M is large enough to find MSTs in input_graph
	boost::add_vertex(N, input_graph); // add a dummy vertex
	for (int i = 0; i < N; i++) {
		boost::add_edge(N, i, M, input_graph); // add dummy edges
	}

	/*find the random MST; https://www.boost.org/doc/libs/1_46_1/libs/graph/doc/prim_minimum_spanning_tree.html */
	std::vector <boost::graph_traits<graph>::vertex_descriptor> p(N + 1); // minimum_spanning_tree traits
	prim_minimum_spanning_tree(input_graph, &p[0]); // 0 is the root; find MST in new_graph
	for (int i = 1; i < N; i++) { // p[0]=0; If p[u] = u then u is either the root of the tree or is a vertex that is not reachable from the root. 
		if (p[i] != N) { // (i, p[i]) is not a dummy edge
			boost::add_edge(i, p[i], get(boost::edge_weight_t(), input_graph, boost::edge(i, p[i], input_graph).first), output_graph);
		}
	}

	clear_vertex(N, input_graph);
	remove_vertex(N, input_graph);

	return output_graph;

}