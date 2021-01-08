#pragma once
#include "iteration_func.h"
#include "node_data_implementation.h"
using namespace shinary_CFD_project;

namespace shinary_CFD_project
{
	//���в����ĵ�������
	__residual_calculation(_Rho);
	__residual_calculation(_Temperature);
	__residual_calculation(_Velocity);
	__residual_calculation(_partial_Rho_partial_t);
	__residual_calculation(_partial_Velocity_partial_t);
	__residual_calculation(_partial_Temperature_partial_t);
	//����߽��
	template<class Mesh>
	void _boundary_iteration(Mesh& mesh_input)
	{
		//��ڵ�
		_Velocity_residual_calculation(*mesh_input.begin(), mesh_input.begin()->_Velocity,
			2 * (mesh_input.begin() + 1)->_Velocity
			- (mesh_input.begin() + 2)->_Velocity);
		mesh_input.begin()->getResidual().getResidualData()._Rho_residual = 0;
		mesh_input.begin()->getResidual().getResidualData()._Temperature_residual = 0;
		mesh_input.begin()->getResidual().getResidualData()._partial_Rho_partial_t_residual = 0;
		mesh_input.begin()->getResidual().getResidualData()._partial_Velocity_partial_t_residual = 0;
		mesh_input.begin()->getResidual().getResidualData()._partial_Temperature_partial_t_residual = 0;
		_delta_t_calculation(*(mesh_input.begin()));
		//���ڵ�
		_Velocity_residual_calculation(*mesh_input.end(), mesh_input.end()->_Velocity,
			2 * (mesh_input.end() - 1)->_Velocity
			- (mesh_input.end() - 2)->_Velocity);
		_Rho_residual_calculation(*mesh_input.end(), mesh_input.end()->_Rho,
			2 * (mesh_input.end() - 1)->_Rho
			- (mesh_input.end() - 2)->_Rho);
		_Temperature_residual_calculation(*mesh_input.end(), mesh_input.end()->_Temperature,
			2 * (mesh_input.end() - 1)->_Temperature
			- (mesh_input.end() - 2)->_Temperature);
		mesh_input.end()->getResidual().getResidualData()._partial_Rho_partial_t_residual = 0;
		mesh_input.end()->getResidual().getResidualData()._partial_Velocity_partial_t_residual = 0;
		mesh_input.end()->getResidual().getResidualData()._partial_Temperature_partial_t_residual = 0;
		_delta_t_calculation(*(mesh_input.end()));
	};

	//�в��ʼ��
	template<class Node>
	void _residual_reset(Node& node)
	{
		node.getResidual()._Rho = 1;
		node.getResidual()._Temperature = 1;
		node.getResidual()._Velocity = 1;
		node.getResidual()._partial_Rho_partial_t = 1;
		node.getResidual()._partial_Velocity_partial_t = 1;
		node.getResidual()._partial_Temperature_partial_t = 1;
	};

	//���ݳ�ʼ��
	template<class Mesh>
	class initialization :public iteration_func_base<Mesh>
	{
	public:
		initialization(Mesh& mesh_input) :iteration_func_base<Mesh>(mesh_input) {};
	public:
		void execute()override
		{
			int i = 0;
			for (auto node = iteration_func_base<Mesh>::_mesh.begin(); node <= iteration_func_base<Mesh>::_mesh.end(); node++)
			{
				node->getData().m_data_common._L = i * iteration_func_base<Mesh>::_mesh.getMeshInfo().delta_x;
				node->getData().m_data_common._Area = 1 + 2.2 * (node->_L - 1.5) * (node->_L - 1.5);

				node->getData().m_data_need_residual._Rho = 1 - 0.314 * node->_L;
				node->getData().m_data_need_residual._Temperature = 1 - 0.2314 * node->_L;
				node->getData().m_data_need_residual._Velocity = (0.1 + 1.09 * node->_L) * sqrt(node->_Temperature);
				node->getData().m_data_need_residual._partial_Rho_partial_t = 0;
				node->getData().m_data_need_residual._partial_Velocity_partial_t = 0;
				node->getData().m_data_need_residual._partial_Temperature_partial_t = 0;

				_delta_t_calculation(*node);
				_residual_reset(*node);

				i++;
			}
		}
	};

