def cost(tile):
    if(tile == 's'):
        return 1
    if(tile == 'x'):
        return 0
    if(tile == 'r'):
        return 1
    if(tile == 'g'):
        return 3
    if(tile == 'm'):
        return 20
    if(tile == 'w'):
        return 100

def main():
    rows = 0
    cols = 0
    f=open("road.txt", "r")
    if f.mode == 'r':
        fl =f.readlines()
        firstline = fl[0]
        for x in firstline:
            cols += 1

        for x in fl:
            rows += 1

    #print(fl)
    print("there are " + str(rows) + " rows")
    print("there are " + str(cols) + " (" + str(cols-1) + ")" +" cols")

    cols -= 1
    #this is to account for the \n character
    #which isnt actually part of the map

    map = [['_' for i in range(0,cols)] for i in range(0,rows)]
    #create second array to store all visited node

    #transfering all the tile data from file into 2-d array
    i = 0
    while i < rows:
        j = 0
        while j < cols:
            map[i][j] = fl[i][j]
            j+=1
        i+=1

    for x in map:
       print(x)
    print()

    secmap = a_star(map)
    for x in secmap:
        print(x)

def a_star(map):

    rows = len(map)
    cols = len(map[0])
    secmap = [['_' for i in range(0,cols)] for i in range(0,rows)]

    for x in map:
        print(x)

    #finding s (start) coordinate and x (goal) coordinate
    i = 0
    while i < rows:
        j = 0
        while j < cols:
            if map[i][j] == 's':
                starti = i
                startj = j

            if map[i][j] == 'x':
                goali = i
                goalj = j
            j+=1
        i+=1

    print("Starting coordinte is (" + str(starti) + "," + str(startj) + ")")
    print("Goal coordinte is (" + str(goali) + "," + str(goalj) + ")")

    scoord = (starti,startj)
    curri = starti
    currj = startj
    xcoord = (goali,goalj)

    #format for the tuple that keeps track of exploritory information
    #(tile,f(n),g(n),h(n),prev node, i, j)
    #tile consists of map data, grass, road, mountain, start, etc
    #f(n) = g(n) + h(n)
    #g(n) = cost (sum of all previous nodes)
    #h(n) = heuritic (man hattan distance, distance from here to goal node)
    #manhattan/taxi-cab distance
    #direction will be < > ^ V, these will denote shortest path to get to current tile
    #i and j will be the coordinates of the map array

    #select first element in the frontier and expand
    #add coordinates to frontier
    #sort the frontier based on heuristics

    manhati = abs(goali - starti)
    manhatj = abs(goalj - startj)
    mandist = manhati + manhatj

    #the first tile's fn is just mandist because cost is 0 so
    #fn = mandist + 0
    #which is just mandist

    frontier = []
    #format for tuple
    #(tile, fn, gn, hn, previous node, i, j)
    frontier.append(('s',mandist,0,mandist,'s',starti,startj))

    notfound = True
    limit = 0
    while(notfound):
        #selecting element with smallest fn and storing contents into variables

        iter = 0
        (tile,fn,gn,hn,direction,i,j) = frontier[0]
        min = fn
        index = 0
        while(iter < len(frontier)):
            (tile,fn,gn,hn,direction,i,j) = frontier[iter]
            print("(",i,j,")",fn)
            if min > fn:
                min = fn
                index = iter
            iter += 1
        print("----------------------")

        #print("VVV")
        #print(str(i) + " " + str(j))
        #print(len(frontier))
        #print(iter)
        (tile,fn,gn,hn,direction,i,j) = frontier.pop(index)
        print("smallest = ", i, j, fn)

        #print(tile + " " + str(fn) + " " + str(gn) + " " + str(hn) + " " + direction + " " + str(i) + " " + str(j) )
        #print("^^^")

        if(tile == 'x'):
            notfound = False
            break

        #expand up, down, left ,right
        upi = i - 1
        upj = j

        downi = i + 1
        downj = j

        lefti = i
        leftj = j - 1

        righti = i
        rightj = j + 1

        #check if valid coordinates
        if(upi > -1 and upi < rows and upj > -1 and upj < cols):
            currtile = map[upi][upj]
            currcost = cost(currtile) + gn
            currhuer = abs(goali - upi) + abs(goalj - upj)
            currfn = currcost + currhuer
            currdir = 'V'

            if(secmap[upi][upj] == '_'):
                secmap[upi][upj] = (currdir,currfn)
                frontier.append((currtile,currfn,currcost,currhuer,currdir,upi,upj))
            else:
                (dir,existingfn) = secmap[upi][upj]
                if(currfn < existingfn):
                    secmap[upi][upj] = (currdir,currfn)
                    frontier.append((currtile,currfn,currcost,currhuer,currdir,upi,upj))


        if(downi > -1 and downi < rows and downj > -1 and downj < cols):
            currtile = map[downi][downj]
            currcost = cost(currtile) + gn
            currhuer = abs(goali - downi) + abs(goalj - downj)
            currfn = currcost + currhuer
            currdir = '^'

            if(secmap[downi][downj] == '_'):
                secmap[downi][downj] = (currdir,currfn)
                frontier.append((currtile,currfn,currcost,currhuer,currdir,downi,downj))
            else:
                (dir,existingfn) = secmap[downi][downj]
                if(currfn < existingfn):
                    secmap[downi][downj] = (currdir,currfn)
                    frontier.append((currtile,currfn,currcost,currhuer,currdir,downi,downj))

        if(lefti > -1 and lefti < rows and leftj > -1 and leftj < cols):
            currtile = map[lefti][leftj]
            currcost = cost(currtile) + gn
            currhuer = abs(goali - lefti) + abs(goalj - leftj)
            currfn = currcost + currhuer
            currdir = '>'

            if(secmap[lefti][leftj] == '_'):
                secmap[lefti][leftj] = (currdir,currfn)
                frontier.append((currtile,currfn,currcost,currhuer,currdir,lefti,leftj))
            else:
                (dir,existingfn) = secmap[lefti][leftj]
                if(currfn < existingfn):
                    secmap[lefti][leftj] = (currdir,currfn)
                    frontier.append((currtile,currfn,currcost,currhuer,currdir,lefti,leftj))

        if(righti > -1 and righti < rows and rightj > -1 and rightj < cols):
            currtile = map[righti][rightj]
            currcost = cost(currtile) + gn
            currhuer = abs(goali - righti) + abs(goalj - rightj)
            currfn = currcost + currhuer
            currdir = '<'

            if(secmap[righti][rightj] == '_'):
                secmap[righti][rightj] = (currdir,currfn)
                frontier.append((currtile,currfn,currcost,currhuer,currdir,righti,rightj))
            else:
                (dir,existingfn) = secmap[righti][rightj]
                if(currfn < existingfn):
                    secmap[righti][rightj] = (currdir,currfn)
                    frontier.append((currtile,currfn,currcost,currhuer,currdir,righti,rightj))

        #for x in secmap:
            #print(x)
        #print()
        limit += 1
        #now frontier is a list of tuples and we need to sort so that the first
        #element contains the lowest fn value

        #actually dont need to sort, just find the minimum

    print("Found goal in " + str(limit) + " steps")

    #for x in secmap:
        #print(x)

    path = []
    #begin constructing path by following the previous nodes starting at goal to start
    i = goali
    j = goalj
    #print(str(i) + " " +str(j))
    #print(str(starti) + " " +str(startj))

    while((i != starti) or (j != startj)):
        (dir,value) = secmap[i][j]
        path.append(dir)
        #print(str(i) + " " +str(j))
        if(dir == '^'):
            i-=1
        if(dir == 'V'):
            i+=1
        if(dir == '>'):
            j+=1
        if(dir == '<'):
            j-=1
    #print()
    #print(path)

    revpath = []
    for x in path:
        revpath = [x] + revpath

    i = 0
    while i < len(revpath):
        if(revpath[i] == '^'):
            revpath[i] = 'V'
        elif(revpath[i] == 'V'):
            revpath[i] = '^'
        elif(revpath[i] == '>'):
            revpath[i] = '<'
        elif(revpath[i] == '<'):
            revpath[i] = '>'
        i+=1

    print()
    print(revpath)

    i = starti
    j = startj

    for x in revpath:
        secmap[i][j] = x
        if(x == '^'):
            i-=1
        if(x == 'V'):
            i+=1
        if(x == '>'):
            j+=1
        if(x == '<'):
            j-=1
    print()
    secmap[i][j] = 'X'

    i = 0
    while i < len(secmap):
        j = 0
        while j < len(secmap[0]):
            if(not isinstance(secmap[i][j], str)):
                secmap[i][j] = '_'
            j+=1
        i+=1

    #for x in secmap:
        #print(x)

    return secmap

if __name__ == '__main__':
    main()
