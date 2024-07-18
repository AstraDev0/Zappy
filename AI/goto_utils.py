import look_for_utils
import utils
import listen


def move_forward(sock):
    print("Forward")
    message = "Forward\n"
    sock.sendall(message.encode())
    return listen.listen(sock)


def move_left(sock):
    print("Left")
    message = "Left\n"
    sock.sendall(message.encode())
    if listen.listen(sock) == "dead\n":
        return "dead"
    return move_forward(sock)


def move_right(sock):
    print("Right")
    message = "Right\n"
    sock.sendall(message.encode())
    if listen.listen(sock) == "dead\n":
        return "dead\n"
    return move_forward(sock)



def take_item(sock, item):
    print("Take " + item + "\n")
    message = "Take " + item + "\n"
    sock.sendall(message.encode())
    return listen.listen(sock)


def goto_item(sock, item):
    found = False
    while found == False:
        current_vision = look_for_utils.look(sock)
        if current_vision == "look failed" :
            return
        if utils.is_string_in_list(item, current_vision[0]):
            action = take_item(sock, item)
            if action == "dead\n":
                return "dead\n"
            elif action == "ko\n":
                break
            else :
                return "found"
        elif utils.is_string_in_list(item, current_vision[2]):
            if move_forward(sock) == "dead\n":
                return "dead\n"
        elif utils.is_string_in_list(item, current_vision[1]):
            if move_right(sock) == "dead\n":
                return "dead\n"
        else:
            if move_left(sock) == "dead\n":
                return "dead\n"
