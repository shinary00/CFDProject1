#pragma once
#include <cmath>

namespace shinary_CFD_project
{
#ifndef BASIC_MESH_INFO
#define BASIC_MESH_INFO
	struct basic_mesh_info
	{
	public:
		double nodes_number = 31;
		double total_length = 3.0;
		double delta_x = total_length / (nodes_number-1);

		double gamma = 1.4;
		double Courant_Number = 1.1;
	} static mesh_info;
#endif // !MESH_INFO
}