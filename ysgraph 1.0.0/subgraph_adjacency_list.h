#pragma once

/*this is an adjacency list; it is more efficient than a vector for Insertion and Deletion*/



/* define subgraph: pair<vertex, adjacent vertices> */
typedef std::pair<int, std::list<int>> subgraph_node;
typedef std::list<std::pair<int, std::list<int>>> subgraph;


void subgraph_add_nonunique_vertex(subgraph& input_graph, int vertex) {

	/*this function only adds a vertex without checking its uniqueness*/

	subgraph_node x;
	x.first = vertex;
	input_graph.push_back(x); // insert a subgraph_node

}



void subgraph_add_unique_vertex(subgraph& input_graph, int vertex) {

	/*this function only adds a unique vertex*/

	bool unique = true;
	for (std::list<std::pair<int, std::list<int>>>::iterator it = input_graph.begin(); it != input_graph.end(); it++) {
		if ((*it).first == vertex) { // this vertex is already inside
			unique = false;
			break;
		}
	}

	if (unique == true) {
		subgraph_node x;
		x.first = vertex;
		input_graph.push_back(x); // insert a subgraph_node
	}

}



void subgraph_remove_vertex(subgraph& input_graph, int vertex) {

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



void subgraph_add_nonunique_edge(subgraph& input_graph, int e1, int e2) {

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
		subgraph_node x;
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
		subgraph_node x;
		x.first = e2;
		x.second = { e1 };
		input_graph.insert(input_graph.end(), x);  // add e2 as a new vertex, and add e1 into adj_list of e2
	}

}



void subgraph_add_unique_edge(subgraph& input_graph, int e1, int e2) {

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
		subgraph_node x;
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
			subgraph_node x;
			x.first = e2;
			x.second = { e1 };
			input_graph.insert(input_graph.end(), x);  // add e2 as a new vertex, and add e1 into adj_list of e2
		}
	}

}





#pragma region
subgraph subgraph_copy_subgraph(subgraph& input_subgraph) {

	return input_subgraph;

}
#pragma endregion subgraph_copy_subgraph