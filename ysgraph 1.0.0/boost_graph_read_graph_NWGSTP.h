#pragma once


void boost_graph_read_graph_NWGSTP(std::string file_name, graph& result_graph, graph& group_graph) {

	result_graph.clear();
	group_graph.clear();

	int V_num; // vertex number
	int P_num; // number of positive vertices
	int E_num; // edge number
	int v1;
	int v2;
	double weight;
	int group_id = 0;


	std::string line_content;
	std::ifstream myfile(file_name); // open the file
	if (myfile.is_open()) // if the file is opened successfully
	{
		while (getline(myfile, line_content)) // read file line by line
		{
			// parse the sting£ºline_content
			std::list<std::string> Parsed_content;
			std::string delimiter = " "; // the delimiter
			std::size_t pos = 0;
			std::string token;
			while ((pos = line_content.find(delimiter)) != std::string::npos) {
				// find(const string& str, size_t pos = 0) function returns the position of the first occurrence of str in the string, or npos if the string is not found.
				token = line_content.substr(0, pos);
				// The substr(size_t pos = 0, size_t n = npos) function returns a substring of the object, starting at position pos and of length npos
				Parsed_content.push_back(token); // store the subtr to the list
				line_content.erase(0, pos + delimiter.length()); // remove the front substr and the first delimiter
			}
			Parsed_content.push_back(line_content); // store the subtr to the list
			if (!Parsed_content.front().compare("Nodes")) // when it's equal, compare returns 0
			{
				Parsed_content.pop_front();
				V_num = std::atoi(Parsed_content.front().c_str()); // convert string to int
				for (int i = 0; i < V_num; i++) {
					boost::add_vertex(i, result_graph);
					boost::add_vertex(i, group_graph);
				}
			}
			else if (!Parsed_content.front().compare("Edges"))
			{
				Parsed_content.pop_front();
				E_num = std::atoi(Parsed_content.front().c_str());
			}
			else if (!Parsed_content.front().compare("E"))
			{
				Parsed_content.pop_front(); // remove E, expose v1
				v1 = std::atoi(Parsed_content.front().c_str());
				Parsed_content.pop_front(); // remove v1, expose v2
				v2 = std::atoi(Parsed_content.front().c_str());
				Parsed_content.pop_front(); // remove v2, expose weight
				weight = std::stof(Parsed_content.front().c_str());
				boost::add_edge(v1, v2, weight, result_graph); // add edge
			}
			else if (!Parsed_content.front().compare("V"))
			{
				Parsed_content.pop_front(); // remove TP, expose v1
				v1 = std::atoi(Parsed_content.front().c_str());
				Parsed_content.pop_front(); // remove v1, expose weight
				boost::put(boost::vertex_name_t(), result_graph, v1, std::stof(Parsed_content.front().c_str()));
			}
			else if (!Parsed_content.front().compare("G"))
			{
				boost::add_vertex(group_id + V_num, group_graph);
				Parsed_content.pop_front(); // remove G, expose v1

				while (Parsed_content.size() > 0) {
					v1 = std::atoi(Parsed_content.front().c_str());
					boost::add_edge(group_id + V_num, v1, 1, group_graph);
					Parsed_content.pop_front();
				}

				group_id++;
			}
		}

		myfile.close(); //close the file
	}
	else
	{
		std::cout << "Unable to open file " << file_name << std::endl 
			<< "Please check the file location or file name." << std::endl; // throw an error message
		getchar(); // keep the console window
		exit(1); // end the program
	}
}
