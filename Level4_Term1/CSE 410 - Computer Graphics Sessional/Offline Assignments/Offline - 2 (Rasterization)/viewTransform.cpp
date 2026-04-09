#include "modelingTransform.cpp"



namespace ViewTransform
{
    Matrix translateCameraMatrix(Vector3D eye){   // move camera to origin
        return ModelingTransform::getTranslationMatrix(eye * -1); 
    }



    Matrix rotateCameraMatrix(Vector3D eye, Vector3D look, Vector3D up){
        Vector3D l, r, u;
        l = (look - eye).normalize();
        r = (l.cross(up)).normalize();
        u = (r.cross(l)).normalize();

        if(r.magnitude() == 0 || u.magnitude() == 0 || l.magnitude() == 0) {
            printf("Error: Invalid camera orientation in ViewTransform::rotateCameraMatrix\n");
            exit(1);
        }

        return Matrix({{r.x, r.y, r.z, 0},    // align r with i
                       {u.x, u.y, u.z, 0},    // align u with j
                       {-l.x, -l.y, -l.z, 0}, // align l with -k
                       {0, 0, 0, 1}});
    }
};


