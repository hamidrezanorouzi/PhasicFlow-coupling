
#define DynamicSchedule 1

# if DynamicSchedule
    #define ParallelRegion  omp parallel for schedule (dynamic)
#else
    #define ParallelRegion  omp parallel for
#endif
