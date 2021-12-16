#include <iostream>
#include <limits>
#include <ctime>
#include <pthread.h>
#include <cstdlib>


const unsigned int arrSize = 40;

bool *flowers ;  // array of flowers.

const int threadNumber = 2;

// Function for watering flowers.
void *func(void *param) {
    //First gardener watering first half of garden, second - second.
    int p = (*(int*)param )*20;
    for(unsigned int i = p ; i < p + 20 ; ++i) {
        if(!flowers[i]) {
            // Gardener is watering flower.
            flowers[i] = true;
            std::cout << "Gardener#"<<p/20<<" watering flower with number "<<i<<std::endl;
        }
        
    }
    return NULL;
}

int main(int argc, char* argv[]) {

    // I added pause(in seconds)to output for pleasure.
    // You can change it to zero, if you don't want wait.
    int pause = 1;

    // Select memory for flowers.
    flowers = new bool[arrSize];
    
    // At the beginning all flowers are dried!
    for(int i = 0; i < arrSize; ++i) {
        flowers[i] = false;
    }

    pthread_t thread[threadNumber];
    int number[threadNumber] ;
    for (int i = 0 ; i < threadNumber ; ++i) {
        number[i]=i ;
    }
    
    clock_t start_time =  clock(); // Create timer.
    
    // Default count of days equals to -1 => loop is infinite.
    int count_of_days = -1;
    if(argc == 2) {
        // If user puts count of days, program set new count. If input is incorrect, count of days = 0.
    	count_of_days = atoi(argv[1]);
    }
    
    // Counter of days.
    unsigned int day;
    
    // Create gardeners.
    for(day = 0; day < count_of_days; ++day) {
        std::cout << std::endl << "Day " << day << std::endl << std::endl;
    
        for (int i = 0 ; i < threadNumber ; ++i) {
            pthread_create(&thread[i], nullptr, func, (void*)(number+i)) ;
        }
        std::cout << std::endl;
    
        for (int i = 0 ; i < threadNumber; i++) {
            pthread_join(thread[i],NULL);
        }
        
        // Program randomly makes some flowers dried.
        std::cout << std::endl;
        int length = 0 + rand() % 40;
        for(int i = 0; i < length; ++i){
            int index = 0 + rand() % 40;
            if(flowers[index]) {
                flowers[index] = false;
                std::cout << "Flower#"<<index<<" is dried!"<<std::endl;
            }
        }
        std::cout << std::endl;
        // It is a timer on 5 seconds for usefull output. This pause helps you to anylise output.
        // Program count all time of working without these pauses!
        clock_t startClock = clock();
        while(clock() < startClock + pause * CLOCKS_PER_SEC);
    }

    clock_t end_time = clock(); // Final time.
    double time = ((double)(end_time-start_time))/CLOCKS_PER_SEC;
    std::cout << day << " days have passed" << std::endl;
    std::cout << "Time of work with pauses: " << time << std::endl;
    std::cout << "Time of work without pauses: " << time - count_of_days * pause << std::endl;
    delete[] flowers;
    return 0;
}
