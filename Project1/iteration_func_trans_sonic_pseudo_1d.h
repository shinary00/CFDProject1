#pragma once
#include "iteration_func.h"
#include "node_data_implementation.h"
using namespace shinary_CFD_project;

namespace shinary_CFD_project
{
	//带残差计算的迭代更新
	__residual_calculation(_Rho);
	__residual_calculation(_Temperature);
	__residual_calculation(_Velocity);
	__residual_calculation(_partial_Rho_partial_t);
	__residual_calculation(_partial_Velocity_partial_t);
	__residual_calculation(_partial_Temperature_partial_t);
	//计算边界点
	template<class Mesh>
	void _boundary_iteration(Mesh& mesh_input)
	{
		//入口点
		_Velocity_residual_calculation(*mesh_input.begin(), mesh_input.begin()->_Velocity,
			2 * (mesh_input.begin() + 1)->_Velocity
			- (mesh_input.begin() + 2)->_Velocity);
		mesh_input.begin()->getResidual().getResidualData()._Rho_residual = 0;
		mesh_input.begin()->getResidual().getResidualData()._Temperature_residual = 0;
		mesh_input.begin()->getResidual().getResidualData()._partial_Rho_partial_t_residual = 0;
		mesh_input.begin()->getResidual().getResidualData()._partial_Velocity_partial_t_residual = 0;
		mesh_input.begin()->getResidual().getResidualData()._partial_Temperature_partial_t_residual = 0;
		_delta_t_calculation(*(mesh_input.begin()));
		//出口点
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

	//残差初始化
	template<class Node>
	void _residual_reset(Node& node)
	{
		node.getResidual().getResidualData()._Rho_residual = 1;
		node.getResidual().getResidualData()._Temperature_residual = 1;
		node.getResidual().getResidualData()._Velocity_residual = 1;
		node.getResidual().getResidualData()._partial_Rho_partial_t_residual = 1;
		node.getResidual().getResidualData()._partial_Velocity_partial_t_residual = 1;
		node.getResidual().getResidualData()._partial_Temperature_partial_t_residual = 1;
	};

	//数据初始化
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
				node->_L  = i * iteration_func_base<Mesh>::_mesh.getMeshInfo().delta_x;
				node->_Area = 1 + 2.2 * (node->_L - 1.5) * (node->_L - 1.5);
				node->_Rho = 1 - 0.314 * node->_L;
				node->_Temperature = 1 - 0.2314 * node->_L;
				node->_Velocity = (0.1 + 1.09 * node->_L) * sqrt(node->_Temperature);
				node->_partial_Rho_partial_t = 0;
				node->_partial_Velocity_partial_t = 0;
				node->_partial_Temperature_partial_t = 0;
				_delta_t_calculation(*node);
				_residual_reset(*node);

				i++;
			}
		}
	};

	//残差整理
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
	//迭代函数
	template<class Mesh>
	class trans_sonic_pseudo_1d :public iteration_func_base<Mesh>
	{
	public:
		trans_sonic_pseudo_1d(Mesh& mesh_input) :iteration_func_base<Mesh>(mesh_input) {};
	public:
		void execute()override
		{
			//备份原值以便计算校正值
			Mesh mesh_backup(iteration_func_base<Mesh>::_mesh);
			//找到delta_t的最小值
			double min_delta_t = mesh_backup.begin()->_delta_t;
			for (auto node = mesh_backup.begin() + 1; node != mesh_backup.end(); node++)
			{
				if (min_delta_t > node->_delta_t)min_delta_t = node->_delta_t;
			}
			//计算预估值，结果储存在备份值中,不改变原值
			for (auto node = mesh_backup.begin() + 1; node != mesh_backup.end(); node++)
			{
				auto next_node = node; next_node++;
				node->_partial_Rho_partial_t =
					(-node->_Velocity * (next_node->_Rho - node->_Rho)
						- node->_Rho * (next_node->_Velocity - node->_Velocity)
						- node->_Rho * node->_Velocity * log(next_node->_Area / node->_Area))
					/ mesh_backup.getMeshInfo().delta_x;

				node->_partial_Velocity_partial_t =
					(-node->_Velocity * (next_node->_Velocity - node->_Velocity)
						- (1 / mesh_backup.getMeshInfo().gamma) *
						((next_node->_Temperature - node->_Temperature)
							+ (node->_Temperature / node->_Rho) *
							(next_node->_Rho - node->_Rho))) / mesh_backup.getMeshInfo().delta_x;

				node->_partial_Temperature_partial_t =
					(-node->_Velocity * (next_node->_Temperature - node->_Temperature)
						- (mesh_backup.getMeshInfo().gamma - 1) * node->_Temperature *
						((next_node->_Velocity - node->_Velocity)
							+ node->_Velocity * log(next_node->_Area / node->_Area))) / mesh_backup.getMeshInfo().delta_x;

				node->_Rho = node->_Rho + min_delta_t * node->_partial_Rho_partial_t;
				node->_Velocity = node->_Velocity + min_delta_t * node->_partial_Velocity_partial_t;
				node->_Temperature = node->_Temperature + min_delta_t * node->_partial_Temperature_partial_t;
				_delta_t_calculation(*node);
			}
			_boundary_iteration(mesh_backup);
			//校正步，结果储存在原值中
			auto node_backup = mesh_backup.begin() + 1;
			auto node = iteration_func_base<Mesh>::_mesh.begin() + 1;
			for (; node != iteration_func_base<Mesh>::_mesh.end(); node++, node_backup++)
			{
				auto ahead_node_backup = node_backup; ahead_node_backup--;

				_partial_Rho_partial_t_residual_calculation(*node, node->_partial_Rho_partial_t,
					0.5 * (node_backup->_partial_Rho_partial_t
						+ ((-node_backup->_Velocity * (node_backup->_Rho - ahead_node_backup->_Rho)
							- node_backup->_Rho * (node_backup->_Velocity - ahead_node_backup->_Velocity)
							- node_backup->_Rho * node_backup->_Velocity * log(node_backup->_Area / ahead_node_backup->_Area)))
						/ mesh_backup.getMeshInfo().delta_x));

				_partial_Velocity_partial_t_residual_calculation(*node, node->_partial_Velocity_partial_t,
					0.5 * (node_backup->_partial_Velocity_partial_t
						+ ((-node_backup->_Velocity * (node_backup->_Velocity - ahead_node_backup->_Velocity)
							- (1 / mesh_backup.getMeshInfo().gamma) *
							((node_backup->_Temperature - ahead_node_backup->_Temperature)
								+ (node_backup->_Temperature / ahead_node_backup->_Rho) *
								(node_backup->_Rho - ahead_node_backup->_Rho)))) / mesh_backup.getMeshInfo().delta_x));

				_partial_Temperature_partial_t_residual_calculation(*node, node->_partial_Temperature_partial_t,
					0.5 * (node_backup->_partial_Temperature_partial_t
						+ ((-node_backup->_Velocity * (node_backup->_Temperature - ahead_node_backup->_Temperature)
							- (mesh_backup.getMeshInfo().gamma - 1) * node_backup->_Temperature *
							((node_backup->_Velocity - ahead_node_backup->_Velocity)
								+ node_backup->_Velocity * log(node_backup->_Area / ahead_node_backup->_Area)))) / mesh_backup.getMeshInfo().delta_x));

				_Rho_residual_calculation(*node, node->_Rho,
					node->_Rho + min_delta_t * node->_partial_Rho_partial_t);
				_Velocity_residual_calculation(*node, node->_Velocity,
					node->_Velocity + min_delta_t * node->_partial_Velocity_partial_t);
				_Temperature_residual_calculation(*node, node->_Temperature,
					node->_Temperature + min_delta_t * node->_partial_Temperature_partial_t);
				_delta_t_calculation(*node);
			}
			_boundary_iteration(iteration_func_base<Mesh>::_mesh);
			//整理残差
			iteration_func_base<Mesh>::_mesh.getResidual() = _find_max_residual_(iteration_func_base<Mesh>::_mesh);
		}
	};


}