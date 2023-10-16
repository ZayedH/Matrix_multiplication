import numpy as np
import matplotlib.pyplot as plt

# gcc_mult_omp_8threads
# gcc_mult_omp_cache_8threads
# mpicc_mult_ompi_9_processors
# mpicc_mult_ompi_cache_9_precessors
file = open("c_code/mpicc_mult_ompi_4_processors.txt", "r")
contenu = file.readlines()
file.close()
file = open("c_code/mpicc_mult_ompi_cache_4_processors.txt", "r")
contenu_cache = file.readlines()
file.close()

matrix_size = []
time_product = []
matrix_size_cache = []
time_product_cache = []

for info in contenu:
    dim_time = info.split(":")
    matrix_size.append(int(dim_time[0]))
    time_product.append(float(dim_time[1].split("\n")[0]))
for info_cache in contenu_cache:
    dim_time_cache = info_cache.split(":")
    matrix_size_cache.append(int(dim_time_cache[0]))
    time_product_cache.append(float(dim_time_cache[1].split("\n")[0]))


fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)

x_min = 0
x_max = 5000

y_min = 0
y_max = 900

plt.xlim(x_min, x_max)
plt.ylim(y_min, y_max)

grid_x_ticks = np.arange(x_min, x_max, 80)
grid_y_ticks = np.arange(y_min, y_max, 20)

ax.set_xticks(grid_x_ticks, minor=True)
ax.set_yticks(grid_y_ticks, minor=True)
ax.grid(which='both')
ax.grid(color='r', which='minor', alpha=0.1, linestyle='--')

plt.plot(matrix_size_cache, time_product_cache,
         'ro-', label='cache friendly code')
plt.plot(matrix_size, time_product, 'b*-', label="cache-unfriendly code")
plt.xlabel("The order of the square matrices")
plt.ylabel("Time taken [s]")
plt.legend()
plt.show()
