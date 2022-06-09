#include <iostream>
#include <ctime>

//Eigen Part
#include <Eigen/Core>
//Thick Matrix Calculation
#include <Eigen/Dense>

#include "eigenMatrix.h"

#define MATRIX_SIZE 50

void EigenMatrixTest() {
    Eigen::Matrix<float, 2, 3> matrix_23;
    Eigen::Vector3d v_3d;  // Eigen::Matrix<double,3,1>
    Eigen::Matrix3d matrix_33 = Eigen::Matrix3d::Zero();  // Eigen::Matrix<double,3,3>
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> matrix_dynamic;
    Eigen::MatrixXd matrix_x;

    matrix_23 << 1, 2, 3, 4, 5, 6;

    std::cout << matrix_23 << std::endl;
}