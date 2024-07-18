import level_quests
import listen


def game_loop(sock):
    message_recieved = "run\n"
    current_level = 1

    while message_recieved != "dead\n":
        print("current level: " + str(current_level))
        if current_level == 1:
            message_recieved = level_quests.leveling_quest(sock, current_level)
            print("leveling quest done")
            current_level = 2
        if current_level == 2:
            message_recieved = level_quests.leveling_quest(sock, current_level)
            print("leveling quest done")
            current_level = 3
        if current_level == 3: 
            message_recieved = level_quests.leveling_quest(sock, current_level)
            print("leveling quest done")
            current_level = 4
        listen.inventory(sock)
    print("IA is dead")
    print("closing socket")
    sock.close()
    return
