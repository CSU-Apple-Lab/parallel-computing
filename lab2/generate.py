import re
import numpy as np
import matplotlib.pyplot as plt

COUNT = 10

# 读取pi.out文件
with open('pi.out', 'r') as f:
    pi_lines = f.readlines()

# 读取pi_mpi.out文件
with open('pi-mpi.out', 'r') as f:
    pi_mpi_lines = f.readlines()

# 从文件内容中提取NP和Time数据
_, *pi_data = map(float, re.findall(r"[-+]?\d*\.\d+|\d+", pi_lines[0]))
avg_time_pi = sum(pi_data) / COUNT

print(pi_data)

pi_mpi_data = {}
for line in pi_mpi_lines:
    np_val, *times = map(float, re.findall(r"[-+]?\d*\.\d+|\d+", line))
    pi_mpi_data[int(np_val)] = times

# 计算每个NP的平均Time和加速比
np_vals = sorted(list(pi_mpi_data.keys()))
avg_times_pi_mpi = []
speedup = []
for np_val in np_vals:
    avg_time_pi_mpi = sum(pi_mpi_data[np_val]) / COUNT
    avg_times_pi_mpi.append(avg_time_pi_mpi)
    speedup.append(avg_time_pi_mpi / avg_time_pi)

# 画图
fig, axs = plt.subplots(2, 1, figsize=(8, 8))
axs[0].plot(np_vals, avg_times_pi_mpi)
axs[0].set_xlabel('NP')
axs[0].set_ylabel('Cost Time of Multi Thread')

axs[1].plot(np_vals, speedup)
axs[1].set_xlabel('NP')
axs[1].set_ylabel('Speedup(Multi Thread/Single Thread)')

plt.tight_layout()
plt.show()
