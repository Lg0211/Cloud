import sys
sys.path.insert(0, "A:\\Code\\Cloud\\pybamm")  # 确保优先加载你的 PyBaMM
import pybamm
import Parameters
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from datetime import datetime
import os
current_time = datetime.now().strftime("%Y%m%d-%H%M")
#%%
def P_ocp(sto):
    sto_data = np.array([
        0.0e0, 2.610000E-01, 2.776070E-01, 2.942140E-01, 3.108210E-01, 3.274280E-01, 3.440350E-01, 3.606420E-01,
        3.772490E-01,
        3.938560E-01, 4.104630E-01, 4.270700E-01, 4.436770E-01, 4.603579E-01, 4.769649E-01, 4.935719E-01, 5.101789E-01,
        5.267859E-01,
        5.433929E-01, 5.599999E-01, 5.766069E-01, 5.932139E-01, 6.098209E-01, 6.264279E-01, 6.430349E-01, 6.596419E-01,
        6.762489E-01,
        6.928559E-01, 7.094629E-01, 7.260699E-01, 7.426769E-01, 7.592839E-01, 7.758909E-01, 7.924980E-01, 8.091050E-01,
        8.257120E-01,
        8.423190E-01, 8.589260E-01, 8.756068E-01, 8.922138E-01, 9.088208E-01, 9.254278E-01, 9.420348E-01, 9.492700E-01,
        9.550000E-01,
        9.600000E-01, 9.650000E-01, 9.700000E-01, 9.750000E-01, 9.800000E-01, 9.850000E-01, 9.900000E-01, 9.950000E-01,
        1.000000E+00])

    OCP_data = np.array([
        4.800e0, 4.2726E+00, 4.239000E+00, 4.207100E+00, 4.175700E+00, 4.145100E+00, 4.115100E+00, 4.086100E+00,
        4.058200E+00,
        4.031300E+00, 4.004900E+00, 3.979000E+00, 3.953400E+00, 3.928300E+00, 3.903500E+00, 3.880200E+00, 3.858200E+00,
        3.837900E+00,
        3.819900E+00, 3.804200E+00, 3.790900E+00, 3.779100E+00, 3.768700E+00, 3.759300E+00, 3.750600E+00, 3.742000E+00,
        3.733900E+00,
        3.725500E+00, 3.716900E+00, 3.707800E+00, 3.698400E+00, 3.688500E+00, 3.678200E+00, 3.667500E+00, 3.656600E+00,
        3.645600E+00,
        3.634400E+00, 3.623100E+00, 3.611100E+00, 3.598000E+00, 3.582800E+00, 3.564100E+00, 3.539200E+00, 3.526200E+00,
        3.504580E+00,
        3.483240E+00, 3.456450E+00, 3.423070E+00, 3.381810E+00, 3.331230E+00, 3.269720E+00, 3.195510E+00, 3.106680E+00,
        3.001080E+00])

    sto = np.clip(sto, sto_data[0], sto_data[-1])  # 防止超出插值范围
    ocp = np.interp(sto, sto_data, OCP_data)
    return ocp

"""
def graphite_ocp(sto):  # 修正过的OCP mohatat
    sto = np.array(sto)  # 确保是 NumPy 数组，支持批量计算
    gamma = -0.01185456
    U_eq1 = (
            0.063 + 0.8 * np.exp(-75 * (((1 - gamma) * sto + gamma) + 0.001))
            - 0.012 * np.tanh((((1 - gamma) * sto + gamma) - 0.127) / 0.016)
            - 0.0118 * np.tanh((((1 - gamma) * sto + gamma) - 0.155) / 0.016)
            - 0.0035 * np.tanh((((1 - gamma) * sto + gamma) - 0.22) / 0.02)
            - 0.0095 * np.tanh((((1 - gamma) * sto + gamma) - 0.19) / 0.013)
            - 0.0145 * np.tanh((((1 - gamma) * sto + gamma) - 0.49) / 0.02)
            - 0.08 * np.tanh((((1 - gamma) * sto + gamma) - 1.03) / 0.055)
    )
    return U_eq1
"""
def graphite_ocp(sto):
    sto = np.array(sto)
    u_eq1 = (
            0.16576
            + 0.84157 * np.exp(-61.25108 * sto)
            + 0.39197 * np.exp(-500.38943 * sto)
            - np.exp(2.81471 * sto - 4.91298)
            - 0.02689 * np.arctan(25.59 * sto - 4.099)
            - 0.00717 * np.arctan(32.49 * sto - 15.74)
    )
    return u_eq1
