#pragma once
#include <array>
#include "mesh_info.h"
#include "node_data_implementation.h"
using namespace shinary_CFD_project;

namespace shinary_CFD_project
{
#ifndef MESH
#define MESH
	template <class T, std::size_t size>//内含计算域内的所有网格节点；
	class mesh
	{
	public:
		typedef std::array<T, size> data_type;
		typedef typename data_type::value_type value_type;
		typedef typename data_type::pointer pointer;
		typedef typename data_type::reference reference;
		typedef typename value_type::node_data_type node_data_type;
	public:
		mesh(basic_mesh_info& mesh_info_input) :mesh_info(mesh_info_input) {};
		mesh(mesh& mesh_input) :m_nodes(mesh_input.m_nodes), mesh_info(mesh_input.mesh_info){};
		void operator=(const mesh& mesh_input) { m_nodes = mesh_input.m_nodes; mesh_info = mesh_input.mesh_info; };
		
	private:
		//节点通过一个数组管理
		data_type m_nodes;
		basic_mesh_info& mesh_info;
		//residual<node_data_type> m_residual;
	public:
		data_type& getData() { return m_nodes; }
		basic_mesh_info& getMeshInfo() { return mesh_info; }
		pointer begin() { return &(m_nodes.front()); }
		pointer end() { return &(m_nodes.back()); }
		//residual<node_data_type>& getResidual() { return m_residual; };
	};
#endif // !MESH
}