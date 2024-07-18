import urequests as requests
import network
import machine
import ujson
import time

# Define the GPIO pin for the built-in LED
led_pin = machine.Pin(2, machine.Pin.OUT)
led_pin.off() 
def ledBlinkWhenConnectedWALN():
    time.sleep(.1)
    led_pin.on()
    time.sleep(.1)
    led_pin.off()
    time.sleep(.1)
    led_pin.on()
    time.sleep(.1)
    led_pin.off()
    time.sleep(.1)
    led_pin.on()
    time.sleep(.1)
    led_pin.off()
    time.sleep(.1)
    led_pin.on()
    time.sleep(1)
    led_pin.off()
    

# Function to connect to Wi-Fi
def connect_to_wifi(ssid, password):
    wlan = network.WLAN(network.STA_IF)
    if not wlan.isconnected():
        print("Connecting to Wi-Fi...")
        wlan.active(True)
        wlan.connect(ssid, password)
        while not wlan.isconnected():
            pass
    print("Connected to Wi-Fi")

# Firebase Realtime Database URL
FIREBASE_URL = "..."

# Function to fetch data from Firebase
def fetch_data_from_firebase(url):
    response = requests.get(url)
    if response.status_code == 200:
        return response.text
    else:
        return None

# Configure your Wi-Fi credentials
WIFI_SSID = "..."
WIFI_PASSWORD = "..."

# Connect to Wi-Fi
connect_to_wifi(WIFI_SSID, WIFI_PASSWORD)

# Make a GET request to fetch data from Firebase
while(True):
    firebase_data = fetch_data_from_firebase(FIREBASE_URL)

    if firebase_data is not None:
        print("Data from Firebase:")
        print(firebase_data)
    else:
        print("Failed to fetch data from Firebase.")
    data =ujson.loads(firebase_data)
    if data["eggs"] == "1":
        led_pin.on()  # Turn on the LED
    else:
        led_pin.off()  # Turn off the LED
  # Wait for 1 second

