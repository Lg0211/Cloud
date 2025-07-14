# -*- coding: utf-8 -*-
"""
Created on Thu Mar 21 23:25:44 2024

@author: 22925
"""
import pybamm
import numpy as np
import pandas as pd
from scipy.interpolate import CubicSpline

x_dUdT_MCMB_3 = np.array([
    0.000454907, 0.00136472, 0.00181963, 0.00238826, 0.00318435, 0.00386671,
    0.00432162, 0.0046628, 0.00511771, 0.00568634, 0.00625498, 0.00659616,
    0.00682361, 0.00727852, 0.00796088, 0.00841579, 0.00875697, 0.0093256,
    0.0101217, 0.0113727, 0.0131923, 0.0151257, 0.0167178, 0.01831, 0.0206983,
    0.0237689, 0.0267258, 0.0290003, 0.0304788, 0.0315023, 0.0322984,
    0.0330945, 0.034118, 0.0352553, 0.0363926, 0.0375299, 0.0383259, 0.0388946,
    0.0395769, 0.0404868, 0.0413966, 0.0421927, 0.042875, 0.0435574,
    0.0443535, 0.0452633, 0.0467417, 0.0483339, 0.04913, 0.0522006, 0.0532242,
    0.0549301, 0.0570909, 0.059138, 0.061185, 0.0632321, 0.0652792,
    0.0677812, 0.0706244, 0.0732401, 0.0756283, 0.0783578, 0.0815421,
    0.0847265, 0.0876834, 0.090754, 0.0943933, 0.0987149, 0.103491, 0.109064,
    0.115205, 0.121688, 0.12817, 0.13488, 0.141704, 0.1483, 0.154668,
    0.160923, 0.16752, 0.17423, 0.180712, 0.186512, 0.192426, 0.198908, 0.205732,
    0.212442, 0.218924, 0.225407, 0.232003, 0.238713, 0.245422, 0.252019,
    0.258387, 0.26487, 0.271466, 0.27829, 0.285682, 0.293529, 0.301604,
    0.309564, 0.317525, 0.325372, 0.333333, 0.341408, 0.349483, 0.357443,
    0.365404, 0.373024, 0.380416, 0.387581, 0.394973, 0.402593, 0.41044,
    0.418515, 0.426817, 0.435574, 0.442739, 0.447288, 0.453429, 0.458547,
    0.465711, 0.470829, 0.474923, 0.477994, 0.479586, 0.480837, 0.481292,
    0.482315, 0.484363, 0.485727, 0.48641, 0.486865, 0.487092, 0.487661,
    0.49039, 0.496418, 0.497214, 0.502559, 0.508814, 0.515865, 0.523485,
    0.531445, 0.539634, 0.547367, 0.554759, 0.562152, 0.569885, 0.578073,
    0.586262, 0.59445, 0.602638, 0.610827, 0.618901, 0.626749, 0.634709,
    0.64267, 0.650745, 0.658933, 0.667122, 0.67531, 0.683385, 0.691573,
    0.699647, 0.707495, 0.715001, 0.722393, 0.730013, 0.737973, 0.746048,
    0.754123, 0.762311, 0.770499, 0.778574, 0.786648, 0.794837, 0.802911,
    0.810986, 0.819174, 0.827249, 0.83521, 0.843171, 0.85079, 0.857955, 0.865006,
    0.872057, 0.878995, 0.885818, 0.892073, 0.897532, 0.902309, 0.906517,
    0.910497, 0.914477, 0.91823, 0.921642, 0.924372, 0.926305, 0.929376
])
y_dUdT_MCMB_3 = np.array([61.4112, 60.5429, 59.6746, 58.8183, 57.9621, 57.0937, 56.2375, 55.3691,
                          54.5008, 53.6325, 52.7641, 51.8958, 51.0274, 50.1712, 49.3028, 48.4466,
                          47.5782, 46.7099, 45.8416, 44.9854, 44.1293, 43.2852, 42.4291, 41.5729,
                          40.741, 39.9453, 39.1496, 38.3176, 37.4615, 36.5932, 35.7249, 34.8566,
                          33.9883, 33.1321, 32.2759, 31.4197, 30.5635, 29.6952, 28.8268, 27.9706,
                          27.1144, 26.2461, 25.3778, 24.5095, 23.6653, 22.8211, 21.9529,
                          21.0968, 19.5169, 18.7574, 17.8891, 17.1174, 16.2854, 15.4414, 14.5973,
                          13.7533, 12.9092, 12.0773, 11.2575, 10.4376, 9.60568, 8.78583, 7.99016,
                          7.18242, 6.37466, 5.56691, 4.79541, 4.06017, 3.36115, 2.73459, 2.16839,
                          1.63842, 1.1205, 0.614671, 0.120915, -0.384928, -0.914916, -1.46904,
                          -1.98694, -2.46865, -2.9745, -3.52868, -4.07078, -4.55251, -5.02214,
                          -5.50385, -6.02177, -6.55174, -7.06965, -7.57548, -8.0813, -8.61127,
                          -9.15332, -9.68329, -10.2133, -10.6829, -11.0319, -11.2602, -11.4523,
                          -11.6444, -11.8606, -12.0889, -12.281, -12.4369, -12.5808, -12.7488,
                          -12.9891, -13.3139, -13.6991, -14.0963, -14.4574, -14.7701, -15.0105,
                          -15.1302, -15.1414, -15.0198, -14.6934, -14.1984, -13.7635, -13.6544,
                          -13.8708, -13.6531, -12.8928, -12.2412, -11.3606, -10.5041, -9.64774,
                          -7.93498, -7.12668, -6.34257, -5.53442, -4.6901, -3.80963, -2.91706,
                          -2.14487, -1.64972, -1.66169, -2.21591, -2.7821, -3.21552, -3.5524, -3.76864,
                          -3.80393, -3.7066, -3.65756, -3.705, -3.77652, -3.81182, -3.81093,
                          -3.83416, -3.89358, -3.96505, -4.08479, -4.25279, -4.45696, -4.62495,
                          -4.72056, -4.76791, -4.75496, -4.69377, -4.60847, -4.58346, -4.67907,
                          -4.90737, -5.2322, -5.60529, -5.91804, -6.14634, -6.30225, -6.40992,
                          -6.46934, -6.55288, -6.67261, -6.76822, -6.81558, -6.85088, -6.91031,
                          -6.99385, -7.1377, -7.31775, -7.53398, -7.83468, -8.21985, -8.65328,
                          -9.09877, -9.56839, -10.0742, -10.6283, -11.267, -11.966, -12.7012,
                          -13.4486, -14.208, -14.9795, -15.7631, -16.5829, -17.4511, -18.2227
                          ])


