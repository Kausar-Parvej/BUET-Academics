#define STB_IMAGE_IMPLEMENTATION
#include "2005076_headers.h"


//------------------Vec3D class------------------------//


Vec3D::Vec3D() : x(0), y(0), z(0) {}
Vec3D::Vec3D(double x, double y, double z) : x(x), y(y), z(z) {}
Vec3D::Vec3D(const Vec3D &p) : x(p.x), y(p.y), z(p.z) {}

Vec3D Vec3D::operator+(const Vec3D &b) const { return Vec3D(x + b.x, y + b.y, z + b.z); }
Vec3D Vec3D::operator+=(Vec3D b){
    *this = *this + b;
    return *this;
}
Vec3D Vec3D::operator-(const Vec3D &b) const { return Vec3D(x - b.x, y - b.y, z - b.z); }
Vec3D Vec3D::operator-=(Vec3D b){
    this->x -= b.x;
    this->y -= b.y;
    this->z -= b.z;
    return *this;
}
Vec3D Vec3D::operator-(){
    return Vec3D(-x, -y, -z);
}
Vec3D Vec3D::operator*(double b) const { return Vec3D(x * b, y * b, z * b); }
Vec3D Vec3D::operator*=(Vec3D b){
    this->x *= b.x;
    this->y *= b.y;
    this->z *= b.z;
    return *this;
}
Vec3D Vec3D::operator/(double b) { return Vec3D(x / b, y / b, z / b); }
Vec3D Vec3D::operator/=(Vec3D b){
    this->x /= b.x;
    this->y /= b.y;
    this->z /= b.z;
    return *this;
}
Vec3D Vec3D::operator/(Vec3D b) { return Vec3D(x / b.x, y / b.y, z / b.y); }
Vec3D Vec3D::operator*(const Vec3D &b) const { return Vec3D(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x); }




