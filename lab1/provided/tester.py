import sys

def test(fil1,fil2):
    try:
        #open the files
        f1 = open(fil1)
        f2 = open(fil2)
        #create dictionarires for the labels
        labels1 = {}
        labels2 = {}

        #read the files
        lines1 = f1.readlines()
        lines2 = f2.readlines()

        #remove white space and seperate by signal
        #lines1/2 are now 2D arrays with the signals in the columns
        #and each row being a tick of the clock
        lines1 = [ line.strip().split('\t') for line in lines1]
        lines2 = [ line.strip().split('\t') for line in lines2]

        count = 0

        #now create a mapping from labels to column number
        #this allows us to ignore the order in which students added
        #the probes and pins to the log file
        for label in lines1[0]:
            labels1[label] = count
            count = count + 1
            
        count = 0
        
        for label in lines2[0]:
            labels2[label] = count
            count = count + 1


        #report a mismatch in the number of lines
        if len(labels1) != len(labels2):
                print fil1 + ' has ' + str(len(labels1)) + 'lines but ' +\
                      fil2 + ' has ' + str(len(labels2)) + 'lines.'


        #report what labels the student is missing
        for label in labels1:
            if label not in labels2:
                print 'Could not find signal ' + label


        #now for each tick see if the students answers match
        #but ignore the signals that we have marked as don't care
        #and those the student hasn't added
        index = 1
        for row1,row2 in zip(lines1[1:], lines2[1:]):
            for label in labels1:
                if label in labels2 and row1[labels1[label]] != 'X' and \
                   row1[labels1[label]] != row2[labels2[label]]:
                    print 'Signal ' + label + ' in row ' +\
                    str(index) + ' do not match.'
                    print 'Signal should be ' + row1[labels1[label]] +\
                          ' but is ' + row2[labels2[label]] + '.'
            index = index + 1
                

        

    except Exception as e:
        print e

if __name__ == '__main__':
    test(sys.argv[1], sys.argv[2])
