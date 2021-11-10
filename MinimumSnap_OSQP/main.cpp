/*
 * @Author: Technician13
 * @Date: 2021-10-02 19:11:06
 * @LastEditTime: 2021-11-10 10:23:37
 * @LastEditors: Technician13
 * @Description: MinimumSnap轨迹规划方法的调用样例
 */
 
#include "MiniSnap.hpp"   

int main(int argc, char** argv)
{
    /* 设定时间占比，总时间以及子轨迹的数目 */
    /* Tips:子轨迹的数目要与时间占比向量中元素数目一致 */
    std::vector<double> proportion{1.0/2.0 , 1.0/2.0};
	double T = 2.0;
    int segment = 2;

    /* 设定给定点的位置与速度 */
    /* Tips:给定点的位置数目 & 给定点的速度数目 = 子轨迹的数目 + 1 */
    std::vector<double> pointX{0.0 , 4.0 , 8.0};
    std::vector<double> velX{0.0 , 8.0 , 0.0};

	std::vector<double> pointY{0.0 , 1.0 , 2.0};
    std::vector<double> velY{0.0 , 2.0 , 0.0};

	std::vector<double> pointZ{0.0 , 4.0 , 0.0};
    std::vector<double> velZ{0.0 , 0.0 , 0.0};

    /* MiniSnap对象实例化 */
    MiniSnap *minisnapX = new MiniSnap(segment);
    /* 完成参数传递与求解 */
    minisnapX->SetParas(proportion , T , pointX , velX);
    minisnapX->SolveOpt();

    /* MiniSnap对象实例化 */
	MiniSnap *minisnapY = new MiniSnap(segment);
    /* 完成参数传递与求解 */
    minisnapY->SetParas(proportion , T , pointY , velY);
    minisnapY->SolveOpt();

    /* MiniSnap对象实例化 */
	MiniSnap *minisnapZ = new MiniSnap(segment);
    /* 完成参数传递与求解 */
    minisnapZ->SetParas(proportion , T , pointZ , velZ);
    minisnapZ->SolveOpt();

    /* 释放内存 */
	delete minisnapX;
	delete minisnapY;
	delete minisnapZ;	
	
    return 0;
}