#pragma once
#include "node_data.h"
#include "iteration_func.h"
using namespace shinary_CFD_project;

namespace shinary_CFD_project
{
	//算法基类
	template<class Mesh>
	class iteration_algorithm_base
	{
	protected:
		typedef iteration_func_base<Mesh> Func;
		typedef typename Mesh::node_data_type node_data_type;
	protected:
		//参与迭代的网格
		Mesh& iteration_mesh;

		//参与迭代的微分方程处理函数指针
		Func& iteration_func;

		//初始化函数指针
		Func& initialization_func;

		//设定的计算精度
		node_data_type precision;
	protected:
		//初始化
		virtual void initialization() {};

		//进行一次迭代
		virtual void executeIteration() = 0;
	public:
		//Ctor
		iteration_algorithm_base(Mesh& mesh, Func& func0, Func& func1, node_data_type precision_input) :iteration_mesh(mesh), iteration_func(func1), initialization_func(func0), precision(precision_input) {};
	};

	//麦考马克推进法
	template<class Mesh>
	class MM_Pushing_Algorithm :public iteration_algorithm_base<Mesh>
	{
		typedef iteration_algorithm_base<Mesh> base_type;
		typedef typename base_type::Func Func;
		typedef typename base_type::node_data_type node_data_type;
	public:
		//Ctor
		MM_Pushing_Algorithm(Mesh& mesh, Func& func0, Func& func1, node_data_type precision_input) :base_type(mesh, func0, func1, precision_input) {};

		//CopyCtor
		MM_Pushing_Algorithm(const MM_Pushing_Algorithm<Mesh>& algorithm_input) : base_type(algorithm_input.iteration_mesh, algorithm_input.initialization_func, algorithm_input.iteration_func, algorithm_input.precision) {};
	public:
		//初始化
		virtual void initialization() { base_type::initialization_func.execute(); };

		//得到设定精度
		node_data_type getPrecision() const { return base_type::precision; }

		//迭代
		void executeIteration() override { base_type::iteration_func.execute(); };
	};
}