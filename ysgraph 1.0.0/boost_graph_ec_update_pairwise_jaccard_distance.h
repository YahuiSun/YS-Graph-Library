#pragma once


#include <boost_graph.h>


void boost_graph_ec_update_pairwise_jaccard_distance(graph& input_graph) {

	/*for introducing this distance: https://en.wikipedia.org/wiki/Jaccard_index ;
	The Jaccard distance, which measures dissimilarity between sample sets, is complementary
	to the Jaccard coefficient and is obtained by subtracting the Jaccard coefficient from 1;
	dist(i,j) = 1 - |V_i \cap V_j| / |V_i \cup V_j|, where V_i is the set of adjacent vertices of i;
	this is different from that in T Lappse's 2009 paper */

	typedef boost::graph_traits<graph>::adjacency_iterator AdjacencyIterator;
	AdjacencyIterator ai, a_end, bi, b_end;
	typedef graph::edge_descriptor Edge;

	int N = num_vertices(input_graph); // number of vertices

	for (int i = 0; i < N; i++) {
		boost::tie(ai, a_end) = boost::adjacent_vertices(i, input_graph);
		for (; ai != a_end; ai++) {
			int j = *ai;
			if (i < j) { // edge (i,j)

				/*update_pairwise_Jaccard_distance for edge (i,j)*/

				std::vector<int> V_i, V_j;
				boost::tie(bi, b_end) = boost::adjacent_vertices(i, input_graph);
				for (; bi != b_end; bi++) {
					V_i.insert(V_i.end(), *bi);
				}
				boost::tie(bi, b_end) = boost::adjacent_vertices(j, input_graph);
				for (; bi != b_end; bi++) {
					V_j.insert(V_j.end(), *bi);
				}

				int V_i_cap_V_j = 0;
				for (int k = 0; k < V_i.size(); k++) {
					bool capped = false;
					for (int m = 0; m < V_j.size(); m++) {
						if (V_i[k] == V_j[m]) {
							capped = true;
							break;
						}
					}
					if (capped == true) {
						V_i_cap_V_j++;
					}
				}

				int V_i_cup_V_j = V_i.size() + V_j.size() - V_i_cap_V_j;

				double ec = 1 - (double)V_i_cap_V_j / V_i_cup_V_j;
				std::pair<Edge, bool> ed = boost::edge(i, j, input_graph);
				boost::put(boost::edge_weight_t(), input_graph, ed.first, ec);

			}
		}
	}


}