import csv
import matplotlib.pyplot as plt

ppm = []
raw_vaisala_data  = "vaisala1_data_raw.csv"
filtered_vaisala_data = "vaisala1_filtered.csv"
median_filtered_data = "vaisala_median_filtered.csv"

def read_csv(file_path):
    values = []
    with open(file_path, 'r') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            values.append(int(row[0]))
    return values
    
raw_data = read_csv(raw_vaisala_data)
filtered_data = read_csv(filtered_vaisala_data)
median_filtered_data = read_csv(median_filtered_data)

# customize plot labels 
plt.figure(figsize=(12, 6), dpi=400)

plt.plot(raw_data, marker='*', color='red', linestyle='-', markersize=4, label="(uC)Vaisala GMP343 raw") # raw data
#plt.plot(filtered_data, marker='o', color='green', markersize=4, label="(uC)Vaisala GMP343 moving average filtered") # filtered data

plt.plot(median_filtered_data, marker='o', color='blue', markersize=4, label="(uC)Vaisala GMP343 filtered(median)") # filtered data

plt.xlabel('Time (s)')
plt.ylabel('CO2 concentration (ppm)')
plt.title('Vaisala GMP343 CO2 Moving Average Filter and Median Filter validation')
plt.xticks(rotation=45)
plt.grid(True)
plt.legend()


# display plot 
plt.tight_layout()
plt.savefig("raw_and_median_filter_plot.png", bbox_inches='tight')
#plt.show()
#plt.savefig("vaisalaraw.png")
#plt.savefig("vaisala_filtered.png")

