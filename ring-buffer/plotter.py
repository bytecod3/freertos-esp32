import csv
import matplotlib.pyplot as plt

# set to 0 to plot median filter
moving_average = 0
moving_avg_and_median = 1

ppm = []
raw_vaisala_file  = "vaisala1_data_raw.csv"
mov_avg_filtered_vaisala_file = "vaisala1_mov_avg_filtered.csv"
median_filtered_file = "vaisala_median_filtered.csv"

def read_csv(file_path):
    values = []
    with open(file_path, 'r') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            values.append(int(row[0]))
    return values
    
raw_data = read_csv(raw_vaisala_file)
mov_avg_filtered_data = read_csv(mov_avg_filtered_vaisala_file)
median_filtered_data = read_csv(median_filtered_file)

def setup_plot(title):
    plt.figure(figsize=(12, 6), dpi=400)
    plt.title(title)
    plt.xlabel('Time (s)')
    plt.ylabel('CO2 concentration (ppm)')
    plt.xticks(rotation=45)
    plt.grid(True)
    plt.legend()
    plt.tight_layout()


def create_comparison_plot(raw_data, filtered_data, filter_type, filter_color, filename):
    setup_plot(f'Vaisala GMP343 CO2 Raw + {filter_type} Filter (Window = 10)')

    # plot both data sets 
    plt.plot(raw_data, marker='*', color='red', linestyle='-', markersize=4, label="Vaisala GMP343 raw") 
    plt.plot(filtered_data, marker='o', color=filter_color, markersize=4, label=f"Vaisala GMP343 {filter_type} Filtered")

    # save
    plt.savefig(filename, bbox_inches='tight')

# plot moving average 
if moving_average == 1:
    create_comparison_plot(
        raw_data = raw_data, 
        filtered_data = mov_avg_filtered_data, 
        filter_type = "Moving Average", 
        filter_color = "green", 
        filename="raw_and_moving_avg_filter_plot.png"
    )

# plot median filter
else:
    create_comparison_plot(
        raw_data = raw_data, 
        filtered_data = median_filtered_data, 
        filter_type = "Median", 
        filter_color = "blue", 
        filename="raw_and_median_filter_plot.png"
    )

# # plot moving average and median filter
# if moving_avg_and_median == 1:
#     plt.title('Vaisala GMP343 CO2 Moving Average + Median Filter (Window = 10)')
#     plt.plot(mov_avg_filtered_data, marker='o', color='green', markersize=4, label="(uC)Vaisala GMP343 Moving Average Filtered")
#     plt.plot(median_filtered_data, marker='o', color='blue', markersize=4, label="(uC)Vaisala GMP343 Median Filter (Window = 10)") # filtered data
#     plt.savefig("moving_average_and_median_filter_plot.png", bbox_inches='tight')
#     # customize plot labels 
#     plt.figure(figsize=(12, 6), dpi=400)
#     plt.xlabel('Time (s)')
#     plt.ylabel('CO2 concentration (ppm)')
#     plt.xticks(rotation=45)
#     plt.grid(True)
#     plt.legend()
#     plt.tight_layout()


