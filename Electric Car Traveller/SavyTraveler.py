def shortest_path(graph, full_capacity, current_capacity, current_city, destination, result, previous):
    return_capacity = 0
    
    for edge in graph[current_city]:
        # next node and distance
        next_city, distance = edge
        
        # keep track of distance between current city and previous city
        previous[current_city] = distance
        
        # Traverse to next city by subtracting fuel and keep track of current capacity
        current_capacity -= distance
            
        # Keep track whether if the car can travel to the next city and return to the previous city
        # incase the next city does not have a charging station
        # current capacity - distance back to previous city
        return_capacity = current_capacity - previous[current_city]
        
        # If the car cannot travel to the next city and return to the previous city,
        # recharge at the previous city
        # Else if the car does not have enough capacity to travel to the next city,
        # Do not travel and recharge
        if return_capacity <= 0:
            if current_city not in result:
                result.append(current_city)
            current_capacity = full_capacity
            
            ## We stop and charge at the previous city
            ## We start traversing from the previous city
            next_city = current_city
        elif current_capacity <= 0:
            result.append(current_city)
            current_capacity = full_capacity
            
        ## If we reached the destination
        if current_capacity > distance:
            if next_city == destination:
                result.append(next_city)
                print(result)
                return
        
        ## Recursively call shortest_path to continuing travelling to the next city
        shortest_path(graph, full_capacity, current_capacity, next_city, destination, result, previous)



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
    graph = {
   	    'A': set([('B', 90)]),
    	'B': set([('C', 60)]),
    	'C': set([('D', 70)]),
    	'D': set([('E', 65)]),
    	'E': set([('F', 83)]),
    	'F': set([('G', 75)]),
    	'G': set([('H', 72)]) 
	}

    ## Graph 2
    #graph = {
   	    #'A': set([('B', 90)]),
     	#'B': set([('C', 94)]),
     	#'C': set([('D', 80)]),
     	#'D': set([('E', 65)]),
     	#'E': set([('F', 83)]),
     	#'F': set([('G', 75)]),
     	#'G': set([('H', 72)]) 
	 #}
    
    
    # ## Graph 3
    #graph = {
   	 #   'A': set([('B', 90)]),
     #	'B': set([('C', 60)]),
     #	'C': set([('D', 80)]),
     #	'D': set([('E', 94)]),
     #	'E': set([('F', 53)]),
     #	'F': set([('G', 75)]),
     #	'G': set([('H', 72)]) 
	 #}
    
    result = ['A']
    shortest_path(graph, C, C, result[0], 'H', result, previous = {})
