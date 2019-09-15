#pragma once

/*this is an adjacency list built using hashes*/

#include <unordered_map>
#include <unordered_set>

/* define subgraph*/
typedef std::unordered_set<int> subgraph_node_adj_hash; // key: an adjacent node; value: this adjacent node
typedef std::unordered_map<int, subgraph_node_adj_hash> subgraph; // key: a node; value: the hash of the adjacent nodes



void subgraph_add_vertex(subgraph& input_graph, int vertex) {

	/*time complexity O(1)*/
	/*since unordered_map containers do not allow for duplicate keys,
	all the vertices in subgraph are unique*/

	if (input_graph.count(vertex) == 0) { // vertex is not in input_graph
		subgraph_node_adj_hash x;
		input_graph[vertex] = x;
	}

}




void subgraph_remove_vertex(subgraph& input_graph, int vertex) {

	/*this function removes a vertex and its adjacent edges;
	time complexity O(|V|)*/

	input_graph.erase(vertex); // remove this vertex

	for (auto it = input_graph.begin(); it != input_graph.end(); ++it) {
		it->second.erase(vertex); // remove adjacent edges
	}

}


void subgraph_remove_leaf(subgraph& input_graph, int vertex) {

	/*this function removes a leaf and its adjacent edge;
	time complexity O(1)*/

	auto search = input_graph.find(vertex);
	int adj_v = *search->second.begin(); // the adjacency vertex

	input_graph.erase(vertex); // remove this vertex

	search = input_graph.find(adj_v);
	search->second.erase(vertex); // remove the adjacency edge

}




bool subgraph_contain_vertex(subgraph& input_graph, int vertex) {

	/*this function checks whether a vertex/key is in input_graph or not;
	time complexity O(1)*/

	if (input_graph.count(vertex) > 0) {
		return true;
	}
	else {
		return false;
	}

}




void subgraph_add_edge(subgraph& input_graph, int e1, int e2) {

	/*this function adds an edge, and may add e1 and e2 into input_graph if they are new vertices;
	time complexity O(1)*/

	if (!subgraph_contain_vertex(input_graph, e1)) { // e1 is a new vertex
		subgraph_add_vertex(input_graph, e1); // add e1
	}
	if (!subgraph_contain_vertex(input_graph, e2)) { // e2 is a new vertex
		subgraph_add_vertex(input_graph, e2); // add e2
	}

	auto search = input_graph.find(e1);
	search->second.insert(e2); // add e2 to adj_hash of e1
	auto search2 = input_graph.find(e2);
	search2->second.insert(e1); // add e1 to adj_hash of e2

}


void subgraph_remove_edge_and_isolated_vertices(subgraph& input_graph, int e1, int e2) {

	/*this function removes an edge, and may remove e1 and e2 if they are isolated;
	time complexity O(1)*/

	auto search = input_graph.find(e1);
	search->second.erase(e2);
	auto search2 = input_graph.find(e2);
	search2->second.erase(e1);

	if (search->second.size() == 0) {
		input_graph.erase(e1);
	}
	if (search2->second.size() == 0) {
		input_graph.erase(e2);
	}

}

void subgraph_remove_edge_but_not_isolated_vertices(subgraph& input_graph, int e1, int e2) {

	/*this function removes an edge, but not remove e1 and e2 if they are isolated;
	time complexity O(1)*/

	auto search = input_graph.find(e1);
	search->second.erase(e2);
	auto search2 = input_graph.find(e2);
	search2->second.erase(e1);

}




subgraph subgraph_copy_subgraph(subgraph& input_subgraph) {

	return input_subgraph;

}



int subgraph_num_vertices(subgraph& input_graph) {

	/*time complexity O(1)*/

	return input_graph.size();

}


int subgraph_num_edges(subgraph& input_graph) {

	/*time complexity O(|V|)*/

	int num = 0;

	for (auto it = input_graph.begin(); it != input_graph.end(); ++it) {
		num = num + it->second.size();
	}

	return num / 2;

}



void subgraph_print(subgraph& input_graph) {

	/*time complexity O(|V|+|E|)*/

	std::cout << "subgraph_print: " << std::endl;
	std::cout << "num_vertices: " << subgraph_num_vertices(input_graph) << std::endl;
	std::cout << "num_edges: " << subgraph_num_edges(input_graph) << std::endl;

	for (auto it = input_graph.begin(); it != input_graph.end(); ++it) {

		std::cout << it->first << ": ";

		for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
			std::cout << *it2 << " ";
		}

		std::cout << '\n';

	}

	std::cout << "subgraph_print END" << '\n';

}




std::list<int> subgraph_adjacent_vertices(subgraph& input_graph, int vertex) {

	/*this function returns the adjacent vertices of the input vertex;
	time complexity O(|V|)*/

	std::list<int> adj_list;

	auto search = input_graph.find(vertex);
	//std::cout << "vertex: " << vertex << std::endl;
	//std::cout << "search->second.size(): " << search->second.size() << std::endl;
	//subgraph_print(input_graph);
	if (search->second.size() > 0) {
		for (auto it = search->second.begin(); it != search->second.end(); ++it) {
			adj_list.push_back(*it);
		}
	}
	

	return adj_list;

}



int subgraph_degree(subgraph& input_graph, int vertex) {

	/*time complexity O(1)*/

	auto search = input_graph.find(vertex);
	return search->second.size();

}










int subgraph_vertex_list_ID(subgraph& input_graph, int vertex) {

	/*this function returns the ID of the hash that corresponds to the vertex*/
	int i = 0;
	for (auto it = input_graph.begin(); it != input_graph.end(); it++) {
		if ((*it).first == vertex) {
			return i;
		}
		i++;
	}

}




subgraph subgraph_merge_subgraph(
	subgraph& g1, subgraph& g2) {

	subgraph merged_g = subgraph_copy_subgraph(g1);

	for (auto i = g2.begin(); i != g2.end(); i++) {
		int v = i->first;
		std::list<int> adj_v_list = subgraph_adjacent_vertices(g2, v);
		subgraph_add_vertex(merged_g, v); // copy vertex
		for (auto j = adj_v_list.begin(); j != adj_v_list.end(); j++) {
			int adj_v = *j;
			if (adj_v > v) {
				subgraph_add_edge(merged_g, v, adj_v); // copy edge
			}
		}
	}

	return merged_g;

}