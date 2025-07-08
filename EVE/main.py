import pybamm
import Parameters
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from datetime import datetime
import os
current_time = datetime.now().strftime("%Y%m%d-%H%M")
#%%
C_rate = 1
#%%
Data = {
    "0.33C_DCHG": pd.read_excel("A:/Code/Cloud/Data/Cycle_0/倍率充放电测试.xlsx",sheet_name="0.33C_DCHG")
}

model = pybamm.lithium_ion.DFN(options = {"thermal": "lumped",
                                          "SEI": "constant",  # 使用恒定SEI层厚度
                                          "SEI film resistance": "average",  # 启用SEI膜电阻
                                          "SEI porosity change": "false",  # 禁用由于SEI导致的孔隙度变化
                                          })

parameter_values = pybamm.ParameterValues(Parameters.get_parameter_values())
list0 = ["0.33C_DCHG"]
solutions = {}

for index in list0:
    parameter_values["Current function [A]"] =  - Data[index]["Current [A]"][0]
    solver = pybamm.CasadiSolver(mode="safe", atol=1e-6, rtol=1e-3)
    sim = pybamm.Simulation(model, parameter_values=parameter_values, solver=solver)
    t_eval = np.linspace(0, 12000, 200)
    solution = sim.solve(t_eval)
    solutions[index] = solution

#%%
blue = (0, 0, 255)
black = (0, 0, 0)
red = (219, 0, 0)
black = tuple([x / 255.0 for x in black])
red = tuple([x / 255.0 for x in red])
blue = tuple([x / 255.0 for x in blue])
colors = {
    "0.3C_charge": red,
    "0.3C_discharge": blue,
    "3C_charge": black,
    "hppc_charge":red
    }
plt.figure(figsize=(10, 8), dpi=100)
for index in list0:
    if "hppc" in index:
        dcap = solutions[index]["Time [s]"].entries
        voltage = solutions[index]["Terminal voltage [V]"].entries
        dcap1 = Data_real[index]["Time [s]"]
        voltage1 = Data_real[index]["Terminal voltage [V]"]
    else:
        dcap = np.abs(solutions[index]["Discharge capacity [A.h]"].data)
        voltage = solutions[index]["Battery voltage [V]"].data
        dcap1 = np.abs(Data[index]["Capacity [A.h]"])
        voltage1 = Data[index]["Terminal voltage [V]"]
    voltage_interp = np.array([])
    voltage1_interp = np.array([])
    interp = np.linspace(np.min(dcap1), np.max(dcap1), 2000)
    voltage_interp = np.interp(interp, dcap, voltage)
    voltage1_interp = np.interp(interp, dcap1, voltage1)
    rmse = np.sqrt(np.mean((voltage1_interp - voltage_interp ) ** 2))*1000
    print(index+"_"+f"RMSE: {rmse}")
    label0 = index + "_PyBaMM"
    label1 = index + "_real"
    plt.plot(dcap, voltage, linewidth=1.8, label=label0, color=red)
    indices = range(0, len(dcap1))  # 每隔10个点的索引
    plt.plot(dcap1, voltage1, linewidth=1.8, label=label1, color=blue)
    #plt.scatter(dcap1[indices], voltage1[indices], color=colors[index], marker='s', label=label1,s=3)
#plt.plot(dcap1, voltage1, marker='s' ,label=labels[1],color=colors[0])`
plt.tick_params(axis="both", which="major", direction="in", width=1.5, length=5)  #设置主副刻度大小
plt.tick_params(axis="both", which="minor", direction="in", width=1.5, length=3)
plt.minorticks_on()  #显示副标题
#plt.gca().xaxis.set_minor_locator(MultipleLocator(.25))  #x轴主副刻度间距
#plt.gca().xaxis.set_major_locator(MultipleLocator(.5))
plt.legend(fontsize=14, frameon=False, prop={'family': 'Times New Roman', 'size': 16})
plt.xlabel("Discharge Capacity [A.h]", fontsize=24, fontproperties="Times New Roman")
plt.ylabel("Cell Voltage [V]", fontsize=24, fontproperties="Times New Roman")
plt.tick_params(axis='x', labelsize=20)
plt.tick_params(axis='y', labelsize=20)
picture_path = "A:/Code/Cloud/Data/Cycle_0/solution"
plt.savefig(os.path.join(picture_path,f"{current_time}_Cap_V.png"), dpi=300, bbox_inches='tight')
#1