#%%
def graphite_ocp(sto):
    u_eq1 = (
            0.16576
            + 0.84157 * pybamm.exp(-61.25108 * sto)
            + 0.39197 * pybamm.exp(-500.38943 * sto)
            - pybamm.exp(2.81471 * sto - 4.91298)
            - 0.02689 * pybamm.arctan(25.59 * sto - 4.099)
            - 0.00717 * pybamm.arctan(32.49 * sto - 15.74)
    )
    return u_eq1

def graphite_ocp_smoothed(sto):
    """平滑过渡的石墨电极开路电位函数"""
    # 原始OCP计算部分
    u_eq1 = graphite_ocp(sto)
    # 平滑过渡参数
    transition_start = 0.6
    transition_width = 0.05
    # 计算sigmoid权重因子
    weight = 1 / (1 + np.exp((sto - transition_start) / transition_width))
    # 计算在0.6处的值作为目标值
    target_value = graphite_ocp(transition_start)
    # 混合原始值和目标值
    return weight * u_eq1 + (1 - weight) * target_value



def graphite_ocp1(sto):  #修正过的OCP
    gamma=-0.01185456
    U_eq1 = (
        0.063+0.8*pybamm.exp(-75*(((1-gamma)*sto+gamma)+0.001))
        -0.012*pybamm.tanh((((1-gamma)*sto+gamma)-0.127)/0.016)
        -0.0118*pybamm.tanh((((1-gamma)*sto+gamma)-0.155)/0.016)
        -0.0035*pybamm.tanh((((1-gamma)*sto+gamma)-0.22)/0.02)
        -0.0095*pybamm.tanh((((1-gamma)*sto+gamma)-0.19)/0.013)
        -0.0145*pybamm.tanh((((1-gamma)*sto+gamma)-0.49)/0.02)
        -0.08*pybamm.tanh((((1-gamma)*sto+gamma)-1.03)/0.055)
        )
    return U_eq1

