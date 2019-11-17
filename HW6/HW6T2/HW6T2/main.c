
#include<stdlib.h>
#include <stdio.h>
#include "knn.h"
int main(int argc, const char * argv[]) {
    
    double train_instances[8] = {1.0,3.7,-1.2,2.6,0.0,4.1,1.0,-4.2};
    double test_instance[4] = {-1.2,1.4,6.7,0.5};
    compute_distances(train_instances,test_instance,2,4);
    
    return 0;
}