#%%
C_rate = 1
#%%
Data = {
    "0.33C_DCHG": pd.read_excel("A:/Code/Cloud/Data/Cycle_0/倍率充放电测试.xlsx",sheet_name="0.33C_DCHG"),
    "1C_DCHG": pd.read_excel("A:/Code/Cloud/Data/Cycle_0/倍率充放电测试.xlsx",sheet_name="1C_DCHG"),
    "0.33C_CHG": pd.read_excel("A:/Code/Cloud/Data/Cycle_0/倍率充放电测试.xlsx",sheet_name="0.33C_CHG"),
}

model = pybamm.lithium_ion.DFN(options = {"thermal": "lumped",
                                          "SEI": "constant",  # 使用恒定SEI层厚度
                                          "SEI film resistance": "average",  # 启用SEI膜电阻
                                          "SEI porosity change": "false",  # 禁用由于SEI导致的孔隙度变化
                                          })

parameter_values = pybamm.ParameterValues(Parameters.get_parameter_values())
list0 = ["0.33C_CHG"]
solutions = {}

for index in list0:
    parameter_values["Current function [A]"] =  - Data[index]["Current [A]"][0] #Data[index]["Current [A]"][0]
    solver = pybamm.CasadiSolver(mode="safe", atol=1e-6, rtol=1e-3)
    sim = pybamm.Simulation(model, parameter_values=parameter_values, solver=solver)
    t_eval = np.linspace(0, 12000, 1200)


    def callback(sol):
        print(f"当前时间: {sol.t[-1]}, 最大插值使用: {sol.all_interpolants_used}")
        return False  # 不终止求解


    solution = sim.solve(t_eval, callbacks=[callback])
    #solution = sim.solve(t_eval,initial_soc=0.7)
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

    #绘制极化
    ncm_concent = solutions[index]['Average positive particle concentration [mol.m-3]'].data
    ncm_ocp = P_ocp(ncm_concent/parameter_values["Maximum concentration in positive electrode [mol.m-3]"])
    gr_concent = solutions[index]['Average negative particle concentration [mol.m-3]'].data
    gr_ocp = graphite_ocp(gr_concent /parameter_values["Maximum concentration in negative electrode [mol.m-3]"])
    plt.plot(dcap, ncm_ocp, linewidth=1.8, label='P_ocp_average', color=black)
    plt.plot(dcap, gr_ocp, linewidth=1.8, label='N_ocp_average', color=black)

    #取表面最大化学计量数，靠近集流体
    c_surf_pos = solutions["0.33C_CHG"]["Positive particle surface concentration [mol.m-3]"].data[0,:].reshape(-1,1)
    ocp_pos =  P_ocp(c_surf_pos/parameter_values["Maximum concentration in positive electrode [mol.m-3]"])
    plt.plot(dcap, ocp_pos, linewidth=1.8, label='P_ocp', color="gray")
    c_surf_neg = solutions["0.33C_CHG"]["Negative particle surface concentration [mol.m-3]"].data[0, :].reshape(-1, 1)
    ocp_neg = graphite_ocp(c_surf_neg / parameter_values["Maximum concentration in negative electrode [mol.m-3]"])
    plt.plot(dcap, ocp_neg, linewidth=1.8, label='N_ocp', color="gray")

    plt.plot(dcap, ocp_pos-ocp_neg, linewidth=1.8, label='P-N', color="green")


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
    plt.plot(dcap, voltage, linewidth=1.8, label=label0, color=red)
    indices = range(0, len(dcap1))  # 每隔10个点的索引
    dcap1 = dcap1
    plt.scatter(dcap1[::50], voltage1[::50],label=label1, color=blue, s=20)
    #

    #plt.scatter(dcap1[indices], voltage1[indices], color=colors[index], marker='s', label=label1,s=3)

# 在曲线图上添加 RMSE 文本，取位置为放电容量中段
mid_idx = len(interp) // 2
plt.text(interp[mid_idx], voltage1_interp[mid_idx] + 0.38,  # Y值可上下微调
         f"RMSE: {rmse:.1f} mV",
         fontsize=18, color='gray')
data_OCV = pd.read_excel(r"A:\Code\Cloud\Data\OCV\OCV.xlsx")
SOC = data_OCV['SOC']
OCV = data_OCV["Voltage"]
plt.scatter(SOC, OCV,label='OCV', color="red")
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
