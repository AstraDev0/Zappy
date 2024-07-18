def contains_str(string, list):
    list = list.split(" ")
    for i in list:
        print(str(i))
        if i in string:
            print("found " + string)
            return True
    return False

def is_string_in_list(string, list):
    list = list.split(" ")
    for i in list:
        print(str(i))
        if string == i:
            print("found " + string)
            return True
    return False
