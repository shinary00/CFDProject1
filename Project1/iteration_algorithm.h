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
		typedef typename Mesh::value_type::node_data_type node_data_type;
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
		iteration_algorithm_base(Mesh& mesh, Func& func0, Func& func1, node_data_type precision_input) :iteration_mesh(mesh), iteration_func(func1), initialization_func(func0), precision(precision_input){};
	};

	template<class Mesh>
	class MM_Pushing_Algorithm :public iteration_algorithm_base<Mesh>
	{
		typedef iteration_algorithm_base<Mesh> Algorithm;
		typedef typename Algorithm::Func Func;
		typedef typename Algorithm::node_data_type node_data_type;
	public:
		//Ctor
		MM_Pushing_Algorithm(Mesh& mesh, Func& func0, Func& func1, node_data_type precision_input) :Algorithm(mesh, func0, func1, precision_input) {};
		//CopyCtor
		MM_Pushing_Algorithm(const MM_Pushing_Algorithm<Mesh>& algorithm_input) : Algorithm(algorithm_input.iteration_mesh, algorithm_input.initialization_func, algorithm_input.iteration_func, algorithm_input.precision) {};
	public:
		//初始化
		virtual void initialization() { Algorithm::initialization_func.execute(); };
		//得到设定精度
		node_data_type getPrecision() const { return Algorithm::precision; }
		//迭代
		void executeIteration() override ;
	};
	//迭代实现
	template<class Mesh>
	inline void MM_Pushing_Algorithm<Mesh>::executeIteration()
	{

		Algorithm::iteration_func.execute();
	}
}