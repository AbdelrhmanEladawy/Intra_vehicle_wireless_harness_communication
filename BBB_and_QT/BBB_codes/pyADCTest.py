import Adafruit_BBIO.ADC as ADC
import time

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
        
        # You might want to convert the ADC value to voltage or scale it as per your requirement
        # For instance, if you are using a 3.3V reference voltage, you can convert the ADC value to voltage
        voltage = pot_value * 3.3  # Assuming 3.3V reference voltage
        print("Voltage:", voltage*(300/3.3))
        
        # Add a small delay before reading again
        time.sleep(0.1)

except KeyboardInterrupt:
    print("Exiting...")
