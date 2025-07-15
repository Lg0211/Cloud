import sys
sys.path.insert(0, "A:\\Code\\Cloud\\pybamm")  # 确保优先加载你的 PyBaMM
import pybamm
import Parameters
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from datetime import datetime
import os
import time
#2025.7.14

#todo
current_time = datetime.now().strftime("%Y%m%d-%H%M")
start_time = time.time()
#%%
Data = {
    "0.33C_DCHG": pd.read_excel("A:/Code/Cloud/Data/Cycle_0/倍率充放电测试.xlsx",sheet_name="0.33C_DCHG"),
    "1C_DCHG": pd.read_excel("A:/Code/Cloud/Data/Cycle_0/倍率充放电测试.xlsx",sheet_name="1C_DCHG"),
    "0.33C_CHG": pd.read_excel("A:/Code/Cloud/Data/Cycle_0/倍率充放电测试.xlsx",sheet_name="0.33C_CHG"),
    "0.5C_CHG": pd.read_excel("A:/Code/Cloud/Data/Cycle_0/倍率充放电测试.xlsx",sheet_name="0.5C_CHG"),
    "1C_CHG": pd.read_excel("A:/Code/Cloud/Data/Cycle_0/倍率充放电测试.xlsx",sheet_name="1C_CHG"),
    "1.5C_CHG": pd.read_excel("A:/Code/Cloud/Data/Cycle_0/倍率充放电测试.xlsx",sheet_name="1.5C_CHG"),
    "2C_CHG": pd.read_excel("A:/Code/Cloud/Data/Cycle_0/倍率充放电测试.xlsx",sheet_name="2C_CHG"),
}
list = ["0.33C_CHG","0.5C_CHG","1C_CHG","1.5C_CHG","2C_CHG"]
time_stop = [12000 , 8000 , 3800 , 2600 , 2000]
time_num = [1200 ,  800, 380 , 260 , 200 ]
dict = {
    item: {"time_stop": stop, "time_num": num}
    for item, stop, num in zip(list, time_stop, time_num)
}
list_opm  = ["0.33C_CHG","0.5C_CHG","1C_CHG","1.5C_CHG"]

#%%
model = pybamm.lithium_ion.DFN(options = {"thermal": "lumped",
                                          "SEI": "constant",  # 使用恒定SEI层厚度
                                          "SEI film resistance": "average",  # 启用SEI膜电阻
                                          "SEI porosity change": "false",  # 禁用由于SEI导致的孔隙度变化
                                          })

parameter_values = pybamm.ParameterValues(Parameters.get_parameter_values())

solutions = {}

for index in list_opm:
    parameter_values["Current function [A]"] =  - Data[index]["Current [A]"][0] #Data[index]["Current [A]"][0]
    solver = pybamm.CasadiSolver(mode="safe", atol=1e-6, rtol=1e-3)
    sim = pybamm.Simulation(model, parameter_values=parameter_values, solver=solver)
    t_eval = np.linspace(0, dict[index]["time_stop"], dict[index]["time_num"])

    def callback(sol):
        print(f"当前时间: {sol.t[-1]}, 最大插值使用: {sol.all_interpolants_used}")
        return False  # 不终止求解

    solution = sim.solve(t_eval, callbacks=[callback])
    #solution = sim.solve(t_eval,initial_soc=0.7)
    solutions[index] = solution

#%%
colors = [
    (49/255.0, 18/255.0, 58/255.0),
    (68/255.0, 145/255.0, 254/255.0),
    (190/255.0, 32/255.0, 2/255.0),
    (253/255.0, 146/255.0, 42/255.0) ,
    (32/255.0, 199/255.0, 224/255.0),
]

plt.figure(figsize=(10, 8), dpi=100)
ax = plt.gca()  # 获取当前坐标轴
text_y_positions = []
i = 0
for index in list_opm:
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
    #RMSE计算
    voltage_interp = np.array([])
    voltage1_interp = np.array([])
    interp = np.linspace(np.min(dcap1), np.max(dcap1), 2000)
    voltage_interp = np.interp(interp, dcap, voltage)
    voltage1_interp = np.interp(interp, dcap1, voltage1)
    rmse = np.sqrt(np.mean((voltage1_interp - voltage_interp ) ** 2))*1000
    print(index+"_"+f"RMSE: {rmse}")
    #曲线绘制
    label0 = index + "_PyBaMM"
    label1 = index + "_real"
    dcap = dcap
    plt.plot(dcap, voltage, linewidth=1.8, label=label0, color=colors[i])
    indices = range(0, len(dcap1))  # 每隔10个点的索引
    dcap1 = dcap1
    plt.scatter(dcap1[::50], voltage1[::50],label=label1, color=colors[i], s=20)
    # 在右侧显示RMSE
    # 获取当前y轴范围
    ymin, ymax = ax.get_ylim()
    # 计算文本的y位置（均匀分布）
    text_y_pos = ymax - (ymax - ymin) * 0.07 * (list_opm.index(index) + 1)
    text_y_positions.append(text_y_pos)
    # 在右侧添加RMSE文本
    plt.text(ax.get_xlim()[1] * 1.02,  # x坐标：稍微超出右边界
             text_y_pos,
             f"{index} RMSE: {rmse:.3f} mV",
             fontdict={'family': 'Times New Roman', 'size': 16},
             color='black',
             verticalalignment='center')
    i = i+1
plt.tick_params(axis="both", which="major", direction="in", width=1.5, length=5)  #设置主副刻度大小
plt.tick_params(axis="both", which="minor", direction="in", width=1.5, length=3)
plt.minorticks_on()  #显示副标题


#添加图例
if text_y_positions:
    lowest_text_y = min(text_y_positions)
    legend_y = lowest_text_y - (ymax - ymin) * 0.1  # 再往下偏移 10% 的 y 轴范围
else:
    legend_y = ymin  # 如果没有 RMSE 文本，默认放在底部
# 计算 legend_y 在轴坐标中的位置（0~1）
_, legend_display_y = ax.transData.transform((0, legend_y))  # 获取显示坐标
_, ymin_display = ax.transData.transform((0, ymin))
_, ymax_display = ax.transData.transform((0, ymax))
legend_axis_y = (legend_display_y - ymin_display) / (ymax_display - ymin_display)  # 归一化
# 添加图例（使用轴坐标）
plt.legend(
    fontsize=14,
    frameon=False,
    prop={'family': 'Times New Roman', 'size': 16},
    bbox_to_anchor=(1.02, legend_axis_y),  # y 现在是 0~1 的轴坐标
    loc='upper left'
)
#plt.legend(fontsize=14, frameon=False, prop={'family': 'Times New Roman', 'size': 16},bbox_to_anchor=(1.02, legend_y),loc='upper left')
#
plt.xlabel("Discharge Capacity [A.h]", fontsize=24, fontproperties="Times New Roman")
plt.ylabel("Cell Voltage [V]", fontsize=24, fontproperties="Times New Roman")
plt.tick_params(axis='x', labelsize=20)
plt.tick_params(axis='y', labelsize=20)
picture_path = "A:/Code/Cloud/Data/Cycle_0/solution"
plt.savefig(os.path.join(picture_path,f"{current_time}_Cap_V.png"), dpi=300, bbox_inches='tight')
#1
end_time = time.time()
print(f"Time cost: {end_time - start_time}s")