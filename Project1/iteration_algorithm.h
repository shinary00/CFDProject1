#pragma once
#include "node_data.h"
#include "iteration_func.h"
using namespace shinary_CFD_project;

namespace shinary_CFD_project
{
	//�㷨����
	template<class Mesh>
	class iteration_algorithm_base 
	{
	protected:
		typedef iteration_func_base<Mesh> Func;
		typedef typename Mesh::value_type::node_data_type node_data_type;
	protected:
		//�������������
		Mesh& iteration_mesh;
		//���������΢�ַ��̴�����ָ��
		Func& iteration_func;
		//��ʼ������ָ��
		Func& initialization_func;
		//�趨�ļ��㾫��
		node_data_type precision;
	protected:
		//��ʼ��
		virtual void initialization() {};
		//����һ�ε���
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
		//��ʼ��
		virtual void initialization() { Algorithm::initialization_func.execute(); };
		//�õ��趨����
		node_data_type getPrecision() const { return Algorithm::precision; }
		//����
		void executeIteration() override ;
	};
	//����ʵ��
	template<class Mesh>
	inline void MM_Pushing_Algorithm<Mesh>::executeIteration()
	{

		Algorithm::iteration_func.execute();
	}
}