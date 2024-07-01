import json

# Define the path to the JSON file
json_file_path = "/home/debian/jsonFileBBB.json"

# Read the JSON file
with open(json_file_path, 'r') as file:
	data = json.load(file)

# Modify the values
data['speed'] = "150"
data['fuel_states'] = False

# Write the modified data back to the JSON file
with open(json_file_path, 'w') as file:
	json.dump(data, file, indent=4)  # Use indent for pretty formatting (optional)
