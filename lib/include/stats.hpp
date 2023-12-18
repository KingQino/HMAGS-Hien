#define MAX_TRIALS 	2 									//DO NOT CHANGE THE NUMBER
#define CHAR_LEN 100
#include <string>
using namespace std;

void open_stats(string algorithm, string output_path);									//creates the output file
void close_stats(void);									//stores the best values for each run
void get_mean(int r, double value);						//stores the observation from each run
void free_stats();										//free memory


extern ofstream log_evols;
extern void open_stats_of_evolution(string output_dir, string algorithm, string task, int run);
extern void close_stats_of_evolution();
extern void stats_evols(long duration,  HMAGS& _hmags);