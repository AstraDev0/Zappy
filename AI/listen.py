import re
import command_utils as cmdu


def listen(sock):
    message = sock.recv(1024)
    return message.decode()


import utils


def inventory(sock):
    message = "Inventory\n"
    sock.sendall(message.encode())
    message_recieved = listen(sock)
    if message_recieved == "ko\n":
        print("look failed")
        return "not inventory\n"
    if message_recieved == "dead\n":
        print("dead")
        return "dead\n"
    if message_recieved == "ok\n":
        return
    inventory = parse_inventory(message_recieved)
    if inventory == "not inventory\n":
        return "not inventory\n"
    return inventory


def parse_inventory(message):
    inventory = []
    if utils.contains_str("player", message[0]) or utils.contains_str("Elevation", message[0])\
        or utils.contains_str("Current", message[0]) or utils.contains_str("ok\n", message[0]):
        print ("not inventory")
        return "not inventory\n"
    print("Inventory received: " + message)
    # Extract the numbers using regular expressions

    numbers = re.findall(r"\d+", message)

    # Convert the numbers from strings to integers
    inventory = [int(num) for num in numbers]

    print("Current inventory:", inventory)
    return inventory

def get_player_level(message):
    last_part = message.split()[-1]
    return int(last_part)
