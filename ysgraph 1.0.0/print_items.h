#pragma once



void print_vector_int(std::vector<int>& input_vector) {

	std::cout << "print_vector_int:" << std::endl;
	for (int i = 0; i < input_vector.size(); i++) {
		std::cout << "item: |" << input_vector[i] << "|" << std::endl;
	}

}


void print_vector_double(std::vector<double>& input_vector) {

	std::cout << "print_vector_double:" << std::endl;
	for (int i = 0; i < input_vector.size(); i++) {
		std::cout << "item: |" << input_vector[i] << "|" << std::endl;
	}

}



void print_vector_string(std::vector<std::string>& input_vector) {

	std::cout << "print_vector_string:" << std::endl;
	for (int i = 0; i < input_vector.size(); i++) {
		std::cout << "item: |" << input_vector[i] << "|" << std::endl;
	}

}