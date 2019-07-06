#pragma once

/*this is an adjacency list built using hashes*/

#include <unordered_map>


/* define subgraph*/
typedef std::unordered_map<int, int> subgraph_node_adj_hash; // key: an adjacent node; value: this adjacent node
typedef std::unordered_map<int, subgraph_node_adj_hash> subgraph_hash; // key: a node; value: the hash of the adjacent nodes



void subgraph_add_vertex(subgraph_hash& input_graph, int vertex) {

	/*time complexity O(1)*/
	/*since unordered_map containers do not allow for duplicate keys,
	all the vertices in subgraph_hash are unique*/

	subgraph_node_adj_hash x;
	input_graph[vertex] = x;

}




void subgraph_remove_vertex(subgraph_hash& input_graph, int vertex) {

	/*this function removes a vertex and its adjacent edges;
	time complexity O(|V|)*/

	input_graph.erase(vertex); // remove this vertex

	for (auto it = input_graph.begin(); it != input_graph.end(); ++it) {
		it->second.erase(vertex); // remove adjacent edges
	}

}




bool subgraph_contain_vertex(subgraph_hash& input_graph, int vertex) {

	/*this function checks whether a vertex/key is in input_graph or not;
	time complexity O(1)*/

	if (input_graph.count(vertex) > 0) {
		return true;
	}
	else {
		return false;
	}

}




void subgraph_add_edge(subgraph_hash& input_graph, int e1, int e2) {

	/*this function adds an edge, and may add e1 and e2 into input_graph if they are new vertices;
	time complexity O(1)*/

	if (!subgraph_contain_vertex(input_graph, e1)) { // e1 is a new vertex
		subgraph_add_vertex(input_graph, e1); // add e1
	}
	if (!subgraph_contain_vertex(input_graph, e2)) { // e2 is a new vertex
		subgraph_add_vertex(input_graph, e2); // add e2
	}

	auto search = input_graph.find(e1);
	search->second[e2] = e2; // add e2 to adj_hash of e1
	search = input_graph.find(e2);
	search->second[e1] = e1; // add e1 to adj_hash of e2

}



subgraph_hash subgraph_copy_subgraph(subgraph_hash& input_subgraph) {

	return input_subgraph;

}




std::list<int> subgraph_adjacent_vertices(subgraph_hash& input_graph, int vertex) {

	/*this function returns the adjacent vertices of the input vertex;
	time complexity O(|V|)*/

	std::list<int> adj_list;

	auto search = input_graph.find(vertex);
	for (auto it = search->second.begin(); it != search->second.end(); ++it) {
		adj_list.push_back(it->first);
	}

	return adj_list;

}



int subgraph_degree(subgraph_hash& input_graph, int vertex) {

	/*time complexity O(1)*/

	auto search = input_graph.find(vertex);
	return search->second.size();

}



int subgraph_num_edges(subgraph_hash& input_graph) {

	/*time complexity O(|V|)*/

	int num = 0;

	for (auto it = input_graph.begin(); it != input_graph.end(); ++it) {
		num = num + it->second.size();
	}

	return num / 2;

}



void subgraph_print(subgraph_hash& input_graph) {

	/*time complexity O(|V|+|E|)*/

	std::cout << "subgraph_print: " << std::endl;

	for (auto it = input_graph.begin(); it != input_graph.end(); ++it) {

		std::cout << it->first << ": ";

		for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
			std::cout << it2->first << " ";
		}

		std::cout << '\n';

	}

	std::cout << "END" << '\n';

}