double dot(Vec3D a, Vec3D b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
double dot2D(Vec3D a, Vec3D b) { return a.x * b.x + a.y * b.y; }
void printPT(Vec3D a) { printf("(%lf,%lf,%lf)\n", a.x, a.y, a.z); }
double Vec3D::dot(const Vec3D &b) const{
    return x * b.x + y * b.y + z * b.z;
}
Vec3D Vec3D::perpRotate(Vec3D axis, double radian){ // Counter Clock
    Vec3D l = *this;
    Vec3D r = axis.normalize();
    return l * cos(radian) + (r * l) * sin(radian);
}
Vec3D Vec3D::rotate(Vec3D axis, double radian){ // Counter Clock
    return *this * cos(radian) + axis * (1 - cos(radian)) * this->dot(axis) + (axis * *this) * sin(radian);
}

double Vec3D::magnitude(){
    return sqrt(this->dot(*this));
}
Vec3D Vec3D::normalize(){
    return *this / this->magnitude();
}
double Vec3D::angle(Vec3D b){
    double magA = this->magnitude();
    double magB = b.magnitude();

    if (magA == 0.0 || magB == 0.0)
    {
        return NAN;
    }

    double cosTheta = this->dot(b) / (magA * magB);
    return acos(max(-1.0, min(1.0, cosTheta)));
}


//--------------------Vec2D class------------------------//



Vec2D::Vec2D() : Vec3D() {}
Vec2D::Vec2D(double x, double y) : Vec3D(x, y, 0) {}
Vec2D::Vec2D(const Vec2D &p) : Vec3D(p.x, p.y, 0) {}



Vec2D Vec2D::operator+(Vec2D b) { return Vec2D(x + b.x, y + b.y); }
Vec2D Vec2D::operator+=(Vec2D b){
    *this = *this + b;
    return *this;
}
Vec2D Vec2D::operator-(Vec2D b) { return Vec2D(x - b.x, y - b.y); }
Vec2D Vec2D::operator-(){
    return *this * (-1);
}
Vec2D Vec2D::operator-=(Vec2D b){
    this->x -= b.x;
    this->y -= b.y;
    this->z -= b.z;
    return *this;
}
Vec2D Vec2D::operator*(double b) { return Vec2D(x * b, y * b); }

Vec2D Vec2D::operator/(double b) { return Vec2D(x / b, y / b); }
Vec2D Vec2D::operator/=(Vec2D b){
    this->x /= b.x;
    this->y /= b.y;
    this->z /= b.z;
    return *this;
}
Vec2D Vec2D::operator/(Vec2D b) { return Vec2D(x / b.x, y / b.y); }
double Vec2D::dot(Vec2D b){
    return x * b.x + y * b.y;
}

bool Vec2D::operator==(Vec2D b){
    return x == b.x && y == b.y;
}

double Vec2D::magnitude(){
    return sqrt(this->dot(*this));
}
Vec2D Vec2D::normalize(){
    return *this / magnitude();
}
Vec2D Vec2D::perp(){
    return Vec2D(-y, x);
}
Vec2D Vec2D::rotate(double radian){
    Vec2D v_perp = this->perp();
    return *this * cos(radian) + v_perp * sin(radian);
}

Vec2D Vec2D::reflect(Vec2D r){
    Vec2D n = r.perp().normalize();
    return *this - n * 2 * this->dot(n);
}
double Vec2D::angle(Vec2D b){
    double magA = this->magnitude();
    double magB = b.magnitude();

    if (magA == 0.0 || magB == 0.0)
    {
        return NAN;
    }

    double cosTheta = this->dot(b) / (magA * magB);
    return acos(max(-1.0, min(1.0, cosTheta)));
}



//--------------------Matrix class------------------------//


Matrix::Matrix(int n_rows, int n_cols){
    data = vector<vector<double>>(n_rows, vector<double>(n_cols));
    for (int i = 0; i < n_rows; ++i)
    {
        for (int j = 0; j < n_cols; ++j)
        {
            data[i][j] = 0.0;
        }
    }
}
Matrix::Matrix(vector<vector<double>> data){
    this->data = data;
}

Matrix::~Matrix(){
    // Destructor does not need to do anything special for vector
    // since it will automatically clean up the memory.
}




void Matrix::identity(){
    for (int i = 0; i < 4; i++)
    {
        data[i][i] = 1.0;
    }
}

Matrix Matrix::operator*(const Matrix &other) const{
    if (this->data[0].size() != other.data.size())
    {
        __throw_invalid_argument("Matrix multiplication error: Incompatible matrix dimensions");
    }

    size_t n_rows = this->data.size();
    size_t n_cols = other.data[0].size();

    Matrix result(n_rows, n_cols);

    for (int i = 0; i < n_rows; ++i)
    {
        for (int j = 0; j < n_cols; ++j)
        {
            for (int k = 0; k < this->data[0].size(); ++k)
            {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

Matrix Matrix::operator*=(const Matrix &other){
    (*this) = (*this) * other;
    return *this;
}

double Matrix::determinant(){
    if (data.size() != data[0].size()){
        __throw_invalid_argument("Matrix determinant error: Matrix is not square");
    }
    if (data.size() == 1){
        return data[0][0];
    }
    if (data.size() == 2){
        return data[0][0] * data[1][1] - data[0][1] * data[1][0];
    }
    if (data.size() == 3){
        return data[0][0] * (data[1][1] * data[2][2] - data[1][2] * data[2][1]) - data[0][1] * (data[1][0] * data[2][2] - data[1][2] * data[2][0]) + data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);
    }
    double det = 0;
    for (int i = 0; i < data.size(); i++){
        vector<vector<double>> submatrix(data.size() - 1, vector<double>(data.size() - 1));
        for (int j = 1; j < data.size(); j++)
        {
            for (int k = 0; k < data.size(); k++)
            {
                if (k < i)
                {
                    submatrix[j - 1][k] = data[j][k];
                }
                else if (k > i)
                {
                    submatrix[j - 1][k - 1] = data[j][k];
                }
            }
        }
        det += (i % 2 == 0 ? 1 : -1) * data[0][i] * Matrix(submatrix).determinant();
    }
    return det;
}

double Matrix::determinant(vector<vector<double>> data)
{
    if (data.size() != data[0].size()){
        __throw_invalid_argument("Matrix determinant error: Matrix is not square");
    }
    if (data.size() == 1){
        return data[0][0];
    }
    if (data.size() == 2){
        return data[0][0] * data[1][1] - data[0][1] * data[1][0];
    }
    if (data.size() == 3){
        return data[0][0] * (data[1][1] * data[2][2] - data[1][2] * data[2][1]) - data[0][1] * (data[1][0] * data[2][2] - data[1][2] * data[2][0]) + data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);
    }
    double det = 0;
    for (int i = 0; i < data.size(); i++){
        vector<vector<double>> submatrix(data.size() - 1, vector<double>(data.size() - 1));
        for (int j = 1; j < data.size(); j++){
            for (int k = 0; k < data.size(); k++){
                if (k < i){
                    submatrix[j - 1][k] = data[j][k];
                }
                else if (k > i){
                    submatrix[j - 1][k - 1] = data[j][k];
                }
            }
        }
        det += (i % 2 == 0 ? 1 : -1) * data[0][i] * Matrix::determinant(submatrix);
    }
    return det;
}

//---------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------//






//----------------------Ray class------------------------//

Ray::Ray(){
    start = Vec3D(0, 0, 0);
    dir = Vec3D(0, 0, 0);
}

Ray::Ray(Vec3D start, Vec3D dir){
    this->start = start;
    this->dir = dir.normalize();
}






//-------------------------------Color class----------------------//

static unsigned long int g_seed = 76;
inline int rand()
{
    g_seed = (214013 * g_seed + 2531011);
    return (g_seed >> 16) & 0x7FFF;
}


Color::Color(){
    r = 0;
    g = 0;
    b = 0;
}

Color::Color(double r, double g, double b){
    this->r = r;
    this->g = g;
    this->b = b;
}

Color Color::operator*(double mul){
    Color temp;
    temp.r = r * mul;
    temp.g = g * mul;
    temp.b = b * mul;
    return temp;
}
Color Color::operator*(const Color &c){
    Color temp;
    temp.r = r * c.r;
    temp.g = g * c.g;
    temp.b = b * c.b;
    return temp;
}
Color Color::operator+=(const Color &c){
    r += c.r;
    g += c.g;
    b += c.b;
    return *this;
}
void Color::randomize(){
    r = rand() / 32767.0;
    g = rand() / 32767.0;
    b = rand() / 32767.0;
}




//-----------------------------PointLight class----------------------//

PointLight::PointLight(){
    light_pos = Vec3D(0, 0, 0);
    color = Color(1, 1, 1);
}

PointLight::PointLight(Vec3D pos, Color c){
    light_pos = pos;
    color = c;
}

void PointLight::draw(){
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(color.r, color.g, color.b);
    glVertex3f(light_pos.x, light_pos.y, light_pos.z);
    glEnd();
}



//-----------------------------SpotLight class----------------------//

SpotLight::SpotLight(PointLight pointLight, Vec3D direction, double angle){
    point_light = new PointLight(pointLight);
    light_direction = direction;
    cutoff_angle = angle;
}

SpotLight::~SpotLight(){
    delete point_light;
}

void SpotLight::draw(){
    Color color = point_light->color;
    Vec3D pos = point_light->light_pos;

    glPointSize(15);
    glBegin(GL_POINTS);
    glColor3f(color.r, color.g, color.b);
    glVertex3f(pos.x, pos.y, pos.z);
    glEnd();
}




//--------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------//







//-----------------------------Object class----------------------//

Object::Object(){
    reference_point = Vec3D(0, 0, 0);
    height = 0;
    width = 0;
    length = 0;
    shine = 0;
}

Object::~Object(){
    materialCoefficients.clear();
    materialCoefficients.shrink_to_fit();
}

void Object::setColor(Color c){
    color = c;
}

void Object::setShine(int s){
    shine = s;
}

void Object::setMaterialCoefficients(vector<double> materialCoefficients){
    this->materialCoefficients = materialCoefficients;
}

Color Object::getColorAt(Vec3D point){
    return color;
}

extern vector<Object *> objects;
extern vector<PointLight *> pointLights;
extern vector<SpotLight *> spotLights;
extern int recursionLevel;

bool isPointInShadow(Vec3D point, Vec3D lightPos){
    Vec3D dir = (lightPos - point).normalize();
    double distance = (lightPos - point).magnitude();
    Ray lightRay(point + dir * 1e-5, dir);
    
    for (Object *obj : objects){
        double t = obj->findIntersection(&lightRay);
        if (t > 1e-5 && t < distance - 1e-5){
            return true;
        }
    }
    return false;
}

void Object::colorSurface(PointLight *pl, Color *color, Vec3D surfacePoint, Color *surfaceColor, Ray *viewRay){
    double t2 = (surfacePoint - pl->light_pos).magnitude();
    if (t2 < 1e-5){
        return;
    }

    if (!isPointInShadow(surfacePoint, pl->light_pos)){
        Vec3D lightDir = (surfacePoint - pl->light_pos).normalize();
        Ray normal = this->getNormal(surfacePoint, viewRay);
        
        double lambertValue = max(0.0, -normal.dir.dot(lightDir));
        if (lambertValue > 0){
            color->r += pl->color.r * surfaceColor->r * materialCoefficients[1] * lambertValue;
            color->g += pl->color.g * surfaceColor->g * materialCoefficients[1] * lambertValue;
            color->b += pl->color.b * surfaceColor->b * materialCoefficients[1] * lambertValue;

            Vec3D reflectedDir = lightDir - normal.dir * 2 * (normal.dir.dot(lightDir));
            double phongValue = max(0.0, -viewRay->dir.dot(reflectedDir));
            if (phongValue > 0){
                double specular = pow(phongValue, shine);
                color->r += pl->color.r * surfaceColor->r * materialCoefficients[2] * specular;
                color->g += pl->color.g * surfaceColor->g * materialCoefficients[2] * specular;
                color->b += pl->color.b * surfaceColor->b * materialCoefficients[2] * specular;
            }
        }
    }
}

void Object::colorSpotLight(PointLight *pl, Color *color, Vec3D surfacePoint, Color *surfaceColor, Ray *viewRay, double beta){
    double t2 = (surfacePoint - pl->light_pos).magnitude();
    if (t2 < 1e-5){
        return;
    }

    if (!isPointInShadow(surfacePoint, pl->light_pos)){
        Vec3D lightDir = (surfacePoint - pl->light_pos).normalize();
        Ray normal = this->getNormal(surfacePoint, viewRay);
        
        double lambertValue = max(0.0, -normal.dir.dot(lightDir));
        if (lambertValue > 0){
            double attenuation = pow(beta, 0.1);
            color->r += pl->color.r * surfaceColor->r * materialCoefficients[1] * lambertValue * attenuation;
            color->g += pl->color.g * surfaceColor->g * materialCoefficients[1] * lambertValue * attenuation;
            color->b += pl->color.b * surfaceColor->b * materialCoefficients[1] * lambertValue * attenuation;

            Vec3D reflectedDir = lightDir - normal.dir * 2 * (normal.dir.dot(lightDir));
            double phongValue = max(0.0, -viewRay->dir.dot(reflectedDir));
            if (phongValue > 0){
                double specular = pow(phongValue, shine) * attenuation;
                color->r += pl->color.r * surfaceColor->r * materialCoefficients[2] * specular;
                color->g += pl->color.g * surfaceColor->g * materialCoefficients[2] * specular;
                color->b += pl->color.b * surfaceColor->b * materialCoefficients[2] * specular;
            }
        }
    }
}
double Object::intersect(Ray *viewRay, Color *color, int level){
    double tmin = this->findIntersection(viewRay);
    if (tmin < 0)
        return -1;
    if (level == 0){
        return tmin;
    }
    
    Vec3D intersectionPoint = viewRay->start + viewRay->dir * tmin;
    Color intersectionPointColor = this->getColorAt(intersectionPoint);

    color->r = intersectionPointColor.r * materialCoefficients[0];
    color->g = intersectionPointColor.g * materialCoefficients[0];
    color->b = intersectionPointColor.b * materialCoefficients[0];

    for (PointLight *pointLight : pointLights){
        colorSurface(pointLight, color, intersectionPoint, &intersectionPointColor, viewRay);
    }

    for (SpotLight *spotLight : spotLights){
        Vec3D dir = (intersectionPoint - spotLight->point_light->light_pos).normalize();
        double angle = acos(max(-1.0, min(1.0, spotLight->light_direction.dot(dir))));
        if (degrees(angle) < spotLight->cutoff_angle){
            colorSpotLight(spotLight->point_light, color, intersectionPoint, &intersectionPointColor, viewRay, spotLight->light_direction.dot(dir));
        }
    }

    if (level < recursionLevel && materialCoefficients[3] > 1e-3){
        Ray normal = this->getNormal(intersectionPoint, viewRay);
        Vec3D reflectedRayDir = viewRay->dir - normal.dir * 2 * (viewRay->dir.dot(normal.dir));
        Ray reflectedRay(intersectionPoint + reflectedRayDir * 1e-5, reflectedRayDir);

        double tmin_refl = -1;
        int nearest = -1;
        for (int k = 0; k < objects.size(); k++){
            double t = objects[k]->findIntersection(&reflectedRay);
            if (t > 0 && (nearest == -1 || t < tmin_refl)){
                tmin_refl = t;
                nearest = k;
            }
        }
        if (nearest != -1){
            Color colorReflected;
            objects[nearest]->intersect(&reflectedRay, &colorReflected, level + 1);

            color->r += colorReflected.r * materialCoefficients[3];
            color->g += colorReflected.g * materialCoefficients[3];
            color->b += colorReflected.b * materialCoefficients[3];
        }
    }
    return tmin;
}



//----------------------------Triangle class----------------------//

Triangle::Triangle() : vertices(vector<Vec3D>(3)){
    materialCoefficients = vector<double>(4);
}

Triangle::Triangle(vector<Vec3D> vertices) : vertices(vertices){
    materialCoefficients = vector<double>(4);
}
void Triangle::fillColor(){
    color.randomize();
}

void Triangle::draw(){
    glBegin(GL_TRIANGLES);
    glColor3f(color.r, color.g, color.b);
    for (int i = 0; i < 3; i++)
    {
        glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
    }
    glEnd();
}


double Triangle::findIntersection(Ray *ray){
    Vec3D v0 = vertices[0];
    Vec3D v1 = vertices[1]; 
    Vec3D v2 = vertices[2];
    
    Vec3D edge1 = v1 - v0;
    Vec3D edge2 = v2 - v0;
    Vec3D h = ray->dir * edge2;
    double a = edge1.dot(h);
    
    if (a > -1e-9 && a < 1e-9) return -1;
    
    double f = 1.0 / a;
    Vec3D s = ray->start - v0;
    double u = f * s.dot(h);
    
    if (u < 0.0 || u > 1.0) return -1;
    
    Vec3D q = s * edge1;
    double v = f * ray->dir.dot(q);
    
    if (v < 0.0 || u + v > 1.0) return -1;
    
    double t = f * edge2.dot(q);
    
    return (t > 1e-9) ? t : -1;
}

Ray Triangle::getNormal(Vec3D point, Ray *incident) const{
    Vec3D edge1 = vertices[1] - vertices[0];
    Vec3D edge2 = vertices[2] - vertices[0];
    Vec3D normal = edge1 * edge2;
    normal = normal.normalize();
    
    if (incident->dir.dot(normal) > 0){
        normal = -normal;
    }
    return Ray(point, normal);
}



//----------------------------Sphere class----------------------//

Sphere::Sphere() : Object(){
    reference_point = Vec3D(0, 0, 0);
    length = 0;
}
Sphere::Sphere(Vec3D center, double radius) : Object(){
    reference_point = center;
    length = radius;
}

void Sphere::draw(){
    int stacks = 30;
    int slices = 20;
    Vec3D points[100][100];
    int i, j;
    double h, r;

    // generate points
    for (i = 0; i <= stacks; i++){
        h = length * sin(((double)i / (double)stacks) * (M_PI / 2));
        r = length * cos(((double)i / (double)stacks) * (M_PI / 2));
        for (j = 0; j <= slices; j++){
            points[i][j].x = r * cos(((double)j / (double)slices) * 2 * M_PI);
            points[i][j].y = r * sin(((double)j / (double)slices) * 2 * M_PI);
            points[i][j].z = h;
        }
    }

    // draw quads using generated points
    glPushMatrix();
    glTranslatef(reference_point.x, reference_point.y, reference_point.z);
    glColor3f(color.r, color.g, color.b);
    for (i = 0; i < stacks; i++){
        for (j = 0; j < slices; j++){
            glBegin(GL_QUADS);
            {
                // upper hemisphere
                glVertex3f(points[i][j].x, points[i][j].y, points[i][j].z);
                glVertex3f(points[i][j + 1].x, points[i][j + 1].y, points[i][j + 1].z);
                glVertex3f(points[i + 1][j + 1].x, points[i + 1][j + 1].y, points[i + 1][j + 1].z);
                glVertex3f(points[i + 1][j].x, points[i + 1][j].y, points[i + 1][j].z);
                // lower hemisphere
                glVertex3f(points[i][j].x, points[i][j].y, -points[i][j].z);
                glVertex3f(points[i][j + 1].x, points[i][j + 1].y, -points[i][j + 1].z);
                glVertex3f(points[i + 1][j + 1].x, points[i + 1][j + 1].y, -points[i + 1][j + 1].z);
                glVertex3f(points[i + 1][j].x, points[i + 1][j].y, -points[i + 1][j].z);
            }
            glEnd();
        }
    }
    glPopMatrix();
}


double Sphere::findIntersection(Ray *r) {
    Vec3D oc = r->start - reference_point;
    double a = r->dir.dot(r->dir);
    double b = 2.0 * oc.dot(r->dir);
    double c = oc.dot(oc) - length * length;

    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return -1;
    }

    double sqrt_discriminant = sqrt(discriminant);
    double t1 = (-b - sqrt_discriminant) / (2 * a);
    double t2 = (-b + sqrt_discriminant) / (2 * a);

    if (t1 > 1e-5) return t1;
    if (t2 > 1e-5) return t2;
    return -1;
}

Ray Sphere::getNormal(Vec3D point, Ray *incident) const {
    return Ray(point, point - reference_point);
}



//----------------------------General Shape class----------------------//

General::General() : Object(){
    reference_point = Vec3D(0, 0, 0);
    length = 1;
}

General::General(Vec3D reference_point, double length, double width, double height, vector<double> materialCoefficients){
    this->reference_point = reference_point;
    this->length = length;
    this->width = width;
    this->height = height;
    this->A = materialCoefficients[0];
    this->B = materialCoefficients[1];
    this->C = materialCoefficients[2];
    this->D = materialCoefficients[3];
    this->E = materialCoefficients[4];
    this->F = materialCoefficients[5];
    this->G = materialCoefficients[6];
    this->H = materialCoefficients[7];
    this->I = materialCoefficients[8];
    this->J = materialCoefficients[9];
}
void General::draw(){
    return;
}

bool General::shouldDraw(Vec3D point){
    if (fabs(length) > 1e-5){ // dimension is not 0
        if (point.x < reference_point.x || point.x > reference_point.x + length)
            return false;
    }

    if (fabs(width) > 1e-5) {
        if (point.y < reference_point.y || point.y > reference_point.y + width)
            return false;
    }

    if (fabs(height) > 1e-5) {
        if (point.z < reference_point.z || point.z > reference_point.z + height)
            return false;
    }

    return true;
}


double General::findIntersection(Ray *ray){
    double R_ox = ray->start.x;
    double R_oy = ray->start.y;
    double R_oz = ray->start.z;

    double R_dx = ray->dir.x;
    double R_dy = ray->dir.y;
    double R_dz = ray->dir.z;

    double a = A * R_dx * R_dx + B * R_dy * R_dy + C * R_dz * R_dz + 
               D * R_dx * R_dy + E * R_dx * R_dz + F * R_dy * R_dz;

    double b = 2 * A * R_ox * R_dx + 2 * B * R_oy * R_dy + 2 * C * R_oz * R_dz + 
               D * (R_ox * R_dy + R_dx * R_oy) + E * (R_ox * R_dz + R_dx * R_oz) + 
               F * (R_oy * R_dz + R_dy * R_oz) + G * R_dx + H * R_dy + I * R_dz;

    double c = A * R_ox * R_ox + B * R_oy * R_oy + C * R_oz * R_oz + 
               D * R_ox * R_oy + E * R_ox * R_oz + F * R_oy * R_oz + 
               G * R_ox + H * R_oy + I * R_oz + J;

    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0){
        return -1;
    }
    
    if (fabs(a) < 1e-9){
        if (fabs(b) < 1e-9) return -1;
        double t = -c / b;
        if (t > 1e-5 && shouldDraw(ray->start + ray->dir * t)){
            return t;
        }
        return -1;
    }

    double sqrt_discriminant = sqrt(discriminant);
    double t1 = (-b - sqrt_discriminant) / (2 * a);
    double t2 = (-b + sqrt_discriminant) / (2 * a);

    if (t1 > 1e-5 && shouldDraw(ray->start + ray->dir * t1)){
        return t1;
    }
    if (t2 > 1e-5 && shouldDraw(ray->start + ray->dir * t2)){
        return t2;
    }

    return -1;
}

Ray General::getNormal(Vec3D point, Ray *incident) const{
    // ○ Normal = (𝜕F/𝜕x, 𝜕F/𝜕y, 𝜕F/𝜕z) [Substitute x, y, z values with that of the intersection point to obtain normals at different points]
    Vec3D normal(2 * A * point.x + D * point.y + E * point.z + G,
                 2 * B * point.y + D * point.x + F * point.z + H,
                 2 * C * point.z + E * point.x + F * point.y + I);

    if (incident->dir.dot(normal) < 0) // opposite direction
    {
        return Ray(point, normal);
    }
    else
    {
        return Ray(point, -normal);
    }
}




//----------------------------Floor class----------------------//

Floor::Floor(double floorWidth, double tileWidth){
    tileCount = floorWidth / tileWidth;
    reference_point = Vec3D(-floorWidth / 2, -floorWidth / 2, 0);
    length = tileWidth;
    useTexture = false;
    textureData = nullptr;
    textureWidth = 0;
    textureHeight = 0;
    textureChannels = 0;
    glTextureId = 0;
    glTextureLoaded = false;
}

Floor::~Floor(){
    if (textureData) {
        stbi_image_free(textureData);
    }
    if (glTextureLoaded && glTextureId) {
        glDeleteTextures(1, &glTextureId);
    }
}

void Floor::loadTexture(const string& filename) {
    if (textureData) {
        stbi_image_free(textureData);
    }
    
    textureData = stbi_load(filename.c_str(), &textureWidth, &textureHeight, &textureChannels, 0);
    if (!textureData) {
        cout << "Failed to load texture: " << filename << endl;
        useTexture = false;
    } else {
        cout << "Loaded texture: " << filename << " (" << textureWidth << "x" << textureHeight << ", " << textureChannels << " channels)" << endl;
        loadGLTexture();
    }
}

void Floor::setUseTexture(bool use) {
    useTexture = use && (textureData != nullptr);
}

bool Floor::isUsingTexture() const {
    return useTexture;
}

Color Floor::sampleTexture(double u, double v) {
    if (!textureData || textureWidth <= 0 || textureHeight <= 0) {
        return Color(0.5, 0.5, 0.5);
    }

    u = max(0.0, min(1.0, u));
    v = max(0.0, min(1.0, v));

    int pixel_x = (int)(u * (textureWidth - 1));
    int pixel_y = (int)((1.0 - v) * (textureHeight - 1));

    pixel_x = max(0, min(textureWidth - 1, pixel_x));
    pixel_y = max(0, min(textureHeight - 1, pixel_y));

    int index = (pixel_y * textureWidth + pixel_x) * textureChannels;
    int max_index = textureWidth * textureHeight * textureChannels;
    if (index < 0 || index + 2 >= max_index) {
        return Color(1.0, 0.0, 1.0);
    }

    Color color;
    color.r = textureData[index] / 255.0;

    if (textureChannels >= 2) {
        color.g = textureData[index + 1] / 255.0;
    } else {
        color.g = color.r;
    }

    if (textureChannels >= 3) {
        color.b = textureData[index + 2] / 255.0;
    } else {
        color.b = color.r;
    }

    return color;
}

void Floor::draw(){
    glPushMatrix();
    glTranslatef(reference_point.x, reference_point.y, reference_point.z);
    
    if (useTexture && glTextureLoaded) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, glTextureId);
        glColor3f(1.0, 1.0, 1.0);
        
        double floorSize = tileCount * length;
        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0); glVertex2f(0, 0);
        glTexCoord2f(1.0, 0.0); glVertex2f(floorSize, 0);
        glTexCoord2f(1.0, 1.0); glVertex2f(floorSize, floorSize);
        glTexCoord2f(0.0, 1.0); glVertex2f(0, floorSize);
        glEnd();
        
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    } else {
        for (int i = 0; i < tileCount; i++){
            for (int j = 0; j < tileCount; j++){
                if ((i + j) % 2 == 0){
                    glColor3f(1.0, 1.0, 1.0);
                }
                else{
                    glColor3f(0.0, 0.0, 0.0);
                }

                glBegin(GL_QUADS);
                glVertex2f(i * length, j * length);
                glVertex2f((i + 1) * length, j * length);
                glVertex2f((i + 1) * length, (j + 1) * length);
                glVertex2f(i * length, (j + 1) * length);
                glEnd();
            }
        }
    }
    glPopMatrix();
}

