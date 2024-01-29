#* Day 2
#* l w h dimensions order
#* Surface formula = 2*l*w + 2*w*h + 2*h*l

def readData():
    surface = 0;
    secondSurface = 0;

    f = open("input.txt", "r");
    line = f.readline();
    while(line):
        i = 0;
        data = line.split("x");

        surface += 2*int(data[0])*int(data[1]) + 2*int(data[1])*int(data[2]) + 2*int(data[2])*int(data[0]);
        surface += min(int(data[0]) * int(data[1]), int(data[1]) * int(data[2]), int(data[0]) * int(data[2]));

        secondSurface += int(data[0]) * int(data[1]) * int(data[2]);
        
        for i in range(0, 3):
            data[i] = int(data[i]);

        min1 = min(data[0], data[1], data[2]);
        data.remove(min1);
        min2 = min(data[0], data[1]);

        secondSurface +=  2 * min1 + 2 * min2;

        line = f.readline();
    
    print("Total surface : " + str(surface));
    print("Second surface : " + str(secondSurface));
    f.close();
readData();