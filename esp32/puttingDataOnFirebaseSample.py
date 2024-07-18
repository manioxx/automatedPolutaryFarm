import urequests as requests
import urandom, network
import time

# Replace with your Firebase Realtime Database URL
firebase_url = '....'

# Replace with the path to the node you want to update
node_path = '....'

# Replace with your Firebase API key
api_key = '...'

# Create the full URL for the update
update_url = f"{firebase_url}/{node_path}.json?auth={api_key}"
def connect_to_wifi(ssid, password):
    wlan = network.WLAN(network.STA_IF)
    if not wlan.isconnected():
        print("Connecting to Wi-Fi...")
        wlan.active(True)
        wlan.connect(ssid, password)
        while not wlan.isconnected():
            pass
    print("Connected to Wi-Fi")
# Configure your Wi-Fi credentials
WIFI_SSID = "..."
WIFI_PASSWORD = "..."

# Connect to Wi-Fi
connect_to_wifi(WIFI_SSID, WIFI_PASSWORD)
while True:
    try:
        time.sleep(.3)

        # Generate a random integer between 0 and 100 (inclusive)
        random_integer = urandom.randint(0, 100)
        random_integer1 = urandom.randint(0, 100)

        # Define the data you want to update
        data_to_update = {
            'humidity': random_integer,
            'temp': random_integer1,

        }

        # Send a PATCH request to update the data
        response = requests.patch(update_url, json=data_to_update)

        if response.status_code == 200:
            print("Data updated successfully")
        else:
            print(f"Error updating data: {response.status_code}")
            print(response.text)

    except OSError as e:
        print(f"An error occurred: {e}")
        # You can add code here to handle the error as needed

    finally:
        if 'response' in locals():
            response.close()
        if 'random_integer' in locals():
            del random_integer
        if 'random_integer1' in locals():
            del random_integer1
