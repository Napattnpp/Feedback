import socket

esp32IP = "192.168.1.4"
udpPort = 63395
message = "@motor|fw$60$60;"

# Create a UDP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

try:
    # Encode the message to bytes
    byte_message = message.encode('utf-8')

    # Send the message to the specified address
    sock.sendto(byte_message, (esp32IP, udpPort))
except Exception as e:
    print(f"An error occurred: {e}")
finally:
    # Close the socket
    sock.close()