double Floor::findIntersection(Ray *ray){
    if (fabs(ray->dir.z) < 1e-9){
        return -1;
    }
    
    double t = -ray->start.z / ray->dir.z;
    if (t <= 1e-5) return -1;
    
    Vec3D intersectionPoint = ray->start + ray->dir * t;
    double maxCoord = reference_point.x + tileCount * length;
    
    if (intersectionPoint.x >= reference_point.x && intersectionPoint.x <= maxCoord &&
        intersectionPoint.y >= reference_point.y && intersectionPoint.y <= maxCoord){
        return t;
    }
    return -1;
}

Ray Floor::getNormal(Vec3D point, Ray *incident) const{
    return Ray(point, Vec3D(0, 0, incident->dir.z > 0 ? -1 : 1));
}

Color Floor::getColorAt(Vec3D point){
    if (useTexture && textureData) {
        double floorSize = tileCount * length;
        double u = (point.x - reference_point.x) / floorSize;
        double v = (point.y - reference_point.y) / floorSize;
        
        u = max(0.0, min(1.0, u));
        v = max(0.0, min(1.0, v));
        
        return sampleTexture(u, v);
    } else {
        int i = (point.x - reference_point.x) / length;
        int j = (point.y - reference_point.y) / length;

        if (i < 0 || i >= tileCount || j < 0 || j >= tileCount)
            return Color(0, 0, 0);
        if ((i + j) % 2 == 0)
            return Color(1, 1, 1);
        else
            return Color(0, 0, 0);
    }
}

