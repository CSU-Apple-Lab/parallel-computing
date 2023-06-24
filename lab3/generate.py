import re
import matplotlib.pyplot as plt

COUNT = 10

# 读取bigmat_omp.out文件
with open('bigmat_omp.out', 'r') as f:
    bigmat_lines = f.readlines()

bigmat_data = {}
for line in bigmat_lines:
    np_val, *times = map(float, re.findall(r"[-+]?\d*\.\d+|\d+", line))
    bigmat_data[int(np_val)] = times

# 计算每个NP的平均速度
np_vals = sorted(list(bigmat_data.keys()))
speed = []

for np_val in np_vals:
    avg_time = sum(bigmat_data[np_val]) / COUNT
    speed.append(1 / avg_time)

# 画图
fig, axs = plt.subplots(1, 1, figsize=(8, 8))
axs.plot(np_vals, speed)
axs.set_xlabel('NP')
axs.set_ylabel('Speed')

plt.tight_layout()
plt.show()
