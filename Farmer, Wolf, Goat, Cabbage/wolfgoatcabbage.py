from search import *
# YOUR CODE GOES HERE
# Daniel Cao
# CPSC 481-06
# Project 1

class WolfGoatCabbage(Problem):

    def __init__(self, initial = frozenset({'C', 'F', 'G', 'W'}), goal = set()):
        """ Define goal state and initialize a problem """
        super().__init__(initial, goal)

    def goal_test(self, state):
        """ returns True if the given state is a goal state """
        return state == self.goal


    def result(self, state, action):
        """ returns the new state reached from the given state and the given action. 
        Assume that the action is valid. """
        new_state = {}

        if state == {'F', 'W', 'G', 'C'} and action == {'F', 'G'}:
            new_state = {'W', 'C'}
        if state == {'W', 'C'} and action == {'F'}:
            new_state = {'F', 'W', 'C'}


        # left path
        if state == {'F', 'W', 'C'} and action == {'F', 'W'}:
            new_state = {'C'}
        if state == {'C'} and action == {'F', 'G'}:
            new_state = {'F', 'G', 'C'}
        if state == {'F', 'G', 'C'} and action == {'F', 'C'}:
            new_state = {'G'}

        # right path
        if state == {'F', 'W', 'C'} and action == {'F', 'C'}:
            new_state = {'W'}
        if state == {'W'} and action == {'F', 'G'}:
            new_state = {'F', 'W', 'G'}
        if state == {'F', 'W', 'G'} and action == {'F', 'W'}:
            new_state = {'G'}

        # last path
        if state == {'G'} and action == {'F'}:
            new_state = {'F', 'G'}
        if state == {'F', 'G'} and action == {'F', 'G'}:
            new_state = {}
        
        # last path backward
        if state == {'W', 'C'} and action == {'F', 'G'}:
            new_state = {'F', 'W', 'G', 'C'}
        if state == {'F', 'W', 'G', 'C'} and action == {'F', 'G'}:
            new_state == {'W', 'C'}
        if state == {'W', 'C'} and action == {'F'}:
            new_state = {'F', 'W', 'C'}
        
        
        # right path right backward
        if state == {'C'} and action == {'F', 'G'}:
            new_state = {'F', 'G', 'C'}
        if state == {'F', 'G', 'C'} and action == {'F', 'C'}:
            new_state = {'G'}
        if state == {'G'} and action == {'F'}:
            new_state = {'F', 'G'}


        # left path right backward
        if state == {'F', 'W', 'C'} and action == {'F', 'C'}:
            new_state = {'W'}
        if state == {'W'} and action == {'F', 'G'}:
            new_state = {'F', 'W', 'G'}
        if state == {'F', 'W', 'G'} and action == {'F', 'W'}:
            new_state = {'G'}


        # top path right backward
        if state == {'G'} and action == {'F'}:
            new_state = {'F', 'G'}
        if state == {'F', 'G'} and action == {'F', 'G'}:
            new_state == {}

        # top path right down
        if state == {} and action == {'F', 'G'}:
            new_state == {'F', 'G'}
        if state == {'F', 'G'} and action == {'F'}:
            new_state == {'G'}

        # right path right down
        if state == {'G'} and action == {'F', 'C'}:
            new_state == {'F', 'G', 'C'}
        if state == {'F', 'G', 'C'} and action == {'F', 'G'}:
            new_state == {'C'}
        if state == {'C'} and action == {'F', 'W'}:
            new_state == {'F', 'W', 'C'}

        #left path right
        if state == {'G'} and action == {'F', 'W'}:
            new_state == {'F', 'W', 'G'}
        if state == {'F', 'W', 'G'} and action == {'F', 'G'}:
            new_state == {'W'}
        if state == {'W'} and action == {'F', 'C'}:
            new_state == {'F', 'W', 'C'}
        if state == {'F', 'W', 'C'} and action == {'F'}:
            new_state == {'W', 'C'}
        
        # bottom path right down
        if state == {'F', 'W', 'C'} and action == {'F'}:
            new_state == {'W', 'C'}



        if state == {'G'} and action == {'F', 'W'}:
            new_state = {'F', 'W', 'G'}
        if state == {'C'} and action == {'F', 'G'}:
            new_state = {'F', 'G', 'C'}
        if state == {'W'} and action == {'F', 'C'}:
            new_state = {'F', 'W', 'C'}
        if state == {'W'} and action == {'F', 'G'}:
            new_state = {'F', 'W', 'G'}
        if state == {'C'} and action == {'F', 'W'}:
            new_state = {'F', 'W', 'C'}
        if state == {'F', 'G', 'C'} and action == {'F', 'G'}:
            new_state = {'C'}
        if state == {'F', 'W', 'G'} and action == {'F', 'G'}:
            new_state = {'W'}
        if state == {'F', 'W', 'C'} and action == {'F'}:
            new_state = {'W', 'C'}
        if state == {'F', 'W', 'G'} and action == {'F'}:
            new_state = {'W', 'G'}
        if state == {'F', 'G', 'C'} and action == {'F'}:
            new_state = {'G', 'C'}
        if state == {'F', 'G'} and action == {'F'}:
            new_state = {'G'}
        if state == {'w', 'G'} and action == {'F'}:
            new_state == {'F', 'W', 'G'}
        if state == {'G', 'C'} and action == {'F'}:
            new_state == {'F', 'C', 'C'}
        if state == {'G'} and action == {'F', 'C'}:
            new_state = {'F', 'C', 'G'}
        if state == {'W'} and action == {'F'}:
            new_state = {'F', 'W'}
        if state == {'C'} and action == {'F'}:
            new_state = {'F', 'C'}
        if state == {'F'} and action == {'F'}:
            new_state = {}
        if state == {} and action == {'F', 'G'}:
            new_state == {'F', 'G'}
        if state == {} and action == {'F'}:
            new_state = {'F'}

        return frozenset(new_state)


    def actions(self, state):
        """ returns a list of valid actions in the given state """

        possible_actions = []

        if state == {'F', 'C', 'G', 'W'}:
            possible_actions.append({'F', 'G'})
        if state == {'W', 'C'}:
            possible_actions.append({'F'})
            possible_actions.append({'F', 'G'})
        if state == {'G'}:
            possible_actions.append({'F'})
            possible_actions.append({'F', 'C'})
            possible_actions.append({'F', 'W'})
        if state == {'F', 'W', 'C'}:
            possible_actions.append({'F'})
            possible_actions.append({'F', 'W'})
            possible_actions.append({'F', 'C'})
        if state == {'C'}:
            possible_actions.append({'F', 'W'})
            possible_actions.append({'F', 'G'})
        if state == ('W'):
            possible_actions.append({'F', 'G'})
            possible_actions.append({'F', 'C'})
        if state == {'F', 'G', 'C'}:
            possible_actions.append({'F', 'G'})
            possible_actions.append({'F', 'C'})
        if state == {'F', 'W', 'G'}:
            possible_actions.append({'F', 'W'})
            possible_actions.append({'F', 'G'})
        if state == {'F', 'G'}:
            possible_actions.append({'F'})
            possible_actions.append({'F', 'G'})
        if state == {'F'}:
            possible_actions.append({'F'})
        if state == {}:
            possible_actions.append({'F'})
            possible_actions.append({'F', 'G'})

        return possible_actions


if __name__ == '__main__':
    wgc = WolfGoatCabbage()
    solution = depth_first_graph_search(wgc).solution()
    print(solution)
    solution = breadth_first_graph_search(wgc).solution()
    print(solution)


# if __name__ == '__main__':
#     wgc = WolfGoatCabbage()
#     print("initial: ")
#     print(wgc.initial)
#     print("goal: ")
#     print(wgc.goal)
#     print("goal_test: ")
#     print(wgc.goal_test(frozenset({})))
#     print("result: ")
#     print(wgc.result(frozenset({'F','C','W','G'}),frozenset({'F','G'})))
#     print("actions: ")
#     print(wgc.actions(frozenset({'F','W','G','C'})))
#     print("DFS solution:")
#     print(depth_first_graph_search(wgc).solution())
#     print("BFS solution:")
#     print(breadth_first_graph_search(wgc).solution())