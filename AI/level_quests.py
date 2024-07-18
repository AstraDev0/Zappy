import listen
import goto_utils
from time import sleep

def leveling_quest(sock, level):
    elevation = False
    
    print("level " + str(level) + " quest")
    while elevation == False:
        inventory = listen.inventory(sock)
        if inventory == "ok\n":
            continue
        if inventory == "dead\n":
            return "dead\n"
        if inventory == "not inventory\n":
            continue
        if inventory[0] < 9:
            if goto_utils.goto_item(sock, "food") == "dead\n":
                return "dead\n"
        if level == 1:
            if level_1(sock, inventory) == "dead\n":
                return "dead\n"
            elevation = True
        if level == 2:
            if level_2(sock, inventory) == "dead\n":
                return "dead\n"
            elevation = True
        if elevation == True:
            print("Elevation in progress\n")
            message = "Incantation\n"
            sock.sendall(message.encode())
            return

def set_item(item, sock):
    print("Set " + item)
    message = "Set " + item + "\n"
    sock.sendall(message.encode())

def level_1(sock, inventory):
    if inventory[1] < 1:
        status = goto_utils.goto_item(sock, "linemate")
        if status == "dead\n":
            return "dead\n"
        set_item("linemate", sock);

def level_2(sock, inventory):
    if inventory[1] < 1:
        status = goto_utils.goto_item(sock, "linemate")
        if status == "dead\n":
            return "dead\n"
    if inventory[2] < 1:
        status = goto_utils.goto_item(sock, "deraumere")
        if status == "dead\n":
            return "dead\n"
    if inventory[3] < 1:
        status = goto_utils.goto_item(sock, "sibur")
        if status == "dead\n":
            return "dead\n"
        set_item("linemate", sock);
        set_item("deraumere", sock);
        set_item("sibur", sock);


def level_3(sock, inventory):
    if inventory[1] < 2:
        status = goto_utils.goto_item(sock, "linemate")
        if status == "dead\n":
            return "dead\n"
    if inventory[2] < 1:
        status = goto_utils.goto_item(sock, "sibur")
        if status == "dead\n":
            return "dead\n"
    if inventory[3] < 2:
        status = goto_utils.goto_item(sock, "phiras")
        if status == "dead\n":
            return "dead\n"
    else:
        set_item("linemate", sock);
        set_item("linemate", sock);
        set_item("sibur", sock);
        set_item("phiras", sock);
        set_item("phiras", sock);