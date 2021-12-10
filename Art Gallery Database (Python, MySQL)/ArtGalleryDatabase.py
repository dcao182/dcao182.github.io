import mysql.connector as mysql

db = mysql.connect(
    host = "localhost",
    user = "root",
    passwd = "jimmy182",
    database = "artgallery"
)

## Creating an instance of 'cursor' class
## which is used to execute the 'SQL' statements in 'Python'
cursor = db.cursor()

print("Hello!  Welcome to the Art gallery!")
print("Enter P to Print records from the DB")
print("Enter A to access any record based on attribute values")
print("Enter S to sort a report according to art style")
print("Enter R to produce a report showing customers who have the same art preference")
userInput = input()

## Print records from DB
if (userInput == 'P'):
    print("Which record to you want to print?")
    print("Enter artists for the artists record")
    print("Enter artwork for the artwork record")
    print("Enter artshows for the artshow record")
    input = input()

    if (input == "artists"):
        ## Artists record
        query = "SELECT * FROM artists"
        cursor.execute(query)
        artist_names = cursor.fetchall()

        for artist_name in artist_names:
            print(artist_name)

    if (input == "artwork"):
        ## artists record
        query = "SELECT * FROM artwork"
        cursor.execute(query)
        artwork_titles = cursor.fetchall()

        for title in artwork_titles:
            print(title)

    if (input == "customers"):
        ## Customer record
        query = "SELECT * FROM customers"
        cursor.execute(query)
        customer_names = cursor.fetchall()

        for customer_name in customer_names:
            print(customer_name)

## Access any record based on attribute files
if (userInput == 'A'):
    print("Which attribute are you looking for?")
    print("Enter T for types of artwork")
    print("Enter S for styles of artists")
    print("Enter P for prices of artwork")

    accessInput = input()

    if (accessInput == 'T'):
        ## displays types of artwork
        query = "SELECT Type FROM OfType"
        cursor.execute(query)
        types = cursor.fetchall()

        for artType in types:
            print(artType)

    if (accessInput == 'S'):
        ## displays styles of artists
        query = "SELECT Style FROM artists"
        cursor.execute(query)
        styles = cursor.fetchall()

        for style in styles:
            print(style)

    if (accessInput == 'P'):
        ## displays prices of artwork
        query = "SELECT Price FROM artwork"
        cursor.execute(query)
        prices = cursor.fetchall()

        for price in prices:
            print(price)

if (userInput == 'S'):
    ## Displays a report sorted by art style
    query = "SELECT * FROM artists ORDER BY Style"
    cursor.execute(query)
    artStyles = cursor.fetchall()

    for artStyle in artStyles:
        print(artStyle)

if (userInput == 'R'):
    ## Displays a list of customers with the same art preferences
    print("What art preference do you want a list of a customers for?")
    print("Enter P for Pop Art")
    print("Enter O for Pottery")
    print("Enter S for Sculpture")
    print("Enter R for Religious")
    artInput = input()

    if (artInput == 'P'):
        query = "SELECT customers.Name, customers.Phone FROM customers WHERE customers.Art_Preference = 'Pop Art'"
        cursor.execute(query)
        artPrefs = cursor.fetchall()

        for artPref in artPrefs:
            print(artPrefs)

    if (artInput == 'O'):
        query = "SELECT customers.Name, customers.Phone FROM customers WHERE customers.Art_Preference = 'Pottery'"
        cursor.execute(query)
        artPrefs = cursor.fetchall()

        for artPref in artPrefs:
            print(artPrefs)

    if (artInput == 'S'):
        query = "SELECT customers.Name, customers.Phone FROM customers WHERE customers.Art_Preference = 'Sculpture'"
        cursor.execute(query)
        artPrefs = cursor.fetchall()

        for artPref in artPrefs:
            print(artPrefs)

    if (artInput == 'R'):
        query = "SELECT customers.Name, customers.Phone FROM customers WHERE customers.Art_Preference = 'Religious'"
        cursor.execute(query)
        artPrefs = cursor.fetchall()

        for artPref in artPrefs:
            print(artPrefs)
