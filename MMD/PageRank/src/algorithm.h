#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <cstring>

namespace pagerank {
	static const int NNODES = 1000000;

	class Algorithm {
		public:
			Algorithm(const char *file_name) : 
				_m_beta(0.8f), _m_epsilion(1e-5),
	   			_m_file_name(file_name), _m_nnodes(0) {
					memset(_m_nodes_map, 0, sizeof(_m_nodes_map));	
					memset(_m_nodes_map_reverse, 0, sizeof(_m_nodes_map_reverse));	
					memset(_m_degree, 0, sizeof(_m_degree));
				};	

			void run();

			std::vector<double> get_r() {};

		private:
			void read_input();

			void power_iterate();

			bool inline sum_up();

		private:
			int _m_nodes_map[NNODES];
			int _m_nodes_map_reverse[NNODES];
			int _m_degree[NNODES];
			int _m_nnodes;

			std::vector<int> _m_matrix_m[NNODES];
			std::vector<double> _m_r;
			std::vector<double> _m_pr;
			const char *_m_file_name;
						
			double _m_beta;
			double _m_epsilion;
	};
}//pagerank

#endif
