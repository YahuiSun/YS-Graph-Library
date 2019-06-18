#pragma once

#include <boost_graph.h>
#include <boost/random.hpp>




graph boost_graph_generate_random_graph_with_nw_ec(int V, int E, double ec_min, double ec_max, 
	double nw_min, double nw_max, int input_precision) {


	typedef boost::graph_traits<graph>::adjacency_iterator AdjacencyIterator;
	AdjacencyIterator ai, a_end;
	typedef graph::edge_descriptor Edge;

	double precision = std::pow(10, input_precision);
	std::time_t now = std::time(0);
	boost::random::mt19937 gen{ static_cast<std::uint32_t>(now) };
	boost::random::uniform_int_distribution<> dist_ec{ static_cast<int>(ec_min*precision), static_cast<int>(ec_max*precision) };
	boost::random::uniform_int_distribution<> dist_nw{ static_cast<int>(nw_min*precision), static_cast<int>(nw_max*precision) };

	graph random_graph(V); // generate vertices

	/*add edges to random_graph*/
	if (E == V * (V - 1) / 2) { // complete graphs
		for (int i = 0; i < V; i++) {
			for (int j = 0; j < i; j++) {
				double new_cost = (double)dist_ec(gen) / precision; // generate ec
				boost::add_edge(i, j, new_cost, random_graph);
			}
		}
	}
	else { // incomplete graphs

		/*generate a random spanning tree*/
		std::vector<int> inside_V; // the included vertex
		inside_V.insert(inside_V.end(), 0);
		while (inside_V.size() < V) {
			int v1 = rand() % inside_V.size();  // generate random number from [0, inside_V.size()-1]
			int v2 = inside_V.size();
			double new_cost = (double)dist_ec(gen) / precision; // generate ec
			boost::add_edge(v1, v2, new_cost, random_graph);
			inside_V.insert(inside_V.end(), v2);
		}

		std::vector<int> not_full_vertices; // vertices without a full degree
		for (int i = 0; i < V; i++) {
			not_full_vertices.insert(not_full_vertices.end(), i);
		}

		while (num_edges(random_graph) < E) {

			int RAND = 0 + (rand() % (int)(not_full_vertices.size() - 1 - 0 + 1)); // generate int random number  0, not_full_vertices.size()-1
			if (in_degree(not_full_vertices[RAND], random_graph) < V - 1) { // this is a vertex without a full degree
				for (int i = 0; i < V; i++) {
					if (not_full_vertices[RAND] != i) {
						std::pair<Edge, bool> ed = boost::edge(not_full_vertices[RAND], i, random_graph);
						if (!ed.second && rand() > 0.5) { // This edge does not exist
							double new_cost = (double)dist_ec(gen) / precision; // generate ec
							boost::add_edge(not_full_vertices[RAND], i, new_cost, random_graph); // add a new edge
							break; // break after adding one edge
						}
					}
				}
			}
			else { // this is a vertex with a full degree
				not_full_vertices.erase(not_full_vertices.begin() + RAND);
			}

		}
	}


	/*generate random node weights*/
	for (int i = 0; i < V; i++) {
		double new_weight = (double)dist_nw(gen) / precision; // generate nw 
		boost::put(boost::vertex_name_t(), random_graph, i, new_weight); // put node weight
	}

	return random_graph;
}