	//�в�����
	/*template<class Mesh>
	_data_need_residual<typename Mesh::value_type::node_data_type>
		_find_max_residual_(Mesh mesh_input)
	{
		residual<typename Mesh::value_type::node_data_type> max_residual;
		max_residual = mesh_input.begin()->getResidual();
		for (auto element : mesh_input.getData())
		{
			max_residual.getResidualData()._partial_Rho_partial_t_residual = max_residual.getResidualData()._partial_Rho_partial_t_residual < element.getResidual().getResidualData()._partial_Rho_partial_t_residual ? element.getResidual().getResidualData()._partial_Rho_partial_t_residual: max_residual.getResidualData()._partial_Rho_partial_t_residual;
			max_residual.getResidualData()._partial_Velocity_partial_t_residual = max_residual.getResidualData()._partial_Velocity_partial_t_residual < element.getResidual().getResidualData()._partial_Velocity_partial_t_residual ? element.getResidual().getResidualData()._partial_Velocity_partial_t_residual: max_residual.getResidualData()._partial_Rho_partial_t_residual;
			max_residual.getResidualData()._partial_Temperature_partial_t_residual = max_residual.getResidualData()._partial_Temperature_partial_t_residual < element.getResidual().getResidualData()._partial_Temperature_partial_t_residual ? element.getResidual().getResidualData()._partial_Temperature_partial_t_residual: max_residual.getResidualData()._partial_Temperature_partial_t_residual;
			max_residual.getResidualData()._Rho_residual = max_residual.getResidualData()._Rho_residual < element.getResidual().getResidualData()._Rho_residual ? element.getResidual().getResidualData()._Rho_residual: max_residual.getResidualData()._Rho_residual;
			max_residual.getResidualData()._Temperature_residual = max_residual.getResidualData()._Temperature_residual < element.getResidual().getResidualData()._Temperature_residual ? element.getResidual().getResidualData()._Temperature_residual: max_residual.getResidualData()._Temperature_residual;
			max_residual.getResidualData()._Velocity_residual = max_residual.getResidualData()._Velocity_residual < element.getResidual().getResidualData()._Velocity_residual ? element.getResidual().getResidualData()._Velocity_residual: max_residual.getResidualData()._Velocity_residual;
		}
		return max_residual;
	}*/
	//��������
	template<class Mesh>
	class trans_sonic_pseudo_1d :public iteration_func_base<Mesh>
	{
	public:
		trans_sonic_pseudo_1d(Mesh& mesh_input) :iteration_func_base<Mesh>(mesh_input) {};
	public:
		void execute()override
		{
			//����ԭֵ�Ա����У��ֵ
			Mesh mesh_backup(iteration_func_base<Mesh>::_mesh);

			//�ҵ�delta_t����Сֵ
			double min_delta_t = mesh_backup.begin()->getData().data_common._delta_t;
			for (auto node = mesh_backup.begin() + 1; node != mesh_backup.end(); node++)
			{
				if (min_delta_t > node->getData().data_common._delta_t)min_delta_t = node->getData().data_common._delta_t;
			}

			//����Ԥ��ֵ����������ڱ���ֵ��,���ı�ԭֵ
			for (auto node = mesh_backup.begin() + 1; node != mesh_backup.end(); node++)
			{
				auto next_node = node; next_node++;
				node->getData().data_need_residual._partial_Rho_partial_t =
					(-node->getData().data_need_residual._Velocity * (next_node->getData().data_need_residual._Rho - node->getData().data_need_residual._Rho)
						- node->getData().data_need_residual._Rho * (next_node->getData().data_need_residual._Velocity - node->getData().data_need_residual._Velocity)
						- node->getData().data_need_residual._Rho * node->getData().data_need_residual._Velocity * log(next_node->getData().data_common._Area / node->getData().data_common._Area))
					/ mesh_backup.getMeshInfo().delta_x;

				node->getData().data_need_residual._partial_Velocity_partial_t =
					(-node->getData().data_need_residual._Velocity * (next_node->getData().data_need_residual._Velocity - node->getData().data_need_residual._Velocity)
						- (1 / mesh_backup.getMeshInfo().gamma) *
						((next_node->getData().data_need_residual._Temperature - node->getData().data_need_residual._Temperature)
							+ (node->getData().data_need_residual._Temperature / node->getData().data_need_residual._Rho) *
							(next_node->getData().data_need_residual._Rho - node->getData().data_need_residual._Rho))) / mesh_backup.getMeshInfo().delta_x;

				node->_partial_Temperature_partial_t =
					(-node->getData().data_need_residual._Velocity * (next_node->getData().data_need_residual._Temperature - node->getData().data_need_residual._Temperature)
						- (mesh_backup.getMeshInfo().gamma - 1) * node->getData().data_need_residual._Temperature *
						((next_node->getData().data_need_residual._Velocity - node->getData().data_need_residual._Velocity)
							+ node->getData().data_need_residual._Velocity * log(next_node->getData().data_common._Area / node->getData().data_common._Area))) / mesh_backup.getMeshInfo().delta_x;

				node->getData().data_need_residual._Rho = node->getData().data_need_residual._Rho + min_delta_t * node->getData().data_need_residual._partial_Rho_partial_t;
				node->getData().data_need_residual._Velocity = node->getData().data_need_residual._Velocity + min_delta_t * node->getData().data_need_residual._partial_Velocity_partial_t;
				node->getData().data_need_residual._Temperature = node->getData().data_need_residual._Temperature + min_delta_t * node->_partial_Temperature_partial_t;
				_delta_t_calculation(*node);
			}
			_boundary_iteration(mesh_backup);

			////У���������������ԭֵ��
			//auto node_backup = mesh_backup.begin() + 1;
			//auto node = iteration_func_base<Mesh>::_mesh.begin() + 1;
			//for (; node != iteration_func_base<Mesh>::_mesh.end(); node++, node_backup++)
			//{
			//	auto ahead_node_backup = node_backup; ahead_node_backup--;

			//	_partial_Rho_partial_t_residual_calculation(*node, node->getData().data_need_residual._partial_Rho_partial_t,
			//		0.5 * (node_backup->getData().data_need_residual._partial_Rho_partial_t
			//			+ ((-node_backup->_Velocity * (node_backup->getData().data_need_residual._Rho - ahead_node_backup->getData().data_need_residual._Rho)
			//				- node_backup->getData().data_need_residual._Rho * (node_backup->_Velocity - ahead_node_backup->_Velocity)
			//				- node_backup->getData().data_need_residual._Rho * node_backup->_Velocity * log(node_backup->getData().data_common._Area / ahead_node_backup->getData().data_common._Area)))
			//			/ mesh_backup.getMeshInfo().delta_x));

			//	_partial_Velocity_partial_t_residual_calculation(*node, node->getData().data_need_residual._partial_Velocity_partial_t,
			//		0.5 * (node_backup->getData().data_need_residual._partial_Velocity_partial_t
			//			+ ((-node_backup->_Velocity * (node_backup->_Velocity - ahead_node_backup->_Velocity)
			//				- (1 / mesh_backup.getMeshInfo().gamma) *
			//				((node_backup->getData().data_need_residual._Temperature - ahead_node_backup->getData().data_need_residual._Temperature)
			//					+ (node_backup->getData().data_need_residual._Temperature / ahead_node_backup->getData().data_need_residual._Rho) *
			//					(node_backup->getData().data_need_residual._Rho - ahead_node_backup->getData().data_need_residual._Rho)))) / mesh_backup.getMeshInfo().delta_x));

			//	_partial_Temperature_partial_t_residual_calculation(*node, node->_partial_Temperature_partial_t,
			//		0.5 * (node_backup->_partial_Temperature_partial_t
			//			+ ((-node_backup->_Velocity * (node_backup->getData().data_need_residual._Temperature - ahead_node_backup->getData().data_need_residual._Temperature)
			//				- (mesh_backup.getMeshInfo().gamma - 1) * node_backup->getData().data_need_residual._Temperature *
			//				((node_backup->_Velocity - ahead_node_backup->_Velocity)
			//					+ node_backup->_Velocity * log(node_backup->getData().data_common._Area / ahead_node_backup->getData().data_common._Area)))) / mesh_backup.getMeshInfo().delta_x));

			//	_Rho_residual_calculation(*node, node->getData().data_need_residual._Rho,
			//		node->getData().data_need_residual._Rho + min_delta_t * node->getData().data_need_residual._partial_Rho_partial_t);
			//	_Velocity_residual_calculation(*node, node->_Velocity,
			//		node->_Velocity + min_delta_t * node->getData().data_need_residual._partial_Velocity_partial_t);
			//	_Temperature_residual_calculation(*node, node->getData().data_need_residual._Temperature,
			//		node->getData().data_need_residual._Temperature + min_delta_t * node->_partial_Temperature_partial_t);
			//	_delta_t_calculation(*node);
			//}
			//_boundary_iteration(iteration_func_base<Mesh>::_mesh);

			//����в�
			//iteration_func_base<Mesh>::_mesh.getResidual() = _find_max_residual_(iteration_func_base<Mesh>::_mesh);
		}
	};


}