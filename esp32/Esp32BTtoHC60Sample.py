'''
Before this file bluetooth should be set in slave mode using AT command
service_uuid, char_uuid should be noted and changed
'''
from ubluez import Bluetooth
from ubinascii import hexlify

# Define a Bluetooth service and characteristic
service_uuid = 0x180F 
char_uuid = 0x2A19

def on_data_received(sender, data):
    print("Received data:", data.decode('utf-8'))

bt = Bluetooth()
bt.advertise('ESP32', service_uuid=service_uuid, services=[(service_uuid, [char_uuid])])
bt.add_service(service_uuid)
bt.add_characteristic(char_uuid, notify=False, indicate=False, broadcast=False, on_read=None, on_write=None, on_notify=None, on_indicate=None)
bt.add_service(service_uuid)

char = bt.characteristic(char_uuid)
char.on_read = on_data_received

while True:
    data_to_send = "Hello, Arduino!"
    char.value(data_to_send.encode('utf-8'))
    bt.advertise()