#%%负极交换电流密度
def graphite_electrolyte_exchange_current_density(c_e, c_s_surf, c_s_max, T):
    i0_ref_n = 2.5
    E_r = 30000
    c_e_ref = 1000
    c_s_ref = c_s_max / 2
    i0_ref_n_T = i0_ref_n * np.exp(E_r / pybamm.constants.R * (1 / 298.15 - 1 / T))

    i0 = (i0_ref_n_T
          * (c_s_surf / c_s_ref) ** 0.5
          * ((c_s_max - c_s_surf) / (c_s_max - c_s_ref)) ** 0.5
          * (c_e / c_e_ref) ** 0.5

          )
    return i0 * 0.1


#%%

def nmc_ocp(sto):
    u_eq = (
            -8020.81494 * (sto ** 9)
            + 39786.59811 * (sto ** 8)
            - 86102.41163 * (sto ** 7)
            + 106677.76244 * (sto ** 6)
            - 83401.82681 * (sto ** 5)
            + 42680.6344 * (sto ** 4)
            - 14297.87593 * (sto ** 3)
            + 3024.41277 * (sto ** 2)
            - 368.92449 * sto
            - 8852.55398
            + 8876.89729 * np.exp(-6395198 * (sto ** 255))
    )
    return u_eq

def nmc_ocp1(sto):
    data = pd.read_excel("A:/Code/Cloud/Data/OCP/Postive_OCP.xlsx")
    sto_data = data["Sto"].to_numpy()
    OCP_data = data["Voltage"].to_numpy()
    # 创建插值函数
    interp = pybamm.Interpolant(sto_data, OCP_data, sto)

def nmc_ocp2(sto):  #change OCP
    sto_data=np.array([
   	 0.0e0, 2.610000E-01, 2.776070E-01, 2.942140E-01, 3.108210E-01, 3.274280E-01, 3.440350E-01, 3.606420E-01, 3.772490E-01,
   	 3.938560E-01, 4.104630E-01, 4.270700E-01, 4.436770E-01, 4.603579E-01, 4.769649E-01, 4.935719E-01, 5.101789E-01, 5.267859E-01,
   	 5.433929E-01, 5.599999E-01, 5.766069E-01, 5.932139E-01, 6.098209E-01, 6.264279E-01, 6.430349E-01, 6.596419E-01, 6.762489E-01,
   	 6.928559E-01, 7.094629E-01, 7.260699E-01, 7.426769E-01, 7.592839E-01, 7.758909E-01, 7.924980E-01, 8.091050E-01, 8.257120E-01,
   	 8.423190E-01, 8.589260E-01, 8.756068E-01, 8.922138E-01, 9.088208E-01, 9.254278E-01, 9.420348E-01, 9.492700E-01, 9.550000E-01,
   	 9.600000E-01, 9.650000E-01, 9.700000E-01, 9.750000E-01, 9.800000E-01, 9.850000E-01, 9.900000E-01, 9.950000E-01, 1.000000E+00])
    OCP_data=np.array([
	 4.800e0, 4.2726E+00, 4.239000E+00, 4.207100E+00, 4.175700E+00, 4.145100E+00, 4.115100E+00, 4.086100E+00, 4.058200E+00,
	 4.031300E+00, 4.004900E+00, 3.979000E+00, 3.953400E+00, 3.928300E+00, 3.903500E+00, 3.880200E+00, 3.858200E+00, 3.837900E+00,
	 3.819900E+00, 3.804200E+00, 3.790900E+00, 3.779100E+00, 3.768700E+00, 3.759300E+00, 3.750600E+00, 3.742000E+00, 3.733900E+00,
	 3.725500E+00, 3.716900E+00, 3.707800E+00, 3.698400E+00, 3.688500E+00, 3.678200E+00, 3.667500E+00, 3.656600E+00, 3.645600E+00,
	 3.634400E+00, 3.623100E+00, 3.611100E+00, 3.598000E+00, 3.582800E+00, 3.564100E+00, 3.539200E+00, 3.526200E+00, 3.504580E+00,
	 3.483240E+00, 3.456450E+00, 3.423070E+00, 3.381810E+00, 3.331230E+00, 3.269720E+00, 3.195510E+00, 3.106680E+00, 3.001080E+00])
    cs = pybamm.Interpolant(sto_data, OCP_data,sto)
    return cs


#%%正极交换电流密度

def nmc_electrolyte_exchange_current_density(c_e, c_s_surf, c_s_max, T):
    i0_ref_p = 1.5
    E_r = 30000
    c_e_ref = 1000
    c_s_ref = c_s_max / 2

    i0_ref_p_T = i0_ref_p * np.exp(E_r / pybamm.constants.R * (1 / 298.15 - 1 / T))

    i0_p = (i0_ref_p_T
            * (c_s_surf / c_s_ref) ** 0.5
            * ((c_s_max - c_s_surf) / (c_s_max - c_s_ref)) ** 0.5
            * (c_e / c_e_ref) ** 0.5

            ) * 0.99
    return i0_p * 0.5


