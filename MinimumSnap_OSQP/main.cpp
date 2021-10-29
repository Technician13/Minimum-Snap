/*
 * @Author: Technician13
 * @Date: 2021-10-02 19:11:06
 * @LastEditTime: 2021-10-27 16:06:33
 * @LastEditors: Technician13
 * @Description: 
 */
 
#include "MiniSnap.hpp"   

int main(int argc, char** argv)
{
    std::vector<double> proportion{1.0/2.0 , 1.0/2.0};
	double T = 2.0;
    int segment = 2;

    std::vector<double> pointX{0.0 , 4.0 , 8.0};
    std::vector<double> velX{0.0 , 8.0 , 0.0};

	std::vector<double> pointY{0.0 , 1.0 , 2.0};
    std::vector<double> velY{0.0 , 2.0 , 0.0};

	std::vector<double> pointZ{0.0 , 4.0 , 0.0};
    std::vector<double> velZ{0.0 , 0.0 , 0.0};

    MiniSnap *minisnapX = new MiniSnap(segment);
    minisnapX->SetParas(proportion , T , pointX , velX);
    minisnapX->SolveOpt();

	MiniSnap *minisnapY = new MiniSnap(segment);
    minisnapY->SetParas(proportion , T , pointY , velY);
    minisnapY->SolveOpt();

	MiniSnap *minisnapZ = new MiniSnap(segment);
    minisnapZ->SetParas(proportion , T , pointZ , velZ);
    minisnapZ->SolveOpt();

	delete minisnapX;
	delete minisnapY;
	delete minisnapZ;	
	
    return 0;
}