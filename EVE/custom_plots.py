import matplotlib.pyplot as plt
import numpy as np
import matplotlib.gridspec as gridspec
import os

colors = [
    (49/255.0, 18/255.0, 58/255.0),
    (68/255.0, 145/255.0, 254/255.0),
    (190/255.0, 32/255.0, 2/255.0),
    (253/255.0, 146/255.0, 42/255.0) ,
    (32/255.0, 199/255.0, 224/255.0),
    (154/255.0, 96/255.0, 180/255.0),
]
def loss_plot(
        solutions , list_opm , Data , current_time
):
    plt.figure(figsize=(23, 8), dpi=400)  # 调整图形大小
    gs = gridspec.GridSpec(1, 3, width_ratios=[3, 3, 0.3] , wspace=0.15)  # 主图:温度图:RMSE区域=1:1:0.3
    # 主图（放电容量-电压）
    ax1 = plt.subplot(gs[0])
    text_y_positions = []
    i = 0
    for index in list_opm:
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
        ax1.plot(dcap, voltage, linewidth=1.8, label=label0, color=colors[i])
        indices = range(0, len(dcap1))  # 每隔10个点的索引
        dcap1 = dcap1
        ax1.scatter(dcap1[::30], voltage1[::30],label=label1, color=colors[list_opm.index(index)],facecolors='none', edgecolors=colors[list_opm.index(index)],s=20)
        # 在右侧显示RMSE
        # 获取当前y轴范围
        ymin, ymax = ax1.get_ylim()
        # 计算文本的y位置（均匀分布）
        text_y_pos = ymax - (ymax - ymin) * 0.07 * (list_opm.index(index) + 1)
        text_y_positions.append(text_y_pos)
        i= i+1
    ax1.tick_params(axis="both", which="major", direction="in", width=1.5, length=5)  #设置主副刻度大小
    ax1.tick_params(axis="both", which="minor", direction="in", width=1.5, length=3)
    ax1.minorticks_on()  #显示副标题
    ax1.set_xlabel("Discharge Capacity [A.h]", fontsize=24, fontproperties="Times New Roman")
    ax1.set_ylabel("Cell Voltage [V]", fontsize=24, fontproperties="Times New Roman")
    ax1.tick_params(axis='x', labelsize=20)
    ax1.tick_params(axis='y', labelsize=20)

    ax2 = plt.subplot(gs[1])
    i = 0
    for index in list_opm:
        # 假设温度数据在solutions和Data中有对应的字段
        dcap = np.abs(solutions[index]["Discharge capacity [A.h]"].data)
        temp = solutions[index]["Cell temperature [K]"].data[0, :] - 273.15 # 转换为摄氏度
        dcap1 = np.abs(Data[index]["Capacity [A.h]"])
        temp1 = Data[index]["Temperature1 [oC]"]  # 假设原始数据已经是摄氏度

        ax2.plot(dcap, temp, linewidth=1.8, color=colors[list_opm.index(index)])
        ax2.scatter(dcap1[::50], temp1[::50], color=colors[list_opm.index(index)],facecolors='none', edgecolors=colors[list_opm.index(index)],s=20)

    ax2.set_xlabel("Discharge Capacity [A.h]", fontsize=20, fontproperties="Times New Roman")
    ax2.set_ylabel("Temperature [°C]", fontsize=20, fontproperties="Times New Roman")
    ax2.tick_params(axis='both', labelsize=16)
    ax2.tick_params(axis="both", which="major", direction="in", width=1.5, length=5)
    ax2.tick_params(axis="both", which="minor", direction="in", width=1.5, length=3)
    ax2.minorticks_on()

    ax3 = plt.subplot(gs[2])
    ax3.axis('off')  # 关闭坐标轴

    num_items = len(list_opm)
    rmse_text_height = 0.1  # 每个RMSE文本占用的垂直空间
    total_rmse_space = num_items * rmse_text_height
    legend_space = 0.3  # 为图例保留的空间
    # 添加RMSE文本（左对齐）
    for idx, index in enumerate(list_opm):
        dcap = np.abs(solutions[index]["Discharge capacity [A.h]"].data)
        voltage = solutions[index]["Battery voltage [V]"].data
        dcap1 = np.abs(Data[index]["Capacity [A.h]"])
        voltage1 = Data[index]["Terminal voltage [V]"]

        interp = np.linspace(np.min(dcap1), np.max(dcap1), 2000)
        voltage_interp = np.interp(interp, dcap, voltage)
        voltage1_interp = np.interp(interp, dcap1, voltage1)
        rmse = np.sqrt(np.mean((voltage1_interp - voltage_interp) ** 2)) * 1000

        # 从顶部开始排列RMSE文本
        ax3.text(0.005, 0.95 - idx * 0.08,  # 调整垂直间距为0.08
                 f"{index} RMSE: {rmse:.3f} mV",
                 fontdict={'family': 'Times New Roman', 'size': 14},
                 color='black',
                 transform=ax3.transAxes,
                 horizontalalignment='left')

    # 添加图例（放在RMSE文本下方）
    handles, labels = ax1.get_legend_handles_labels()
    ax3.legend(handles, labels,
               fontsize=12,
               frameon=False,
               prop={'family': 'Times New Roman', 'size': 14},
               loc='upper left',
               bbox_to_anchor=(0.005, 0.95 - num_items * 0.08),  # 在RMSE文本下方
               borderaxespad=0.05)
    # 调整子图间距
    plt.subplots_adjust(wspace=0.1)
    picture_path = "A:/Code/Cloud/Data/Cycle_0/solution"
    plt.savefig(os.path.join(picture_path,f"{current_time}_Cap_V.png"), dpi=300, bbox_inches='tight')