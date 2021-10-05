/*
 * @Author: Technician13
 * @Date: 2021-10-03 14:03:49
 * @LastEditTime: 2021-10-05 11:09:09
 * @LastEditors: Technician13
 * @Description: 
 */

#ifndef MINISNAP_HPP
#define MINISNAP_HPP

#include <osqp.h>
#include <iostream>    
#include <Eigen/Dense>
#include <vector>
#include <math.h>
#include <string>

class MiniSnap
{
    private:
        c_float *P_x;
        c_int    P_nnz;
        c_int   *P_i;
        c_int   *P_p;
        c_float *q;
        c_int    A_nnz;
        c_float *A_x;
        c_int   *A_i;
        c_int   *A_p;
        c_float *l;
        c_float *u;
        c_int    n;
        c_int    m;
        const int segment;
        std::vector<double> t;
        double T;

    protected:

    public:
        MiniSnap(int p_segment);
        virtual ~MiniSnap(void);
        void SetParas(std::vector<double> p_proportion, double p_T, std::vector<double> p_point, std::vector<double> p_vel);
        void SolveOpt();
};

#endif