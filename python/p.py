#!/usr/bin/python

import argparse

def main():
    # find the file to read
    args = parseArguments()
    print args
    
    returner = parseFile(args.input)
    
    print returner
    
    if args.start and args.string:
        stringIterator = iterateString(args.string)
        success = execute(returner, args.start, stringIterator)
        
        if success:
            print "Success"
        else:
            print "Failure"

def parseFile(fileName):
    with open(fileName) as fileStream:
        return parseStream(fileStream)
    

def parseStream(stream):
    # initialize parse results with distincguisted end state
    returner = {
        'END' : []
    }
    
    for line in stream:
        parseLine(line, returner)
        
    return returner
        
def parseLine(
        line,
        returner):
    tokens = line.strip().split()
    
    if len(tokens) < 3:
        return

    # If a successor state is not specified,
    # it means its going to the end state
    if len(tokens) == 3:
        tokens.append('END')

    # extract salient elements of the line
    stateName = tokens[0]
    charName = tokens[2][1:-1]
    successorStateName = tokens[3]

    if stateName in returner:
        returner[stateName].append(
            (charName, successorStateName))
    else:
        returner[stateName] = [
            (charName, successorStateName)]


def parseArguments():
    parser = argparse.ArgumentParser()
    
    parser.add_argument(
        "--input",
        help="input file",
        required=True)
    
    parser.add_argument(
        "--start",
        help="start symbol--start the parsing from here")
    
    parser.add_argument(
        "--string",
        help="string to parse")
    
    args = parser.parse_args()

    return args

def execute(
        nfa,
        startState,
        stringIterator):

    states= set(startState)
    
    for character in stringIterator:
        states = executeStep(nfa, states, character)
        if "END" in states:
            return True
        
        if len(states) == 0:
            return False

    return False


def executeStep(nfa, states, character):
    returner = set()
    for state in states:
        for arc in nfa[state]:
            if arc[0] == character:
                returner.add(arc[1])
    return returner
    
    
def iterateString(string):
    for character in string:
        yield character

if __name__ == "__main__":
    main()

    
    
