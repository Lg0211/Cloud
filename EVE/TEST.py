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