void Floor::loadGLTexture() {
    if (!textureData) return;
    
    if (glTextureLoaded && glTextureId) {
        glDeleteTextures(1, &glTextureId);
    }
    
    glGenTextures(1, &glTextureId);
    glBindTexture(GL_TEXTURE_2D, glTextureId);
    
    GLenum format = (textureChannels == 3) ? GL_RGB : GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, format, textureWidth, textureHeight, 0, format, GL_UNSIGNED_BYTE, textureData);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glTextureLoaded = true;
}





//----------------------------Camera class----------------------//

Camera::Camera(){
    init(Vec3D(100, 100, 100), Vec3D(0, 0, 1), Vec3D(-1 / sqrt(2), 1 / sqrt(2), 0), Vec3D(-1 / sqrt(2), -1 / sqrt(2), 0));

}
void Camera::init(Vec3D p, Vec3D u, Vec3D r, Vec3D l){
    pos = p;
    up = u;
    right = r;
    look = l;
    focal_length = pos.magnitude();

}
void Camera::set(){
    gluLookAt(
        pos.x, pos.y, pos.z,
        pos.x + look.x, pos.y + look.y, pos.z + look.z,
        up.x, up.y, up.z);
}


void Camera::rotateAroundUp(double radian){
    right = right.perpRotate(up, radian);
    look = look.perpRotate(up, radian);
}
void Camera::rotateLeft(){
    rotateAroundUp(radians(1));
}
void Camera::rotateRight(){
    rotateAroundUp(-radians(1));
}
void Camera::rotateAroundRight(double radian){
    up = up.perpRotate(right, radian);
    look = look.perpRotate(right, radian);
}
void Camera::rotateUp(){
    rotateAroundRight(radians(1));
}
void Camera::rotateDown(){
    rotateAroundRight(-radians(1));
}
void Camera::rotateAroundLook(double radian){
    right = right.perpRotate(look, radian);
    up = up.perpRotate(look, radian);
}
void Camera::tiltClock(){
    rotateAroundLook(radians(1));
}
void Camera::tiltCounterClock(){
    rotateAroundLook(-radians(1));
}
void Camera::moveForward(){
    pos = pos + (look * 2);
}
void Camera::moveBackward(){
    pos = pos - (look * 2);
}
void Camera::moveLeft(){
    pos = pos - (right * 2);
}
void Camera::moveRight(){
    pos = pos + (right * 2);
}
void Camera::moveUp(){
    pos = pos + (up * 2);
}
void Camera::moveDown(){
    pos = pos - (up * 2);
}
void Camera::moveAroundRef(int dir)
{
    Vec3D C = pos + look * focal_length; // current reference

    Vec3D A = pos;    // prev camera position
    pos.z += dir * 2; // move the camera along z axis

    Vec3D B = pos; // new camera position
    Vec3D normalVector = (A - C) * (B - C);

    double ang = (A - C).angle(B - C);
    look = look.perpRotate(normalVector, ang);

    // up = up.perpRotate(normalVector, ang);
    up = right * look; // Not sure
    right = look * up;

    focal_length = distancePointToPoint3D(pos, C);
}
void Camera::moveUpRef(){
    moveAroundRef(1);
}
void Camera::moveDownRef(){
    moveAroundRef(-1);
}

