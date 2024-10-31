#include <iostream>

#include "matrix.h"
#include "point.h"

Point Matrix::vec_mul_mat(Point p)
{
    Point output;
    output.x = p.x * this->x_axis[0] + p.y * this->y_axis[0] + p.z * this->z_axis[0] + this->translation_axis[0];
    output.y = p.x * this->x_axis[1] + p.y * this->y_axis[1] + p.z * this->z_axis[1] + this->translation_axis[1];
    output.z = p.x * this->x_axis[2] + p.y * this->y_axis[2] + p.z * this->z_axis[2] + this->translation_axis[2];

    return output;
};

// pass holder for matrix inverse
Matrix Matrix::inverse()
{
    Matrix output(1.0);
    // step 1: set rows so pivot is not zero
    for (int col = 0; col < this->matrix[0].size(); col++)
    {
        if (this->matrix[col][col] == 0)
        {
            // search element in column with the largest absolute value and swap rows
            int row_largest = 0;
            for (int row = 0; row < this->matrix.size(); row++)
            {
                // if aboslute value if current row,col is larger than the largest seen so far, mark that as the current largest
                if (fabs(this->matrix[row][col]) > fabs(this->matrix[row_largest][col]))
                {
                    row_largest = row;
                }
            }

            if (row_largest == 0)
            {
                // return 0 matrix if not inverible
                return Matrix();
            }

            // swap original matrix rows
            std::swap(this->matrix[col], this->matrix[row_largest]);

            // swap output matrix values
            std::swap(output.matrix[col], output.matrix[row_largest]);
        }
    }

    // step 2: eliminate all number under the diagonal elements
    for (int col = 0; col < this->matrix[0].size(); col++)
    {
        for (int row = col + 1; row < this->matrix.size(); row++)
        {
            float k = -this->matrix[row][col] / this->matrix[col][col];
            for (int j = 0; j < this->matrix[row].size(); j++)
            {
                this->matrix[row][j] += k * this->matrix[col][j];
                output.matrix[row][j] += k * output.matrix[col][j];
            }
            this->matrix[row][col] = 0;
        }
    }

    // step 3: scale all pivot coefficents to 1
    for (int row = 0; row < this->matrix.size(); row++)
    {
        float divisor = this->matrix[row][row];
        for (int col = 0; col < this->matrix[0].size(); col++)
        {
            this->matrix[row][col] /= divisor;
            output.matrix[row][col] /= divisor;
        }
    }

    // step 4: eliminate numebrs above the diagonal
    for (int row = 0; row < this->matrix.size(); row++)
    {
        for (int col = row + 1; col < this->matrix[0].size(); col++)
        {
            float constant = this->matrix[row][col];
            for (int k = 0; k < this->matrix.size(); k++)
            {
                this->matrix[row][k] -= this->matrix[col][k] * constant;
                output.matrix[row][k] -= output.matrix[col][k] * constant;
            }
            this->matrix[row][col] = 0.f;
        }
    }

    // reset our x,y, and z axis
    this->x_axis = this->matrix[0];
    this->y_axis = this->matrix[1];
    this->z_axis = this->matrix[2];
    this->translation_axis = this->matrix[3];

    // reset our x,y,z, and translation axis
    output.x_axis = output.matrix[0];
    output.y_axis = output.matrix[1];
    output.z_axis = output.matrix[2];
    output.translation_axis = output.matrix[3];

    return output;
}

void Matrix::transpose()
{
    for (int i = 0; i < this->matrix.size(); i++)
    {
        for (int j = i + 1; j < this->matrix[0].size(); j++)
        {
            float tmp = this->matrix[i][j];
            this->matrix[i][j] = this->matrix[j][i];
            this->matrix[j][i] = tmp;
        }
    }

    this->x_axis = this->matrix[0];
    this->y_axis = this->matrix[1];
    this->z_axis = this->matrix[2];
    this->translation_axis = this->matrix[3];
}

void Matrix::print_values()
{
    for (int i = 0; i < this->matrix[0].size(); i++)
    {
        std::cout << this->matrix[i][0] << " " << this->matrix[i][1] << " " << this->matrix[i][2] << " " << this->matrix[i][3] << std::endl;
    }
}

Point Matrix::local2world(Point p)
{
    return this->vec_mul_mat(p);
}

Point Matrix::world2camera(Point p)
{
    return this->vec_mul_mat(p);
}