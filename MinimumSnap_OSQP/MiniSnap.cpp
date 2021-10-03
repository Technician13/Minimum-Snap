/*
 * @Author: Technician13
 * @Date: 2021-10-03 14:03:27
 * @LastEditTime: 2021-10-03 14:40:06
 * @LastEditors: Technician13
 * @Description: 
 */

#include "MiniSnap.hpp"

MiniSnap::MiniSnap(void)
{
    
}

MiniSnap::~MiniSnap(void)
{

}

void MiniSnap::SetParas()
{

}

void MiniSnap::SolveOpt()
{
    // Problem settings
    OSQPSettings *settings = (OSQPSettings *)c_malloc(sizeof(OSQPSettings));

    // Structures
    OSQPWorkspace *work; // Workspace
    OSQPData *data;      // OSQPData

    // Populate data
    data    = (OSQPData *)c_malloc(sizeof(OSQPData));
    data->n = n;
    data->m = m;
    data->P = csc_matrix(data->n, data->n, P_nnz, P_x, P_i, P_p);
    data->q = q;
    data->A = csc_matrix(data->m, data->n, A_nnz, A_x, A_i, A_p);
    data->l = l;
    data->u = u;

    // Define Solver settings as default
    osqp_set_default_settings(settings);

    // Setup workspace
    work = osqp_setup(data, settings);

    // Solve Problem
    osqp_solve(work);

    std::cout<<"================================================================================================="<<std::endl;
    std::cout << "res: " <<std::endl<<std::endl;
    std::cout << work->solution->x[0] << " " 
                << work->solution->x[1] << " " 
                << work->solution->x[2] << " "
                << work->solution->x[3] << " "
                << work->solution->x[4] << " "
                << work->solution->x[5] << std::endl << std::endl;
    std::cout << work->solution->x[6] << " " 
                << work->solution->x[7] << " " 
                << work->solution->x[8] << " "
                << work->solution->x[9] << " "
                << work->solution->x[10] << " "
                << work->solution->x[11] << std::endl << std::endl;
    std::cout << work->solution->x[12] << " " 
                << work->solution->x[13] << " " 
                << work->solution->x[14] << " "
                << work->solution->x[15] << " "
                << work->solution->x[16] << " "
                << work->solution->x[17] << std::endl;
    std::cout<<"================================================================================================="<<std::endl;

    // Clean workspace
    osqp_cleanup(work);
    c_free(data->A);
    c_free(data->P);
    c_free(data);
    c_free(settings);
}

void MiniSnap::PrintInfo()
{
    
}