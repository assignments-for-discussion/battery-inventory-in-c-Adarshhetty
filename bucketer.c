#include <stdio.h>
#include <assert.h>

struct CountsBySoH {
  int healthy;
  int exchange;
  int failed;
};

struct CountsBySoH countBatteriesByHealth(const int* presentCapacities, int nBatteries) {
  struct CountsBySoH counts = {0, 0, 0};
  static int rated_capacity=120;
  for(int battery=0;battery<nBatteries;battery++){
    double SoH=(100*presentCapacities[battery])/rated_capacity; //Calculating SoH of the batteries assuming rated capacity to be 120Ah
    if(SoH>80&&SoH<=100)        //Check if the battery is healthy
      counts.healthy++;
    else if(SoH>=62&&SoH<=80)   //Check if the battery needs to be exchanged
      counts.exchange++;         
    else                        ////Check if the battery is failed
      counts.failed++;
  }
  return counts;
}

void testBucketingByHealth() {
  const int presentCapacities[] = {113, 116, 80, 95, 92, 70};
  const int numberOfBatteries = sizeof(presentCapacities) / sizeof(presentCapacities[0]);
  printf("Counting batteries by SoH...\n");
  struct CountsBySoH counts = countBatteriesByHealth(presentCapacities, numberOfBatteries);
  assert(counts.healthy == 2);
  assert(counts.exchange == 3);
  assert(counts.failed == 1);
  printf("Done counting :)\n");
}

int main() {
  testBucketingByHealth();
  return 0;
}
