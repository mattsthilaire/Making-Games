#include <cmath>
#include <vector>
#include "point.h"

#ifndef MATRIX_H
#define MATRIX_H

// based off of https://www.scratchapixel.com/lessons/3d-basic-rendering/computing-pixel-coordinates-of-3d-point/mathematics-computing-2d-coordinates-of-3d-points.html
class Matrix
{
public:
    // matric component parts
    std::vector<float> x_axis;
    std::vector<float> y_axis;
    std::vector<float> z_axis;
    std::vector<float> translation_axis;

    // overall matrix
    std::vector<std::vector<float>> matrix;

    Matrix()
    {
        this->x_axis = std::vector<float>{0.0, 0.0, 0.0, 0.0};
        this->y_axis = std::vector<float>{0.0, 0.0, 0.0, 0.0};
        this->z_axis = std::vector<float>{0.0, 0.0, 0.0, 0.0};
        this->translation_axis = std::vector<float>{0.0, 0.0, 0.0, 0.0};

        this->matrix = std::vector<std::vector<float>>{x_axis,
                                                       y_axis,
                                                       z_axis,
                                                       translation_axis};
    };

    Matrix(float diag_val)
    {
        this->x_axis = std::vector<float>{diag_val, 0.0, 0.0, 0.0};
        this->y_axis = std::vector<float>{0.0, diag_val, 0.0, 0.0};
        this->z_axis = std::vector<float>{0.0, 0.0, diag_val, 0.0};
        this->translation_axis = std::vector<float>{0.0, 0.0, 0.0, diag_val};

        this->matrix = std::vector<std::vector<float>>{x_axis,
                                                       y_axis,
                                                       z_axis,
                                                       translation_axis};
    };

    Matrix(std::vector<float> x_axis, std::vector<float> y_axis, std::vector<float> z_axis, std::vector<float> translation_axis)
    {
        this->x_axis = x_axis;
        this->y_axis = y_axis;
        this->z_axis = z_axis;
        this->translation_axis = translation_axis;

        this->matrix = std::vector<std::vector<float>>{x_axis,
                                                       y_axis,
                                                       z_axis,
                                                       translation_axis};
    }

    // change point values passed to this function
    Point vec_mul_mat(Point p);
    void transpose();
    Matrix inverse();
    void print_values();

    Point local2world(Point p);
    Point world2camera(Point p);
};

#endif