import Adafruit_BBIO.ADC as ADC
import time
import json

# Define the path to the JSON file
json_file_path = "/home/debian/jsonFileBBB.json"
# Define the pin connected to the potentiometer
potentiometer_pin = "P9_40"
# Initialize the ADC library
ADC.setup()

try:
	while True:
		# Read the analog value from the potentiometer
		pot_value = ADC.read(potentiometer_pin)

        # Print the raw ADC value
		print("Raw ADC Value:", pot_value)

        # You might want to convert the ADC value to voltage or scale it as per>
        # For instance, if you are using a 3.3V reference voltage, you can conv>
		speed = pot_value*(300)
		print("speed:", speed)

	# Read the JSON file
		with open(json_file_path, 'r') as file:
			data = json.load(file)

	# Modify the values
		data['speed'] = str(int(speed))
	# Write the modified data back to the JSON file
		with open(json_file_path, 'w') as file:
			json.dump(data, file, indent=4)  # Use indent for pretty formatting

        # Add a small delay before reading again
		time.sleep(0.1)

except KeyboardInterrupt:
    print("Exiting...")

