#pragma once


graph boost_graph_EA_for_KleinNWSTP(graph& instance_graph, std::vector<int>& terminal, int V_upperbound) {

	graph::out_edge_iterator eit, eend;
	typedef boost::graph_traits<graph>::adjacency_iterator AdjacencyIterator;
	AdjacencyIterator ai, a_end;
	typedef graph::edge_descriptor Edge;

	int N = num_vertices(instance_graph);
	int E = num_edges(instance_graph);

	std::vector<int> CompulsoryVertex;
	std::vector<int> NonCompulsoryVertex;
	for (int i = 0; i < N; i++) {
		if (terminal[i] == 1) {
			CompulsoryVertex.insert(CompulsoryVertex.end(), i);
		}
		else {
			NonCompulsoryVertex.insert(NonCompulsoryVertex.end(), i);
		}
	}
	int CompulsoryVertex_Num = CompulsoryVertex.size();
	int NonCompulsoryVertex_Num = NonCompulsoryVertex.size();

	if (NonCompulsoryVertex_Num > V_upperbound) {
		std::cout << "EA_for_KleinNWSTP: NonCompulsoryVertex_Num > V_upperbound!" << std::endl;
		getchar();
		exit(1);
	}

	// find SMT; at least one vertex in min_binary
	double min_net_weight = 1e30;
	std::vector<int> min_included_vertices;
	graph SMT;
	// start iterating
	for (int i = 0; i < pow(2, NonCompulsoryVertex_Num); i++) {

		graph temporary_graph = copy_graph(instance_graph);

		std::vector<int> count_binary(NonCompulsoryVertex_Num);
		convert_number_to_array_of_binary(i, std::begin(count_binary), std::end(count_binary));

		std::vector<int> included_vertices = copy_vector_int(CompulsoryVertex);
		for (int j = 0; j < NonCompulsoryVertex_Num; j++) {
			if (count_binary[j] == 1) {
				included_vertices.insert(included_vertices.end(), NonCompulsoryVertex[j]);
			}
			else {
				clear_vertex(NonCompulsoryVertex[j], temporary_graph); // temporary_graph only contain included parts
			}
		}

		double net_weight = 0;
		for (int j = 0; j < included_vertices.size(); j++) {
			net_weight = net_weight + get(boost::vertex_name_t(), instance_graph, included_vertices[j]); // inside nw
		}


		if (net_weight < min_net_weight) { // graph_for_MST may be better

			int cpn_size = boost_graph_count_connected_cpn_Vsize(temporary_graph, included_vertices[0]);

			if (cpn_size == included_vertices.size()) { // graph_for_MST is connected

				graph MST = boost_graph_find_MST(temporary_graph); // MST on temporary_graph

				for (int k = 0; k < included_vertices.size(); k++) {
					boost::tie(ai, a_end) = boost::adjacent_vertices(included_vertices[k], MST);
					for (; ai != a_end; ai++) {
						if (included_vertices[k] < *ai) {
							double ec = get(boost::edge_weight_t(), MST, boost::edge(included_vertices[k], *ai, MST).first);
							net_weight = net_weight + ec; // inside ec
						}
					}
				}

				
				//std::cout << "cpn_size: " << cpn_size << std::endl;
				//std::cout << "net_weight: " << net_weight << std::endl;
				//print_vector_int(included_vertices);

				if (min_net_weight > net_weight) {
					min_net_weight = net_weight;
					SMT = copy_graph(MST);
					min_included_vertices = copy_vector_int(included_vertices);

					//boost_graph_print_all_edges(temporary_graph);
					//boost_graph_print_all_edges(MST);

				}

			}

		}
	}

	//boost_graph_print_all_edges(SMT);

	return SMT;

}