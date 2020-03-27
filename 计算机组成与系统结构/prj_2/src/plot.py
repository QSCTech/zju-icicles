import matplotlib.pyplot as plt
import numpy as np


# input_str = 'median, cycles: 11312'
# num_list = [23.020, 38.393, 32.753, 5.835]

# input_str = 'multiply, cycles: 43316'
# num_list = [65.366, 2.685, 30.714, 1.235]

# input_str = 'qsort, cycles: 228004'
# num_list = [37.979, 32.030, 26.806, 3.185]

# input_str = 'towers, cycles: 13636'
# num_list = [38.428, 51.914, 4.246, 5.412]

# input_str = 'dhrystone, cycles: 72'
# num_list = [59.722, 12.500, 1.389, 26.389]

# input_str = 'vvadd, cycles: 7336'
# num_list = [44.234, 37.555, 16.399, 1.813]

# task 1
'''
x = ['median','multiply','qsort','towers','dhrystone','vvadd']
name_list = ['Arith instr', 'Ld/St instr', 'branch instr', 'misc instr']

Arith = np.array([ 23.020, 65.366, 37.979, 38.428, 59.722, 44.234 ])
Ld =    np.array([ 38.393, 2.685,  32.030, 51.914, 12.500, 37.555 ])
branch= np.array([ 32.753, 30.714, 26.806, 4.246,  1.389 , 16.399 ])
misc =  np.array([ 5.835,  1.235,  3.185,  5.412,  26.389,  1.813 ])

plt.bar(x,Arith,color = 'orange',label = name_list[0])
plt.bar(x,Ld,bottom=Arith, color = 'chartreuse',label = name_list[1])
plt.bar(x,branch,bottom=Arith+Ld  ,color='lightblue',label=name_list[2])
plt.bar(x,misc,bottom=Arith+Ld+branch,color='yellow',label=name_list[3])
plt.ylabel("percentage(%)") # y轴标签
plt.legend(loc=0)
plt.show()
'''

# task 2
'''
cpi = [1, 2, 1.5, 1.5]
cpi_overall = []
for i in range(len(Arith)):
  cpi_overall.append(cpi[0] * Arith[i] + cpi[1] * Ld[i] + cpi[2] * branch[i] + cpi[3] * misc[i])
  cpi_overall[i] = cpi_overall[i] * 0.01
  print(x[i],cpi_overall[i])

cpi_new = [1, 1, 1.5, 1.5] 
cpi_overall_new = []
for i in range(len(Arith)):
  cpi_overall_new.append(cpi_new[0] * Arith[i] + cpi_new[1] * Ld[i] + cpi_new[2] * branch[i] + cpi_new[3] * misc[i])
  cpi_overall_new[i] = cpi_overall_new[i] * 0.01
  print(x[i],cpi_overall_new[i],(cpi_overall[i] - cpi_overall_new[i]) / cpi_overall[i])
'''

# task 3

# name_list = ['Bubbles', 'nop','Arith instr', 'Ld/St instr', 'branch instr', 'misc instr']
# x = [i for i in range(46)]

