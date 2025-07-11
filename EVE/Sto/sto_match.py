# -*- coding: utf-8 -*-
"""
Created on Mon Aug  5 17:35:01 2024
利用粒子群寻优算法实现OCP与OCV之间的匹配
@author: Lg
"""
# %%导入
import pandas as pd
import numpy as np
from scipy.interpolate import interp1d
from scipy.interpolate import CubicSpline
import matplotlib.pyplot as plt
from matplotlib.pyplot import MultipleLocator
from scipy.interpolate import CubicSpline
# %%数据读取
#note：[0.01422177 0.01325047 0.85907807 0.01138894]

data_OCV = pd.read_excel(r"A:\Code\Cloud\Data\OCV\OCV.xlsx")
data_pos_OCP = pd.read_excel(r"A:\Code\Cloud\Data\OCP\Postive_OCP.xlsx")
"""
def neg_OCP(sto):
    u_eq1 = (
            0.16576
            + 0.84157 * np.exp(-61.25108 * sto)
            + 0.39197 * np.exp(-500.38943 * sto)
            - np.exp(2.81471 * sto - 4.91298)
            - 0.02689 * np.arctan(25.59 * sto - 4.099)
            - 0.00717 * np.arctan(32.49 * sto - 15.74)
    )
    return u_eq1
"""
def neg_OCP(sto):  #修正过的OCP mohatat
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
"""
def pos_OCP(sto):
    sto_data = data_pos_OCP["Sto"].to_numpy()
    OCP_data = data_pos_OCP["Voltage"].to_numpy()
    cs = CubicSpline(sto_data, OCP_data)
    return cs(sto)
"""
def pos_OCP(sto):  #change OCP
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
    cs = CubicSpline(sto_data, OCP_data)
    return cs(sto)
dSOC=[0,
      0.1893,0.1893,0.1893,0.1893,0.1893,
      0.7572,0.7572,0.7572,0.7572,0.7572,
      0.7572,0.7572,0.7572,0.7572,0.7572,
      0.1893,0.1893,0.1893,0.1893,0.1893,0.1893
      ]
dd = [0,
      1,2,3,4,5,
      9,13,17,21,25,
      29,33,37,41,45,
      46,47,48,49,50,51
]
# %%%寻优边界 x_init dx y_init dy  #x:负极 y:正极
x_min = [0.85, 0,  0.85, 0]
x_max = [0.92, 0.02, 0.98 , 0.02]
# %%粒子群参数###############可修改
size = 200  # 粒子数
iter_num = 100  # 迭代次数
max_vel = 1  # 粒子最大速度
tol = 1e-4  # 截至误差
C1 = 2  # 粒子最优位置权重
C2 = 2  # 粒子群最优位置权重
W = 0.5  # 遗忘率

# %%%

def fit_fun(x):  # 适应函数
    x_init , dx, y_init, dy = x
    #print(x)
    loss = 0
    for i in range(22):
        OCV = data_OCV["Voltage"][i]
        pos_ocp = pos_OCP(y_init - int(dd[i])*dy)
        #print(pos_ocp)
        neg_ocp = graphite_ocp(x_init - 51*dx + int(dd[i])*dx)
        #print(neg_ocp)
        loss += ((pos_ocp - neg_ocp)-OCV)**2
    #print(loss)
    return loss

class Particle:
    # 初始化
    def __init__(self, x_min, x_max, max_vel, dim, ):
        self.x_min = np.array(x_min)
        self.x_max = np.array(x_max)
        self.__pos = np.random.uniform(self.x_min, self.x_max, dim)  # 粒子的位置
        self.__vel = np.random.uniform(-max_vel, max_vel, dim)  # 粒子的速度
        self.__bestPos = self.__pos.copy()  # 粒子最好的位置
        self.__fitnessValue = fit_fun(self.__pos)  # 适应度函数值

    def set_pos(self, value):
        self.__pos = value

    def get_pos(self):
        return self.__pos

    def set_best_pos(self, value):
        self.__bestPos = value

    def get_best_pos(self):
        return self.__bestPos

    def set_vel(self, value):
        self.__vel = value

    def get_vel(self):
        return self.__vel

    def set_fitness_value(self, value):
        self.__fitnessValue = value

    def get_fitness_value(self):
        return self.__fitnessValue


