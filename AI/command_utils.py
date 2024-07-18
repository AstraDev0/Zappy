##zappy_byte_encoder Documentation
# this function takes a string as a parameter and formats it into a byte object
# and send it through the socket. 
#It also formats the print to the console so no unnecessary spaces will be there

def zappy_byte_encoder(cmd_as_str, socket):
    message = cmd_as_str + "\n"
    #sent data to server
    socket.sendall(message.encode())
    message.replace("\n", "")
    print('-->' "%s" % message, end="")
    

##zappy_byte_parser Documentation
# basically the reverse operation of the encoder, 
# but also splitting the data in separate strings
# and prints them clean into the console
# empty byte objects (no response from Server) will be ignored as stated in the task
### Maybe we need to add an if tree into it because some commands are vary from the response

def zappy_byte_parser(socket):
    limit_client = socket.recv(1024).decode()
    map_size = socket.recv(1024).decode()
    if limit_client == "b''" or map_size == "b''":
        return
    split_data = [limit_client, map_size]
    return split_data

    

