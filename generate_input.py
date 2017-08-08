import random


def main():
    create_worst_case()

def create_random_case ():
    # my code here
    file = open("input.txt", "w");
    file.write("50\n");
    for i in range (50):
        file.write("200000\n")
        for j in range (200000):
            r = random.randint(a=0, b=j)
            file.write("%d " % r)
        file.write("\n")
    file.close()

def create_worst_case ():
    # worst case
    infile = open("input.txt", "w");
    outfile = open("output.txt", "w");

    nums = 200000

    infile.write("1\n%d\n" % nums)
    for i in range (1, nums + 1):
        inp = i - 1;
        out = nums - i + 1;
        infile.write("%d " % inp)
        outfile.write("%d " % out);

    infile.close()
    outfile.close()


if __name__ == "__main__":
    main()
