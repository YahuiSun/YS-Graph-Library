#pragma once


#include <boost_graph.h>
#include <subgraph_adjacency_list.h>


subgraph_adjacency_list subgraph_adjacency_list_MST_postprocessing_boost(graph& input_graph, subgraph_adjacency_list& input_subgraph_adjacency_list) {

	/*input_subgraph_adjacency_list may not be connected*/

	typedef boost::graph_traits<graph>::adjacency_iterator AdjacencyIterator;
	AdjacencyIterator ai, a_end;

	int N_graph = num_vertices(input_graph);
	int N_subgraph_adjacency_list = input_subgraph_adjacency_list.size();

	/*build a base_graph that contains all the edges between vertices in input_subgraph_adjacency_list*/
	graph base_graph(N_subgraph_adjacency_list);
	std::vector<int> baseV_to_V(N_subgraph_adjacency_list), V_to_baseV(N_graph), V_in_baseV_or_not(N_graph);
	int i = 0;
	for (subgraph_adjacency_list::iterator it = input_subgraph_adjacency_list.begin(); it != input_subgraph_adjacency_list.end(); it++) {
		baseV_to_V[i] = (*it).first;
		V_to_baseV[(*it).first] = i;
		V_in_baseV_or_not[(*it).first] = 1;
		i++;
	}
	for (int i = 0; i < N_subgraph_adjacency_list; i++) {
		int e1 = baseV_to_V[i];
		boost::tie(ai, a_end) = boost::adjacent_vertices(e1, input_graph); // adjacent vertices of e1
		for (; ai != a_end; ai++) {
			if (V_in_baseV_or_not[*ai] == 1) { // *ai is in input_subgraph_adjacency_list
				int e2 = *ai; // (e1, e2) in input_graph is in base_graph
				if (e1 < e2) { // count an edge only once
					double ec = get(boost::edge_weight_t(), input_graph, boost::edge(e1, e2, input_graph).first); // edge cost
					boost::add_edge(V_to_baseV[e1], V_to_baseV[e2], ec, base_graph); // add an edge to base_graph
				}
			}
		}
	}

	/*find MST of base_graph*/
	subgraph_adjacency_list MST;
	for (int i = 0; i < N_subgraph_adjacency_list; i++) {
		subgraph_adjacency_list_add_nonunique_vertex(MST, baseV_to_V[i]); // add vertices to MST
	}
	/*add dummy vertices and edges for disconnected base_graph*/
	double M = 1e20; // we assume that M is large enough to find MSTs in input_graph
	boost::add_vertex(N_subgraph_adjacency_list, base_graph); // add a dummy vertex
	for (int i = 0; i < N_subgraph_adjacency_list; i++) {
		boost::add_edge(N_subgraph_adjacency_list, i, M, base_graph); // add dummy edges
	}
	/*find the random MST; https://www.boost.org/doc/libs/1_46_1/libs/graph/doc/prim_minimum_spanning_tree.html */
	std::vector <boost::graph_traits<graph>::vertex_descriptor> p(N_subgraph_adjacency_list + 1); // minimum_spanning_tree traits
	prim_minimum_spanning_tree(base_graph, &p[0]); // 0 is the root; find MST in new_graph
	for (int i = 1; i < N_subgraph_adjacency_list; i++) { // p[0]=0; If p[u] = u then u is either the root of the tree or is a vertex that is not reachable from the root. 
		if (p[i] != N_subgraph_adjacency_list) { // (i, p[i]) is not a dummy edge
			subgraph_adjacency_list_add_nonunique_edge(MST, baseV_to_V[i], baseV_to_V[p[i]]); // add edges to MST
		}
	}

	return MST;

}

