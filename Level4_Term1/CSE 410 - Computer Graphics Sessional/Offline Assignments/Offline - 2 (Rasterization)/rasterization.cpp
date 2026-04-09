#include <vector>
#include "Vector3D.cpp"
#include "shapes.cpp"

using namespace std;

namespace Rasterization {
    int getTopRow(vector<Vector3D> vertices, double top_y, double dy);
    int getBottomRow(vector<Vector3D> vertices, double top_y, double bottom_y, double dy);
    vector<Vector3D> findIntersectingPoints(Triangle t, double ys);  
};



int Rasterization::getTopRow(vector<Vector3D> vertices, double top_y, double dy) {
    double max_y = max(vertices[0].y, max(vertices[1].y, vertices[2].y));
    max_y = min(max_y, top_y);
    int top_row = static_cast<int>(round((top_y - max_y) / dy)); 
    return top_row;
}


int Rasterization::getBottomRow(vector<Vector3D> vertices, double top_y, double bottom_y, double dy) {
    double min_y = min(vertices[0].y, min(vertices[1].y, vertices[2].y));
    min_y = max(min_y, bottom_y);
    int bottom_row = static_cast<int>(round((top_y - min_y) / dy)); 
    return bottom_row;
}


vector<Vector3D> Rasterization::findIntersectingPoints(Triangle t, double ys) {  //ys => y-coordinate of the scanline
    vector<Vector3D> intersections;
    for (int i = 0; i < 3; i++) {
        int j = (i + 1) % 3;

        double x1 = t.vertices[i].x, y1 = t.vertices[i].y, z1 = t.vertices[i].z;
        double x2 = t.vertices[j].x, y2 = t.vertices[j].y, z2 = t.vertices[j].z;

        if (abs(y1 - y2) < 1e-9) { // Edge parallel to x axis
            // If the edge is horizontal (constant y), it won’t intersect a horizontal scanline at any unique point
        } 
        else if (ys >= min(y1, y2) && ys <= max(y1, y2)) { // check if intersects triangle edges
            double x = x1 - (x1 - x2) * (y1 - ys) / (y1 - y2);   // Interpolate intersection point
            double z = z1 - (z1 - z2) * (y1 - ys) / (y1 - y2);   // (x1-x)/(y1-ys)=(x1-x2)/(y1-y2)
            intersections.push_back(Vector3D(x, ys, z));
        }
    }
    return intersections;
}