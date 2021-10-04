/*
 * @Author: Technician13
 * @Date: 2021-10-02 19:11:06
 * @LastEditTime: 2021-10-04 15:02:17
 * @LastEditors: Technician13
 * @Description: 
 */
 
#include "MiniSnap.hpp"   

int main(int argc, char** argv)
{
    std::vector<double> proportion{1.0/3.0 , 1.0/3.0 , 1.0/3.0};
    double T = 3;

    MiniSnap *minisnap = new MiniSnap(3);
    minisnap->SetParas(proportion , T);
    minisnap->SolveOpt();

    return 0;
}