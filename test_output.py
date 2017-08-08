def main():
    file = open("output.txt", "r")
    w = [int(x) for x in file.next().split()] # read first line
    flag = False
    for i in range(200000):
        if w[i] != 200000-i+1:
            flag = True
            break
    if flag:
        print "Output Correct"
    else:
        print "Output Incorrect"

if __name__ == "__main__":
    main()
