#include<iostream>
#include<string>
#include <chrono>
#include<filesystem>
#include "utils.hpp"         

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
  if (argc < 4) {
    cout << "Usage: " << argv[0] << " <algorithm> <problem_instance> <output_path>" << endl;
    return 1;
  }

  fs::path project_root;
  try {
    const fs::path exec_path = fs::canonical(argv[0]);  // get the absolute path of the executable
    project_root = exec_path.parent_path().parent_path();  // assume the project root is two levels up
  } catch (const fs::filesystem_error& e) {
    std::cerr << "Error resolving path: " << e.what() << '\n';
    std::exit(1);
  }

  const string algorithm = argv[1];
  const fs::path instance_path =  project_root / "benchmark" /fs::path(argv[2]);
  const fs::path output_path = project_root / fs::path(argv[3]);

  // Check if problem instance file exists
  if (!fs::exists(instance_path)) {
    cerr << "Error: Problem instance file not found: " << instance_path << endl;
    return 1;
  }

  std::string instance_string = instance_path.string();
  problem_instance = instance_string.data();
  read_problem(problem_instance);             // Read EVRP instance
  cout << "Reading from: " << problem_instance << "\n";
  fs::path p(problem_instance);
  string instance_name = p.stem().string();  // safely get "E-n22-k4"

  fs::path full_output_path = output_path / algorithm / instance_name;
  open_stats(algorithm, full_output_path.string());  // open stats output file
  cout << "Running " << MAX_TRIALS << " times" << endl;


  for (int run = 1; run <= MAX_TRIALS; ++run) {
    start_run(run);
    auto start_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::high_resolution_clock::now() - start_time;

    if (algorithm == "SACO") {
      SACO* ANTS = new SACO(1, 2, 80, 0.1, 2, 0);
      while (!termination_condition(1)) {
        ANTS->optimize();
      }
      save_solution(full_output_path.string(), algorithm, problem_instance, run);
      ANTS->free_SACO();
      delete ANTS;
    }
    else if (algorithm == "GS") {
      initialize_GS();
      gs_optimizer.run(gs_optimizer.best_solution);
      save_solution(full_output_path.string(), algorithm, problem_instance, run);
      free_GS();
    }
    else if (algorithm == "HMAGS") {
      initialize_HMAGS();

      open_stats_of_evolution(full_output_path, algorithm, problem_instance, run);
      while (!termination_condition(1)) {
        run_HMAGS();
        duration = std::chrono::high_resolution_clock::now() - start_time;

        stats_evols(duration, hmags);
      }
      close_stats_of_evolution();

      save_solution(full_output_path.string(), algorithm, problem_instance, run);
      free_HMAGS();
    }
    else if (algorithm == "SA") {
      initialize_SA();
      SA_optimizer.run(SA_optimizer.cur_sol);
      save_solution(full_output_path.string(), algorithm, problem_instance, run);
      free_SA();
    }
    else {
      cerr << "Error: Algorithm \"" << algorithm << "\" not found" << endl;
    }

    end_run(run);
  }

  close_stats();
  return 0;
}
