#pragma once
#include "mesh.h"
#include <cmath>
using namespace shinary_CFD_project;


namespace shinary_CFD_project
{
#ifndef ITERATION_FUNC
#define ITERATION_FUNC

	/*带残差计算的迭代更新函数构造宏，
生成的函数名：[传入参数+_residual_calculation]；需要<cmath>；
传入参数：操作节点，需要计算残差的值，该值的新的计算结果*/
#define __residual_calculation(__PROPERTY__) \
template<class Node>\
inline void __PROPERTY__##_residual_calculation(\
	Node& node_input,\
	typename Node::node_data_type& data_input,\
	typename Node::node_data_type data_calculated)\
{\
	##__PROPERTY__##_map(node_input, data_input) = abs(data_input - data_calculated);\
	data_input = data_calculated;\
}\
template<class Node>\
inline typename Node::node_data_type& ##__PROPERTY__##_map(\
	Node& node_input,\
	typename Node::node_data_type& data_input)\
{\
	return &(data_input) == &(node_input.##__PROPERTY__##) ? (node_input.getResidual().getResidualData().##__PROPERTY__##_residual) : node_input.##__PROPERTY__##;\
}

	//迭代函数基类
	template<class Mesh>
	class iteration_func_base
	{
	public:
		iteration_func_base(Mesh& mesh_input): _mesh(mesh_input){};
		virtual ~iteration_func_base() {};
		virtual void execute() {};
	protected:
		Mesh& _mesh;
	};

	//计算delta_t
	template<class node>
	inline void _delta_t_calculation(node& node_input){__delta_t_calculation(node_input, mesh_info);}

	template<class node, class basic_mesh_info>
	inline void __delta_t_calculation(node& node_input, basic_mesh_info& info) { node_input._delta_t = info.Courant_Number * info.delta_x / (node_input._Velocity + sqrt(node_input._Temperature)); }
#endif // !ITERATION_FUNC
}