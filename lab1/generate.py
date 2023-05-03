import re
import numpy as np
import matplotlib.pyplot as plt

COUNT = 10

# 读取qusort.out文件
with open('qusort.out', 'r') as f:
    qusort_lines = f.readlines()

# 读取qusort_multi.out文件
with open('qusort_multi.out', 'r') as f:
    qusort_multi_lines = f.readlines()

# 读取qusort_pool.out文件
with open('qusort_pool.out', 'r') as f:
    qusort_pool_lines = f.readlines()

# 从文件内容中提取N和Time数据
qusort_data = {}
for line in qusort_lines:
    np_val, *times = map(float, re.findall(r"[-+]?\d*\.\d+|\d+", line))
    qusort_data[int(np_val)] = times

qusort_multi_data = {}
for line in qusort_multi_lines:
    np_val, *times = map(float, re.findall(r"[-+]?\d*\.\d+|\d+", line))
    qusort_multi_data[int(np_val)] = times

qusort_pool_data = {}
for line in qusort_pool_lines:
    np_val, *times = map(float, re.findall(r"[-+]?\d*\.\d+|\d+", line))
    qusort_pool_data[int(np_val)] = times

# 计算每个NP的平均Time和加速比
np_vals = sorted(list(qusort_data.keys()))
speedup_multi = []
speedup_pool = []
for np_val in np_vals:
    avg_times_qusort = sum(qusort_data[np_val]) / COUNT
    avg_times_qusort_multi = sum(qusort_multi_data[np_val]) / COUNT
    avg_times_qusort_pool = sum(qusort_pool_data[np_val]) / COUNT
    speedup_multi.append(avg_times_qusort / avg_times_qusort_multi)
    speedup_pool.append(avg_times_qusort / avg_times_qusort_pool)

print(np_vals)
print(np_vals)
print(np_vals)

# 画图
fig, axs = plt.subplots(2, 1, figsize=(8, 8))
axs[0].plot(np_vals, speedup_multi)
axs[0].set_xlabel('Numbers')
axs[0].set_ylabel('Speedup(Multi Thread/Single Thread)')

axs[1].plot(np_vals, speedup_pool)
axs[1].set_xlabel('Numbers')
axs[1].set_ylabel('Speedup(Thread Pool/Single Thread)')

plt.tight_layout()
plt.show()
