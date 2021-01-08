#pragma once
#include <cmath>

namespace shinary_CFD_project
{
	//包含科朗数、空间步长等基本常量
	class basic_mesh_info
	{
	public:
		double nodes_number = 31;
		double total_length = 3.0;
		double delta_x = total_length / (nodes_number-1);

		double gamma = 1.4;
		double Courant_Number = 1.1;
	}static mesh_info;
}