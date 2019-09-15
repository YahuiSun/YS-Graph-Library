#pragma once

#include <boost_graph.h>

std::vector<std::pair<int, int>> boost_graph_depth_first_search_a_tree_of_edges(graph& input_graph, int& root) {

	/*the Pseudocode is in https://www.hackerearth.com/zh/practice/algorithms/graphs/breadth-first-search/tutorial/ */
	/*we assume that input_graph is connected,
	otherwise the components that are disconnected with the root will not be traversed*/

	std::vector<pair<int, int>> discovered_edges;

	typedef boost::graph_traits<graph>::adjacency_iterator AdjacencyIterator;
	AdjacencyIterator ai, a_end;

	int N = num_vertices(input_graph); // number of vertices

	std::vector<bool> discovered(N);
	discovered[root] = true; // mark root as visited

	std::queue<int> Q; // Queue is a data structure designed to operate in FIFO (First in First out) context.
	Q.push(root);

	while (Q.size() > 0) {

		int v = Q.front();
		Q.pop(); //Removing that vertex from queue,whose neighbour will be visited now

		/*processing all the neighbours of v*/
		boost::tie(ai, a_end) = boost::adjacent_vertices(v, input_graph);
		for (; ai != a_end; ai++) {
			if (discovered[*ai] == false) { // *ai has not been discovered
				Q.push(*ai);
				discovered[*ai] = true;  // *ai has been discovered
				discovered_edges.insert(discovered_edges.end(), { v,*ai }); // the discovered_edges in order
				//cout << "discovered_edges(" << v << "," << *ai << ")" << endl;
			}
		}

	}

	return discovered_edges;
}