# t3_on
# x = [
# 'dhrystone','median','multiply','qsort','rsort','rv32mi-p-csr',
# 'rv32mi-p-illegal','rv32mi-p-sbreak','rv32mi-p-scall','rv32ui-p-addi',
# 'rv32ui-p-add','rv32ui-p-andi','rv32ui-p-and','rv32ui-p-auipc',
# 'rv32ui-p-beq','rv32ui-p-bge','rv32ui-p-bgeu','rv32ui-p-blt','rv32ui-p-bltu',
# 'rv32ui-p-bne','rv32ui-p-fence_i','rv32ui-p-jal','rv32ui-p-jalr',
# 'rv32ui-p-lb','rv32ui-p-lbu','rv32ui-p-lh','rv32ui-p-lhu','rv32ui-p-lui',
# 'rv32ui-p-lw','rv32ui-p-ori','rv32ui-p-or','rv32ui-p-sb','rv32ui-p-sh',
# 'rv32ui-p-simple','rv32ui-p-slli','rv32ui-p-sll','rv32ui-p-slti',
# 'rv32ui-p-slt','rv32ui-p-srai','rv32ui-p-sra','rv32ui-p-sub','rv32ui-p-sw',
# 'rv32ui-p-xori','rv32ui-p-xor','towers','vvadd'
# ]
# Bubbles = np.array([18.056,32.010,36.655,36.215,6.894,34.239,39.103,38.281,39.844,17.593,12.591,19.776,12.326,36.719,23.284,25.229,23.922,23.284,22.248,23.775,43.576,38.281,33.152,17.593,17.593,16.358,17.330,33.594,16.761,20.608,12.326,12.885,11.979,39.000,17.593,11.979,18.210,12.956,15.741,11.921,12.956,11.458,20.270,12.326,13.950,21.255])
# nop = np.array([0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,3.704,6.934,4.478,6.597,0.781,7.843,7.339,6.897,7.843,7.339,7.843,4.861,0.000,3.261,4.012,4.012,4.012,3.693,0.000,3.693,4.054,6.597,6.154,5.556,0.000,3.704,6.597,3.704,6.934,3.704,6.291,6.934,5.556,4.054,6.597,0.000,0.000])
# Arith =   np.array([55.556,15.666,41.457,24.229,55.663,35.870,33.974,33.594,31.250,52.469,59.854,48.881,48.958,31.250,43.627,42.890,34.914,43.627,35.092,43.627,24.306,31.250,36.413,42.593,42.593,42.593,39.205,35.156,39.205,44.257,49.132,42.500,38.368,32.000,50.926,59.028,53.086,60.584,47.840,51.490,58.942,38.021,44.257,49.132,33.158,35.000])
# Ld =      np.array([8.333,26.096,1.663,20.430,32.932,4.348,2.564,3.125,5.469,2.160,0.547,1.493,0.868,4.688,1.471,0.917,1.078,1.471,1.376,1.225,2.604,4.688,1.630,9.259,9.259,8.333,8.807,3.906,8.807,2.703,0.694,14.423,13.021,5.000,2.160,0.521,2.469,0.730,1.235,0.828,0.912,12.674,2.703,0.694,44.741,29.578])
# branch=   np.array([1.389,22.331,19.469,17.100,4.476,8.696,8.333,8.594,4.688,13.272,13.504,11.940,10.938,7.031,19.118,19.954,18.750,19.118,17.890,19.118,18.924,7.031,8.152,13.272,13.272,13.272,12.216,9.375,12.216,10.811,10.938,12.500,11.285,6.000,13.272,13.542,13.272,13.504,13.272,13.079,13.321,11.285,10.811,10.938,3.590,12.900])
# misc =    np.array([16.667,3.898,0.757,2.027,0.035,16.848,16.026,16.406,18.750,10.802,6.569,13.433,20.312,19.531,4.657,3.670,14.440,4.657,16.055,4.412,5.729,18.750,17.391,13.272,13.272,15.432,18.750,17.969,19.318,17.568,20.312,11.538,19.792,18.000,12.346,8.333,9.259,5.292,18.210,16.391,6.934,21.007,17.905,20.312,4.561,1.266])
# cpi = [1.22,1.47,1.58,1.57,1.07,1.52,1.64,1.62,1.66,1.21,1.14,1.25,1.14,1.58,1.30,1.34,1.31,1.30,1.29,1.31,1.77,1.62,1.50,1.21,1.21,1.20,1.21,1.51,1.20,1.26,1.14,1.15,1.14,1.64,1.21,1.14,1.22,1.15,1.19,1.14,1.15,1.13,1.25,1.14,1.16,1.27]
# ipc = [0.82,0.68,0.63,0.64,0.93,0.66,0.61,0.62,0.60,0.82,0.87,0.80,0.88,0.63,0.77,0.75,0.76,0.77,0.78,0.76,0.56,0.62,0.67,0.82,0.82,0.84,0.83,0.66,0.83,0.79,0.88,0.87,0.88,0.61,0.82,0.88,0.82,0.87,0.84,0.88,0.87,0.89,0.80,0.88,0.86,0.79]

