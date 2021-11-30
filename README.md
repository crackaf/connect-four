The code comments are helpful.

minimax implmented from:https://www.javatpoint.com/ai-alpha-beta-pruning
heuristic/evaluation function: https://stackoverflow.com/questions/10985000/how-should-i-design-a-good-evaluation-function-for-connect-4

The struct is made for minimax to return two values. The score and the col for which that score is obtained. The minimax function works on score but we need col also so we keeo track of that in the struct.

The scoring idea is taken from internet and I have provided link for that. Basically I'm looking the whole board and making the arry of 4 stones. After that I'm checking those stones, e.g Can I make the 4 stones in this state? Or Can the 
opponent make the 4 stones in this state. Checking these types of few things and score it accordingly.

More abstract code: https://github.com/crackaf/connect4