#%%

def electrolyte_diffusivity(c_e, T): #155
    def DL_int(x):
        y = 3.55476e-10 + 2.4037e-13 * x - 2.23266e-16 * (x ** 2) + 3.11389e-20 * (x ** 3)
        return y
    T_ref = 298.15
    D_c_e = DL_int(c_e) * np.exp(16500 / 8.314 * (1 / T_ref - 1 / T))
    return D_c_e

def electrolyte_conductivity(c_e, T):
    T_ref = 298.15

    def sigmal_int1(x):
        y = 0.0098 + 0.00254 * x - 2.29036e-6 * x ** 2 + 8.00916e-10 * x ** 3 - 1.077e-13 * x ** 4
        return y

    sigma_e = sigmal_int1(c_e) * np.exp(14000 / 8.314 * (1 / T_ref - 1 / T))
    return sigma_e


def NMC_electrode_diffusivity(sto, T):
    D_s_p_ref = 3.5e-15* 5 #-14 - -15
    R = 8.314472
    D_s_p = D_s_p_ref * np.exp(12e4 / R * (1 / 298.15 - 1 / T))
    return D_s_p * 0.99999 *5


def graphite_electrode_diffusivity(sto, T):
    R = 8.314472 #-13 -14
    D_s_n = 1.15 * 0.21e-14 * np.exp(12e4 / R * (1 / 298.15 - 1 / T)) * (1.5 - sto) ** 1.5 * 1.2
    return D_s_n * 0.999 * 10


def Cation_transference_number(c_s, T):
    num = (0.37396
           + 8.94711e-5 * c_s
           - 6.56778e-7 * c_s ** 2
           + 6.18161e-10 * c_s ** 3
           - 1.72576e-13 * c_s ** 4
           )
    return num * 0.999


#%% #note 待修改
def Negative_electrode_OCP(sto):
    #print(type(sto))
    data = pd.read_excel("A:/Code/ACES/Pybamm/DFN/dOCPdT/N_dOCPdT.xlsx")
    sto_data = data["化学计量数"].to_numpy()
    OCP_entropic_change_data = data["dOCPdT"].to_numpy()
    sto_data1 = x_dUdT_MCMB_3
    OCP_entropic_change_data1 = y_dUdT_MCMB_3 / 96485.33212
    # 创建插值函数
    interp = pybamm.Interpolant(sto_data1, OCP_entropic_change_data1, sto)
    return interp


def Positive_electrode_OCP(sto):

    docpdt = (((0.4 - sto) * 0.2e-3) * (sto <= 0.4)
              + ((-3.0 * (sto - 0.4)) * 0.2e-3) * (sto > 0.4) * (sto <= 0.5)
              + ((-0.3 + (sto - 0.5) * 2.5) * 0.2e-3) * (sto > 0.5) * (sto <= 0.7)
              + ((0.2 - (sto - 0.7) * 5.0 / 3.0) * 0.2e-3) * (sto > 0.7) * (sto <= 1)
              )

    return docpdt


