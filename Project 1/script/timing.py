import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np

sns.set()

x = np.arange(0, 10)

read_1 = np.array([0.14, 0.127, 0.122, 0.13, 0.124,  0.134, 0.126, 0.126, 0.125, 0.126])
read_2 = np.array([0.020, 0.0197, 0.0182, 0.0183, 0.0191, 0.0208, 0.0224, 0.0172, 0.018, 0.0222])

plt.title('Testing read_graph_from_file with the 36k nodes graph')
plt.plot(x, read_1, 'r--o', label='read_graph_from_file1')
plt.plot(x, read_2, 'g--o', label='read_graph_from_file2')
plt.legend(loc='best')
plt.xlabel('test nr')
plt.ylabel('time [s]')
plt.savefig('figures/read_36k_graph.jpg')
plt.show()


count1_seq = np.array([44.774,  43.827, 44.468, 43.688, 43.986, 42.399, 43.161, 44.445, 43.408, 42.762])
count1_par = np.array([28.515, 29.196, 28.983, 28.907, 28.409, 29.818, 29.0143, 29.0143, 29.267, 29.049])

plt.title('Testing count_mutual_links1 with the 36k nodes graph')
plt.plot(x, count1_seq, 'r--o', label='sequential')
plt.plot(x, count1_par, 'g--o', label='parallel')
plt.legend(loc='best')
plt.xlabel('test nr')
plt.ylabel('time [s]')
plt.savefig('figures/count_1_36k_graph.jpg')
plt.show()


count2_seq = np.array([0.045, 0.045, 0.04, 0.041, 0.04, 0.043, 0.044, 0.042, 0.041, 0.04])
count2_par = np.array([0.081, 0.082, 0.086, 0.083, 0.078, 0.081, 0.079, 0.081, 0.08, 0.081])

plt.title('Testing count_mutual_links2 with the Amazon 0505 graph')
plt.plot(x, count2_seq, 'r--o', label='sequential')
plt.plot(x, count2_par, 'g--o', label='parallel')
plt.legend(loc='best')
plt.xlabel('test nr')
plt.ylabel('time [s]')
plt.savefig('figures/count_2_Amazon_graph.jpg')
plt.show()


