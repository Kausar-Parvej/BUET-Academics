#include "utils.cpp"
#include "vector3D.cpp"
#include "matrix.cpp"
#include "shapes.cpp"



namespace ModelingTransform{
    Matrix getTranslationMatrix(Vector3D t);
    Matrix getScalingMatrix(Vector3D s);
    Matrix getRotationMatrix(double degree, Vector3D axis);
    Matrix getIdentityMatrix();

    Vector3D transformPoint(Matrix mat, Vector3D point);
    Triangle transformTriangle(Matrix mat, Triangle triangle);
}






Matrix ModelingTransform :: getTranslationMatrix(Vector3D t) {
    return Matrix({{1, 0, 0, t.x},
                   {0, 1, 0, t.y},
                   {0, 0, 1, t.z},
                   {0, 0, 0, 1}});
}

Matrix ModelingTransform :: getScalingMatrix(Vector3D s) {
    return Matrix({{s.x, 0, 0, 0},
                   {0, s.y, 0, 0},
                   {0, 0, s.z, 0},
                   {0, 0, 0, 1}});
}

Matrix ModelingTransform :: getRotationMatrix(double degree, Vector3D axis) {
    axis = axis.normalize();
    Vector3D i(1.0, 0.0, 0.0), j(0.0, 1.0, 0.0), k(0.0, 0.0, 1.0);
    Vector3D c1 = i.rotate(axis, radians(degree));
    Vector3D c2 = j.rotate(axis, radians(degree));
    Vector3D c3 = k.rotate(axis, radians(degree));

    return Matrix({{c1.x, c2.x, c3.x, 0},
                   {c1.y, c2.y, c3.y, 0},
                   {c1.z, c2.z, c3.z, 0},
                   {0, 0, 0, 1}});
}

Matrix ModelingTransform :: getIdentityMatrix() {
    Matrix identity_matrix(4, 4);
    identity_matrix.identity();
    return identity_matrix;
}


Vector3D ModelingTransform :: transformPoint(Matrix mat, Vector3D point) {
    vector<vector<double>> homogeneous_coords = {{point.x},
                                                 {point.y},
                                                 {point.z},
                                                 {1.0}};

    Matrix h(homogeneous_coords);
    Matrix t = mat * h;
    Vector3D transformed_point(t.data[0][0] / t.data[3][0], 
                            t.data[1][0] / t.data[3][0], 
                            t.data[2][0] / t.data[3][0]);
    return transformed_point;
}


Triangle ModelingTransform :: transformTriangle(Matrix mat, Triangle triangle) {
    for (Vector3D &v : triangle.vertices) {
        v = ModelingTransform::transformPoint(mat, v);
    }
    return triangle;
}
