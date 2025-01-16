def shortest_path(graph, full_capacity, current_capacity, current_city, destination, result):
    
    
    return_capacity = 0
    
    for edge in graph[current_city]:
        # next node and distance
        next_city, distance = edge
        
        if current_capacity <= (distance * 2):
            if current_city not in result:
                result.append(current_city)
            current_capacity = full_capacity
        
        if current_capacity > distance:
            if next_city == destination:
                result.append(next_city)
                print(result)
                return
        
        current_capacity -= distance
        
        ## Recursively call shortest_path to continuing travelling to the next city
        shortest_path(graph, full_capacity, current_capacity, next_city, destination, result)


if __name__ == '__main__':
    C = 0
    
    ## Ask for capacity
    while True:
        try:
            C = int(input("Please enter a positive integer for capacity in between 250 and 350: "))
            if C >= 250 and C <= 350:
                print("Capacity is valid.")
                break
            else:
                print("Capacity should be a positive integer between 250 and 350.")
        except ValueError:
            print("Provide a positive integer value between 250 and 350.")
            continue
        
    

    # Graph 1
    # graph = {
    #     'A': set([('B', 90)]),
    #     'B': set([('C', 60)]),
    #     'C': set([('D', 70)]),
    #     'D': set([('E', 65)]),
    #     'E': set([('F', 83)]),
    #     'F': set([('G', 75)]),
    #     'G': set([('H', 72)]) 
    # }

    ## Graph 2
    # graph = {
   	#     'A': set([('B', 90)]),
    #  	'B': set([('C', 94)]),
    #  	'C': set([('D', 80)]),
    #  	'D': set([('E', 65)]),
    #  	'E': set([('F', 83)]),
    #  	'F': set([('G', 75)]),
    #  	'G': set([('H', 72)]) 
	# }
    
    
    # ## Graph 3
    graph = {
        'A': set([('B', 90)]),
        'B': set([('C', 60)]),
        'C': set([('D', 80)]),
        'D': set([('E', 94)]),
        'E': set([('F', 53)]),
        'F': set([('G', 75)]),
        'G': set([('H', 72)]) 
    }
    
    result = ['A']
    shortest_path(graph, C, C, result[0], 'H', result)
