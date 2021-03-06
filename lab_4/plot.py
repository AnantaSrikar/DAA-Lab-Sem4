import matplotlib
matplotlib.use('TkAgg')

import matplotlib.pyplot as plt

blk_size_x = [4, 8, 16, 32, 64]

laptop_y = [4.200981, 4.0165942, 3.9266004, 3.8985178, 3.8848438]
m_laptop_y = [3.0184216, 1.0951214, 0.8405726, 0.7738358, 0.7443266]

raspi_y = [20.6318888, 19.7421162, 19.063083, 19.2877818, 18.8439374]
m_raspi_y = [13.076453, 6.7204974, 5.7891698, 5.7571964, 5.5411358]

plt.plot(blk_size_x, m_raspi_y)

# plt.legend(["Laptop - upto 4.1GHz - 16 threads"])
plt.legend(["Raspberry Pi - upto 1.5GHz - 4 threads"])

# plt.plot(blk_size_x, raspi_y)
# plt.legend(["Laptop - upto 4.1GHz", "Raspberry Pi - upto 1.5GHz"])

plt.title("Multi Threaded implementation - Block matrix multiplication")
plt.xlabel('Block size')
plt.ylabel('Time taken to execute (in seconds)')

plt.savefig('MultiThread-raspi.jpg')
plt.show()