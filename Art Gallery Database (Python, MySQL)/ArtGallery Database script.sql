
CREATE TABLE artists (
	Name				VARCHAR(30),
    Birthplace			VARCHAR(30),
    Age					INT,
    Style				VARCHAR(30),
    Phone				VARCHAR(30),
    Address				VARCHAR(200),
    PRIMARY KEY (Name)
);

CREATE TABLE artwork (
	Artist				VARCHAR(30),
    Title				VARCHAR(30),
    Date_Created		VARCHAR(30),
    Date_Acquired		VARCHAR(30),
    Price				INT,
    Location			VARCHAR(30),
    TypeOfArt			VARCHAR(30),
    PRIMARY KEY(Title)
);

CREATE TABLE customers (
	Name				VARCHAR(30),
    Customer_Number		INT,
    Phone				VARCHAR(30),
    Art_Preference		VARCHAR(30),
    PRIMARY KEY (Name)
);

CREATE TABLE ArtShows (
	Contact_Phone	VARCHAR(30),
    Contact			VARCHAR(30),
    Location		VARCHAR(30),
    Date			VARCHAR(30),
    Time			VARCHAR(30),
    Artist_Name		VARCHAR(30),
    FOREIGN KEY (Artist_Name) REFERENCES artists(Name)
);

INSERT INTO artists (Name, Birthplace, Age, Style, Phone, Address)
VALUES ('Daniel', '1994-10-30', 22, 'Pop Art', 7145374649, '12345 Joe Street'),
	   ('Dave', '1990-05-22', 21, 'Pottery', 7145554444, '54321 Bob Street'),
       ('Cloud', '1995-08-01', 20, 'Sculpture', 7143332222, '10001 Tom Street'),
       ('Lebron', '1981-10-22', 19, 'Religious', 7141119999, '22222 Cob Street');
       
       
INSERT INTO artwork (Artist, Title, Date_Created, Date_Acquired, Price, Location, TypeOfArt)
VALUES ('Daniel', 'Pop Art Flowers', '2011-01-02', '2012-03-04', 1000, 'California', 'Pop Art'),
	   ('Dave', 'Pottery Trees', '2010-05-06', '2011-04-03', 2000, 'New York', 'Pottery'),
       ('Cloud', 'Sculpture Statues', '2004-11-20', '2005-12-12', 3000, 'Washington', 'Sculpture'),
       ('Lebron', 'Religious Temples', '1999-09-09', '2000-02-02', 4000, 'Ohio', 'Religious');
       
INSERT INTO customers (Name, Customer_Number, Phone, Art_Preference)
VALUES ('Iron Man', '123', '7141112222', 'Pop Art'),
	   ('Captain America', '456', '7142223333', 'Pottery'),
       ('Thor', '789', '714445555', 'Religious'),
       ('Hulk', '000', '7149998888', 'Pop Art');
       
INSERT INTO ArtShows (Artist_Name, Date, Time, Location, Contact, Contact_Phone)
VALUES ('Daniel', '2020-01-01', '10:00 AM', 'California', 'Museum', '7775554444'),
	   ('Dave', '2021-02-02', '11:00 AM', 'Texas', 'Library', '3334441111'),
       ('Cloud', '2019-03-03', '12:00 PM', 'Arizona', 'Mansion', '5557779999'),
       ('Lebron', '2018-04-04', '1:00 PM', 'Ohio', 'Staples Center', '8883335555');
       