import serial
import requests
import json
# Set the serial port and baud rate
serial_port = 'COM5'  # Change this to your Arduino's serial port
baud_rate = 9600
# Open the serial port
ser = serial.Serial(serial_port, baud_rate)
#Firebase
firebase_url = ""
api_key = ""

# data to check if the data has been changed in system

dummyData , dummyLineData = '',''

#fetching data from Firebase
def FirebaseGetData(node_path):
    r = requests.get(f"{firebase_url}/{node_path}.json?auth={api_key}")
    try:
        if r.status_code == 200:
            return r.text
        else:
            return None
    finally:
        r.close()
#uploadind data in realtime db
def FirebaseUpload(data, node_path):
    response = requests.patch(f"{firebase_url}/{node_path}.json?auth={api_key}", json=data)
    response.close()


#mainloop
try:
    while True:
        # Getting Sensors value from the Mega
        line = ser.readline().decode('utf-8').rstrip()
        if (dummyLineData == line):
            pass
        else:
            dummyLineData = line
            try:
                temperature, humidity, ir, flame = line.split(',')
                flame = '0' if flame == '1' else '1' # the change as this sensor give 1 on no flame and 0 on flame
                sensordict = {
                    'temp': temperature, 
                    'ir' : ir, 
                    'flame':flame,
                    "humidity": humidity,
                }

                FirebaseUpload(node_path='realtime', data=sensordict)
                print(sensordict)
                #fire alram system
            except:
                pass
        
        switchesDataString = ''
        #fetching switch data 
        firebase_data = FirebaseGetData("switches") #{"auto":"0","eggs":"1","fan":"1","food":"1","heater":"0","light":"1","waste":"1"}
        print(firebase_data)
        if (firebase_data == dummyData):
            pass
        else:
            dummyData = firebase_data
            for i in list(json.loads(firebase_data).values()):
                switchesDataString = switchesDataString + i
            print(switchesDataString)
            ser.write(switchesDataString.encode('utf-8'))

except KeyboardInterrupt:
    # Close the serial port when Ctrl+C is      pressed
    ser.close()
    print("Serial port closed.")