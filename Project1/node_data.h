#pragma once
#include <iostream>

namespace shinary_CFD_project
{
#ifndef NODE_DATA
#define NODE_DATA
	//节点基类
	template<class DATA_COMMON, class DATA_RESIDUAL>
	class _node_data_base
	{
	protected:
		typedef _node_data_base<DATA_COMMON, DATA_RESIDUAL> SELF;
		typedef typename DATA_COMMON::data_type data_type;
	protected:
		struct _data {
			DATA_COMMON* m_data_common;
			DATA_RESIDUAL* m_data_need_residual;
		}m_data_set;
		typedef _data node_data_set_type;
		DATA_RESIDUAL* m_residual;
	protected:
		_node_data_base()
		{
			m_data_set.m_data_common = new DATA_COMMON;
			m_data_set.m_data_need_residual = new DATA_RESIDUAL;
			m_residual = new DATA_RESIDUAL;
		}
		virtual ~_node_data_base()
		{
			delete m_data_set.m_data_common;
			delete m_data_set.m_data_need_residual;
			delete m_residual;
		}
	public:
		virtual node_data_set_type& getData() { return m_data_set; }
		virtual node_data_set_type getData() const{ return m_data_set; }
		virtual DATA_RESIDUAL& getResidual() { return *m_residual; }
		//virtual bool operator>(const data_type& compare)const = 0;
		virtual std::ostream& operator<<(std::ostream& out) = 0;
		virtual void operator=(const SELF& residual_input) = 0;
	};

	//需要重载的操作符
	template<class TYPE, class T>
	class __data_node_operations
	{
	protected:
		virtual bool operator>(const T& compare)const = 0;
		virtual std::ostream& operator<<(std::ostream& out) = 0;
		virtual void operator=(const TYPE& residual_input) = 0;
	};
	//不计算残差的参数基类
	template<class TYPE, class T>
	class _data_common_base :private __data_node_operations<TYPE, T> {};
	//需要计算残差的参数基类
	template<class TYPE, class T>
	class _data_need_residual_base :private __data_node_operations<TYPE, T> {};
	////残差内的数据结构体
	//template<class T>
	//struct _residual_data
	//{
	//	T _Rho_residual = 1;
	//	T _Temperature_residual = 1;
	//	T _Velocity_residual = 1;
	//	T _partial_Rho_partial_t_residual = 1;
	//	T _partial_Velocity_partial_t_residual = 1;
	//	T _partial_Temperature_partial_t_residual = 1;
	//};

	////残差类基类
	//template<class RESIDUAL>
	//class _residual_base 
	//{
	//protected:
	//	RESIDUAL* m_residual_data;
	//protected:
	//	_residual_base() { m_residual_data = new RESIDUAL; }
	//	virtual ~_residual_base() { delete m_residual_data; }
	//	RESIDUAL& getResidualData() { return *m_residual_data; }
	//	RESIDUAL getResidualData()const { return *m_residual_data; }
	//};

	////网格节点基类
	//template<class T>
	//struct _node_data_base
	//{
	//protected:
	//	typedef T node_data_type;
	//};
#endif // !NODE_DATA
}

