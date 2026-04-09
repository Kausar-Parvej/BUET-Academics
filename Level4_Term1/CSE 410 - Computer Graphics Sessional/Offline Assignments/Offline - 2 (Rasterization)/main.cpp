#include <bits/stdc++.h>
#include "bitmap_image.hpp"
#include "viewTransform.cpp"
#include "rasterization.cpp"

using namespace std;


static string file_dir = "io_files/";
ifstream fin, fin2;
ofstream fout;

Vector3D eye, look, up;
double fov_y, aspect_ratio, z_near, z_far;


void stage1(); // Modeling Transformation
void stage2(); // viewing Transformation
void stage3(); // Projection Transformation
void stage4(); // Rasterization




int main(){
    fin.open(file_dir + "scene.txt");
    fout.open(file_dir + "stage1.txt");

    fin >> eye >> look >> up;
    fin >> fov_y >> aspect_ratio >> z_near >> z_far;
    stage1(); 
    fin.close();
    fout.close();


    fin.open(file_dir + "stage1.txt");
    fout.open(file_dir + "stage2.txt");
    stage2();
    fin.close();
    fout.close();


    fin.open(file_dir + "stage2.txt");
    fout.open(file_dir + "stage3.txt");
    stage3();
    fin.close();
    fout.close();



    fin.open(file_dir + "stage3.txt");
    fin2.open(file_dir + "config.txt");
    fout.open(file_dir + "z_buffer.txt");
    stage4();
    fin.close();
    fin2.close();
    fout.close();

    cout<<"\n-------------------------------------------------------------------//\n";
    cout << "All stages completed successfully. Output files generated.\n";
    cout << "Output files:\n";
    cout << file_dir + "stage1.txt\n";
    cout << file_dir + "stage2.txt\n";
    cout << file_dir + "stage3.txt\n";
    cout << file_dir + "z_buffer.txt\n";
    cout << file_dir + "out.bmp\n";
    cout << "-------------------------------------------------------------------//\n";
    

    return 0;
}

//------------------------------------------------------------------//






void stage1() {
    using namespace ModelingTransform;

    stack<Matrix> matrix_stack;
    Matrix mat(getIdentityMatrix());

    string command;
    while (fin >> command) {
        if (command == "triangle") {
            Triangle T;
            fin >> T;
            fout << transformTriangle(mat, T) << "\n";
        } 
        else if (command == "translate") {
            Vector3D t;
            fin >> t;
            mat *= getTranslationMatrix(t);
        } 
        else if (command == "scale") {
            Vector3D s;
            fin >> s;
            mat *= getScalingMatrix(s);
        } 
        else if (command == "rotate") {
            double degree;
            fin >> degree;
            Vector3D axis;
            fin >> axis;
            mat *= getRotationMatrix(degree, axis);
        } 
        else if (command == "push") {
            matrix_stack.push(mat);
        } 
        else if (command == "pop") {
            mat = matrix_stack.top();
            matrix_stack.pop();
        } 
        else if (command == "end") {
            break;
        }
    }

}


void stage2() {
    using namespace ViewTransform;

    Matrix T = translateCameraMatrix(eye);
    Matrix R = rotateCameraMatrix(eye, look, up);
    Matrix V = R * T;

    Triangle triangle;
    while (fin >> triangle) {
        fout << ModelingTransform::transformTriangle(V, triangle) << "\n";
    }
}


void stage3() {
    double fov_x = fov_y * aspect_ratio;
    double t = z_near * tan(radians(fov_y / 2));  //half-height of the near plane
    double r = z_near * tan(radians(fov_x / 2));  //half-width of the near plane


    //transforms frustum into a normalized cube
    Matrix P({  
        {z_near / r, 0, 0, 0},
        {0, z_near / t, 0, 0},
        {0, 0, -(z_far + z_near) / (z_far - z_near), -(2 * z_far * z_near) / (z_far - z_near)},
        {0, 0, -1, 0}
    });

    Triangle triangle;
    while (fin >> triangle) {
        fout << ModelingTransform::transformTriangle(P, triangle) << "\n";
    }
}


void stage4() {
    using namespace Rasterization;

    int screen_width, screen_height;
    double left_limit, right_limit, bottom_limit, top_limit, z_front_limit, z_back_limit;
    fin2 >> screen_width >> screen_height;
    fin2 >> left_limit >> bottom_limit >> z_front_limit >> z_back_limit;
    right_limit = -left_limit;
    top_limit = -bottom_limit;


    double dx = (right_limit - left_limit) / screen_width;   //width of each pixel
    double dy = (top_limit - bottom_limit) / screen_height;  //height of each pixel
    double top_y = top_limit - dy / 2;                       //y-coordinate of the top row
    double bottom_y = bottom_limit + dy / 2;                 //y-coordinate of the bottom row
    double left_x = left_limit + dx / 2;                     //x-coordinate of the left column
    double right_x = right_limit - dx / 2;                   //x-coordinate of the right column
    double max_z = z_back_limit;                             //maximum z value for the back plane


    vector<vector<double>> z_buffer(screen_height, vector<double>(screen_width, max_z));
    bitmap_image image(screen_width, screen_height);
    image.set_all_channels(0, 0, 0);


    vector<Vector3D> vertices(3);
    while(fin >> vertices[0] >> vertices[1] >> vertices[2]) {
        Triangle triangle(vertices);
        triangle.fillColor();

        int topRow = getTopRow(vertices, top_y, dy);
        int bottomRow = getBottomRow(vertices, top_y, bottom_y, dy);

        for (int rowNum = topRow; rowNum <= bottomRow; rowNum++) {
            double ys = top_y - rowNum * dy;  //y-coordinate of the current scanline
            vector<Vector3D> intersections = findIntersectingPoints(triangle, ys);
            if (intersections.empty()) continue;  //no valid intersections

            double x1 = intersections[0].x;
            double z1 = intersections[0].z;
            double x2 = intersections[1].x;
            double z2 = intersections[1].z;
            if (x1 > x2) {
                swap(x1, x2);
                swap(z1, z2);
            }

            x1 = max(x1, left_x);
            x2 = min(x2, right_x);
            int left_col = round((x1 - left_x) / dx);
            int right_col = round((x2 - left_x) / dx);

            for (int colNum = left_col; colNum <= right_col; colNum++) {
                double x_p = left_x + colNum * dx;
                double z_p = z1 - (z1 - z2) * ((x1 - x_p) / (x1 - x2));

                if (z_p < z_buffer[rowNum][colNum] && z_p >= z_front_limit) {
                    z_buffer[rowNum][colNum] = z_p;
                    image.set_pixel(colNum, rowNum, triangle.color.r, triangle.color.g, triangle.color.b);
                }
            }
        }
    }

    image.save_image(file_dir + "out.bmp");
    fout << fixed << setprecision(6);
    for (int i = 0; i < screen_height; i++) {
        for (int j = 0; j < screen_width; j++) {
            if(z_buffer[i][j] < max_z) fout << z_buffer[i][j] << "\t";            
        }
        fout << "\n";
    }
    fout << std::resetiosflags(ios_base::fixed);
    z_buffer.clear();
    image.clear();
    z_buffer.shrink_to_fit();
}

