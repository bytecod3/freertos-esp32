import csv
import matplotlib.pyplot as plt

ppm = []
raw_vaisala_data  = "vaisala1_data_raw.csv"
filtered_vaisala_data = "vaisala1_filtered.csv"

def read_csv(file_path):
    values = []
    with open(file_path, 'r') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            values.append(int(row[0]))
    return values
    
raw_data = read_csv(raw_vaisala_data)
filtered_data = read_csv(filtered_vaisala_data)



# customize plot labels 
plt.figure(figsize=(12, 6), dpi=400)

plt.plot(raw_data, marker='*', color='red', linestyle='-', markersize=4, label="(uC)Vaisala GMP343 raw") # raw data
plt.plot(filtered_data, marker='o', color='green', markersize=4, label="(uC)Vaisala GMP343 filtered") # filtered data


plt.xlabel('Time (s)')
plt.ylabel('CO2 concentration (ppm)')
plt.title('Microcolumns Vaisala GMP343 CO2 Moving Average Filter validation')
plt.xticks(rotation=45)
plt.grid(True)
plt.legend()


# display plot 
plt.tight_layout()
plt.savefig("median_filter_plot.png", bbox_inches='tight')
#plt.show()
#plt.savefig("vaisalaraw.png")
#plt.savefig("vaisala_filtered.png")

