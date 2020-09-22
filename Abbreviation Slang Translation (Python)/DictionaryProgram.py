#Daniel Cao
#This program translates abbreviation slang into the actual English words

def main():
   transDict=createTrans()
   message=input('Enter a message to be translated: ')
   words=message.split()
   translation=''
   for abbrv in words:
      translation=translation+translateAbbrv(transDict,abbrv)+' '  
   printTrans(translation)
      
def createTrans():
   transDict={}
   infile=open('textabbrv.txt','r')
   for line in infile :
      parts=line.split(':')
      transDict[parts[0]]=parts[1].rstrip()
   infile.close()
   return transDict

def translateAbbrv(transDict,abbrv):
   lastChar=abbrv[len(abbrv)-1]
   if lastChar in '.?!,;:':
      abbrv=abbrv.rstrip(lastChar)
   else:
      lastChar=''
   if abbrv in transDict:
      transWord=transDict[abbrv]
   else:
      transWord=abbrv
   return transWord+lastChar

def printTrans(translation):
   print('The translated text is: ',end='')
   print(translation)

main()

##OUTPUT>>> 
##Enter a message to be translated: r u , lol ?
##The translated text is: are you , laughing out loud ? 

