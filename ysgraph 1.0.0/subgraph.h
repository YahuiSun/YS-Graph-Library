#pragma once



/* define subgraph: pair<vertex, adjacent vertices> */
typedef std::pair<int, std::vector<int>> subgraph_node;
typedef std::vector<std::pair<int, std::vector<int>>> subgraph;



#pragma region
void subgraph_add_vertex(subgraph& input_graph, int vertex) {

	/*this function only adds a unique vertex*/

	bool unique = true;
	int i = 0;
	while (i < input_graph.size()) {
		if (input_graph[i].first == vertex) { // this vertex is already inside
			unique = false;
			break;
		}
		i++;
	}

	if (unique == true) {
		subgraph_node x;
		x.first = vertex;
		input_graph.insert(input_graph.end(), x); // insert a subgraph_node
	}

}
#pragma endregion subgraph_add_vertex



#pragma region
void subgraph_remove_vertex(subgraph& input_graph, int vertex) {

	int i = 0;
	while (i < input_graph.size()) {
		if (input_graph[i].first == vertex) { // i is the list of this vertex
			input_graph.erase(input_graph.begin() + i); // remove this list
			i--;
		}
		else {
			/*remove vertex from input_graph[i].second*/
			int j = 0;
			while (j < input_graph[i].second.size()) {
				if (input_graph[i].second[j] == vertex) {
					input_graph[i].second.erase(input_graph[i].second.begin() + j); // remove vertex from input_graph[i].second
					break; // move on from this list
				}
				j++;
			}
		}
		i++;
	}

}
#pragma endregion subgraph_remove_vertex



#pragma region
void subgraph_add_edge(subgraph& input_graph, int e1, int e2) {

	/*this function only adds a unique edge, and may add e1 and e2 into input_graph if they are new vertices*/

	bool unique_edge = true;

	bool e1_is_new_vertex = true;
	int i = 0;
	while (i < input_graph.size()) {
		if (input_graph[i].first == e1) {
			e1_is_new_vertex = false;
			for (int j = 0; j < input_graph[i].second.size(); j++) {
				if (input_graph[i].second[j] == e2) {
					unique_edge == false;
					break;
				}
			}
			if (unique_edge == true) {
				input_graph[i].second.insert(input_graph[i].second.end(), e2); // add e2 into adj_list of e1
			}
			break;
		}
		i++;
	}
	if (e1_is_new_vertex == true) {
		subgraph_node x;
		x.first = e1;
		x.second = { e2 };
		input_graph.insert(input_graph.end(), x);  // add e1 as a new vertex, and add e2 into adj_list of e1
	}


	if (unique_edge == true) { // only continue when the edge is unique
		bool e2_is_new_vertex = true;
		int i = 0;
		while (i < input_graph.size()) {
			if (input_graph[i].first == e2) {
				e2_is_new_vertex = false;
				input_graph[i].second.insert(input_graph[i].second.end(), e1); // add e1 into adj_list of e2
				break;
			}
			i++;
		}
		if (e2_is_new_vertex == true) {
			subgraph_node x;
			x.first = e2;
			x.second = { e1 };
			input_graph.insert(input_graph.end(), x);  // add e2 as a new vertex, and add e1 into adj_list of e2
		}
	}

}
#pragma endregion subgraph_add_edge



#pragma region
subgraph subgraph_copy_subgraph(subgraph& input_subgraph) {

	return input_subgraph;

}
#pragma endregion subgraph_copy_subgraph