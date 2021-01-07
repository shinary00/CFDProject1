#pragma once
#include "mesh.h"
#include <stdio.h>
using namespace shinary_CFD_project;

namespace shinary_CFD_project
{
	template<class Mesh>
	class _post_processing_base
	{
	protected:
		Mesh& _mesh;
	protected:
		_post_processing_base(Mesh& mesh_input) :_mesh(mesh_input) {};
		virtual ~_post_processing_base() {};
	protected:
		virtual void dataOutput() {};
	};

	template<class Mesh>
	class post_processing :public _post_processing_base<Mesh>
	{
	public:
		post_processing(Mesh& mesh_input) :
			call_count(int(0)), filename(NULL),
			_post_processing_base<Mesh>(mesh_input)
		{
			freopen_s(&filename, "../data_log.txt", "w", stdout);
		};
		~post_processing() { freopen_s(&filename, "CON", "w", stdout); }
	private:
		int call_count;
		FILE* filename;
	public:
		void dataOutput();
		int getIterationNumber()const { return call_count; }
	};
}

template<class Mesh>
inline void shinary_CFD_project::post_processing<Mesh>::dataOutput()
{
	call_count++;
	for (auto element : _post_processing_base<Mesh>::_mesh.getData())
	{
		std::cout << call_count << ' ' << element << std::endl;
	}
}