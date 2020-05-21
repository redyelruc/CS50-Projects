while True:
    height = input("Height: ")
    if len(height) == 1:
        height = int(height)
        if height >= 1 and height <= 8:
            for i in range(1, height + 1):
                print(' '*(height-i) + '#' * i + '  ' + '#' * i)
            break
        