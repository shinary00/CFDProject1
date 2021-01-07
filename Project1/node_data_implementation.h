#pragma once
#include "node_data.h"
using namespace shinary_CFD_project;

namespace shinary_CFD_project
{
	//不计算残差的参数类实现
	template<class T>
	class _data_common :public _data_common_base<_data_common<T>, T>
	{
		friend class _data_common<T>;
	private:
		T _L = 0;
		T _delta_t = 0;
		T _Area = 0;
	public:
		typedef _data_common<T> SELF;
		typedef T data_type;
	public:
		bool operator>(const data_type& compare)const override
		{
			return (_L > compare) &&
				(_delta_t > compare) &&
				(_Area > compare);
		};
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
		friend class _data_need_residual<T>;
	private:
		T _Rho = 0;
		T _Temperature = 0;
		T _Velocity = 0;

		T _partial_Rho_partial_t = 0;
		T _partial_Velocity_partial_t = 0;
		T _partial_Temperature_partial_t = 0;
	public:
		typedef _data_need_residual<T> SELF;
		typedef T data_type;
	public:
		bool operator>(const data_type& compare)const override
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
	class node_data_set1 :public _node_data_base<_data_common<T>, _data_need_residual<T>>
	{
	public:
		typedef node_data_set1<T> SELF;
		typedef T data_type;
		typedef _node_data_base<_data_common<T>, _data_need_residual<T>> base_type;
		typedef typename base_type::node_data_set_type node_data_set_type;
	public:
		//node_data_set1() :base_type() {};
	public:
		node_data_set_type& getData()override { return base_type::getData(); }
		node_data_set_type getData()const override { return base_type::getData(); }
		/*bool operator>(const data_type& compare)const override
		{
			return (*(base_type::getData().m_data_common) > compare) && (*(base_type::getData().m_data_need_residual) > compare);
		}*/
		virtual std::ostream& operator<<(std::ostream& out) override { return (*(getData().m_data_need_residual)).operator<<((*(getData().m_data_common)).operator<<(out)); };
		friend std::ostream& operator<<(std::ostream& out, SELF& obj) { obj << out; return out; }
		void operator=(const base_type& node_data_input)override
		{
			*(getData().m_data_common)= *(node_data_input.getData().m_data_common);
			*(getData().m_data_need_residual) = *(node_data_input.getData().m_data_need_residual);
		}
	};
	////残差类实现
	//template<class T>
	//class residual :public _data_need_residual<T>
	//{
	//public:
	//	typedef _residual_base<T> base_type;
	//	typedef _residual_data<T> residual_data_type;
	//public:
	//	//Ctor
	//	//residual() :_residual_base<T>() {};
	//	residual_data_type& getResidualData() { return base_type::getResidualData(); }
	//public:
	//	void operator=(const base_type& residual_input)
	//	{
	//		getResidualData()._Rho_residual = residual_input.getResidualData()._Rho_residual;
	//		getResidualData()._Temperature_residual = residual_input.getResidualData()._Temperature_residual;
	//		getResidualData()._Velocity_residual = residual_input.getResidualData()._Velocity_residual;
	//		getResidualData()._partial_Rho_partial_t_residual = residual_input.getResidualData()._partial_Rho_partial_t_residual;
	//		getResidualData()._partial_Velocity_partial_t_residual = residual_input.getResidualData()._partial_Velocity_partial_t_residual;
	//		getResidualData()._partial_Temperature_partial_t_residual = residual_input.getResidualData()._partial_Temperature_partial_t_residual;
	//	}
	//	bool operator<(const T& compare)
	//	{
	//		return (getResidualData()._Rho_residual < compare) &&
	//			(getResidualData()._Temperature_residual < compare) &&
	//			(getResidualData()._Velocity_residual < compare) &&
	//			(getResidualData()._partial_Rho_partial_t_residual < compare) &&
	//			(getResidualData()._partial_Velocity_partial_t_residual < compare) &&
	//			(getResidualData()._partial_Temperature_partial_t_residual < compare);
	//	}
	//	bool operator>(const T& compare) {
	//		return !(*this < compare);
	//	}
	//	friend std::ostream& operator<<(std::ostream& out, const base_type& obj)
	//	{
	//		out << obj.getResidualData()._Rho_residual << ' ';
	//		out << obj.getResidualData()._Temperature_residual << ' ';
	//		out << obj.getResidualData()._Velocity_residual << ' ';
	//		out << obj.getResidualData()._partial_Rho_partial_t_residual << ' ';
	//		out << obj.getResidualData()._partial_Velocity_partial_t_residual << ' ';
	//		out << obj.getResidualData()._partial_Temperature_partial_t_residual << ' ';

	//		return out;
	//	}
	//};

	//网格节点的实现;项目1的网格节点属性，包含距离、面积、压力、焓、温度、密度等；
	/*template <class T>
	struct node_data_set1 :public _node_data_base<T>
	{
	public:
		typedef typename _node_data_base<T>::node_data_type node_data_type;
	public:
		T _L = 0;
		T _Area = 0;
		T _Rho = 0;
		T _Temperature = 0;
		T _Velocity = 0;
		T _delta_t = 0;

		T _partial_Rho_partial_t = 0;
		T _partial_Velocity_partial_t = 0;
		T _partial_Temperature_partial_t = 0;

		residual<T> m_residual;
	public:
		residual<T>& getResidual() { return m_residual; };
		residual<T> getResidual()const { return m_residual; }
	public:
		friend std::ostream& operator<<(std::ostream& out, const node_data_set1<T>& node_input)
		{
			out << node_input._L << ' ';
			out << node_input._Area << ' ';
			out << node_input._Rho << ' ';
			out << node_input._Temperature << ' ';
			out << node_input._Velocity << ' ';
			out << node_input._delta_t << ' ';

			out << node_input._partial_Rho_partial_t << ' ';
			out << node_input._partial_Velocity_partial_t << ' ';
			out << node_input._partial_Temperature_partial_t << ' ';

			out << node_input.getResidual();

			return out;
		}
	};*/
}