void Camera::drawReference(){
    Vec3D C = pos + look * focal_length;

    glPushMatrix();
    glTranslatef(C.x, C.y, C.z);
    glScalef(0.5, 0.5, 0.5);
    GraphicsManager::drawAxis();
    glPopMatrix();
}

void Camera::keyPress(unsigned char key){
    switch (key){
    case '1':
        this->rotateLeft();
        break;
    case '2':
        this->rotateRight();
        break;
    case '3':
        this->rotateUp();
        break;
    case '4':
        this->rotateDown();
        break;
    case '5':
        this->tiltClock();
        break;
    case '6':
        this->tiltCounterClock();
        break;
    case 'w':
        this->moveUpRef();
        break;
    case 's':
        this->moveDownRef();
        break;

    default:
        break;
    }
}

void Camera::specialKeyPress(int key){
    switch (key){
    case GLUT_KEY_UP:
        this->moveForward();
        break;
    case GLUT_KEY_DOWN:
        this->moveBackward();
        break;

    case GLUT_KEY_RIGHT:
        this->moveRight();
        break;

    case GLUT_KEY_LEFT:
        this->moveLeft();
        break;

    case GLUT_KEY_PAGE_UP:
        this->moveUp();
        break;
    case GLUT_KEY_PAGE_DOWN:
        this->moveDown();
        break;

    default:
        break;
    }
}

