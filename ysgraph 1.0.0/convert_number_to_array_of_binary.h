#pragma once



template<class output_iterator>
void convert_number_to_array_of_binary(const unsigned number,
	output_iterator first, output_iterator last)
{
	const unsigned number_bits = CHAR_BIT * sizeof(int);
	//extract bits one at a time
	for (unsigned i = 0; i < number_bits && first != last; ++i) {
		const unsigned shift_amount = number_bits - i - 1;
		const unsigned this_bit = (number >> i) & 1;
		*first = this_bit;
		++first;
	}
	//pad the rest with zeros
	while (first != last) {
		*first = 0;
		++first;
	}
}


/*Example:

for (int i = 0; i < pow(2, NonCompulsoryVertex_Num); i++) {

		graph temporary_graph = copy_graph(instance_graph);

		std::vector<int> count_binary(NonCompulsoryVertex_Num);
		convert_number_to_array_of_digits(i, std::begin(count_binary), std::end(count_binary));

		std::vector<int> included_vertices = copy_vector_int(CompulsoryVertex);
		for (int j = 0; j < NonCompulsoryVertex_Num; j++) {
			if (count_binary[j] == 1) {
				included_vertices.insert(included_vertices.end(), NonCompulsoryVertex[j]);
			}
			else {
				clear_vertex(NonCompulsoryVertex[j], temporary_graph); // temporary_graph only contain included parts
			}
		}
}
			*/