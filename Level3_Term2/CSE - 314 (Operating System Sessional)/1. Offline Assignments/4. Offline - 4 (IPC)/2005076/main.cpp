#include "IPC.cpp"
#include<algorithm>
using namespace std;


void init_semaphore(){
    pthread_mutex_init(&stair1_lock, NULL);
    pthread_mutex_init(&stair2_lock, NULL);
    pthread_mutex_init(&stair3_lock, NULL);

    pthread_mutex_init(&log_lock, NULL);
    sem_init(&corridor_sem, 0, MAX_CORRIDOR);
    sem_init(&gallery1_sem, 0, MAX_GALLERY1);

    pthread_mutex_init(&pb_lock, NULL);
    pthread_mutex_init(&standard_lock, NULL);
    pthread_mutex_init(&premium_lock, NULL);
    pthread_mutex_init(&access_check_lock, NULL);
}

void destroy_semaphore(){
    pthread_mutex_destroy(&stair1_lock);
    pthread_mutex_destroy(&stair2_lock);
    pthread_mutex_destroy(&stair3_lock);
    pthread_mutex_destroy(&log_lock);

    sem_destroy(&corridor_sem);
    sem_destroy(&gallery1_sem);

    pthread_mutex_destroy(&pb_lock);
    pthread_mutex_destroy(&standard_lock);
    pthread_mutex_destroy(&premium_lock);
    pthread_mutex_destroy(&access_check_lock);
}

int main(int argc, char* argv[]) {
    if(argc != 7){
        cout << "Usage: ./main <N> <M> <w> <x> <y> <z>\n";
        return 1;
    }

    int N = stoi(argv[1]);
    int M = stoi(argv[2]);
    w = stoi(argv[3]);
    x = stoi(argv[4]);
    y = stoi(argv[5]);
    z = stoi(argv[6]);

    init_semaphore();

    vector<pthread_t> threads;
    vector<Visitor*> visitors;

    for(int i=0; i<N; i++) 
        visitors.push_back(new Visitor(1001+i, STANDARD));

    for(int i=0; i<M; i++)
        visitors.push_back(new Visitor(2001+i, PREMIUM));

    random_shuffle(visitors.begin(), visitors.end());
    for(auto visitor: visitors) {
        pthread_t tid;
        pthread_create(&tid, NULL, visitor_thread, (void*)visitor);
        threads.push_back(tid);
        usleep(5);
    }

    for(auto &tid: threads) {
        pthread_join(tid, NULL);
    }

    destroy_semaphore();


    return 0;

}