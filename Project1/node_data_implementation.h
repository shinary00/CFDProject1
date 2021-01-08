#pragma once
#include "node_data.h"
using namespace shinary_CFD_project;

namespace shinary_CFD_project
{
	//不计算残差的参数类实现
	template<class T>
	class _data_common :public _data_common_base<_data_common<T>, T>
	{
		template<class Mesh>
		friend class iteration_func_base;
	private:
		T _L = 0;
		T _delta_t = 0;
		T _Area = 0;
	public:
		typedef _data_common<T> SELF;
		typedef T node_data_type;
	public:
		std::ostream& operator<<(std::ostream& out) override
		{
			out << _L << ' ';
			out << _delta_t << ' ';
			out << _Area << ' ';
			return out;
		};
		void operator=(const SELF& residual_input) override
		{
			_L = residual_input._L;
			_delta_t = residual_input._delta_t;
			_Area = residual_input._Area;
		};
	};
	//需要计算残差的参数类实现
	template<class T>
	class _data_need_residual :public _data_need_residual_base<_data_need_residual<T>, T>
	{
		template<class Mesh>
		friend class iteration_func_base;
	private:
		T _Rho = 0;
		T _Temperature = 0;
		T _Velocity = 0;

		T _partial_Rho_partial_t = 0;
		T _partial_Velocity_partial_t = 0;
		T _partial_Temperature_partial_t = 0;
	public:
		typedef _data_need_residual<T> SELF;
		typedef T node_data_type;
	public:
		bool operator>(const node_data_type& compare)const override
		{
			return (_Rho > compare) &&
				(_Temperature > compare) &&
				(_Velocity > compare) &&
				(_partial_Rho_partial_t > compare) &&
				(_partial_Velocity_partial_t > compare) &&
				(_partial_Temperature_partial_t > compare);
		};
		std::ostream& operator<<(std::ostream& out) override
		{
			out << _Rho << ' ';
			out << _Temperature << ' ';
			out << _Velocity << ' ';
			out << _partial_Rho_partial_t << ' ';
			out << _partial_Velocity_partial_t << ' ';
			out << _partial_Temperature_partial_t << ' ';
			return out;
		};
		void operator=(const SELF& residual_input) override
		{
			_Rho = residual_input._Rho;
			_Temperature = residual_input._Temperature;
			_Velocity = residual_input._Velocity;
			_partial_Rho_partial_t = residual_input._partial_Rho_partial_t;
			_partial_Velocity_partial_t = residual_input._partial_Velocity_partial_t;
			_partial_Temperature_partial_t = residual_input._partial_Temperature_partial_t;
		};
	};
	//节点实现
	template<class T>
	class node_data_set1 :public _node_base<_data_common<T>, _data_need_residual<T>>
	{
	public:
		typedef node_data_set1<T> SELF;
		typedef _node_base<_data_common<T>, _data_need_residual<T>> base_type;
		typedef typename base_type::node_data_set node_data_set;
	public:
		friend std::ostream& operator<<(std::ostream& out, SELF& obj) { obj << out; return out; }
	};
}