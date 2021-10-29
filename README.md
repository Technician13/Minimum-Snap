# MinimumSnap
## description    
* The code in this repository provides three projects of Minimum-Snap trajectory planning method.       
## construction
* `MinimumSnap_Cplex` contains the version using cplex, this is an assignment for my graduate program.
* `MinimumSnap_MATLAB` contains the version using MATLAB, download the project and set up the path correctly, then run the following command, you will get two figures, the fisrt one
contains three demos of velocity changing directions and the other contains the change curves of the position, velocity and acceleration of the first demo in X and Y directions, respectively, 
to verify the higher-order continuity of this trajectory planning method.
```
Untitled
```
These are the results of project in `MinimumSnap_MATLAB`:         
<div align=center><img src=https://github.com/Technician13/MinimumSnap/blob/master/MinimumSnap_MATLAB/res/res_data.png></div>       
<div align=center><img src=https://github.com/Technician13/MinimumSnap/blob/master/MinimumSnap_MATLAB/res/res_1.png></div>        
<div align=center><img src=https://github.com/Technician13/MinimumSnap/blob/master/MinimumSnap_MATLAB/res/res_2.png></div>      
* `MinimumSnap_OSQP` contains the version using OSQP 0.4.1 & Eigen, download the project and run the following commands, OSQP will solve the problem quickly.In this project, we use the first demo in 
`MinimumSnap_MATLAB` to verify that the code is correct.
```
cd MinimumSnap_OSQP
mkdir build
cd build
cmake ..
make -j
./MINI_SNAP
```
This is the result of project in `MinimumSnap_OSQP`:           
![image]( https://github.com/Technician13/MinimumSnap/blob/master/MinimumSnap_OSQP/res/res_1.png)              
We can  find that the result is consistent with the one in `MinimumSnap_MATLAB`.
