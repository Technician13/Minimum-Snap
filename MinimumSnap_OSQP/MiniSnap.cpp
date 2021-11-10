/*
 * @Author: Technician13
 * @Date: 2021-10-03 14:03:27
 * @LastEditTime: 2021-11-10 10:35:14
 * @LastEditors: Technician13
 * @Description: MinimumSnap轨迹规划方法
 */

#include "MiniSnap.hpp"

/**
 * @brief 构造函数，完成基于子轨迹数目的内存的分配
 * 
 * @param p_segment 子轨迹数目
 */
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

/**
 * @brief 析构函数，释放掉申请的内存
 * 
 */
MiniSnap::~MiniSnap(void)
{
    delete []P_x;
    delete []P_i;
    delete []P_p;
    delete []q;
    delete []A_x;
    delete []A_i;
    delete []l;
    delete []u;
}

/**
 * @brief 参数配置函数
 * 
 * @param p_proportion 时间占比向量，总时间，给定点的位置向量，给定点的速度向量
 * @param p_T 
 * @param p_point 
 * @param p_vel 
 */
void MiniSnap::SetParas(std::vector<double> p_proportion, double p_T, std::vector<double> p_point, std::vector<double> p_vel)
{
    T = p_T;

    /* 更新衔接点的时刻 */
    t.clear();
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
    #ifdef MINISNAP_TEST
        std::cout<<" [ 衔接点的时刻 ] "<<std::endl;
        for(int i = 0 ; i < t.size() ; i++)
        {
            std::cout<<t[i]<<"    ";
        }
        std::cout<<std::endl;
    #endif

    /* 更新P_x */
    for(int i = 1 ; i <= segment ; i++)
    {
        P_x[4 * (i - 1)] = 4800.0 * (pow(t[i] , 3) - pow(t[i-1] , 3));
        P_x[4 * (i - 1) + 1] = 1440.0 * (pow(t[i] , 2) - pow(t[i-1] , 2));
        P_x[4 * (i - 1) + 2] = 1440.0 * (pow(t[i] , 2) - pow(t[i-1] , 2));
        P_x[4 * (i - 1) + 3] = 576.0 * (t[i] - t[i-1]);
    }
    #ifdef MINISNAP_TEST
        std::cout<<" [ P_x ] "<<std::endl;
        for(int i = 1 ; i <= segment ; i++)
        {
            std::cout<<P_x[4 * (i - 1)]<<"    "<<P_x[4 * (i - 1) + 1]<<"    "<<P_x[4 * (i - 1) + 2]<<"    "<<P_x[4 * (i - 1) + 3]<<"    ";
        }
        std::cout<<std::endl;
    #endif

    /* 更新P_nnz */
    P_nnz = sizeof(P_x);
    #ifdef MINISNAP_TEST
        std::cout<<" [ P_nnz ] "<<std::endl;
        std::cout<<P_nnz<<std::endl;
    #endif

    /* 更新P_i */
    for(int i = 0 ; i < segment ; i++)
    {
        P_i[4 * i] = 6 * i;
        P_i[4 * i + 1] = 6 * i + 1;
        P_i[4 * i + 2] = 6 * i;
        P_i[4 * i + 3] = 6 * i + 1;
    }
    #ifdef MINISNAP_TEST
        std::cout<<" [ P_i ] "<<std::endl;
        for(int i = 0 ; i < segment ; i++)
        {
            std::cout<<P_i[4 * i]<<"    "<<P_i[4 * i + 1]<<"    "<<P_i[4 * i + 2]<<"    "<<P_i[4 * i + 3]<<"    ";
        }
        std::cout<<std::endl;
    #endif

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
    #ifdef MINISNAP_TEST
        std::cout<<" [ P_p ] "<<std::endl;
        for(int i = 0 ; i < segment ; i++)
        {
            std::cout<<P_p[6 * i + 1]<<"    "<<P_p[6 * i + 2]<<"    "<<P_p[6 * i + 3]<<"    "<<P_p[6 * i + 4]<<"    "<<P_p[6 * i + 5]<<"    "<<P_p[6 * i + 6]<<"    ";
        }
        std::cout<<std::endl;
    #endif

    /* 更新q */
    for(int i = 0 ; i < 6 * segment ; i++)
    {
        q[i] = 0.0;
    }
    #ifdef MINISNAP_TEST
        std::cout<<" [ q ] "<<std::endl;
        for(int i = 0 ; i < 6 * segment ; i++)
        {
            std::cout<<q[i]<<"    ";
        }
        std::cout<<std::endl;
    #endif

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
    #ifdef MINISNAP_TEST
        std::cout<<" [ Aeq ] "<<std::endl;
        std::cout<<Aeq<<std::endl;
    #endif

    /* 更新A_x & A_i & A_p*/
    std::vector<int> A_pVector;
    A_pVector.push_back(0);
    int A_xIndex = 0;
    int A_iIndex = 0;
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
    #ifdef MINISNAP_TEST
        std::cout<<"[ A_x  &  A_i ] "<<std::endl;
        for(int i = 0 ; i < A_xIndex ; i++)
        {
            std::cout<<A_x[i]<<"    "<<A_i[i]<<std::endl;
        }

        std::cout<<"[ A_p ] "<<std::endl;
        for(int i = 0 ; i < (int)A_pVector.size() ; i++)
        {
            std::cout<<A_p[i]<<std::endl;
        }
    #endif

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

/**
 * @brief 调用OSQP求解器完成求解
 * 
 */
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
    settings->polish = 1;
    settings->max_iter = 40000;
    settings->eps_prim_inf = 10.0;
    settings->sigma = 0.005;

    // Setup workspace
    work = osqp_setup(data, settings);

    // Solve Problem
    osqp_solve(work);

    #ifdef MINISNAP_TEST 
        std::cout<<"========================================================================================="<<std::endl;   
        std::cout << "[ res ]" <<std::endl<<std::endl;
        for(int i = 0 ; i < segment ; i++)
        {
            for(int j = 0 ; j < 6 ; j++)
            {
                std::cout << work->solution->x[6 * i + j] << " ";
            }
            std::cout << std::endl;
        }

        std::cout<<"========================================================================================="<<std::endl;
        std::cout<<"[ Pos ]"<<std::endl;
        std::cout<<work->solution->x[0] * pow(0.5 * T , 5) +
                   work->solution->x[1] * pow(0.5 * T , 4) +
                   work->solution->x[2] * pow(0.5 * T , 3) +
                   work->solution->x[3] * pow(0.5 * T , 2) +
                   work->solution->x[4] * pow(0.5 * T , 1) +
                   work->solution->x[5] * pow(0.5 * T , 0)<<"    ";
        std::cout<<work->solution->x[6] * pow(0.5 * T , 5) +
                   work->solution->x[7] * pow(0.5 * T , 4) +
                   work->solution->x[8] * pow(0.5 * T , 3) +
                   work->solution->x[9] * pow(0.5 * T , 2) +
                   work->solution->x[10] * pow(0.5 * T , 1) +
                   work->solution->x[11] * pow(0.5 * T , 0)<<std::endl;
        
        std::cout<<"[ Vel ]"<<std::endl;
        std::cout<<5 * work->solution->x[0] * pow(0.5 * T , 4) +
                   4 * work->solution->x[1] * pow(0.5 * T , 3) +
                   3 * work->solution->x[2] * pow(0.5 * T , 2) +
                   2 * work->solution->x[3] * pow(0.5 * T , 1) +
                   1 * work->solution->x[4] * pow(0.5 * T , 0)<<"    ";
        std::cout<<5 * work->solution->x[6] * pow(0.5 * T , 4) +
                   4 * work->solution->x[7] * pow(0.5 * T , 3) +
                   3 * work->solution->x[8] * pow(0.5 * T , 2) +
                   2 * work->solution->x[9] * pow(0.5 * T , 1) +
                   1 * work->solution->x[10] * pow(0.5 * T , 0)<<std::endl;

        std::cout<<"[ Acc ]"<<std::endl;
        std::cout<<4 * 5 * work->solution->x[0] * pow(0.5 * T , 3) +
                   3 * 4 * work->solution->x[1] * pow(0.5 * T , 2) +
                   2 * 3 * work->solution->x[2] * pow(0.5 * T , 1) +
                   1 * 2 * work->solution->x[3] * pow(0.5 * T , 0)<<"    ";
        std::cout<<4 * 5 * work->solution->x[6] * pow(0.5 * T , 3) +
                   3 * 4 * work->solution->x[7] * pow(0.5 * T , 2) +
                   2 * 3 * work->solution->x[8] * pow(0.5 * T , 1) +
                   1 * 2 * work->solution->x[9] * pow(0.5 * T , 0)<<std::endl;

        std::cout<<"========================================================================================="<<std::endl;
        std::cout<<"[ Pos-continuous ]"<<std::endl;
        for(int i = 0 ; i < 2 ; i++)
        {
            for(int j = 0 ; j < 10 ; j++)
            {
                std::cout<<work->solution->x[6 * i + 0] * pow(0.5 * i * T + 0.05 * j * T , 5) +
                           work->solution->x[6 * i + 1] * pow(0.5 * i * T + 0.05 * j * T , 4) +
                           work->solution->x[6 * i + 2] * pow(0.5 * i * T + 0.05 * j * T , 3) +
                           work->solution->x[6 * i + 3] * pow(0.5 * i * T + 0.05 * j * T , 2) +
                           work->solution->x[6 * i + 4] * pow(0.5 * i * T + 0.05 * j * T , 1) +
                           work->solution->x[6 * i + 5] * pow(0.5 * i * T + 0.05 * j * T , 0)<<std::endl;
            }
        }

        std::cout<<"========================================================================================="<<std::endl;
        std::cout<<"[ Vel-continuous ]"<<std::endl;
        for(int i = 0 ; i < 2 ; i++)
        {
            for(int j = 0 ; j < 10 ; j++)
            {
                std::cout<<5 * work->solution->x[6 * i + 0] * pow(0.5 * i * T + 0.05 * j * T , 4) +
                           4 * work->solution->x[6 * i + 1] * pow(0.5 * i * T + 0.05 * j * T , 3) +
                           3 * work->solution->x[6 * i + 2] * pow(0.5 * i * T + 0.05 * j * T , 2) +
                           2 * work->solution->x[6 * i + 3] * pow(0.5 * i * T + 0.05 * j * T , 1) +
                           1 * work->solution->x[6 * i + 4] * pow(0.5 * i * T + 0.05 * j * T , 0)<<std::endl;
            }
        }     
    #endif
    
    // Clean workspace
    osqp_cleanup(work);
    c_free(data->A);
    c_free(data->P);
    c_free(data);
    c_free(settings);
    delete []A_p;
}