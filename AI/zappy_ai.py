#!/usr/bin/env python3
import sys
import port_handling

if len(sys.argv) == 2 and sys.argv[1] == "--help":
    help = open("help-command.txt", "r+")
    print(help.read())
    help.close()
    exit(0)

if len(sys.argv) != 7 and len(sys.argv) != 5:
    print("Usage: ./zappy_ai -p port -n name -h machine")
    exit(84)
elif len(sys.argv) == 7:
    port_handling.ia_loop(sys.argv[2], sys.argv[4], sys.argv[6])
else:
    port_handling.ia_loop(sys.argv[2], sys.argv[4], "localhost")
