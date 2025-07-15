#%%

M_Li = 6.941
M_Ni = 58.693
M_Mn = 54.938
M_Co = 58.933
M_O = 15.999

Mw = (M_Li+M_Ni*0.6+M_Mn*0.2+M_Co*0.2+M_O*2.0)*1.0e-3
density = 4.8e3
cs_max = density/Mw #NCM622的最大嵌锂浓度：49520.7832537218
#%%
Mw = 72.06e-3
density = 2.24e3
cs_max =density/Mw
print(cs_max)
#%%
a = 2.6e-01
b =  8.9e-02
h = 7.5e-05

sto_max = ( 52/26.8 ) / ((a*b*h*70)*0.64)/31252
print(sto_max)
#%%正极最大嵌锂浓度计算
Cs_neg = 31252
h_neg = 7.5e-05
h_pos = 5.9e-05

dx = 0.01654871
dy = 0.01086689

Cs_pos = Cs_neg * h_neg * dx / ( h_pos * dy)
print(Cs_pos)
#%% 绘制杨老师的化学计量数
import numpy as np

def graphite_ocp1(sto):  #修正过的OCP
    gamma=-0.01185456
    U_eq1 = (
        0.063+0.8*np.exp(-75*(((1-gamma)*sto+gamma)+0.001))
        -0.012*np.tanh((((1-gamma)*sto+gamma)-0.127)/0.016)
        -0.0118*np.tanh((((1-gamma)*sto+gamma)-0.155)/0.016)
        -0.0035*np.tanh((((1-gamma)*sto+gamma)-0.22)/0.02)
        -0.0095*np.tanh((((1-gamma)*sto+gamma)-0.19)/0.013)
        -0.0145*np.tanh((((1-gamma)*sto+gamma)-0.49)/0.02)
        -0.08*np.tanh((((1-gamma)*sto+gamma)-1.03)/0.055)
        )
    return U_eq1
#%%
def graphite_ocp(sto):
    u_eq1 = (
            0.16576
            + 0.84157 * np.exp(-61.25108 * sto)
            + 0.39197 * np.exp(-500.38943 * sto)
            - np.exp(2.81471 * sto - 4.91298)
            - 0.02689 * np.arctan(25.59 * sto - 4.099)
            - 0.00717 * np.arctan(32.49 * sto - 15.74)
    )
    return u_eq1

def graphite_ocp1(sto):  #修正过的OCP
    gamma=-0.01185456
    U_eq1 = (
        0.063+0.8*np.exp(-75*(((1-gamma)*sto+gamma)+0.001))
        -0.012*np.tanh((((1-gamma)*sto+gamma)-0.127)/0.016)
        -0.0118*np.tanh((((1-gamma)*sto+gamma)-0.155)/0.016)
        -0.0035*np.tanh((((1-gamma)*sto+gamma)-0.22)/0.02)
        -0.0095*np.tanh((((1-gamma)*sto+gamma)-0.19)/0.013)
        -0.0145*np.tanh((((1-gamma)*sto+gamma)-0.49)/0.02)
        -0.08*np.tanh((((1-gamma)*sto+gamma)-1.03)/0.055)
        )
    return U_eq1
#%%
import matplotlib.pyplot as plt
import pandas as pd
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
df = pd.DataFrame({
    'Stoichiometry': sto_data,
    'Open_Circuit_Potential': OCP_data
})

# 保存到Excel文件
output_file = 'OCP_pos.xlsx'
df.to_excel(output_file, index=False, sheet_name='OCP Data')

print(f"数据已成功保存到 {output_file}")
plt.plot(sto_data, OCP_data)
plt.show()
#%%
import pandas as pd
from scipy.interpolate import CubicSpline
import matplotlib.pyplot as plt
data = pd.read_excel(r"A:\Code\Cloud\Data\dOCPdV\graphite_docp_data.xlsx")
sto = data["Stoichiometry"].to_numpy()
Voltage = data["Open_Circuit_Potential"].to_numpy()
cs = CubicSpline(sto,Voltage, extrapolate=True)
#0 60.62939876363249
#1 5339.241501217437


