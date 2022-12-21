#pragma once

#include "Common.h"

class deep_field_search{
public:
	deep_field_search() {};
	~deep_field_search() {};
	
	int search(vector<vector<int>>& input) {
		int maximum_island = 0;
		for (int i = 0; i < input.size(); i++) {
			for (int j = 0; j < input[0].size(); j++)
			{
				if (input[i][j] == 1) {
					maximum_island = max(single_search(input, i, j), maximum_island);
				}
			}
		}
		return maximum_island;
	}

	int single_search(vector<vector<int>>& input, int i, int j) {
		if (i >= input.size() || i < 0 || j >= input[0].size() || j < 0 || input[i][j] == 0)
		{
			return 0;
		}
		else
		{
			input[i][j] = 0;
			return 1 + single_search(input, i + 1, j) + single_search(input, i, j + 1) + single_search(input, i, j - 1) + single_search(input, i - 1, j);
		}
	}
};