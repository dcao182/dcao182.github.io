#Daniel Cao
#This is an icecream sales report using files, lists, and dictionaries

def main(): 
    icecreamDict=readData()
    printData(icecreamDict)
    
def readData():
    icecreamDict={}
    infile=open('icecream.txt', 'r')
    for line in infile:
        fields=line.split(':')
        flavorName=fields[0]
        icecreamDict[flavorName]=createList(fields)
    infile.close()   
    return icecreamDict

def createList(fields):
    storeSales=[]
    for i in range(1,len(fields)):
        sales=float(fields[i])
        storeSales.append(sales)
    return storeSales

def printData(icecreamDict):
    numStores=0
    
    for storeSales in icecreamDict.values():
        numStores=len(storeSales)
    storeTotals=[0.0]*len(storeSales)
    
    for flavorName in sorted(icecreamDict):
        print(format(flavorName,'15s'),end='')
      
        flavorTotal=0.0
        storeSales=icecreamDict[flavorName]
        
        for i in range(len(storeSales)):
            salesData=storeSales[i]
            flavorTotal+=salesData
            storeTotals[i]+=salesData
            print(format(salesData,'10.2f'),end='')
            
        print(format(flavorTotal,'11.2f'))

    print(format(' ','15s'),end='')
    for i in range(numStores):
        print(format(storeTotals[i],'10.2f'),end='')
        
main()



##OUTPUT>>> 
##                     
##chocolate        10225.25   9025.00   9505.00   28755.25
##cookie dough      7901.25   4267.00   7056.50   19224.75
##rocky road        6700.10   5012.45   6011.00   17723.55
##strawberry        9285.15   8276.10   8705.00   26266.25
##vanilla           8580.00   7201.25   8900.00   24681.25
##                 42691.75  33781.80  40177.50
