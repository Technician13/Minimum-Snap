/*
 * @Author: Technician13
 * @Date: 2021-10-03 14:03:27
 * @LastEditTime: 2021-10-05 09:30:50
 * @LastEditors: Technician13
 * @Description: 
 */

#include "MiniSnap.hpp"

MiniSnap::MiniSnap(int p_segment):segment(p_segment)
{
    P_x = new c_float[4 * segment];
    P_i = new c_int[4 * segment];
    P_p = new c_int[6 * segment + 1];
    q   = new c_float[6 * segment];
    /* A_x内存分配原理：
     * (segment + 1)个位置约束共(1 + 6 * segment)
     * (segment - 1)个位置-速度-加速度衔接约束共((segment - 1) * (12 + 10 + 8))
     * (segment + 1)个速度约束共(1 + 5 * segment)
     * 最后时刻的加速度约束共4
     * 综上，共有(41 * segment - 24)个非零项 */
    A_x = new c_float[41 * segment - 24];
    A_i = new c_int[41 * segment - 24];
    l = new c_float[5 * segment];
    u = new c_float[5 * segment];
}

MiniSnap::~MiniSnap(void)
{

}

void MiniSnap::SetParas(std::vector<double> p_proportion, double p_T, std::vector<double> p_point, std::vector<double> p_vel)
{
    T = p_T;

    /* 更新衔接点的时刻 */
    t.push_back(0.0);
    for(int i = 0 ; i < segment ; i++)
    {
        double temp = 0.0;
        for(int j = 0 ; j <= i ; j++)
        {
            temp += p_proportion[j];
        }
        t.push_back(temp * T);
    }

    /* 更新P_x */
    for(int i = 1 ; i <= segment ; i++)
    {
        P_x[4 * (i - 1)] = 4800.0 * (pow(t[i] , 3) - pow(t[i-1] , 3));
        P_x[4 * (i - 1) + 1] = 1440.0 * (pow(t[i] , 2) - pow(t[i-1] , 2));
        P_x[4 * (i - 1) + 2] = 1440.0 * (pow(t[i] , 2) - pow(t[i-1] , 2));
        P_x[4 * (i - 1) + 3] = 576.0 * (t[i] - t[i-1]);
    }

    /* 更新P_nnz */
    P_nnz = sizeof(P_x);

    /* 更新P_i */
    for(int i = 0 ; i < segment ; i++)
    {
        P_i[4 * i] = 6 * i;
        P_i[4 * i + 1] = 6 * i + 1;
        P_i[4 * i + 2] = 6 * i;
        P_i[4 * i + 3] = 6 * i + 1;
    }

    /* 更新P_p */
    P_p[0] = 0;
    for(int i = 0 ; i < segment ; i++)
    {
        P_p[6 * i + 1] = 4 * i + 2;
        P_p[6 * i + 2] = 4 * i + 4;
        P_p[6 * i + 3] = 4 * i + 4;
        P_p[6 * i + 4] = 4 * i + 4;
        P_p[6 * i + 5] = 4 * i + 4;
        P_p[6 * i + 6] = 4 * i + 4;
    }

    /* 更新q */
    for(int i = 0 ; i < (int)sizeof(q) ; i++)
    {
        q[i] = 0.0;
    }

    Eigen::MatrixXd Aeq;
    Aeq.resize(5 * segment , 6 * segment);
    Aeq.setZero();
    /* 第一组约束 */
    Aeq(0,5) = 1.0;
    for(int i = 0 ; i < segment ; i++)
    {
        Eigen::Matrix<double , 1 , 6> v1;
        v1 << pow(t[i+1] , 5) , pow(t[i+1] , 4) , pow(t[i+1] , 3) , pow(t[i+1] , 2) , pow(t[i+1] , 1) , pow(t[i+1] , 0);
        Aeq.block(i + 1 , 6 * i , 1 , 6) = v1;
    }
    /* 第二组约束 */
    for(int i = 0 ; i < (segment - 1) ; i++)
    {   
        Eigen::Matrix<double , 1 , 6> v1;
        v1 << pow(t[i+1] , 5) , pow(t[i+1] , 4) , pow(t[i+1] , 3) , pow(t[i+1] , 2) , pow(t[i+1] , 1) , pow(t[i+1] , 0);
        Eigen::Matrix<double , 1 , 5> v2;
        v2 << 5 * pow(t[i+1] , 4) , 4 * pow(t[i+1] , 3) , 3 * pow(t[i+1] , 2) , 2 * pow(t[i+1] , 1) , pow(t[i+1] , 0);
        Eigen::Matrix<double , 1 , 4> v3;
        v3 << 20 * pow(t[i+1] , 3) , 12 * pow(t[i+1] , 2) , 6 * pow(t[i+1] , 1) , 2 *pow(t[i+1] , 0);

        Aeq.block(segment + 1 + 3 * i , 6 * i , 1 , 6) = v1;
        Aeq.block(segment + 1 + 3 * i , 6 * i + 6, 1 , 6) = -v1;
        Aeq.block(segment + 2 + 3 * i , 6 * i , 1 , 5) = v2;
        Aeq.block(segment + 2 + 3 * i , 6 * i + 6, 1 , 5) = -v2;
        Aeq.block(segment + 3 + 3 * i , 6 * i , 1 , 4) = v3;
        Aeq.block(segment + 3 + 3 * i , 6 * i + 6, 1 , 4) = -v3;
    }
    /* 第三组约束 */
    Aeq(4 * segment - 2 , 4) = 1.0;
    for(int i = 1 ; i < (segment + 1) ; i++)
    {
        Eigen::Matrix<double , 1 , 5> v2;
        v2 << 5 * pow(t[i] , 4) , 4 * pow(t[i] , 3) , 3 * pow(t[i] , 2) , 2 * pow(t[i] , 1) , pow(t[i] , 0);
        Aeq.block(4 * segment - 2 + i , 6 * (i - 1) , 1 , 5) = v2;    
    }
    /* 第四组约束 */
    {
        Eigen::Matrix<double , 1 , 4> v3;
        v3 << 20 * pow(t[segment] , 3) , 12 * pow(t[segment] , 2) , 6 * pow(t[segment] , 1) , 2 *pow(t[segment] , 0);
        Aeq.block(5 * segment - 1 , 6 * (segment - 1) , 1 , 4) = v3; 
    }

    /* 更新A_x & A_i & A_p*/
    std::vector<int> A_pVector;
    A_pVector.push_back(0);
    int A_xIndex = 0;
    int A_iIndex = 0;
    // int A_pIndex = 0;
    int A_pNum = 0;

    for(int j = 0 ; j < 6 * segment ; j++)
    {
        for(int i = 0 ; i < 5 * segment ; i++)
        {
            if(Aeq(i,j)<-0.0000001 || Aeq(i,j)>0.0000001)
            {
                A_x[A_xIndex++] = Aeq(i , j);
                A_i[A_iIndex++] = i;
                A_pNum++;
            }
        }
        A_pVector.push_back(A_pNum);
    }
    A_p = new c_int[(int)A_pVector.size()];
    for(int i = 0 ; i < (int)A_pVector.size() ; i++)
    {
        A_p[i] = A_pVector[i];
    }
    

    std::cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++ "<<A_xIndex<<std::endl;
    for(int i = 0 ; i < A_xIndex ; i++)
    {
        std::cout<<A_x[i]<<"    "<<A_i[i]<<std::endl;
    }
    std::cout<<"================================================== "<<A_pNum<<std::endl;
    for(int i = 0 ; i < (int)A_pVector.size() ; i++)
    {
        std::cout<<A_pVector[i]<<std::endl;
    }

    /* 更新A_nnz */
    A_nnz = sizeof(A_x);

    /* 更新l & u*/
    /* 第一组约束 */
    for(int i = 0 ; i < (segment + 1) ; i++)
    {
        l[i] = p_point[i];
        u[i] = p_point[i];
    }
    /* 第二组约束 */
    for(int i = 0 ; i < 3 * (segment - 1) ; i++)
    {   
        l[segment + 1 + i] = 0.0;
        u[segment + 1 + i] = 0.0;
    }
    /* 第三组约束 */
    for(int i = 0 ; i < (segment + 1) ; i++)
    {
        l[4 * segment - 2 + i] = p_vel[i];
        u[4 * segment - 2 + i] = p_vel[i];     
    }
    /* 第四组约束 */
    {
        l[5 * segment - 1] = 0.0; 
        u[5 * segment - 1] = 0.0; 
    }

    /* 更新n */
    n = 6 * segment;

    /* 更新m */
    m = 5 * segment;
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
    delete []A_p;
}