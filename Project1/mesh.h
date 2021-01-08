#pragma once
#include <array>
#include "mesh_info.h"
#include "node_data_implementation.h"
using namespace shinary_CFD_project;

namespace shinary_CFD_project
{
	//�ں��������ڵ���������ڵ�; �������: �ڵ��е���������, �����ģ, �в�ṹ������;
	template <class T, std::size_t size, template<class>class RESIDUAL>
	class mesh
	{
	public:
		typedef std::array<T, size> data_type;
		typedef typename T node_data_type;
		typedef typename data_type::pointer pointer;
		typedef typename data_type::reference reference;
	public:
		mesh(basic_mesh_info& mesh_info_input) :mesh_info(mesh_info_input) {};
		mesh(mesh& mesh_input) :m_nodes(mesh_input.m_nodes), mesh_info(mesh_input.mesh_info) {};
		void operator=(const mesh& mesh_input) { m_nodes = mesh_input.m_nodes; mesh_info = mesh_input.mesh_info; };
	private:
		//�ڵ�ͨ��һ���������
		data_type m_nodes;
		basic_mesh_info mesh_info;
		RESIDUAL<node_data_type> m_residual;
	public:
		data_type& getData() { return m_nodes; }
		basic_mesh_info& getMeshInfo() { return mesh_info; }
		pointer begin() { return &(m_nodes.front()); }
		pointer end() { return &(m_nodes.back()); }
		RESIDUAL<node_data_type>& getResidual() { return m_residual; };
	};
}