void Camera::mouseScroll(int dir){
    if (dir == 1)
    {
        this->moveForward();
    }
    else if (dir == -1)
    {
        this->moveBackward();
    }
}





//----------------------------GraphicsManager class----------------------//

GLint GraphicsManager::windowHeight = 700;
GLint GraphicsManager::windowWidth = 600;
double GraphicsManager::viewAngle = 90;
double GraphicsManager::nearPlane = 1;
double GraphicsManager::farPlane = 1000;



void GraphicsManager::draw2DLine(Vec2D p, Vec2D q, double r, double g, double b){
    glBegin(GL_LINE_STRIP);
    glColor3f(r, g, b);
    glVertex2f(p.x, p.y);
    glVertex2f(q.x, q.y);
    glEnd();
}
void GraphicsManager::draw3DLine(Vec3D p, Vec3D q, double r, double g, double b){
    glBegin(GL_LINE_STRIP);
    glColor3f(r, g, b);
    glVertex3f(p.x, p.y, q.z);
    glVertex3f(q.x, q.y, q.z);
    glEnd();
}
void GraphicsManager::drawCheckerboard(){
    int size = 100;
    for (int i = -size; i < size; i += 2)
    {
        for (int j = abs(i) - size; j < size - abs(i); j += 2)
        {
            if ((i + j) / 2 % 2 == 0)
            {
                glColor3f(1.0, 1.0, 1.0); // White
            }
            else
            {
                glColor3f(0.0, 0.0, 0.0); // Black
            }

            glBegin(GL_QUADS);
            glVertex2f(i, j);
            glVertex2f(i + 2, j);
            glVertex2f(i + 2, j + 2);
            glVertex2f(i, j + 2);
            glEnd();
        }
    }
}
void GraphicsManager::drawCircle(double radius, double r, double g, double b, int segments){
    vector<Vec2D> points(segments + 1);
    glColor3f(r, g, b);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= segments; i++)
    {
        points[i] = Vec2D(radius * cos(((double)i / (double)segments) * 2 * M_PI), radius * sin(((double)i / (double)segments) * 2 * M_PI));

        glVertex2f(radius * cos(((double)i / (double)segments) * 2 * M_PI), radius * sin(((double)i / (double)segments) * 2 * M_PI));
    }
    glEnd();
}

