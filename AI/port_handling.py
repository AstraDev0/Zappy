import socket
import game_loop
import command_utils as cmdu


def send_handshake(name, sock):
    cmdu.zappy_byte_encoder(name, sock)
    message = cmdu.zappy_byte_parser(sock)
    if message[0] == 'ko':
        print("<--" "%s" % message[0])
        return 84
    elif int(message[0]) >= 1:
        for msg in message:
            print("<--" "%s" % msg)
        return 0
    else:
        print("<--", end="")
        print(message[0])
        return 84
    


def ia_loop(port, name, machine):
    valid_handshake = 84
    print("port: %s, name: %s, machine: %s" % (port, name, machine))
    # Create a TCP/IP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # Connect the socket to the port where the server is listening
    server_address = (machine, int(port))
    print("connecting to %s port %s" % server_address)
    sock.connect(server_address)
    try:
        # Send data
        data = sock.recv(512).decode()
        if data == "WELCOME\n":
            data.replace("\n", "")
            print("<--" "%s" % data, end="")
            valid_handshake = send_handshake(name, sock)
            if valid_handshake == 84:
                return 84
            game_loop.game_loop(sock)
        else:
            return 84
    finally:
        return 0
