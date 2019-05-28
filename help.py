
stuff=[]
f = open("help.txt",'rt')
for i in f:
	item = i.replace('\n',"").replace('\t',"").replace(",","")
	stuff.append(item)
f.close()
stuff = sorted(stuff)
print(stuff)
f = open("output.txt",'wt')
for i in stuff:
	f.write(i+",\n")

f.write("\n")

count = 0
for i in stuff:
	f.write("case "+str(count)+": return \""+i+"\";\n")
	count+=1


f.close()