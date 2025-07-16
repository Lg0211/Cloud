import sys
sys.path.insert(0, "A:\\Code\\Cloud\\pybamm")  # 确保优先加载你的 PyBaMM
import pybamm
import Parameters
import numpy as np
import pandas as pd
from datetime import datetime
import time
from custom_plots import loss_plot
current_time = datetime.now().strftime("%Y%m%d-%H%M")
start_time = time.time()
#%%
Data = {
    "0.33C_DCHG": pd.read_excel("A:/Code/Cloud/Data/Cycle_0/倍率充放电测试.xlsx",sheet_name="0.33C_DCHG"),
    "0.5C_DCHG": pd.read_excel("A:/Code/Cloud/Data/Cycle_0/倍率充放电测试.xlsx",sheet_name="0.5C_DCHG"),
    "1C_DCHG": pd.read_excel("A:/Code/Cloud/Data/Cycle_0/倍率充放电测试.xlsx",sheet_name="1C_DCHG"),

    "0.33C_CHG": pd.read_excel("A:/Code/Cloud/Data/Cycle_0/倍率充放电测试.xlsx",sheet_name="0.33C_CHG"),
    "0.5C_CHG": pd.read_excel("A:/Code/Cloud/Data/Cycle_0/倍率充放电测试.xlsx",sheet_name="0.5C_CHG"),
    "1C_CHG": pd.read_excel("A:/Code/Cloud/Data/Cycle_0/倍率充放电测试.xlsx",sheet_name="1C_CHG"),
    "2C_CHG": pd.read_excel("A:/Code/Cloud/Data/Cycle_0/倍率充放电测试.xlsx",sheet_name="2C_CHG"),
    "3C_CHG": pd.read_excel("A:/Code/Cloud/Data/Cycle_0/倍率充放电测试.xlsx",sheet_name="3C_CHG"),
}
list =      ["0.33C_CHG","0.5C_CHG","1C_CHG","1.5C_CHG","2C_CHG","3C_CHG","0.33C_DCHG","0.5C_DCHG","1C_DCHG"]
time_stop = [ 12000 ,     8000 ,     3800 ,   2600 ,     2000,    1400,    12000,       8000,       3800]
time_num =  [ 1200 ,      800,       380 ,    260 ,      400,     700 ,    1200,        800 ,       380]
dict = {
    item: {"time_stop": stop, "time_num": num}
    for item, stop, num in zip(list, time_stop, time_num)
}
#list_opm  = ["0.33C_DCHG","0.5C_DCHG","1C_DCHG"]
list_opm_DCHG  = ["0.33C_DCHG"]
list_opm_CHG  = ["0.33C_CHG","0.5C_CHG","1C_CHG","2C_CHG","3C_CHG"]
#%%
model = pybamm.lithium_ion.DFN(options = {"thermal": "lumped",
                                          "SEI": "constant",  # 使用恒定SEI层厚度
                                          "SEI film resistance": "average",  # 启用SEI膜电阻
                                          "SEI porosity change": "false",  # 禁用由于SEI导致的孔隙度变化
                                          "lithium plating" :"reversible" #可逆析锂
                                          })

parameter_values = pybamm.ParameterValues(Parameters.get_parameter_values())

solutions = {}
for index in list_opm_DCHG:
    parameter_values["Current function [A]"] =  - Data[index]["Current [A]"][0] #Data[index]["Current [A]"][0]
    solver = pybamm.CasadiSolver(mode="safe", atol=1e-6, rtol=1e-3)
    sim = pybamm.Simulation(model, parameter_values=parameter_values, solver=solver)
    t_eval = np.linspace(0, dict[index]["time_stop"], dict[index]["time_num"])
    solution = sim.solve(t_eval,initial_soc=0.98)
    solutions[index] = solution
loss_plot(solutions, list_opm_DCHG, Data, current_time)

for index in list_opm_CHG:
    parameter_values["Current function [A]"] =  - Data[index]["Current [A]"][0] #Data[index]["Current [A]"][0]
    solver = pybamm.CasadiSolver(mode="safe", atol=1e-6, rtol=1e-3)
    sim = pybamm.Simulation(model, parameter_values=parameter_values, solver=solver)
    t_eval = np.linspace(0, dict[index]["time_stop"], dict[index]["time_num"])
    solution = sim.solve(t_eval)
    solutions[index] = solution
loss_plot(solutions,list_opm_CHG, Data, current_time)