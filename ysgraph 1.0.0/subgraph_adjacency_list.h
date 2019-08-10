#pragma once

/*this is an adjacency list; it is more efficient than a vector for Insertion and Deletion*/



/* define subgraph_adjacency_list: pair<vertex, adjacent vertices> */
typedef std::pair<int, std::list<int>> subgraph_adjacency_list_node;
typedef std::list<std::pair<int, std::list<int>>> subgraph_adjacency_list;


void subgraph_adjacency_list_add_nonunique_vertex(subgraph_adjacency_list& input_graph, int vertex) {

	/*this function adds a vertex without checking its uniqueness;
	time complexity O(1)*/

	subgraph_adjacency_list_node x;
	x.first = vertex;
	input_graph.push_back(x); // insert a subgraph_adjacency_list_node

}



void subgraph_adjacency_list_add_unique_vertex(subgraph_adjacency_list& input_graph, int vertex) {

	/*this function only adds a unique vertex;
	time complexity O(|V|)*/

	bool unique = true;
	for (std::list<std::pair<int, std::list<int>>>::iterator it = input_graph.begin(); it != input_graph.end(); it++) {
		if ((*it).first == vertex) { // this vertex is already inside
			unique = false;
			break;
		}
	}

	if (unique == true) {
		subgraph_adjacency_list_node x;
		x.first = vertex;
		input_graph.push_back(x); // insert a subgraph_adjacency_list_node
	}

}



void subgraph_adjacency_list_remove_vertex(subgraph_adjacency_list& input_graph, int vertex) {

	/*this function removes a vertex and its adjacent edges;
	if this is an redundant vertex, then all of its copies will be removed*/


	for (std::list<std::pair<int, std::list<int>>>::iterator it = input_graph.begin(); it != input_graph.end(); it++) {
		if ((*it).first == vertex) {
			input_graph.erase(it); // remove this vertex's list
			*it--;
		}
		else {
			(*it).second.remove(vertex); // remove adjacent edges
		}
	}

}



void subgraph_adjacency_list_add_nonunique_edge(subgraph_adjacency_list& input_graph, int e1, int e2) {

	/*this function adds an edge without checking its uniqueness, and may add e1 and e2 into input_graph if they are new vertices*/

	bool e1_is_new_vertex = true;
	for (std::list<std::pair<int, std::list<int>>>::iterator it = input_graph.begin(); it != input_graph.end(); it++) {
		if ((*it).first == e1) {
			e1_is_new_vertex = false;
			(*it).second.push_back(e2); // add e2 into adj_list of e1
			break;
		}
	}
	if (e1_is_new_vertex == true) {
		subgraph_adjacency_list_node x;
		x.first = e1;
		x.second = { e2 };
		input_graph.insert(input_graph.end(), x);  // add e1 as a new vertex, and add e2 into adj_list of e1
	}

	bool e2_is_new_vertex = true;
	for (std::list<std::pair<int, std::list<int>>>::iterator it = input_graph.begin(); it != input_graph.end(); it++) {
		if ((*it).first == e2) {
			e2_is_new_vertex = false;
			(*it).second.push_back(e1); // add e1 into adj_list of e2
			break;
		}
	}
	if (e2_is_new_vertex == true) {
		subgraph_adjacency_list_node x;
		x.first = e2;
		x.second = { e1 };
		input_graph.insert(input_graph.end(), x);  // add e2 as a new vertex, and add e1 into adj_list of e2
	}

}



void subgraph_adjacency_list_add_unique_edge(subgraph_adjacency_list& input_graph, int e1, int e2) {

	/*this function only adds a unique edge, and may add e1 and e2 into input_graph if they are new vertices*/

	bool unique_edge = true;

	bool e1_is_new_vertex = true;
	for (std::list<std::pair<int, std::list<int>>>::iterator it = input_graph.begin(); it != input_graph.end(); it++) {
		if ((*it).first == e1) {
			e1_is_new_vertex = false;
			for (std::list<int>::iterator it2 = (*it).second.begin(); it2 != (*it).second.end(); it2++) {
				if ((*it2) == e2) {
					unique_edge == false;
					break;
				}
			}
			if (unique_edge == true) {
				(*it).second.push_back(e2); // add e2 into adj_list of e1
			}
			break;
		}
	}
	if (e1_is_new_vertex == true) {
		subgraph_adjacency_list_node x;
		x.first = e1;
		x.second = { e2 };
		input_graph.insert(input_graph.end(), x);  // add e1 as a new vertex, and add e2 into adj_list of e1
	}



	if (unique_edge == true) { // only continue when the edge is unique

		bool e2_is_new_vertex = true;
		for (std::list<std::pair<int, std::list<int>>>::iterator it = input_graph.begin(); it != input_graph.end(); it++) {
			if ((*it).first == e2) {
				e2_is_new_vertex = false;
				(*it).second.push_back(e1); // add e1 into adj_list of e2
				break;
			}
		}
		if (e2_is_new_vertex == true) {
			subgraph_adjacency_list_node x;
			x.first = e2;
			x.second = { e1 };
			input_graph.insert(input_graph.end(), x);  // add e2 as a new vertex, and add e1 into adj_list of e2
		}
	}

}



