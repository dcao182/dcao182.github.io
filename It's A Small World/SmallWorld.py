if __name__ == '__main__':
    CAST = []
    n = 1
    current_cast = []
    
    with open("C:\SW_data_1.txt") as f:
    
        lines = f.readlines()
        ## Remove newlines from each line
        lines = [x.strip() for x in lines]
        
        for line in lines:
            ## If a blank line is read
            ## We have reached the end of one cast
            ## Append the finished cast to CAST list
            ## Increment n by 1
            ## Reset current_cast list to an empty list for the next cast
            if line == '':
                CAST.append(current_cast)
                ## We initialize n to the number of lists in CAST
                n += 1
                current_cast = []
            else:
                current_cast.append(str(line))
        ## Add the last list of actors from text file to CAST        
        CAST.append(current_cast)
        
    ## Used to see value n is
    print("n is " + str(n))


    ## Variables
    ## Keep track of shortest number of connections
    shortest_connection = float('inf')
    ## Track number of connections
    num_connections = 0
    ## Variable to store actor name connection
    actor_match = ''
    ## Store index of CAST list with connection
    temp_cast_index = 0
    

    ## Begin with CAST[0] and CAST[1]
    for name1 in CAST[0]:
        if name1 in CAST[1]:
            ## If there is a connection between CAST[0] and CAST[1]
            ## Increment num_connections to keep connection count
            ## Store the string aka actor name in common
            num_connections += 1
            actor_match = name1

            ## Update to keep the number of shortest connections
            if num_connections < shortest_connection:
                shortest_connection = num_connections
            ## Only necessary to find one connection, we break out of the loop
            break
    

    
    ## If no shortest connection between CAST[0] and CAST[1], we check another cast with a string in common with CAST[0]
    if num_connections == 0:       
        for name1 in CAST[0]:
            for i in range(2, n):
                if name1 in CAST[i]:
                    ## If there is a connection in CAST[0] and another cast
                    ## Store the index of the list in CAST to use for output later
                    ## Increment num_connections to keep connection count
                    temp_cast_index = i
                    num_connections += 1
                
                ## If we found a connection between CAST[0] and another cast    
                if temp_cast_index != 0:
                    ## We check the other cast has a string in common with CAST[1]
                    for name2 in CAST[temp_cast_index]:
                        if name2 in CAST[1]:
                            ## Store the cast list that has a connection to CAST[0] and CAST[1]
                            cast_match = CAST[temp_cast_index]
                            ## Increment num_connections to keep connection count
                            num_connections += 1
                            
                            ## Update to keep the number of shortest connections
                            if num_connections < shortest_connection:
                                shortest_connection = num_connections
                            break
                    ## Only necessary to find at most 2 connections, we break out of the loop
                    if num_connections >= 2:
                        break
    
    
    ## Output
    if shortest_connection == 0 or shortest_connection > 2:
        print("shortest connection > 2 or no connection")
    elif shortest_connection == 2:
        print("shortest connection: " + str(shortest_connection) + ", cast: " + str(cast_match))
    else:
        print("shortest connection = " + str(shortest_connection) + ", actor = " + ''.join(actor_match))       