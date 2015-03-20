#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "sys/time.h"
#include "algorithm.h"

namespace pagerank {
	void Algorithm::run()
	{
		timeval t1, t2, t3;
		double elapsed_time = 0.0f;
		gettimeofday(&t1, NULL);

		read_input();	

		gettimeofday(&t2, NULL);
		elapsed_time = (t2.tv_sec - t1.tv_sec) * 1000.0; 
		elapsed_time += (t2.tv_usec - t1.tv_usec) / 1000.0;
		printf("reading time->execute %f\n", elapsed_time);

		_m_pr.resize(_m_nnodes + 1, 1.0f / _m_nnodes);
		_m_r.resize(_m_nnodes + 1, 0);

		power_iterate();

		printf("answer 99 %.11f\n", _m_r[_m_nodes_map[99]]);

		gettimeofday(&t3, NULL);
		elapsed_time = (t3.tv_sec - t2.tv_sec) * 1000.0; 
		elapsed_time += (t3.tv_usec - t2.tv_usec) / 1000.0;
		printf("elapsed time->execute %f\n", elapsed_time);
	}

	void Algorithm::power_iterate()
	{
		int n_steps = 0;

		do {
			double sum_r = 0.0f;

			for (size_t i = 1; i <= _m_nnodes; ++i) {
				_m_r[i] = 0.0f;					

				for (size_t j = 0; j < _m_matrix_m[i].size(); ++j) {
					int to_id = _m_matrix_m[i][j];
					_m_r[i] += _m_beta * _m_pr[to_id] / _m_degree[to_id];	
				}

				sum_r += _m_r[i];
			}

			double plus = (1.0 - sum_r) / _m_nnodes;
			for (size_t i = 1; i <= _m_nnodes; ++i) {
				_m_r[i] += plus;
			}

			++n_steps;
			printf("n_steps %d\n", n_steps);
		}while (sum_up());
	} 

	bool inline Algorithm::sum_up()
	{
		double sum = 0.0f;

		for (size_t i = 1; i <= _m_nnodes; ++i) {
			sum += fabs(_m_r[i] - _m_pr[i]);
			_m_pr[i] = _m_r[i];
		}	

		printf("sum %f\n", sum);
		return sum > _m_epsilion;
	}

	void Algorithm::read_input()
	{
		FILE *fp = fopen(_m_file_name, "r+");

		if (fp == NULL) {
			fprintf(stderr, "No such file->%s\n", _m_file_name);
			exit(1);
		}

		int from, to;
		int prev_id = -1;
		int prev_count = 0;
		int cnt = 1;

		while (fscanf(fp, "%d %d", &from, &to) != EOF) {
			if (prev_id != from) {
				if (prev_id != -1) {
					_m_degree[_m_nodes_map[prev_id]] = prev_count;
					prev_count = 0;
				}
				prev_id = from;
			}

			if (_m_nodes_map[from] == 0) {
				_m_nodes_map_reverse[cnt] = from;
				_m_nodes_map[from] = cnt++;
			}

			if (_m_nodes_map[to] == 0) {
				_m_nodes_map_reverse[cnt] = to;
				_m_nodes_map[to] = cnt++;
			}

			_m_matrix_m[_m_nodes_map[to]].push_back(_m_nodes_map[from]);
			++prev_count;
		}
		
		fclose(fp);

		_m_degree[_m_nodes_map[prev_id]] = prev_count;
		_m_nnodes = cnt - 1;

		printf("nodes %d\n", _m_nnodes);
		printf("read file end\n");
	}

}//pagerank