subgraph_adjacency_list subgraph_adjacency_list_copy_subgraph_adjacency_list(subgraph_adjacency_list& input_subgraph_adjacency_list) {

	return input_subgraph_adjacency_list;

}



std::list<int> subgraph_adjacency_list_adjacent_vertices(subgraph_adjacency_list& input_graph, int vertex) {

	/*this function returns the adjacent vertices of the input vertex*/

	for (subgraph_adjacency_list::iterator it = input_graph.begin(); it != input_graph.end(); it++) {

		if ((*it).first == vertex) {
			return (*it).second;
		}

	}
}



int subgraph_adjacency_list_degree(subgraph_adjacency_list& input_graph, int vertex) {

	return subgraph_adjacency_list_adjacent_vertices(input_graph, vertex).size();

}


int subgraph_adjacency_list_num_vertices(subgraph_adjacency_list& input_graph) {

	return input_graph.size();

}



int subgraph_adjacency_list_num_edges(subgraph_adjacency_list& input_graph) {

	int num = 0;

	for (std::list<std::pair<int, std::list<int>>>::iterator it = input_graph.begin(); it != input_graph.end(); it++) {
		num = num + (*it).second.size();
	}

	return num / 2;

}




int subgraph_adjacency_list_vertex_list_ID(subgraph_adjacency_list& input_graph, int vertex) {

	/*this function returns the ID of the list that corresponds to the vertex*/
	int i = 0;
	for (std::list<std::pair<int, std::list<int>>>::iterator it = input_graph.begin(); it != input_graph.end(); it++) {
		if ((*it).first == vertex) {
			return i;
		}
		i++;
	}

}



bool subgraph_adjacency_list_contain_vertex(subgraph_adjacency_list& input_graph, int vertex) {

	/*this function returns whether the vertex is contained or not*/
	for (std::list<std::pair<int, std::list<int>>>::iterator it = input_graph.begin(); it != input_graph.end(); it++) {
		if ((*it).first == vertex) {
			return true;
		}
	}

	return false;

}



void subgraph_adjacency_list_print(subgraph_adjacency_list& input_graph) {

	std::cout << "subgraph_adjacency_list_print: " << std::endl;
	std::cout << "num_vertices: " << subgraph_adjacency_list_num_vertices(input_graph) << std::endl;
	std::cout << "num_edges: " << subgraph_adjacency_list_num_edges(input_graph) << std::endl;

	for (std::list<std::pair<int, std::list<int>>>::iterator it = input_graph.begin(); it != input_graph.end(); it++) {

		std::cout << (*it).first << ": ";

		for (std::list<int>::iterator it2 = (*it).second.begin(); it2 != (*it).second.end(); it2++) {
			std::cout << (*it2) << " ";
		}

		std::cout << '\n';

	}

	std::cout << "END" << '\n';

}



#include <subgraph_unordered_map.h>
subgraph subgraph_adjacency_list_2_subgraph(subgraph_adjacency_list& input_subgraph_adjacency_list) {

	/* this function changes a subgraph_adjacency_list to a subgraph_hash*/

	subgraph output_subgraph;

	for (auto i = input_subgraph_adjacency_list.begin(); i != input_subgraph_adjacency_list.end(); i++) {
		int v = i->first;
		std::list<int> adj_v_list = i->second;
		subgraph_add_vertex(output_subgraph, v); // copy vertex
		for (auto j = adj_v_list.begin(); j != adj_v_list.end(); j++) {
			int adj_v = *j;
			if (adj_v > v) {
				subgraph_add_edge(output_subgraph, adj_v, v); // copy edge
			}
		}
	}

	return output_subgraph;

}



subgraph_adjacency_list subgraph_adjacency_list_merge_subgraph_adjacency_list(
	subgraph_adjacency_list& list1, subgraph_adjacency_list& list2) {

	subgraph_adjacency_list merged_list = subgraph_adjacency_list_copy_subgraph_adjacency_list(list1);

	for (auto i = list2.begin(); i != list2.end(); i++) {
		int v = i->first;
		std::list<int> adj_v_list = i->second;
		subgraph_adjacency_list_add_unique_vertex(merged_list, v); // copy vertex
		for (auto j = adj_v_list.begin(); j != adj_v_list.end(); j++) {
			int adj_v = *j;
			if (adj_v > v) {
				subgraph_adjacency_list_add_unique_edge(merged_list, v, adj_v); // copy edge
			}
		}
	}

	return merged_list;

}










