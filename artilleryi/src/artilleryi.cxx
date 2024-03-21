#include <fstream>
#include <iostream>
#include <limits>
#include <math.h>
#include <random>
#include <sstream>
using namespace std;

void play();
bool ask_user_if_wanna_repeat();
bool user_got_it_right(int distance, int angle);
int generate_random_distances();
double mod(double n);
void print_header();
void print_exit_message();
void print_readme();
void print_gameover();
double dist_btw_shot_enemy(int dist, int angle);

const double PI = 3.14159265359;
int score;
vector<int> distances = {
    0,    43,   87,   130,  173,  216,  258,  301,  342,  384,  425,  465,
    505,  545,  583,  621,  658,  695,  730,  765,  798,  831,  863,  894,
    923,  952,  979,  1005, 1030, 1053, 1076, 1097, 1117, 1135, 1152, 1167,
    1181, 1194, 1205, 1215, 1223, 1230, 1235, 1239, 1241, 1242};

int main(int argc, char *argv[]) {
  score = 0;
  print_header();

  bool repeat = false;
  do {

    play();
    repeat = ask_user_if_wanna_repeat();

  } while (repeat);

  print_exit_message();
  return 0;
}//// *-*

void play() {
  int remaning_shots = 10;
  int enemy_distance = generate_random_distances();
  cout << "The enemy is " << enemy_distance << " fts away!!" << endl;

  do {
    int angle;
    cout << "What angle? "
         << "(" << remaning_shots << " shots) ";

    if (!(cin >> angle)) {
      cout << "Only integers for angle is allowed!!" << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }

    if (angle > 90 || angle < 0) {
      cout << "Come on... chose a value btw 0-90" << endl;
      continue;
    }

    if (user_got_it_right(enemy_distance, angle)) {
      score++;
      return;
    } else
      remaning_shots--;

  } while (remaning_shots > 0);
  print_gameover();
}

double mod(double n){
  if(n < 0)
    return (n*(-1));
  return n;
}
bool user_got_it_right(int distance, int angle) {
  double calc = dist_btw_shot_enemy(distance, angle);
  double accuracy_tolerance = 1.0;

  if (mod(calc) < accuracy_tolerance) {
    cout << "Nice shot!" << endl;
    return true;

  } else {
    stringstream ss;
    ss.precision(2);

    string miss_msg = "";
    miss_msg = "You ";
    miss_msg += (calc < 0) ? "under " : "over ";

    ss << miss_msg << std::fixed << calc << " fts away!";
    cout << ss.str() << endl;
    return false;
  }

  throw runtime_error("Unexpected error!");
}

bool ask_user_if_wanna_repeat() {
  string answer;

  cout << "Your score: " << score << endl;
  cout << " Do u wanna play again? [y/n] ";
  cin >> answer;
  return (answer == "y" || answer == "Y" || answer == "yes" ||
          answer == "Yes" || answer == "YES");
}

int generate_random_distances() {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(0, distances.size() - 1);

  return distances[dis(gen)];
}

double degree_to_rad(int degree) { return ((double)degree * (PI / 180.0)); }
double dist_btw_shot_enemy(int dist, int angle) {
  float velocity = 200.0; // fts/s
  float gravity = 32.2;
  double rad = degree_to_rad(angle);
  double time_in_air = (2.0 * velocity * sin(rad)) / gravity;
  double shot_dist = round((velocity * cos(rad)) * time_in_air);
  double precision = (double)dist - shot_dist;

  return precision;
}

void print_score() { std::cout << "SCORE: " << score << std::endl; }

void print_exit_message() {
  print_score();
  std::cout << "Exitting now..." << std::endl;
}

void print_header() {
  print_readme();
  cout << "Lets begin..." << endl;
}

void print_readme() {
  cout << "Welcome to Artilleryi *-* " << endl;
  cout << "You are in the middle of a war and being charged by thousands of "
          "enemies."
       << endl;
  cout << "You have one cannon, whick you can shoot at any angle." << endl;
  cout << "you have a limitited number of cannonballs for each target... "
       << endl;
  cout << "and u need adjust the cannon angle before each shot." << endl;
  cout << "if u get it right, ur cannonballs is recharged..." << endl;
  cout << "but if u miss all shots... is a GAME OVER!" << endl << endl << endl;
}

void print_gameover() {
  cout << "\033[2J\033[1;1H"; // clear
  cout << "\033[1;31m";

  const string filename = "src/data/gameover_char_drawn.txt";
  ifstream file(filename);

  if (file.is_open()) {
    string line;
    while (std::getline(file, line)) {
      std::cout << line << std::endl;
    }

    file.close();
  } else {
    cout << "Game Over!" << endl;
  }
}
