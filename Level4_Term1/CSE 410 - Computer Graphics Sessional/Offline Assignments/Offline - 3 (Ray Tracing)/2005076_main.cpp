#include "2005076_headers.h"

const string io_dir = "io_files/";
string INPUT_FILE = io_dir + "scene.txt";
string TEXTURE_FILE = io_dir + "texture1.jpg";

Camera *camera = new Camera();
Floor *floorObject = nullptr;

vector<Object *> objects;
vector<PointLight *> pointLights;
vector<SpotLight *> spotLights;

int recursionLevel;
int imageHeight, imageWidth;

ostream &operator<<(ostream &os, const Vec3D &v){
    os << fixed << setprecision(7);
    os << v.x << ' ' << v.y << ' ' << v.z;
    os << std::resetiosflags(ios_base::fixed);
    return os;
}
istream &operator>>(istream &is, Vec3D &v){
    is >> v.x >> v.y >> v.z;
    return is;
}
ostream &operator<<(ostream &os, const Color &c){
    os << fixed << setprecision(7);
    os << c.r << ' ' << c.g << ' ' << c.b;
    os << std::resetiosflags(ios_base::fixed);
    return os;
}
istream &operator>>(istream &is, Color &c){
    is >> c.r >> c.g >> c.b;
    return is;
}
ostream &operator<<(ostream &os, const Triangle &t){
    for (Vec3D v : t.vertices)
    {
        os << v << endl;
    }
    return os;
}
istream &operator>>(istream &is, Triangle &t){
    for (Vec3D &v : t.vertices)
    {
        is >> v;
    }
    is >> t.color.r >> t.color.g >> t.color.b; // color
    for (double &c : t.materialCoefficients)
    {
        is >> c;
    }
    is >> t.shine;
    return is;
}
ostream &operator<<(ostream &os, const Sphere &s){
    // for (Vec3D v : t.vertices)
    // {
    //     os << v << endl;
    // }
    return os;
}
istream &operator>>(istream &is, Sphere &s){
    is >> s.reference_point >> s.length;       // center and radius
    is >> s.color.r >> s.color.g >> s.color.b; // color
    for (double &c : s.materialCoefficients){
        is >> c;
    }
    is >> s.shine;
    return is;
}
ostream &operator<<(ostream &os, const General &g){
    // for (Vec3D v : t.vertices)
    // {
    //     os << v << endl;
    // }
    return os;
}
istream &operator>>(istream &is, General &g){
    is >> g.A >> g.B >> g.C >> g.D >> g.E >> g.F >> g.G >> g.H >> g.I >> g.J;
    is >> g.reference_point >> g.length >> g.width >> g.height;
    is >> g.color.r >> g.color.g >> g.color.b; // color
    for (double &c : g.materialCoefficients){
        is >> c;
    }
    is >> g.shine;
    return is;
}

void loadData(){
    ifstream fin;
    fin.open(INPUT_FILE);

    fin >> recursionLevel >> imageHeight;

    imageWidth = imageHeight;

    int objectCount;
    fin >> objectCount;

    Object *object;

    cout << "Loading " << objectCount << " objects..." << endl;

    for (int i = 0; i < objectCount; i++){
        string type;
        fin >> type;

        if (type == "triangle"){
            vector<Vec3D> vertices(3);
            for (int j = 0; j < 3; j++){
                fin >> vertices[j];
            }
            object = new Triangle(vertices);
        }
        else if (type == "sphere"){
            Vec3D center;
            double radius;
            fin >> center >> radius;
            object = new Sphere(center, radius);
        }
        else if (type == "general"){
            vector<double> coefficients;
            for (int i = 0; i < 10; i++)
            {
                double c;
                fin >> c;
                coefficients.push_back(c);
            }
            Vec3D reference_point;
            double length, width, height;
            fin >> reference_point >> length >> width >> height;
            object = new General(reference_point, length, width, height, coefficients);
        }

        Color color;
        fin >> color;
        object->setColor(color);
        vector<double> coefficients;
        for (int i = 0; i < 4; i++){
            double c;
            fin >> c;
            coefficients.push_back(c);
        }
        object->setMaterialCoefficients(coefficients);
        int shine;
        fin >> shine;
        object->setShine(shine);
        objects.push_back(object);
    }

    // Point Lights
    int pointLightCount;
    fin >> pointLightCount;
    for (int i = 0; i < pointLightCount; i++){
        Vec3D position;
        Color color;
        fin >> position >> color;
        PointLight *pointLight = new PointLight(position, color);
        pointLights.push_back(pointLight);
    }

    // Spot Lights
    int spotlightCount;
    fin >> spotlightCount;
    for (int i = 0; i < spotlightCount; i++){
        Vec3D position;
        Color color;
        fin >> position >> color;
        Vec3D direction;
        double angle;
        fin >> direction >> angle;
        SpotLight *spotLight = new SpotLight(PointLight(position, color), direction, angle);
        spotLights.push_back(spotLight);
    }

    // Floor
    Floor *floor = new Floor(1000, 20);
    floor->setColor(Color(0.5, 0.5, 0.5));
    floor->setMaterialCoefficients({0.4, 0.2, 0.2, 0.2});
    floor->setShine(10);
    
    // Try to load texture (you can change this filename)
    floor->loadTexture(TEXTURE_FILE);
    floor->setUseTexture(true); // Set to false for checkerboard
    
    floorObject = floor; // Store reference for texture toggling
    objects.push_back(floor);
}