void GraphicsManager::drawFilledCircle(double radius, double r, double g, double b, int segments){
    vector<Vec2D> points(segments + 1);
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i <= segments; i++)
    {
        glVertex2f(radius * cos(((double)i / (double)segments) * 2 * M_PI), radius * sin(((double)i / (double)segments) * 2 * M_PI));
    }
    glEnd();
}

void GraphicsManager::drawPolygon(vector<Vec2D> points, double r, double g, double b){
    glBegin(GL_LINE_LOOP);
    for (Vec2D p : points)
    {
        glVertex2f(p.x, p.y);
    }
    glEnd();
}
void GraphicsManager::drawFilledPolygon(vector<Vec2D> points, double r, double g, double b){
    glBegin(GL_POLYGON);
    glColor3f(r, g, b);
    for (Vec2D p : points)
    {
        glVertex2f(p.x, p.y);
    }
    glEnd();
}
void GraphicsManager::drawSquare(double a, double r, double g, double b){
    glBegin(GL_LINE_LOOP);
    {
        glColor3f(r, g, b);
        glVertex2f(a, a);
        glVertex2f(a, -a);
        glVertex2f(-a, -a);
        glVertex2f(-a, a);
    }
    glEnd();
}

void GraphicsManager::drawFilledSquare(double a, double r, double g, double b){
    glBegin(GL_QUADS);
    {
        // Anticlock
        glColor3f(r, g, b);
        glVertex2f(a, a);
        glVertex2f(a, -a);
        glVertex2f(-a, -a);
        glVertex2f(-a, a);
    }
    glEnd();
}



void GraphicsManager::drawAxis()
{
    glPushMatrix();
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    glVertex3f(1, 0, 0);
    glVertex3f(-1, 0, 0);
    glEnd();

    glColor3f(0, 1, 0);
    glBegin(GL_LINES);
    glVertex3f(0, 1, 0);
    glVertex3f(0, -1, 0);
    glEnd();

    glColor3f(0, 0, 1);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 1);
    glVertex3f(0, 0, -1);
    glEnd();
    glPopMatrix();
}

void GraphicsManager::draw2DAxis()
{
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    {
        glVertex2f(1000, 0);
        glVertex2f(-1000, 0);

        glVertex2f(0, -1000);
        glVertex2f(0, 1000);
    }
    glEnd();
    glPopMatrix();
}
void GraphicsManager::drawCube()
{
    // Front face
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0); // Red
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glEnd();

    // Back face
    glBegin(GL_QUADS);
    glColor3f(0.0, 1.0, 0.0); // Green
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glEnd();

    // Connect front and back faces with lines
    glColor3f(0.0, 0.0, 0.0); // Black
    glBegin(GL_LINES);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(-1.0, -1.0, -1.0);

    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, -1.0);

    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, -1.0);

    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glEnd();
}

void GraphicsManager::drawCylinder(float radius, float height){
    int numSegments = 50;
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= numSegments; ++i)
    {
        float theta = 2.0 * M_PI * static_cast<float>(i) / numSegments;
        float x = radius * cos(theta);
        float y = radius * sin(theta);

        glVertex3f(x, y, 0.0);
        glVertex3f(x, y, height);
    }
    glEnd();
}