#%%
# Call dict via a function to avoid errors when editing in place
def get_parameter_values():
    return {
        "chemistry": "lithium_ion",
        # cell
        "Negative current collector thickness [m]": 1e-05,  #measure
        "Negative electrode thickness [m]": 7.5e-05,  #measure
        "Separator thickness [m]": 1.6e-05,#622
        "Positive electrode thickness [m]": 5.9e-05,#measure
        "Positive current collector thickness [m]": 1.5e-05,  #measure
        "Electrode height [m]": 2.6e-01,  #measure
        "Electrode width [m]": 8.9e-02,  #measure
        "Nominal cell capacity [A.h]": 53.19,  #measure
        "Current function [A]": 25.25,  #main中修改
        # negative electrode
        "Negative electrode conductivity [S.m-1]": 100.0,  #622
        "Maximum concentration in negative electrode [mol.m-3]": 31252.0,  #622
        "Negative electrode diffusivity [m2.s-1]": graphite_electrode_diffusivity,#622
        "Negative electrode OCP [V]": graphite_ocp_smoothed,#Yang
        "Negative electrode porosity": 0.32608,  #622
        "Negative electrode active material volume fraction": 0.64392, #0.97 - Negative electrode porosity
        "Negative particle radius [m]": 5e-06,  #622      负极粒子半径6，直径10
        "Negative electrode Bruggeman coefficient (electrolyte)": 2.5, #622
        "Negative electrode Bruggeman coefficient (electrode)": 0,
        "Negative electrode exchange-current density [A.m-2]"
        "": graphite_electrolyte_exchange_current_density,#622
        "Negative electrode OCP entropic change [V.K-1]": Negative_electrode_OCP, #622
        # positive electrode
        "Positive electrode conductivity [S.m-1]": 10,  #622
        "Maximum concentration in positive electrode [mol.m-3]":49520.78,  #622
        "Positive electrode diffusivity [m2.s-1]": NMC_electrode_diffusivity, #622
        "Positive electrode OCP [V]": nmc_ocp2,
        "Positive electrode porosity": 0.32,  #Yang
        "Positive electrode active material volume fraction": 0.65, #0.95 - "Positive electrode porosity"
        "Positive particle radius [m]": 5e-06, #Yang
        "Positive electrode Bruggeman coefficient (electrolyte)": 2.15, #1.5-2.5
        "Positive electrode Bruggeman coefficient (electrode)": 0,
        "Positive electrode exchange-current density [A.m-2]"
        "": nmc_electrolyte_exchange_current_density, #622
        "Positive electrode OCP entropic change [V.K-1]": Positive_electrode_OCP,#622
        # separator
        "Separator porosity": 0.43,#622
        "Separator Bruggeman coefficient (electrolyte)": 2.6,#622
        # electrolyte
        "Initial concentration in electrolyte [mol.m-3]": 1000.0,#622
        "Cation transference number": Cation_transference_number,#622
        "Thermodynamic factor": 1.0,#622
        "Electrolyte diffusivity [m2.s-1]": electrolyte_diffusivity,#622
        "Electrolyte conductivity [S.m-1]": electrolyte_conductivity,#622
        # experiment #初始SEI几十纳米 密度找文献
        "Reference temperature [K]": 298.15,
        "Ambient temperature [K]": 298.15,
        "Number of electrodes connected in parallel to make a cell": 70.0, #measure
        "Number of cells connected in series to make a battery": 1.0,#measure
        "Lower voltage cut-off [V]": 2.5,
        "Upper voltage cut-off [V]": 4.2,
        "Open-circuit voltage at 0% SOC [V]": 2.8,#measure
        "Open-circuit voltage at 100% SOC [V]": 4.18,#measure 4.18
        "Initial concentration in negative electrode [mol.m-3]": 31252.0 * (0.01462867 - 0.01 ) ,#note  31252.0 * 0.69000747  0.01422177   31252.0 * 0.8250747
        "Initial concentration in positive electrode [mol.m-3]": 49520.78 * (0.89252436 + 0.019),#note 36360 * 0.27824213   0.85907807
        "Initial temperature [K]": 298.15,  #%%
        #themal
        "Total heat transfer coefficient [W.m-2.K-1]": 10,  #note 待修正
        "Negative current collector conductivity [S.m-1]": 58411000.0,
        "Positive current collector conductivity [S.m-1]": 36914000.0,
        "Cell volume [m3]": 3.487E-4, #规格书计算结果
        "Cell cooling surface area [m2]": 6.91e-02, #规格书计算结果
        "Negative current collector density [kg.m-3]": 2124.5, #measure
        "Positive current collector density [kg.m-3]": 2124.5, #measure
        "Negative current collector specific heat capacity [J.kg-1.K-1]": 1100.0, #EVE
        "Positive current collector specific heat capacity [J.kg-1.K-1]": 1100.0, #EVE
        "Negative electrode density [kg.m-3]": 2.24e3,  #measure
        "Positive electrode density [kg.m-3]": 4.8e3,   #measure
        "Negative electrode specific heat capacity [J.kg-1.K-1]": 1100, #EVE
        "Positive electrode specific heat capacity [J.kg-1.K-1]": 1100, #EVE
        "Separator density [kg.m-3]": 2124.5, #measure
        "Separator specific heat capacity [J.kg-1.K-1]": 1100, #EVE
        #SEI#note待修正
        "Ratio of lithium moles to SEI moles": 2.0, #
        "SEI partial molar volume [m3.mol-1]": 9.585e-05,
        "SEI resistivity [Ohm.m]": 1 / (5e-6),
        "Initial SEI thickness [m]": 5e-09,  #待修正
    }
