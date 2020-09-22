#Daniel Cao
#This program calculates and displays the loan for buying a car

class Loan:
    #initializer aka constructor
    def __init__(self,annualInterestRate=1,numYears=1,loanAmount=1,borrowerName=''):
        self.__annualInterestRate=annualInterestRate
        self.__numYears=numYears
        self.__loanAmount=loanAmount
        self.__borrowerNamer=borrowerName
        
    #accessors aka getters
    def getAnnualInterestRate(self):
        return self.__annualInterestRate

    def getNumYears(self):
        return self.__numYears

    def getLoanAmount(self):
        return self.__loanAmount

    def getBorrowerName(self):
        return self.__borrowerName
        
    #mutators aka setters
    def setAnnualInterestRate(self,annualInterestRate):
        self.__annualInterestRate=annualInterestRate

    def setNumYears(self,numYears):
        self.__numYears=numYears

    def setLoanAmount(self,loanAmount):
        self.__loanAmount=loanAmount

    def setBorrowerName(self,borrowerName):
        self.__borrowerName=borrowerName
    
    def getMonthlyPayment(self):
        monthlyInterestRate=self.__annualInterestRate/1200
        monthlyPayment=self.__loanAmount*monthlyInterestRate/(1- (1/ (1+monthlyInterestRate) ** (self.__numYears*12)))
        return monthlyPayment

    def getTotalPayment(self):
        totalPayment=self.getMonthlyPayment()*self.__numYears*12
        return totalPayment
        
def main():
    annualInterestRate=float(input('Enter yearly interest rate, for example, 7.25: '))
    numYears=float(input('Enter the number of years as an integer: '))
    loanAmount=float(input('Enter loan amount, for example, 120000.95: '))
    borrowerName=input("Enter a borrower's name: ")
    
    loan1=Loan(annualInterestRate,numYears,loanAmount,borrowerName)

    print('The loan is for',borrowerName)
    print('The monthly payment is',(format(loan1.getMonthlyPayment(),'.2f')))
    print('The total payment is',(format(loan1.getTotalPayment(),'.2f')))
    print()

    another=input('Do you want to change the loan amount? Y for yes or enter y to quit ')
    if another=='Y':
        newLoanAmnt=float(input('Enter new loan amount '))
        loan1.setLoanAmount(newLoanAmnt)
        
        print('The loan is for',borrowerName)
        print('The monthly payment is',(format(loan1.getMonthlyPayment(),'.2f')))
        print('The total payment is',(format(loan1.getTotalPayment(),'.2f')))
main()


##OUTPUT #1
##>>> 
##Enter yearly interest rate, for example, 7.25: 2.5
##Enter the number of years as an integer: 5
##Enter loan amount, for example, 120000.95: 1000
##Enter a borrower's name: John Jones
##The loan is for John Jones
##The monthly payment is 17.75
##The total payment is 1064.84
##
##Do you want to change the loan amount? Y for yes or enter y to quit Y
##Enter new loan amount 5000
##The loan is for John Jones
##The monthly payment is 88.74
##The total payment is 5324.21

##OUTPUT #2
##>>> 
##Enter yearly interest rate, for example, 7.25: 2.5
##Enter the number of years as an integer: 5
##Enter loan amount, for example, 120000.95: 1000
##Enter a borrower's name: John Jones
##The loan is for John Jones
##The monthly payment is 17.75
##The total payment is 1064.84
##
##Do you want to change the loan amount? Y for yes or enter y to quit y
