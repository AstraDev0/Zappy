import listen
import utils

def look(sock):
    message = "Look\n"
    sock.sendall(message.encode())
    message_recieved = listen.listen(sock)
    print('received "%s"' % message_recieved)
    if message_recieved == "ko\n":
        print("look failed")
        return "look failed"
    if message_recieved == "dead\n":
        print("dead")
        return "dead\n"
    if message_recieved == "ok\n":
        return "look failed"

    current_vision = parse_vision(message_recieved)
    if (utils.contains_str("player",current_vision[0]) == False) :
        print ("look failed")
        return "look failed"
    for i in current_vision:
        print(i)
    return current_vision


def parse_vision(message):
    message = message.split(",")
    current_vision = message
    return current_vision


def find_player(level, sock):
    current_vision = look(sock)
    while current_vision[0] != "player":
        if current_vision[0] == "player":
            return
        else:
            if current_vision[1] == "player":
                message = "Forward\n"
                sock.sendall(message.encode())
            elif current_vision[2] == "player":
                message = "Right\n"
                sock.sendall(message.encode())
            else:
                message = "Left\n"
                sock.sendall(message.encode())
        current_vision = look(sock)
