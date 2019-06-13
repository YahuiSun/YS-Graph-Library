#pragma once


#include <boost/graph/adjacency_list.hpp>

#pragma region 
// define an adjacency list with edge weights
typedef boost::property<boost::edge_weight_t, double> EdgeWeightProperty; // define edge weight property
typedef boost::property<boost::vertex_name_t, double> VertexWeightProperty; // define node weight property; note that: vertex_index_t is not mutable
typedef boost::adjacency_list<boost::setS, boost::vecS,
	boost::undirectedS, VertexWeightProperty, EdgeWeightProperty> graph; // define all the graph properties
typedef boost::graph_traits<graph>::adjacency_iterator AdjacencyIterator;
#pragma endregion define graph property 2018_1_6_16:31:58


#pragma region
graph copy_graph(graph& input_graph) {

	return input_graph; // this input_graph is just a copy of the outside input_graph

}
#pragma endregion copy_graph 2018_5_9_17:39:01
