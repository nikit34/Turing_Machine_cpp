import sys

class BadSyntax: pass
class NothingDo: pass

class Machine:
    def __init__(self, filename):
        f = open(filename, 'r')
        self.program = []
        while True:
            line = f.readline()
            if not line: break
            tuple = line.strip().split(',')
            if len(tuple) > 4 or len(tuple[1]) > 1 or len(tuple[2]) > 1:
                raise BadSyntax()
            self.program.append(tuple)

    def init(self, tape, pos, state):
        self.tape = list(tape)
        self.pos = pos
        self.state = state

    def step(self):
        for tuple in self.program:
            if tuple[0] == self.state and tuple[1] == self.tape[self.pos]:
                self.state = tuple[3]
                if tuple[2] == "<": self.pos -= 1
                elif tuple[2] == ">": self.pos += 1
                elif tuple[2] == "=": pass
                elif tuple[2] == "#": return False
                else: self.tape[self.pos] = tuple[2]
                if len(self.tape) <= self.pos:
                    self.tape.append(' ')
                return True
        raise NothingDo()

    def run(self):
        while self.step(): pass

    def trace(self):
        while self.step():
            print(''.join(self.tape))

if len(sys.argv) != 2:
    print ('Usage: machine program.tu')
    sys.exit(1)

try:
    machine = Machine(sys.argv[1])
except SyntaxError:
    print ('Syntax error')
    sys.exit(1)

tape = sys.stdin.readline().rstrip('\n')
posstr = sys.stdin.readline()
pos = posstr.find('^')

machine.init(tape + " ", pos, '00')

try:
    machine.run()
    print(''.join(machine.tape))
except NothingDo:
    print('Nothing to do')