class PSO:
    def __init__(self, dim, size, iter_num, x_min, x_max, max_vel, tol, best_fitness_value=float('Inf'), C1=2, C2=2,
                 W=1):
        self.C1 = C1
        self.C2 = C2
        self.W = W
        self.dim = dim  # 粒子的维度
        self.size = size  # 粒子个数
        self.iter_num = iter_num  # 迭代次数
        self.x_min = np.array(x_min)
        self.x_max = np.array(x_max)
        self.max_vel = max_vel  # 粒子最大速度
        self.tol = tol  # 截至条件
        self.best_fitness_value = best_fitness_value
        self.best_position = np.zeros(dim)  # 种群最优位置
        self.fitness_val_list = []  # 每次迭代最优适应值

        # 对种群进行初始化
        self.Particle_list = [Particle(self.x_min, self.x_max, self.max_vel, self.dim) for _ in range(self.size)]

    def set_best_fitness_value(self, value):
        self.best_fitness_value = value

    def get_best_fitness_value(self):
        return self.best_fitness_value

    def set_best_position(self, value):
        self.best_position = value

    def get_best_position(self):
        return self.best_position

    # 更新速度
    def update_vel(self, part):
        vel_value = self.W * part.get_vel() + self.C1 * np.random.rand() * (part.get_best_pos() - part.get_pos()) \
                    + self.C2 * np.random.rand() * (self.get_best_position() - part.get_pos())
        vel_value = np.clip(vel_value, -self.max_vel, self.max_vel)
        part.set_vel(vel_value)

    # 更新位置
    def update_pos(self, part):

        pos_value = part.get_pos() + part.get_vel()
        # print(pos_value[0])
        pos_value = np.clip(pos_value, self.x_min, self.x_max)  # 边界检查

        part.set_pos(pos_value)
        value = fit_fun(part.get_pos())
        if value < part.get_fitness_value():
            part.set_fitness_value(value)
            part.set_best_pos(pos_value)
        if value < self.get_best_fitness_value():
            self.set_best_fitness_value(value)
            self.set_best_position(pos_value)

    def update_ndim(self):
        for i in range(self.iter_num):
            for part in self.Particle_list:
                self.update_vel(part)  # 更新速度
                self.update_pos(part)  # 更新位置
            self.fitness_val_list.append(self.get_best_fitness_value())
            print('第{}次最佳适应值为{}'.format(i, self.get_best_fitness_value()))
            if self.get_best_fitness_value() < self.tol:
                break

        return self.fitness_val_list, self.get_best_position()


if __name__ == '__main__':
    pso = PSO(dim=4, size=400, iter_num=100, x_min=x_min, x_max=x_max, max_vel=1, tol=1e-4, C1=2, C2=2, W=0.5)
    fit_var_list, best_pos = pso.update_ndim()
    print("最优位置:" + str(best_pos))
    print("最优解:" + str(fit_var_list[-1]))
    black = (0, 0, 0)
    red = (219, 0, 0)
    black = tuple([x / 255.0 for x in black])
    red = tuple([x / 255.0 for x in red])

    x_init, dx, y_init, dy = best_pos

    SOC = data_OCV["SOC"]
    OCV = data_OCV["Voltage"]
    pos_ocp = pos_OCP(y_init - np.array(dd) * dy)
    neg_ocp = graphite_ocp(x_init + np.array(dd) * dx)
    neg_ocp = graphite_ocp(x_init - 51 * dx + np.array(dd) * dx)
    OCV_ = pos_ocp - neg_ocp

plt.scatter(SOC, OCV,label='OCV', color="red")
plt.plot(SOC, OCV_, linewidth=1.6, label='_PE', color="gray")

plt.tick_params(axis="both", which="major", direction="in", width=1.5, length=5)  # 设置主副刻度大小
plt.tick_params(axis="both", which="minor", direction="in", width=1.5, length=3)
plt.minorticks_on()  # 显示副标题
plt.gca().xaxis.set_minor_locator(MultipleLocator(.1))  # x轴主副刻度间距
plt.gca().xaxis.set_major_locator(MultipleLocator(.2))
plt.legend(fontsize=20, frameon=False, prop={'family': 'Times New Roman', 'size': 20})
plt.xlabel("SOC", fontsize=24, fontproperties="Times New Roman")
plt.ylabel("OCV [V]", fontsize=24, fontproperties="Times New Roman")
plt.tick_params(axis='x', labelsize=20)
plt.tick_params(axis='y', labelsize=24)
