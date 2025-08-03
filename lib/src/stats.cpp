#include<cmath>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<cstring>
#include<math.h>
#include<fstream>
#include<time.h>
#include<limits.h>
#include <sys/stat.h>

#include "EVRP.hpp"
#include "stats.hpp"

using namespace std;

//Used to output offline performance and population diversity

FILE *log_performance;
//output files
char *perf_filename;

double* perf_of_trials;

void open_stats(string algorithm, string outpath){
  // Initialize trial performance array
  perf_of_trials = new double[MAX_TRIALS];
  for (int i = 0; i < MAX_TRIALS; i++) {
    perf_of_trials[i] = 0.0;
  }

  // Get the task name from problem_instance
  const fs::path problem_path(problem_instance);
  string problem_name = problem_path.stem().string();  // safely get "E-n22-k4"

  // Ensure output directory exists
  fs::create_directories(outpath);

  // Build output filename
  const string perf_path_str = outpath + "/stats." + problem_name + ".txt";

  // Open output file (safe version)
  log_performance = fopen(perf_path_str.c_str(), "w");
  if (log_performance == nullptr) {
    cerr << "Error: cannot open file for writing: " << perf_path_str << endl;
    exit(2);
  }
}


void get_mean(int r, double value) {

  perf_of_trials[r] = value;

}


double mean(double* values, int size){
  int i;
  double m = 0.0;
  for (i = 0; i < size; i++){
      m += values[i];
  }
  m = m / (double)size;
  return m; //mean
}

double stdev(double* values, int size, double average){
  int i;
  double dev = 0.0;

  if (size <= 1)
    return 0.0;
  for (i = 0; i < size; i++){
    dev += ((double)values[i] - average) * ((double)values[i] - average);
  }
  return sqrt(dev / (double)(size - 1)); //standard deviation
}

double best_of_vector(double *values, int l ) {
  double min;
  int k;
  k = 0;
  min = values[k];
  for( k = 1 ; k < l ; k++ ) {
    if( values[k] < min ) {
      min = values[k];
    }
  }
  return min;
}


double worst_of_vector(double *values, int l ) {
  double max;
  int k;
  k = 0;
  max = values[k];
  for( k = 1 ; k < l ; k++ ) {
    if( values[k] > max ){
      max = values[k];
    }
  }
  return max;
}



void close_stats(void){
  int i;
  double perf_mean_value, perf_stdev_value;

  //For statistics
  for(i = 0; i < MAX_TRIALS; i++){
    //cout << i << " " << perf_of_trials[i] << endl;
    //cout << i << " " << time_of_trials[i] << endl;
    fprintf(log_performance, "%.2f", perf_of_trials[i]);
    fprintf(log_performance,"\n");

  }

  perf_mean_value = mean(perf_of_trials,MAX_TRIALS);
  perf_stdev_value = stdev(perf_of_trials,MAX_TRIALS,perf_mean_value);
  fprintf(log_performance,"Mean %.2f\t ",perf_mean_value);
  fprintf(log_performance,"\tStd Dev %.2f\t ",perf_stdev_value);
  fprintf(log_performance,"\n");
  fprintf(log_performance, "Min: %.2f\t ", best_of_vector(perf_of_trials,MAX_TRIALS));
  fprintf(log_performance,"\n");
  fprintf(log_performance, "Max: %.2f\t ", worst_of_vector(perf_of_trials,MAX_TRIALS));
  fprintf(log_performance,"\n");


  fclose(log_performance);


}


void free_stats(){

  //free memory
  delete[] perf_of_trials;

}

ofstream log_evols;

void open_stats_of_evolution(string output_dir, string algorithm, string task, int run) {
  output_dir = output_dir + '/' + to_string(run);
  mkdir(output_dir.c_str(), 0777);
  const fs::path p(task);
  string evols_file_name = output_dir + "/evols." + p.stem().string() + ".csv";
  log_evols.open(evols_file_name);
  log_evols << "obj" << "," << "evals" << "," << "time" << endl;
  log_evols << std::fixed << std::setprecision(2);
}


void close_stats_of_evolution() {
  log_evols.close();
}

void stats_evols(const std::chrono::duration<double> duration, HMAGS& _hmags) {
  double evals = get_evals();

  log_evols << best_sol->tour_length << "," << evals << "," << duration.count() << endl;
}




