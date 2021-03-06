#pragma once
#include <array>
#include "mesh_info.h"
#include "node_data_implementation.h"
using namespace shinary_CFD_project;

namespace shinary_CFD_project
{
	//内含计算域内的所有网格节点; 输入参数: 节点中的数据类型, 网格规模, 残差结构体类型;
	template <class NODE_TYPE, std::size_t size, template<class>class RESIDUAL>
	class mesh
	{
	public:
		typedef std::array<NODE_TYPE, size> mesh_data_type;
		typedef NODE_TYPE node_type;
		typedef typename node_type::node_data_type node_data_type;
		typedef typename mesh_data_type::pointer pointer;
		typedef typename mesh_data_type::reference reference;
	public:
		mesh(basic_mesh_info& mesh_info_input) :mesh_info(mesh_info_input) {};
		mesh(mesh& mesh_input) :m_nodes(mesh_input.m_nodes), mesh_info(mesh_input.mesh_info) {};
		void operator=(const mesh& mesh_input) { m_nodes = mesh_input.m_nodes; mesh_info = mesh_input.mesh_info; };
	private:
		//节点通过一个数组管理
		mesh_data_type m_nodes;
		basic_mesh_info mesh_info;
		RESIDUAL<node_data_type> m_residual;
	public:
		mesh_data_type& getData() { return m_nodes; }
		basic_mesh_info& getMeshInfo() { return mesh_info; }
		pointer begin() { return &(m_nodes.front()); }
		pointer end() { return &(m_nodes.back()); }
		RESIDUAL<node_data_type>& getResidual() { return m_residual; };
	};
}