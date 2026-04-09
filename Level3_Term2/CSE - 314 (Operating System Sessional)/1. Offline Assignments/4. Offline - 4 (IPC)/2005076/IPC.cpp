#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <vector>
#include <chrono>
#include <random>

using namespace std;

const int MAX_GALLERY1 = 5;
const int MAX_CORRIDOR = 3;

int w, x, y, z;

pthread_mutex_t stair1_lock;
pthread_mutex_t stair2_lock;
pthread_mutex_t stair3_lock;

pthread_mutex_t log_lock;
sem_t corridor_sem;
sem_t gallery1_sem;

pthread_mutex_t pb_lock;
pthread_mutex_t standard_lock;
pthread_mutex_t premium_lock;
pthread_mutex_t access_check_lock;

int premium_count = 0;
int standard_count = 0;


enum VisitorType {
    STANDARD,
    PREMIUM
};

auto start_time = chrono::high_resolution_clock::now();

long long get_time() {
    auto current_time = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(current_time - start_time).count();
}

// Function to generate a Poisson-distributed random number

std::random_device rd;
std::mt19937 generator(rd());

// Lambda value for the Poisson distribution
double lambda = 10000.234;
std::poisson_distribution<int> poissonDist(lambda);

int get_random_number() {
  return poissonDist(generator);
}


const std::string RESET = "\033[0m";
const std::string BLUE = "\033[34m";  // For STANDARD visitors
const std::string RED = "\033[31m";   // For PREMIUM visitors
const std::string GREEN = "\033[32m"; // For general actions



class Visitor {
public:
    int id;
    VisitorType type;
    Visitor(int id, VisitorType type) {
        this->id = id;
        this->type = type;
    }

    void print_log(string message) {
        pthread_mutex_lock(&log_lock);
        if(type == STANDARD) cout << BLUE;
        else if(type == PREMIUM) cout << RED;
        cout << "Visitor " << id << " " << message << " at timestamp " << get_time() << "\n";
        cout << RESET;
        pthread_mutex_unlock(&log_lock);
    }

};

//TASK 1: (A to D)
void visit_gallery1(Visitor* visitor, int w, int x){
    visitor->print_log("has arrived at A");
    usleep(w*1000);     //usleep takes microseconds as argument
    visitor->print_log("has arrived at B");

    //visitor->print_log("waiting s for gallery1");
    pthread_mutex_lock(&stair1_lock);
    visitor->print_log("is at step 1");
    usleep(1000);

    pthread_mutex_lock(&stair2_lock);
    visitor->print_log("is at step 2");
    pthread_mutex_unlock(&stair1_lock);
    usleep(1000);

    pthread_mutex_lock(&stair3_lock);
    visitor->print_log("is at step 3");
    pthread_mutex_unlock(&stair2_lock);
    usleep(1000);

    sem_wait(&gallery1_sem);
    visitor->print_log("is at C(entered Gallery 1)");
    pthread_mutex_unlock(&stair3_lock);
    usleep(x*1000);

}

//TASK 2: (D to PB)
void visit_gallery2(Visitor* visitor, int y){
    sem_wait(&corridor_sem);
    visitor->print_log("is at D (exiting Gallery 1)");
    sem_post(&gallery1_sem);

    usleep(1000 + get_random_number()%1500); //random delay

    sem_post(&corridor_sem);
    visitor->print_log("is at E(entered Gallery 2)");
    usleep(y*1000 + get_random_number()%2500); //allowed random delay
}

//TASK 3: (PB to Exit)
void use_photo_booth(Visitor* visitor, int z){
    //Reader-writer problem
    visitor->print_log("is about to enter the photo booth");

    if(visitor->type == PREMIUM){
        pthread_mutex_lock(&premium_lock);
        premium_count++;
        if(premium_count == 1) pthread_mutex_lock(&access_check_lock);
        pthread_mutex_unlock(&premium_lock);

        pthread_mutex_lock(&pb_lock);
        visitor->print_log("is inside the photo booth");
        usleep(z*1000);
        pthread_mutex_unlock(&pb_lock);

        pthread_mutex_lock(&premium_lock);
        premium_count--;
        if(premium_count == 0) pthread_mutex_unlock(&access_check_lock);
        pthread_mutex_unlock(&premium_lock);

    }

    else if(visitor->type == STANDARD){
        pthread_mutex_lock(&access_check_lock);
        pthread_mutex_lock(&standard_lock);
        standard_count++;
        if(standard_count == 1) pthread_mutex_lock(&pb_lock);
        pthread_mutex_unlock(&standard_lock);
        pthread_mutex_unlock(&access_check_lock);

        visitor->print_log("is inside the photo booth");
        usleep(z*1000);

        pthread_mutex_lock(&standard_lock);
        standard_count--;
        if(standard_count == 0) pthread_mutex_unlock(&pb_lock);
        pthread_mutex_unlock(&standard_lock);
    }
}


//visitor thread function
void* visitor_thread(void* arg){
    Visitor* visitor = (Visitor*)arg;

    usleep(1000 + get_random_number()%2500); //random delay
    //cout<<"\n Delay: "<<1000 + get_random_number()%2500<<"\n";

    visit_gallery1(visitor, w, x);
    visit_gallery2(visitor, y);
    use_photo_booth(visitor, z);

    visitor->print_log("is at F (exiting the museum)");

    return NULL;
}
