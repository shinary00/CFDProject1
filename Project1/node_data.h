#pragma once
#include <iostream>

namespace shinary_CFD_project
{
	//需要重载的操作符
	template<class TYPE, class T>
	class __residual_node_operations
	{
	protected:
		virtual bool operator>(const T& compare)const = 0;
		virtual std::ostream& operator<<(std::ostream& out) = 0;
		virtual void operator=(const TYPE& residual_input) = 0;
	};

	template<class TYPE, class T>
	class __common_node_operations
	{
	protected:
		virtual std::ostream& operator<<(std::ostream& out) = 0;
		virtual void operator=(const TYPE& residual_input) = 0;
	};

	//不计算残差的参数基类
	template<class TYPE, class T>
	class _data_common_base :private __common_node_operations<TYPE, T> {};

	//需要计算残差的参数基类
	template<class TYPE, class T>
	class _data_need_residual_base :private __residual_node_operations<TYPE, T> {};

	//节点数据组
	template<class DATA_COMMON, class DATA_RESIDUAL>
	class _node_base;//友元提前声明
	template<class DATA_COMMON, class DATA_RESIDUAL>
	class _node_data_set
	{
	public:
		DATA_COMMON data_common;
		DATA_RESIDUAL data_need_residual;
		DATA_RESIDUAL residual;
	};

	//节点基类
	template<class DATA_COMMON, class DATA_RESIDUAL>
	class _node_base :
		private __common_node_operations<
		_node_base<DATA_COMMON, DATA_RESIDUAL>,
		typename DATA_COMMON::node_data_type>
	{
	public:
		typedef _node_base<DATA_COMMON, DATA_RESIDUAL> SELF;
		typedef typename DATA_COMMON::node_data_type node_data_type;
		typedef _node_data_set<DATA_COMMON, DATA_RESIDUAL> node_data_set;
	private:
		_node_data_set<DATA_COMMON, DATA_RESIDUAL>* m_data_set;
	public:
		_node_base() { m_data_set = new node_data_set; }
		virtual ~_node_base() { delete m_data_set; }
	public:
		virtual node_data_set& getData() { return *m_data_set; }
		virtual node_data_set getData() const { return *m_data_set; }
		virtual DATA_RESIDUAL& getResidual() { return getData().residual; }
		virtual std::ostream& operator<<(std::ostream& out)override { return (getData().data_need_residual).operator<<((getData().data_common).operator<<(out)); }
		void operator=(const SELF& node_data_input) override { getData() = node_data_input.getData();
		}
	};
}

