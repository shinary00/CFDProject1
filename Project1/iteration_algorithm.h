#pragma once
#include "node_data.h"
#include "iteration_func.h"
using namespace shinary_CFD_project;

namespace shinary_CFD_project
{
#ifndef ITERATION_ALGORITHM_BASE
#define ITERATION_ALGORITHM_BASE
	template<class Mesh>
	class iteration_algorithm_base //�㷨����
	{
	protected:
		typedef iteration_func_base<Mesh> Func;
		typedef typename Mesh::value_type::node_data_type node_data_type;
	protected:
		//���ǲ������������
		Mesh& iteration_mesh;
		//���ǲ��������΢�ַ��̴�����ָ��
		Func& iteration_func;
		Func& initialization_func;
		//���㾫��
		node_data_type precision;
	protected:
		//��ʼ��
		virtual void initialization() {};
		//����һ�ε���
		virtual void executeIteration() = 0;
	public:
		virtual ~iteration_algorithm_base() {};
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
	public:
		//��ʼ��
		virtual void initialization() { Algorithm::initialization_func.execute(); };
		//����һ�ε���
		void executeIteration() override { Algorithm::iteration_func.execute(); };
		node_data_type getPrecision() const { return Algorithm::precision; }
	};
#endif // !ITERATION_ALGORITHM_BASE
}