# -*- coding: utf-8 -*-
"""
Created on Thu Mar 21 23:25:44 2024

@author: 22925
"""
import pybamm
import numpy as np
import pandas as pd

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
    """
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
	 """
    data = pd.read_excel("A:/Code/Cloud/Data/OCP/Postive_OCP_yang_3.xlsx")
    sto_data = data["Sto"].to_numpy()
    OCP_data = data["Voltage"].to_numpy()
    cs = pybamm.Interpolant(sto_data, OCP_data,sto,interpolator = "cubic" )
    return cs


""#%%正极交换电流密度

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
    data = pd.read_excel(r"A:\Code\Cloud\Data\dOCPdV\graphite_docp_data.xlsx")
    sto_data = data["Stoichiometry"].to_numpy()
    OCP_entropic_change_data = (data["Open_Circuit_Potential"]/96485.33212).to_numpy()
    #sto_data1 = x_dUdT_MCMB_3
    #OCP_entropic_change_data1 = y_dUdT_MCMB_3 / 96485.33212
    # 创建插值函数
    interp = pybamm.Interpolant(sto_data, OCP_entropic_change_data, sto,interpolator="cubic",extrapolate = True)
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
        "Negative electrode OCP entropic change [V.K-1]":Negative_electrode_OCP, #622
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
