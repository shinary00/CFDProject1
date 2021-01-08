#include "iteration_algorithm.h"
#include "mesh.h"
#include "iteration_func_trans_sonic_pseudo_1d.h"
#include "post_processing.h"

using namespace shinary_CFD_project;

namespace shinary_CFD_project
{
#ifndef CMNFTS
#define CMNFTS
	template<class Mesh>//MM_Pushing_Algorithm创建接口
	inline MM_Pushing_Algorithm<Mesh> MM_Pushing_Algorithm_Setup(
		Mesh& mesh, 
		iteration_func_base<Mesh>& func0, 
		iteration_func_base<Mesh>& func1, 
		typename Mesh::node_data_type residual)
	{
		return MM_Pushing_Algorithm<Mesh>(mesh, func0, func1,residual);
	}

	template<class Mesh>//trans_sonic_pseudo_1d接口
	inline trans_sonic_pseudo_1d<Mesh> trans_sonic_pseudo_1d_Setup(Mesh& mesh_input)
	{
		return trans_sonic_pseudo_1d<Mesh>(mesh_input);
	}

	template<class Mesh>//initialization接口
	inline initialization<Mesh> initialization_Setup(Mesh& mesh_input)
	{
		return initialization<Mesh>(mesh_input);
	}

	template<class Mesh>//initialization接口
	inline post_processing<Mesh> post_progressing_Setup(Mesh& mesh_input)
	{
		return post_processing<Mesh>(mesh_input);
	}
#endif // !CMNFTS
}