void GraphicsManager::drawEllipse(double x, double y, double a, double b, int slices){
    double t, PI = acos(-1.0), dt, x1, y1, xp, yp;
    dt = 2 * PI / slices;
    glBegin(GL_LINE_LOOP);
    xp = x + a;
    yp = y + b;
    for (t = 0; t <= 2 * PI; t += dt)
    {
        x1 = x + a * cos(t);
        y1 = y + b * sin(t);
        glVertex2f(xp, yp);
        xp = x1;
        yp = y1;
    }
    glEnd();
}

void GraphicsManager::drawFilledEllipse(double x, double y, double a, double b, int slices){
    double t, PI = acos(-1.0), dt, x1, y1, xp, yp;
    dt = 2 * PI / slices;
    xp = x + a;
    yp = y + b;
    glBegin(GL_POLYGON);
    for (t = 0; t <= 2 * PI; t += dt)
    {
        x1 = x + a * cos(t);
        y1 = y + b * sin(t);
        glVertex2f(xp, yp);
        xp = x1;
        yp = y1;
    }
    glEnd();
}

void GraphicsManager::drawCone(float radius, float height){
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0, 0.0, height); // Apex
    int numSegments = 50;
    for (int i = 0; i <= numSegments; ++i)
    {
        float theta = 2.0 * M_PI * static_cast<float>(i) / numSegments;
        float x = radius * cos(theta);
        float y = radius * sin(theta);

        glVertex3f(x, y, 0.0);
    }
    glEnd();
}
void GraphicsManager::drawArrow(double length){
    drawCylinder(0.05, length);
    glTranslatef(0.0, 0.0, length); // Move the cone up to connect with the cylinder
    drawCone(0.1, 0.5);
}


void GraphicsManager::keyHandler(unsigned char key, int, int){ // Callback When normal key is pressed down
    keyboard(key);
    glutPostRedisplay();
}
void GraphicsManager::specialKeyHandler(int key, int, int){ // Callback when special key is pressed down
    specialKeyboard(key);
    glutPostRedisplay();
}
void GraphicsManager::displayHandler(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // Ensures that each time when we enter the projection mode, the matrix will be reset to identity matrix
    display();
    glutSwapBuffers();
}

void GraphicsManager::mouseClickHandler(int button, int state, int x, int y){
    if (button == 3)
    {
        mouseScroll(1);
    }
    else if (button == 4)
    {
        mouseScroll(-1);
    }

    glutPostRedisplay();
}

void GraphicsManager::resize(int w, int h){
    glViewport(0, 0, w, h); // resizing the window

    // Setup viewing volume
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    windowWidth = w;
    windowHeight = h;

    gluPerspective(
        viewAngle,   // fov
        1.0 * w / h, // aspect
        nearPlane,
        farPlane);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GraphicsManager::resize2D(int w, int h){
    glViewport(0, 0, w, h); // resizing the window

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    windowWidth = w;
    windowHeight = h;

    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -100, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void GraphicsManager::initialize(int width, int height, char *title, int mode)
{
    windowWidth = width;
    windowHeight = height;
    // Initialize GLUT // Without this : Other glut functions can't be called .
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(500, 0);                // Position the window's initial top-left corner
    glutInitWindowSize(windowWidth, windowHeight); // Set the window's initial width & height // Default value : 300,300
    glutCreateWindow(title);                       // Create a window with the given tit le	// Without this : ERROR:  glutMainLoop called with no windows created.
    glutDisplayFunc(GraphicsManager::displayHandler);    // Register display callback handler for window re-paint  // Without this: ERROR:  No display callback registered for window 1
    if (mode == 2)
        glutReshapeFunc(GraphicsManager::resize2D);
    else if (mode == 3)
        glutReshapeFunc(GraphicsManager::resize);
    // Input handlers
    glutKeyboardFunc(GraphicsManager::keyHandler);
    glutSpecialFunc(GraphicsManager::specialKeyHandler); // special keys
    glutMouseFunc(GraphicsManager::mouseClickHandler);

    // glutTimerFunc(10, collision, 0);

    glEnable(GL_DEPTH_TEST); // je object kache setake rakhe
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLineWidth(3.0);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
    GraphicsManager::init();
}



//-----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//



bool doRayIntersectLine(Vec2D ray_p, Vec2D ray_d, Vec2D line_p, Vec2D line_d){
    if (abs(ray_d.x * line_d.y - ray_d.y * line_d.x) > 1e-5)
    {
        Vec2D I = getIntersectionPoint(ray_p, ray_d, line_p, line_d);
        return haveSameDirection(I - ray_p, ray_d);
    }
    return false;
}

bool doIntersect(Vec2D a_dir, Vec2D b_dir){
    return abs(a_dir.x * b_dir.y - a_dir.y * b_dir.x) > 1e-5;
}
bool haveSameDirection(Vec2D v1, Vec2D v2){
    double crossProduct = v1.x * v2.y - v1.y * v2.x;
    double dotProduct = v1.x * v2.x + v1.y * v2.y;

    return abs(crossProduct) < 1e-5 && dotProduct > 0;
}


Vec2D getIntersectionPoint(Vec2D a_point, Vec2D a_dir, Vec2D b_point, Vec2D b_dir){
    if (!doIntersect(a_dir, b_dir))
        return {NAN, NAN};

    double x1 = a_point.x, y1 = a_point.y;
    double x2 = b_point.x, y2 = b_point.y;
    double dx1 = a_dir.x, dy1 = a_dir.y;
    double dx2 = b_dir.x, dy2 = b_dir.y;
    double det = dx1 * dy2 - dy1 * dx2;

    double t1 = ((x2 - x1) * dy2 + (y1 - y2) * dx2) / det;

    double intersectX = x1 + t1 * dx1;
    double intersectY = y1 + t1 * dy1;
    return {intersectX, intersectY};
}

double radians(double degrees){
    return degrees * M_PI / 180;
}
double degrees(double radians){
    return radians * 180 / M_PI;
}

double distancePointToPoint2D(Vec2D a, Vec2D b){
    return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}
double distancePointToPoint3D(Vec3D a, Vec3D b){
    return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y) + (b.z - a.z) * (b.z - a.z));
}
