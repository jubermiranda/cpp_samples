#include <iostream>
#include <math.h>

using namespace std;

const double PI = 3.14159265359;
double distance(int i);

int main(int argc, char *argv[])
{
  for(int i=0; i <= 90; i++){
    cout << "angle: " << i << "; distance: " << distance(i) << endl;
  }
  return 0;
}

double degree_to_rad(int degree){
  return ((double) degree * (PI/180.0));
}

double distance(int angle){
  double velocity = 200.0; //ft/s
  double gravity = 32.2;

  double rad = degree_to_rad(angle);

  double time_in_air = (2.0 * velocity * sin(rad)) / gravity;
  double shot_dist = round((velocity * cos(rad)) * time_in_air);

  return shot_dist;
}
