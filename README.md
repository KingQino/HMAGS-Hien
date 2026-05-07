# HMAGS-Hien

This repository contains a C++ implementation of `HMAGS` for the Electric Vehicle Routing Problem (EVRP).

## Source

This project is based on the following paper:

```bibtex
@article{hien2023greedy,
  title={A greedy search based evolutionary algorithm for electric vehicle routing problem},
  author={Hien, Vu Quoc and Dao, Tran Cong and Binh, Huynh Thi Thanh},
  journal={Applied Intelligence},
  volume={53},
  number={3},
  pages={2908--2922},
  year={2023},
  publisher={Springer}
}
```

## Build

From the project root:

```bash
cmake -S . -B build
cmake --build build
```

## Run HMAGS

Run from the project root:

```bash
./build/CEVRP-Hien HMAGS E-n22-k4.evrp stats
```

Or, if you are already in `build/`:

```bash
./CEVRP-Hien HMAGS E-n22-k4.evrp stats
```

Notes:

- The instance argument should be the filename only, for example `E-n22-k4.evrp`.
- Instance files are read from [benchmark](/Users/yhq/Desktop/AI-Code/Alg-Comparison/HMAGS-Hien/benchmark).
- Output is written under [stats](/Users/yhq/Desktop/AI-Code/Alg-Comparison/HMAGS-Hien/stats), for example `stats/HMAGS/E-n22-k4/`.