# print(sum(cpi)/len(cpi))
# plt.plot(x,cpi,color = 'orange',label = 'cpi_full_bypass')
# plt.plot(x,ipc,color='red',label='ipc_full_bypass')
# t3_off
# x = ['dhrystone','median','multiply','qsort','rsort','rv32mi-p-csr','rv32mi-p-illegal','rv32mi-p-sbreak','rv32mi-p-scall','rv32ui-p-addi','rv32ui-p-add','rv32ui-p-andi','rv32ui-p-and','rv32ui-p-auipc','rv32ui-p-beq','rv32ui-p-bge','rv32ui-p-bgeu','rv32ui-p-blt','rv32ui-p-bltu','rv32ui-p-bne','rv32ui-p-fence_i','rv32ui-p-jal','rv32ui-p-jalr','rv32ui-p-lb','rv32ui-p-lbu','rv32ui-p-lh','rv32ui-p-lhu','rv32ui-p-lui','rv32ui-p-lw','rv32ui-p-ori','rv32ui-p-or','rv32ui-p-sb','rv32ui-p-sh','rv32ui-p-simple','rv32ui-p-slli','rv32ui-p-sll','rv32ui-p-slti','rv32ui-p-slt','rv32ui-p-srai','rv32ui-p-sra','rv32ui-p-sub','rv32ui-p-sw','rv32ui-p-xori','rv32ui-p-xor','towers','vvadd']

# Bubbles = np.array([34.722,45.711,47.318,64.545,57.109,62.838,65.672,64.623,66.038,55.729,50.413,58.654,58.054,63.679,50.791,51.364,54.534,51.108,54.190,51.266,67.234,63.679,62.346,58.861,58.861,60.029,60.615,61.321,60.754,59.489,58.279,53.409,57.216,66.026,55.556,50.488,55.208,49.681,57.437,51.895,50.106,57.886,59.672,58.138,34.799,42.016])
# nop = np.array([0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,0.000,2.083,3.926,2.308,3.188,0.472,5.063,4.848,4.145,5.063,4.469,5.063,2.979,0.000,1.852,2.057,2.057,1.890,1.816,0.000,1.816,2.190,3.115,3.306,2.749,0.000,2.083,3.711,2.083,4.043,1.899,3.430,4.043,2.685,2.190,3.188,0.000,0.000])
# Arith =   np.array([51.389,12.502,34.488,13.468,25.643,22.297,19.776,20.283,18.868,29.514,33.884,25.192,23.658,18.868,28.165,28.333,20.984,28.165,21.369,28.165,14.894,18.868,20.679,21.835,21.835,20.058,19.274,21.226,19.274,23.905,23.197,22.831,18.986,20.513,28.646,33.203,29.861,35.319,24.525,28.069,34.362,18.372,23.905,23.742,25.145,25.817])
# Ld =      np.array([4.167,20.813,1.369,11.355,15.170,1.351,1.119,1.415,2.358,0.521,0.310,0.769,0.252,1.887,0.791,0.303,0.518,0.633,0.279,0.633,0.957,2.830,0.926,4.272,4.272,4.070,3.911,1.887,3.771,0.730,0.410,7.645,6.186,1.282,0.521,0.293,0.868,0.319,0.475,0.451,0.213,5.872,0.547,0.168,33.897,21.725])
# branch=   np.array([1.389,17.838,16.192,9.505,2.061,5.405,4.851,5.189,2.830,7.465,7.645,6.154,5.285,4.245,12.342,13.182,11.269,12.342,10.894,12.342,11.596,4.245,4.630,6.804,6.804,6.250,6.006,5.660,6.006,5.839,5.164,6.715,5.584,3.846,7.465,7.617,7.465,7.872,6.804,7.130,7.766,5.453,5.839,5.285,2.680,9.465])
# misc =    np.array([8.333,3.135,0.633,1.128,0.016,8.108,8.582,8.491,9.906,4.688,3.822,6.923,9.564,10.849,2.848,1.970,8.549,2.690,8.799,2.532,2.340,10.377,9.568,6.171,6.171,7.703,8.380,9.906,8.380,7.847,9.836,6.095,9.278,8.333,5.729,4.688,4.514,2.766,8.861,9.025,3.511,9.732,7.847,9.480,3.480,0.977])
# cpi = [1.53,1.84,1.90,2.82,2.33,2.69,2.91,2.83,2.94,2.26,2.02,2.42,2.38,2.75,2.03,2.06,2.20,2.05,2.18,2.05,3.05,2.75,2.66,2.43,2.43,2.50,2.54,2.59,2.55,2.47,2.40,2.15,2.34,2.94,2.25,2.02,2.23,1.99,2.35,2.08,2.00,2.37,2.48,2.39,1.53,1.72]
# ipc = [0.65,0.54,0.53,0.35,0.43,0.37,0.34,0.35,0.34,0.44,0.50,0.41,0.42,0.36,0.49,0.49,0.45,0.49,0.46,0.49,0.33,0.36,0.38,0.41,0.41,0.40,0.39,0.39,0.39,0.41,0.42,0.47,0.43,0.34,0.44,0.50,0.45,0.50,0.43,0.48,0.50,0.42,0.40,0.42,0.65,0.58]

