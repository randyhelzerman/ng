#!/usr/local/bin/python3

"""
operator precidence parser using precidence parsing

run unit tests like:
pytest -s op.py
"""

# imports
import io

class Opp(object):
    """
    operator precidence parser using precidence parsing
    """

    def __init__(
            self):
        self.operators = {}


    def parse(
            self,
            grammar_file_name,
            input_string):
        """
        Read in the grammar from grammar file name, and use it to parse
        the input string.
        """
        self.t_read_operator_file(grammar_file_name)
        self.parse_string(input_string)


    def parse_string(
            self,
            input_string):
        """
        Assumes grammar has already been read in
        parses the input string with it
        """

        self._parse_expression(tokenIterator, 0)




    def t_read_operator_file(
            self,
            operator_file_name):
        """
        opens the file and reads the operators
        """
        with open(operator_file_name) as operator_file_stream:
            self.read_operator_stream(
                operator_file_stream)

    def read_operator_stream(
            self,
            operator_file_stream):
        """
        read operators from a stream
        """
        for line in operator_file_stream:
            tokens = line.split()
            operator = tokens[0]
            precidence = tokens[1]
            associativity = tokens[2]
            self.operators[operator] = (precidence, associativity)


    def __str__(self):
        """
        dump for debugging
        """
        returner = "Operators:\n"
        for operator in self.operators:
            operator_info = self.operators[operator]
            returner = returner + "{operator}   {precidence}   {associativity}\n".format(
                operator=operator,
                precidence=operator_info[0],
                associativity=operator_info[1])

        return returner


#------------#
# unit tests #
#------------#


def testread_operator_stream():
    """
    excercise the read operator functionality
    """

    test_stream = io.StringIO(u"""+  1  left
-  1  left
*  2  left
/  2  left
=  3  right
""")

    opp = Opp()

    opp.read_operator_stream(test_stream)
    print opp