int imageCount = 1;
void capture(){
    cout << "Capturing Image" << endl;
    
    bitmap_image image(imageWidth, imageHeight);

    double planeDistance = GraphicsManager::nearPlane;
    double windowHeight = 2.0 * tan(radians(GraphicsManager::viewAngle / 2.0)) * planeDistance;
    double windowWidth = windowHeight;

    Vec3D topleft = camera->pos + (camera->look * planeDistance) - (camera->right * (windowWidth / 2.0)) +
                    (camera->up * (windowHeight / 2.0));

    double du = windowWidth / imageWidth;
    double dv = windowHeight / imageHeight;

    topleft = topleft + (camera->right * du / 2.0) - (camera->up * dv / 2.0);

    const int objectCount = objects.size();
    Ray ray(Vec3D(0,0,0), Vec3D(0,0,1));
    Color color;

    for (int i = 0; i < imageWidth; i++){
        if(i % 100 == 0) {
            cout << "Progress: " << (100.0 * i / imageWidth) << "%" << endl;
        }
        
        for (int j = 0; j < imageHeight; j++){
            Vec3D currentPixel = topleft + (camera->right * (du * i)) - (camera->up * (dv * j));
            Vec3D ray_dir = (currentPixel - camera->pos).normalize();
            
            ray.start = camera->pos;
            ray.dir = ray_dir;

            double minT = -1;
            int nearest = -1;
            
            for (int k = 0; k < objectCount; k++){
                double t = objects[k]->findIntersection(&ray);
                if (t > 0 && (nearest == -1 || t < minT)){
                    minT = t;
                    nearest = k;
                }
            }

            if (nearest != -1){
                color.r = color.g = color.b = 0.0;
                objects[nearest]->intersect(&ray, &color, 1);
                
                image.set_pixel(i, j, 
                    (int)(255 * max(0.0, min(1.0, color.r))), 
                    (int)(255 * max(0.0, min(1.0, color.g))), 
                    (int)(255 * max(0.0, min(1.0, color.b))));
            }
        }
    }
    
    string filename = io_dir + "captured_" + to_string(imageCount++) + ".bmp";
    cout << "Saving Image: " << filename << endl;
    image.save_image(filename);
    cout << "Image saved successfully: " << filename << endl;
}
int current_id = 0;
void update(int time){
    glutTimerFunc(time, update, time);
}

void GraphicsManager::display()
{
    camera->set();
    // GraphicsManager::drawAxis();

    for (Object *o : objects){
        o->draw();
    }

    for (PointLight *l : pointLights){
        l->draw();
    }

    for (SpotLight *l : spotLights){
        l->draw();
    }
}

void GraphicsManager::init(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    loadData();
}

void GraphicsManager::keyboard(unsigned char key){
    camera->keyPress(key);
    switch (key)
    {
    case ' ':
        capture();
        break;
    case 't':
    case 'T':
        if (floorObject) {
            bool currentState = floorObject->isUsingTexture();
            floorObject->setUseTexture(!currentState);
            cout << "Floor texture " << (floorObject->isUsingTexture() ? "enabled" : "disabled") << endl;
        }
        break;
    }
}

void GraphicsManager::specialKeyboard(int key){
    camera->specialKeyPress(key);
}

void GraphicsManager::mouseScroll(int dir){
    camera->mouseScroll(dir);
}

void destructor(){
    for (Object *o : objects){
        delete o;
    }
    objects.clear();
    objects.shrink_to_fit();

    for (PointLight *l : pointLights){
        delete l;
    }
    pointLights.clear();
    pointLights.shrink_to_fit();

    for (SpotLight *l : spotLights){
        delete l;
    }
    spotLights.clear();
    spotLights.shrink_to_fit();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutTimerFunc(10, update, 10);
    char title[] = "Ray Tracing";
    GraphicsManager::initialize(700, 600, title, 3);
    //return 0;
    glutMainLoop();
    destructor();
    return 0;
}