# print(sum(cpi)/len(cpi))
# plt.plot(x,cpi,color = 'chartreuse',label = 'cpi_not_full_bypass')
# plt.plot(x,ipc,color='yellow',label='ipc_not_full_bypass')

# for i in range(len(Bubbles)):
#   if 100 - (Bubbles[i] + nop[i] + Arith[i] + Ld[i] + branch[i] + misc[i]) > 1:
#     print(x[i],Bubbles[i],nop[i],Arith[i],Ld[i],branch[i],misc[i])

# plt.bar(x,Bubbles,color = 'red',label = name_list[0])
# plt.bar(x,nop,bottom = Bubbles,color = 'green',label=name_list[1])
# plt.bar(x,Arith,bottom=Bubbles+nop,color = 'orange',label = name_list[2])
# plt.bar(x,Ld,bottom=Bubbles+nop+ Arith, color = 'chartreuse',label = name_list[3])
# plt.bar(x,branch,bottom=Bubbles+nop+Arith+Ld  ,color='lightblue',label=name_list[4])
# plt.bar(x,misc,bottom=Bubbles+nop+Arith+Ld+branch,color='yellow',label=name_list[5])
# plt.ylabel("percentage(%)") # y轴标签
# plt.legend(loc=0)
# plt.show()

# plt.legend()
# plt.show()

# task 6
x = ['dhryst','median','multiply','qsort','rsort','towers','vvadd']
name_list = ['Bubbles instr','Arith instr', 'Ld/St instr', 'branch instr', 'misc instr']

# new
Bubbles = np.array([14.239, 19.074, 22.316, 27.354, 4.664, 9.930, 12.882 ])
Arith =   np.array([29.221, 21.672, 50.885, 27.746, 57.023, 36.532, 41.165 ])
Ld =    np.array([ 33.966, 29.130, 2.208, 23.153, 33.619, 44.151, 29.726 ])
branch= np.array([ 12.650, 25.230, 23.475, 19.407, 4.620, 4.376, 13.959  ])
misc =  np.array([ 9.924, 4.893, 1.115, 2.340, 0.074, 5.011, 2.269 ])

# old
# Bubbles = np.array([12.821, 19.401, 22.529, 27.430, 3.588, 9.502, 12.587])
# Arith =   np.array([53.846, 18.564, 50.664, 27.563, 57.636, 34.838, 38.765])
# Ld =      np.array([10.256, 30.935, 2.067, 23.244, 34.102, 47.030, 32.843])
# branch  = np.array([1.282, 26.446, 23.802, 19.454, 4.636, 3.802, 14.334])
# misc =    np.array([21.795, 4.653, 0.938, 2.308, 0.038, 4.828, 1.472])


plt.bar(x,Bubbles,color = 'red',label = name_list[0])
plt.bar(x,Arith,bottom=Bubbles,color = 'orange',label = name_list[1])
plt.bar(x,Ld,bottom=Bubbles+Arith, color = 'chartreuse',label = name_list[2])
plt.bar(x,branch,bottom=Bubbles+Arith+Ld  ,color='lightblue',label=name_list[3])
plt.bar(x,misc,bottom=Bubbles+Arith+Ld+branch,color='yellow',label=name_list[4])
plt.title("Changed Processor Result")
plt.ylabel("percentage(%)") # y轴标签
plt.legend(loc=0)
plt.show()


