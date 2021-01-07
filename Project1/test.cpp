#include "cmnfts.h"
#include <iostream>
#include "post_processing.h"
using namespace shinary_CFD_project;



int main()
{
	//mesh<node_data_set1<double>, 31> test_mesh1(mesh_info);

	//auto post_process = post_progressing_Setup(test_mesh1);

	//auto initial_func = initialization_Setup(test_mesh1);
	//auto iteration_func = trans_sonic_pseudo_1d_Setup(test_mesh1);
	//auto iteration_algorithm = MM_Pushing_Algorithm_Setup(test_mesh1, initial_func, iteration_func, 1e-6);

	//iteration_algorithm.initialization();
	//while (test_mesh1.getResidual() > iteration_algorithm.getPrecision())
	//{
	//	iteration_algorithm.executeIteration();
	//	post_process.dataOutput();
	//}
	//int iterations = post_process.getIterationNumber();
	//post_process.~post_processing();
	//std::cout << "Iterations : " << iterations << std::endl;
	node_data<_data_common<int>, _data_need_residual<int>> node_data_temp1;
	node_data<_data_common<int>, _data_need_residual<int>> node_data_temp2;
	//node_data_temp1 > 1;
}