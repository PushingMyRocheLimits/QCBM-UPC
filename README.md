# QCBM-UPC
Project for PHSX 801; A Quantum Circuit Born Machine that is to be trained on Ultra-Peripheral Collision Monte-Carlo data.   

<img width="1634" height="475" alt="2DQCBM" src="https://github.com/user-attachments/assets/2f85e43b-ab66-4344-b5b6-e0139be24c07" />

## Repository Structure:
- Start-up:
  - Convert the `slight.out` ASCII file into a `.root` file using `code.py`
- QCBM Simulations
  - Run a 4-Qubit QCBM simulation for the 1D p_T spectra using `code.py`
  - Run a 6-Qubit QCBM simulation for the 2D p_T and invariant mass spectra using `code.py`
- QCBM for IBM Quantum Computer grid
  - Run a 6-Qubit QCBM for the 2D p_t and invariant mass spectra on a real IBM QPU using `code.py`

## How to Run
1) Install [STARlight](https://github.com/STARlightsim/STARlight) and make your desired MC dataset
2) Create a new virtual environment: `python -m venv qcbm_env`
3) Activate the environment: `source qcbm_env/bin/activate`
4) Install Qiskit, local simulators, and plotting/optimization tools: `pip install qiskit qiskit-aer qiskit-ibm-runtime scipy numpy matplotlib uproot awkward`
5) Download desired QCBM code and place in same directory as MC dataset
6) Run the `code.py` to convert the output of STARlight into something the QCBM code can read
7) Run desired QCBM code using: `python3 ***.py`
